// 檔案名稱：QuizLib.h
#ifndef QUIZLIB_H  // 避免重複定義的保護機制
#define QUIZLIB_H

#include <vector>
#include <string>

using namespace std;

// 1. 定義結構
struct Word {
    char english[50];
    char chinese[50];
};

// 2. 宣告函式 (只寫名字和參數，不寫內容)
void loadData(vector<Word>& list);
void saveMistake(const Word& w);
bool checkAnswer(string userAns, string correctAnsStr);

#endif