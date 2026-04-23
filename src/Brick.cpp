#include "Brick.h"
#include "Smoothing.h"

void Brick::Update(float dt) {
    if (IsDestroyed()) {
        destroyDelay += dt;
    }
}

void Brick::Draw() {
    if (!IsDestroyed()) {
        DrawRectangleV(pos, size, color);
    }
}