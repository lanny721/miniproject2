#include "ScoreBoardScene.hpp"
#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <fstream>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "Scene/StartScene.h"
#include "Scene/ScoreBoardScene.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/Slider.hpp"

// TODO HACKATHON-2 (1/3): You can imitate the 2 files: 'StartScene.hpp', 'StartScene.cpp' to implement your SettingsScene.
void ScoreboardScene::Initialize() {
    UIGroup = new Group(); // Initialize UIGroup
    AddNewControlObject(UIGroup);

    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton *btn;
    // std::vector<std::pair<std::string, int>> scores;
    curPage=1;

    // getScoreboard(scores);

    //stable label
    AddNewObject(new Engine::Label("Score Board", "pirulen.ttf", 60, halfW - 80, halfH / 3 -80 ,255, 255, 255, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("name", "pirulen.ttf", 38, halfW - 350, halfH / 3 , 255, 255, 255, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("score", "pirulen.ttf", 38, halfW + 350, halfH / 3 , 255, 255, 255, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 150 , halfH * 3 / 2 + 100, 300, 75);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 36, halfW + 5, halfH * 3 / 2 +140, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 720, halfH * 3 / 2 + 100, 300, 75);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::PrevOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("<- Prev", "pirulen.ttf", 36, halfW - 575, halfH * 3 / 2 +140, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 430, halfH * 3 / 2 + 100, 300, 75);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::NextOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Next ->", "pirulen.ttf", 36, halfW + 600, halfH * 3 / 2 +140, 0, 0, 0, 255, 0.5, 0.5));

    UpdateScoreboardDisplay();

}
void ScoreboardScene::Terminate() {
    printf("Terminate ScoreboardScene\n");

    scoreLabels.clear();
    printf("scoreLabels clear\n");

    IScene::Terminate();
    printf("IScene Terminate\n");

    UIGroup = nullptr;
    printf("Terminate ScoreboardScene end\n");
}
void ScoreboardScene::getScoreboard(std::vector<std::pair<std::string, int>>& scores) {
    std::ifstream file("C:/2025_I2P2_TowerDefense-main/Resource/scoreboard.txt");
    std::string name;
    int score;

    if(!file.is_open()) {
        printf( "Error opening scoreboard.txt!!!\n");
        return;
    }
    while (file >> name >> score) {
        scores.push_back({name, score});
    }
    file.close();

    if(scores.size()<=7)
        totalPage=1;
    else if(scores.size()%7==0)
        totalPage=scores.size()/7;
    else
        totalPage=scores.size()/7+1;
}
void ScoreboardScene::UpdateScoreboardDisplay(){
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    std::vector<std::pair<std::string, int>> scores;
    getScoreboard(scores);

    for (auto* label : scoreLabels) {
        UIGroup->RemoveObject(label->GetObjectIterator());
    }
    scoreLabels.clear();

    std::string pageText = "(" + std::to_string(curPage) + "/" + std::to_string(totalPage) + ")";
    Engine::Label* pageLabel = new Engine::Label(pageText, "pirulen.ttf", 45, halfW + 325, halfH / 3 - 80, 255, 255, 255, 255, 0.5, 0.5);
    AddNewObject(pageLabel);
    scoreLabels.push_back(pageLabel);

    int startIndex = (curPage - 1) * 7;
    int endIndex = std::min(startIndex + 7, static_cast<int>(scores.size()));

    for(int i=startIndex;i<endIndex;i++){
        //name
        Engine::Label* nameLabel = new Engine::Label(scores[i].first, "pirulen.ttf", 48, halfW - 350, halfH / 3 + 80 + 75 * (i - startIndex), 255, 255, 255, 255, 0.5, 0.5);
        AddNewObject(nameLabel);
        scoreLabels.push_back(nameLabel);
        //score
        Engine::Label* scoreLabel = new Engine::Label(std::to_string(scores[i].second), "pirulen.ttf", 48,
            halfW + 350, halfH / 3 + 80 + 75 * (i - startIndex), 255, 255, 255, 255, 0.5, 0.5);
        AddNewObject(scoreLabel);
        scoreLabels.push_back(scoreLabel);
    }
    //最多七個每個height +75
}
void ScoreboardScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("start");
}
void ScoreboardScene::PrevOnClick(int stage) {
    if(curPage==1)
        return;
    else{
        --curPage;
        UpdateScoreboardDisplay();
    }
    
    // Engine::GameEngine::GetInstance().ChangeScene("start");
}
void ScoreboardScene::NextOnClick(int stage) {
    if(curPage==totalPage)
        return;
    else{
        ++curPage;
        UpdateScoreboardDisplay();
    }
    // Engine::GameEngine::GetInstance().ChangeScene("start");
}