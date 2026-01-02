
#define _CRT_SECURE_NO_WARNINGS 

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> 
#include <ctime>   
#include <iomanip>

//引入 Windows API 和 多媒體標頭檔
#include <windows.h> 
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib") // 告訴編譯器要連結音效庫

#include "QuizLib.h" 

using namespace std;

//設定文字顏色的函式
void SetColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int main() {
    vector<Word> vocabList;
    srand((unsigned int)time(0));

    // 讀取資料
    loadData(vocabList);

    if (vocabList.empty()) {
        SetColor(12); // 紅色警告
        cout << "題庫是空的，請先建立 database.txt 檔案！" << endl;
        SetColor(7);  // 恢復白色
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

        // 顯示題目
        SetColor(11); // 亮青色
        cout << "\n[第 " << i << "/" << totalQuestions << " 題] ";
        SetColor(7); // 恢復白色
        cout << "請問 [" << currentWord.english << "] 的中文是？: ";
        cin >> userAns;

        if (userAns == "exit") {
            totalQuestions = i - 1;
            break;
        }

        if (checkAnswer(userAns, currentWord.chinese)) {
            //答對用綠色
            SetColor(10);
            cout << " [O] 答對了！" << endl;

            //播放系統音效
            PlaySound(TEXT("SystemAsterisk"), NULL, SND_ALIAS | SND_ASYNC);

            SetColor(7); // 恢復白色
            score++;
        }
        else {
            // 答錯用紅色
            SetColor(12);
            cout << " [X] 答錯了！正確答案是: " << currentWord.chinese << endl;

            //播放系統音效
            PlaySound(TEXT("SystemHand"), NULL, SND_ALIAS | SND_ASYNC);

            cout << "[系統] 已加入錯題本..." << endl;
            SetColor(7); // 恢復白色
            saveMistake(currentWord);
        }
    }

    // 結算畫面
    cout << "\n==========================" << endl;
    cout << "測驗結束！" << endl;

    if (totalQuestions > 0) {
        double accuracy = (double)score / totalQuestions * 100.0;

        // 使用 math.h 的 round 
        cout << "總共練習: " << totalQuestions << " 題" << endl;
        cout << "答對題數: " << score << " 題" << endl;
        cout << "正確率  : " << fixed << setprecision(1) << accuracy << "%" << endl;

        if (accuracy == 100) {
            SetColor(14); // 金黃色
            cout << "評語: 太神啦！全對！" << endl;
        }
        else if (accuracy >= 60) {
            SetColor(10); // 綠色
            cout << "評語: 及格了，再接再厲！" << endl;
        }
        else {
            SetColor(12); // 紅色
            cout << "評語: 加油，記得去複習錯題本喔！" << endl;
        }
        SetColor(7);
    }

    // 確保程式結束前音效播完
    Sleep(500);
    return 0;
}