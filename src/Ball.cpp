#include "Ball.h"
#include "World.h"

void Ball::Update(float dt) {
    if (!isActive) return;
    
    pos.x += velocity.x * dt;
    pos.y += velocity.y * dt;

    HandleScreenBounds();

    CheckCollisions();
}

void Ball::Draw() {
    if (isActive) {
        Vector2 sizeGot = GetSize();
        DrawRectangle(pos.x, pos.y, sizeGot.x, sizeGot.y, BLUE);
    }
}

bool Ball::CollidingWith(GameObject* other) {
    if (!other) return false;
    
    Rectangle otherBounds = other->GetBounds();
    return CheckCollisionRecs(GetBounds(), otherBounds);
}

void Ball::CheckCollisions() {
    const auto& objects = GetWorld()->GetObjects();
    for (GameObject* obj : objects) {
        if (obj == this) continue;
        
        if (CollidingWith(obj)) {
            Rectangle bounds = obj->GetBounds();
            Rectangle ballBounds = GetBounds();
            float overlapX = std::min(ballBounds.x + ballBounds.width, bounds.x + bounds.width)  - std::max(ballBounds.x, bounds.x);
            float overlapY = std::min(ballBounds.y + ballBounds.height, bounds.y + bounds.height) - std::max(ballBounds.y, bounds.y);

            if (overlapX < overlapY) {
                velocity.x = -velocity.x;
            } else {
                velocity.y = -velocity.y;
            }
            break; // Only one collision at a time
        }
    }
}

void Ball::HandleScreenBounds() {
    int width = GetScreenWidth();
    int height = GetScreenHeight();

    // Bounce off sides
    Vector2 sizeGot = GetSize();
    if (pos.x - sizeGot.x/2 < 0 || pos.x + sizeGot.x/2 > width) {
        velocity.x = -velocity.x;
        if (pos.x - sizeGot.x/2 < 0) pos.x = sizeGot.x/2;
        if (pos.x + sizeGot.x/2 > width) pos.x = width - sizeGot.x/2;
    }

    // Bounce off top
    if (pos.y - sizeGot.y/2 < 0) {
        velocity.y = -velocity.y;
        pos.y = sizeGot.y/2;
    }

    // Game over if ball falls off bottom
    if (pos.y - sizeGot.y/2 > height) {
        isActive = false;
    }
}