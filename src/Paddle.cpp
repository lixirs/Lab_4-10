#include "Paddle.h"
#include "Smoothing.h"

void Paddle::Update(float dt) {
    HandleInput();
    
    pos.x += velocity * dt;

    // Clamp paddle to screen bounds
    int width = GetScreenWidth();
    if (pos.x < 0) pos.x = 0;
    if (pos.x + size.x > width) pos.x = width - size.x;
}

void Paddle::Draw() {
    DrawRectangleV(pos, size, WHITE);
}

void Paddle::HandleInput() {
    velocity = 0.0f;
    
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        velocity = -PADDLE_SPEED;
    } else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        velocity = PADDLE_SPEED;
    }
}