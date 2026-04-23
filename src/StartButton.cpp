#include "StartButton.h"
#include "Smoothing.h"

void StartButton::Update(float dt) {
    if (IsDestroyed()) return;

    if (!isPressed) {
        HandleClick();
    } else {
        scaleTimer += dt;
        if (scaleTimer >= PRESS_ANIMATION_TIME) {
            DestroyObject();
        }
    }
}

void StartButton::Draw() {
    if (IsDestroyed()) return;

    float scale = 1.0f;
    if (isPressed) {
        float progress = scaleTimer / PRESS_ANIMATION_TIME;
        scale = Smoothing::Lerp(1.0f, 0.0f, Smoothing::EaseIn(progress));
    }

    Vector2 scaledSize = {size.x * scale, size.y * scale};
    Vector2 scaledPos = {
        pos.x + (size.x - scaledSize.x) / 2.0f,
        pos.y + (size.y - scaledSize.y) / 2.0f
    };

    Color buttonColor = IsMouseOver() ? LIGHTGRAY : WHITE;
    DrawRectangleV(scaledPos, scaledSize, buttonColor);

    const char* text = "START";
    int textWidth = MeasureText(text, 20);
    DrawText(text, pos.x + (size.x - textWidth) / 2, pos.y + 10, 20, DARKGRAY);
}

bool StartButton::IsMouseOver() {
    Vector2 mousePos = GetMousePosition();
    return CheckCollisionPointRec(mousePos, GetBounds());
}

void StartButton::HandleClick() {
    if (IsMouseOver() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        isPressed = true;
    }
}
