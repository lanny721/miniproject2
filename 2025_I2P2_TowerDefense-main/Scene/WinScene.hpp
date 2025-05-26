#ifndef WINSCENE_HPP
#define WINSCENE_HPP
#include "Engine/IScene.hpp"
#include <allegro5/allegro_audio.h>

class WinScene final : public Engine::IScene {
private:
    float ticks;
    ALLEGRO_SAMPLE_ID bgmId;
    std::string currentInput;  // typing name
    bool nameEntered=0;        // 確認名字是否已確定
    Engine::Label* inputLabel; // 顯示當前輸入的 player name Label
    std::vector<std::tuple<std::string, int, std::string>> scores;

public:
    explicit WinScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void BackOnClick(int stage);
    void OnKeyDown(int keyCode);
    void inputNewScore();
};

#endif   // WINSCENE_HPP
