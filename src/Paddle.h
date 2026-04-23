#pragma once
#include "raylib.h"
#include "GameObject.h"

class Paddle : public GameObject {
public:
    Paddle(World* world)
        : GameObject("paddle", world), velocity(0.0f) {
        size = {80, 20};
    }

    virtual ~Paddle() = default;

    void Update(float dt) override;
    void Draw() override;

    inline float GetVelocity() { return velocity; }
    inline void SetVelocity(float v) { velocity = v; }

private:
    float velocity;
    static constexpr float PADDLE_SPEED = 500.0f;

    void HandleInput();
};