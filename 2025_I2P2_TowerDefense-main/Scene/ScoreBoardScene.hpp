#ifndef SCOREBOARDSCENE_HPP
#define SCOREBOARDSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <memory>

#include "Engine/IScene.hpp"
#include "UI/Component/Label.hpp"

class ScoreboardScene final : public Engine::IScene {
private:
    Group* UIGroup = nullptr;

    int curPage=1;
    int totalPage;
    std::vector<Engine::Label*> scoreLabels;
    void UpdateScoreboardDisplay();
public:
    explicit ScoreboardScene() = default;
    void Initialize() override;
    void Terminate() override;
    void NextOnClick(int stage);
    void PrevOnClick(int stage);
    void BackOnClick(int stage);

    void getScoreboard(std::vector<std::pair<std::string, int>>& scores);
};

#endif   // SCOREBOARDSCENE_HPP