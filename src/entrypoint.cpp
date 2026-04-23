#include "entrypoint.h"
#include "Breakout.h"

void raylib_start(void)
{
    Game* game = new Breakout();
    game->Init();
    while (!WindowShouldClose())
    {
        BeginDrawing();
        game->Update(GetFrameTime());
        game->Draw();
        EndDrawing();
    }
    game->Deinit();
    CloseWindow();
}