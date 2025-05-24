#include <functional>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <fstream>

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
    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
    bgmId = AudioHelper::PlayAudio("win.wav");

    //
    std::vector<std::pair<std::string, int>> scores;
    std::ifstream file("C:/2025_I2P2_TowerDefense-main/Resource/scoreboard.txt");
    std::string name;
    int score;
    while (file >> name >> score) {
        scores.push_back({name, score});
    }
    file.close();

    std::string newPlayerName = "Player" + std::to_string(scores.size()+1);
    int newScore = dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"))->GetMoney();
    scores.push_back({newPlayerName, newScore});

    std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
    std::ofstream fout("C:/2025_I2P2_TowerDefense-main/Resource/scoreboard.txt");
    for (const auto& score : scores) {
        fout << score.first << " " << score.second << "\n";
    }
    fout.close();

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
