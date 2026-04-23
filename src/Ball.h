#pragma once
#include "raylib.h"
#include "GameObject.h"

class Ball : public GameObject {
public:
    Ball(World* world)
        : GameObject("ball", world), velocity({0, 0}), size({10.0f, 10.0f}), isActive(false) {}

    virtual ~Ball() = default;

    void Update(float dt) override;
    void Draw() override;

    inline Vector2 GetVelocity() { return velocity; }
    inline void SetVelocity(float vx, float vy) { velocity = {vx, vy}; }
    inline bool IsActive() { return isActive; }
    inline void SetActive(bool active) { isActive = active; }
    inline Vector2 GetSize() { return size; }

    // Collision helpers
    bool CollidingWith(GameObject* other);

private:
    Vector2 previousPos;
    Vector2 velocity;
    Vector2 size;
    bool isActive;

    void CheckCollisions();
    void HandleScreenBounds();
};