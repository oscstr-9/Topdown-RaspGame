#pragma once
#include "render/window.h"

class UI
{
private:
    int points = 0;
    int highscore = 0;
    bool isDead = false;
    float currentTime = glfwGetTime();
    bool blinkResetMsg = false;

public:
    UI();
    ~UI();
    void RenderUI();
    void SetIsDead(bool isDeadIn);
    void IncreaseScore();
    void SaveScore();
    void LoadScore();
    void GameOverScreen();
};
