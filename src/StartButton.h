#pragma once
#include "raylib.h"
#include "GameObject.h"

class StartButton : public GameObject {
public:
    StartButton(World* world)
        : GameObject("startButton", world), isPressed(false), scaleTimer(0.0f) {
        pos = {GetScreenWidth() / 2.0f - 50, GetScreenHeight() / 2.0f - 20};
        size = {100, 40};
    }

    virtual ~StartButton() = default;

    void Update(float dt) override;
    void Draw() override;

    inline bool IsPressed() { return isPressed; }
    void Reset() { isPressed = false; scaleTimer = 0.0f; }

private:
    bool isPressed;
    float scaleTimer;
    static constexpr float PRESS_ANIMATION_TIME = 0.3f;

    bool IsMouseOver();
    void HandleClick();
};
