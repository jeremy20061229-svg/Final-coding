// 檔案名稱：QuizLib.cpp
#define _CRT_SECURE_NO_WARNINGS 

#include "QuizLib.h" // 匯入剛剛寫好的標頭檔
#include <iostream>
#include <cstdio>
#include <sstream>

using namespace std;

// 這裡放函式的具體實作內容

void loadData(vector<Word>& list) {
    FILE* fp = fopen("database.txt", "r");
    if (fp == NULL) {
        cout << "[系統] 找不到題庫，請確認目錄下是否有 database.txt" << endl;
        return;
    }
    Word tmp;
    while (fscanf(fp, "%s %s", tmp.english, tmp.chinese) != EOF) {
        list.push_back(tmp);
    }
    fclose(fp);
    cout << "[系統] 成功載入 " << list.size() << " 個單字。" << endl;
}

void saveMistake(const Word& w) {
    FILE* fp = fopen("mistakes.txt", "a");
    if (fp == NULL) {
        cout << "[錯誤] 無法寫入錯題本。" << endl;
        return;
    }
    fprintf(fp, "%s %s\n", w.english, w.chinese);
    fclose(fp);
}

bool checkAnswer(string userAns, string correctAnsStr) {
    stringstream ss(correctAnsStr);
    string segment;

    while (getline(ss, segment, '/')) {
        if (userAns == segment) {
            return true;
        }
    }
    return false;
}