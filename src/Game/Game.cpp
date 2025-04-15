#include "Game.hpp"

#include "../SpawnPlanets.hpp"

void Game::Init()
{
    for (Entity& entity : entities)
    {
        entity.Init();
    }
}

void Game::Update()
{
    camera.target = Vector2{ game_plr->position.x + 20.0f, game_plr->position.y + 20.0f };
    camera.offset = Vector2{ WIDTH/2.0f, HEIGHT/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    mouse_pos = GetScreenToWorld2D(GetMousePosition(), camera);

    for (Entity& entity : entities)
    {
        entity.Update();
    }
}

void Game::Draw()
{
    for (Entity& entity : entities)
    {
        entity.Draw();
    }
    DrawRectangleLines(
        spawn_barrier.x, 
        spawn_barrier.z, 
        spawn_barrier.y - spawn_barrier.x, 
        spawn_barrier.w - spawn_barrier.z, 
        GREEN
    );
}