#include "Breakout.h"
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "Smoothing.h"
#include "StartButton.h"
#include <thread>
#include <chrono>

void Breakout::Init() {
    if (isFirstInit)
    {
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout");
        SetTargetFPS(60);
        isFirstInit = false;
    }

    World& world = GetWorld();

    // Create start button
    StartButton* startBtn = new StartButton(&world);
    world.AddObject(startBtn);

    // Create paddle
    Paddle* paddle = new Paddle(&world);
    paddle->SetPos({SCREEN_WIDTH / 2.0f - 40, SCREEN_HEIGHT - 50.0f});
    world.AddObject(paddle);

    // Create ball
    Ball* ball = new Ball(&world);
    ball->SetPos({SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f});
    ball->SetVelocity(200.0f, -250.0f);
    world.AddObject(ball);

    // Create initial bricks
    CreateBricks();

    gameStarted = false;
}

void Breakout::Update(float dt) {
    // Check if start button was pressed
    if (!gameStarted) {
        StartButton* startBtn = dynamic_cast<StartButton*>(FindObjectByName("startButton"));
        if (startBtn && startBtn->IsPressed()) {
            gameStarted = true;
            Ball* ball = dynamic_cast<Ball*>(FindObjectByName("ball"));
            if (ball) {
                ball->SetActive(true);
            }
        }
    }

    UpdateObjects(dt);

    // Check collisions between ball and the other objects
    if (gameStarted) {
        Ball* ball = dynamic_cast<Ball*>(FindObjectByName("ball"));
        if (ball && ball->IsActive()) {
            const auto& objects = GetWorld().GetObjects();
            for (GameObject* obj : objects) {
                if (obj == ball) continue;
                
                Brick* brick = dynamic_cast<Brick*>(obj);
                if (brick && ball->CollidingWith(brick)) {
                    Destroy(brick);
                    break;
                }
            }
        }

        CheckGameOver();
    }
}

void Breakout::Draw() {
    ClearBackground(BLACK);

    DrawObjects();
}

void Breakout::Deinit() {
    CloseWindow();
}

void Breakout::CreateBricks() {
    World& world = GetWorld();
    static constexpr int brickWidth = 70;
    static constexpr int brickHeight = 20;
    static constexpr int spacingX = 5;
    static constexpr int spacingY = 5;
    static constexpr int startX = 10;
    static constexpr int startY = 80;

    int brickIndex = 0;
    for (int row = 0; row < BRICK_ROWS; row++) {
        for (int col = 0; col < BRICKS_PER_ROW; col++) {
            float x = startX + col * (brickWidth + spacingX);
            float y = startY + row * (brickHeight + spacingY);

            // Clamp to screen
            if (x + brickWidth > SCREEN_WIDTH)
            {
                continue;
            }

            Vector2 pos = {x, y};

            Color brickColor = 
            {
                (unsigned char)Smoothing::Lerp(255, 255, (float)row / BRICK_ROWS),
                (unsigned char)Smoothing::Lerp(0, 255, (float)row / BRICK_ROWS),
                0,
                255
            };

            std::string brickName = "brick-" + std::to_string(brickIndex++);
            Brick* brick = new Brick(brickName, &world, pos, brickColor);
            world.AddObject(brick);
        }
    }
}

void Breakout::CheckGameOver() {
    Ball* ball = dynamic_cast<Ball*>(FindObjectByName("ball"));
    if (ball && !ball->IsActive()) {
        gameStarted = false;
        ResetGame();
    }
}

void Breakout::ResetGame() {
    // Clear all objects
    World& world = GetWorld();
    auto objects = world.GetObjects();
    for (GameObject* obj : objects) {
        Destroy(obj);
    }
    UpdateObjects(0);

    // Reinitialize the game
    Init();
}