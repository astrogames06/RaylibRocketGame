#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#include "Game/Game.hpp"
#include "Player/Player.hpp"
#include "SpawnPlanets.hpp"

Game game;

void UpdateDrawFrame();

int main(void)
{
	InitWindow(game.WIDTH, game.HEIGHT, "raylib [core] example - basic window");
	game.Init();

	Player plr;
	plr.position = Vector2 { (float)game.WIDTH / 2, (float)game.HEIGHT / 2 };
	plr.Init();
	game.game_plr = &plr;

	#if defined(PLATFORM_WEB)
    	emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
	#else
		SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
		//--------------------------------------------------------------------------------------

		// Main game loop
		while (!WindowShouldClose())    // Detect window close button or ESC key
		{
			UpdateDrawFrame();
		}
	#endif

	CloseWindow();

	return 0;
}

void UpdateDrawFrame()
{
	game.Update();
	SpawnPlanets();

	BeginDrawing();
	BeginMode2D(game.camera);
	
	ClearBackground(RAYWHITE);

	game.Draw();
	DrawPlanets();

	EndMode2D();
	EndDrawing();
}