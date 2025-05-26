#include <functional>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "PlayScene.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "WinScene.hpp"

void WinScene::Initialize() {
    ticks = 0;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH, 0, 0, 0.5, 0.5));
    AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW, halfH / 4 - 10, 255, 255, 255, 255, 0.5, 0.5));
    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 -5 , 400, 100);
    btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4 + 45, 0, 0, 0, 255, 0.5, 0.5));
    bgmId = AudioHelper::PlayAudio("win.wav");

    //
    nameEntered=0;

    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream timeStr;
    timeStr << std::put_time(&tm, "%Y-%m-%d");

    scores.clear();
    std::ifstream file("C:/miniproject2/2025_I2P2_TowerDefense-main/Resource/scoreboard.txt");
    std::string name,timestamp;
    int score;
    while (file >> name >> score >> timestamp) {
        scores.push_back({name, score,timestamp});
    }
    file.close();

    currentInput = "Player" + std::to_string(scores.size()+1);
    inputLabel = new Engine::Label("Name: " + currentInput, "pirulen.ttf", 32, 
        halfW, halfH /2 , 255, 255, 255, 255, 0.5, 0.5);
    AddNewObject(inputLabel);

    // int newScore = dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"))->GetMoney();
    // scores.push_back({currentInput, newScore,timeStr.str()});

    // std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) { return std::get<1>(a) > std::get<1>(b); });
    // std::ofstream fout("C:/miniproject2/2025_I2P2_TowerDefense-main/Resource/scoreboard.txt");
    // for (const auto& score : scores) {
    //     fout << std::get<0>(score) << " " << std::get<1>(score) <<" " << std::get<2>(score) << "\n";
    // }
    // fout.close();

    //std::string scoreText = newPlayerName + " Score: " + std::to_string(newScore);
    //AddNewObject(new Engine::Label(scoreText, "pirulen.ttf", 32, halfW, halfH / 2, 255, 255, 255, 255, 0.5, 0.5));
}
void WinScene::Terminate() {
    IScene::Terminate();
    AudioHelper::StopBGM(bgmId);
}
void WinScene::Update(float deltaTime) {
    ticks += deltaTime;
    if (ticks > 4 && ticks < 100 &&
        dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
        ticks = 100;
        bgmId = AudioHelper::PlayBGM("happy.ogg");
    }
}
void WinScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

void WinScene::OnKeyDown(int key){
    if (nameEntered) return; 

    if (key == ALLEGRO_KEY_BACKSPACE) {
        if(!currentInput.empty()){
            currentInput.pop_back(); 
            inputLabel->Text = "name: " + currentInput;
        } else {
            return;
        }
    } else if (key == ALLEGRO_KEY_ENTER) {
        nameEntered = true; // 確認名字已經輸入完成
        inputLabel->Text = "name: " + currentInput;
        inputNewScore();
    } else if(key==ALLEGRO_KEY_SPACE){
        return;
    } else if (currentInput.size() < 20) { // 限制名字長度
        if (key >= ALLEGRO_KEY_PAD_0 && key <= ALLEGRO_KEY_PAD_9) {
            currentInput += ('0' + (key - ALLEGRO_KEY_PAD_0));
        } else {
            currentInput += al_keycode_to_name(key);
        } 
    }
    inputLabel->Text = "name: " + currentInput;
}

void WinScene::inputNewScore(){
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    if(nameEntered){
        AddNewObject(new Engine::Label("Name Entered!", "pirulen.ttf", 48, halfW, halfH * 7 / 4 -50 , 255, 255, 255, 255, 0.5, 0.5));
        auto now = std::time(nullptr);
        auto tm = *std::localtime(&now);
        std::ostringstream timeStr;
        timeStr << std::put_time(&tm, "%Y-%m-%d");

        int newScore = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"))->GetMoney();
        scores.push_back({currentInput, newScore, timeStr.str()});

        std::sort(scores.begin(), scores.end(), 
            [](const auto& a, const auto& b) { return std::get<1>(a) > std::get<1>(b); });
        
        std::ofstream fout("C:/miniproject2/2025_I2P2_TowerDefense-main/Resource/scoreboard.txt");
        for (const auto& score : scores) {
            fout << std::get<0>(score) << " " << std::get<1>(score) << " " << std::get<2>(score) << "\n";
        }
        fout.close();
    }
}