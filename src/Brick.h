#pragma once
#include "raylib.h"
#include "GameObject.h"

class Brick : public GameObject {
public:
    Brick(const std::string& name, World* world, Vector2 position, Color color)
        : GameObject(name, world), color(color) {
        pos = position;
        size = {50, 20};
    }

    virtual ~Brick() = default;

    void Update(float dt) override;
    void Draw() override;

    Color GetColor() { return color; }
    void SetColor(Color newColor) { color = newColor; }

private:
    Color color;
    float destroyDelay = 0.0f;
};