// 檔案名稱：main.cpp
#define _CRT_SECURE_NO_WARNINGS 

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> 
#include <ctime>   
#include <iomanip>
#include "QuizLib.h" // [關鍵] 匯入你自己的 Library

using namespace std;

int main() {
    vector<Word> vocabList;
    srand((unsigned int)time(0));

    // 直接呼叫 Library 裡的函式
    loadData(vocabList);

    if (vocabList.empty()) {
        cout << "題庫是空的，請先建立 database.txt 檔案！" << endl;
        return 0;
    }

    int totalQuestions = 0;
    cout << "目前題庫共有 " << vocabList.size() << " 個單字。" << endl;
    cout << "請問今天想挑戰幾題？: ";
    cin >> totalQuestions;

    if (totalQuestions <= 0) {
        cout << "至少要練習 1 題喔！程式結束。" << endl;
        return 0;
    }

    int score = 0;
    string userAns;
    int lastIndex = -1;

    cout << "=== 單字測驗開始 (輸入 exit 可中途結束) ===" << endl;
    cout << "註：若有多種翻譯，輸入其中一種即可" << endl;

    for (int i = 1; i <= totalQuestions; i++) {
        int index;

        if (vocabList.size() > 1) {
            do {
                index = rand() % vocabList.size();
            } while (index == lastIndex);
        }
        else {
            index = 0;
        }

        lastIndex = index;
        Word currentWord = vocabList[index];

        cout << "\n[第 " << i << "/" << totalQuestions << " 題] 請問 [" << currentWord.english << "] 的中文是？: ";
        cin >> userAns;

        if (userAns == "exit") {
            totalQuestions = i - 1;
            break;
        }

        // 使用 Library 裡的檢查函式
        if (checkAnswer(userAns, currentWord.chinese)) {
            cout << " [O] 答對了！" << endl;
            score++;
        }
        else {
            cout << " [X] 答錯了！正確答案是: " << currentWord.chinese << endl;
            cout << "[系統] 已加入錯題本..." << endl;
            saveMistake(currentWord); // 使用 Library 裡的紀錄函式
        }
    }

    cout << "\n==========================" << endl;
    cout << "測驗結束！" << endl;

    if (totalQuestions > 0) {
        double accuracy = (double)score / totalQuestions * 100.0;
        cout << "總共練習: " << totalQuestions << " 題" << endl;
        cout << "答對題數: " << score << " 題" << endl;
        cout << "正確率  : " << fixed << setprecision(1) << accuracy << "%" << endl;

        if (accuracy == 100) cout << "評語: 太神啦！全對！" << endl;
        else if (accuracy >= 80) cout << "評語: 很棒喔，繼續保持！" << endl;
        else if (accuracy >= 60) cout << "評語: 及格了，再接再厲！" << endl;
        else cout << "評語: 加油，記得去複習錯題本喔！" << endl;
    }
    else {
        cout << "你沒有練習任何題目。" << endl;
    }
    cout << "==========================" << endl;

    return 0;
}