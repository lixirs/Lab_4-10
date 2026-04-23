#pragma once
#include "Game.h"

class Breakout : public Game {
public:
    Breakout() : gameStarted(false) {}
    virtual ~Breakout() = default;

    void Init() override;
    void Update(float dt) override;
    void Draw() override;
    void Deinit() override;

private:
    bool isFirstInit;
    bool gameStarted;
    static constexpr int SCREEN_WIDTH = 800;
    static constexpr int SCREEN_HEIGHT = 600;
    static constexpr int BRICK_ROWS = 5;
    static constexpr int BRICKS_PER_ROW = 10;

    void CreateBricks();
    void CheckGameOver();
    void ResetGame();
};