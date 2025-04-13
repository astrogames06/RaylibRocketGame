#ifndef SPAWNPLANETS_H
#define SPAWNPLANETS_H

#include <string>

#include "Game/Game.hpp"

extern Game game;

int spawn_delay;

void SpawnPlanets()
{
    spawn_delay++;

    if (spawn_delay >= GetFPS()*2)
    {
        int random_planet = GetRandomValue(0, 9);
        Texture2D planet_texture = LoadTexture(("assets/planets/planet" + std::to_string(random_planet) + ".png").c_str());
        planet_texture.width /= 5;
        planet_texture.height /= 5;
        /*
        typedef struct Vector4 {
            float x;                // Vector x component
            float y;                // Vector y component
            float z;                // Vector z component
            float w;                // Vector w component
        } Vector4;
        */
        Vector2 planet_position = {
            GetRandomValue(game.spawn_barrier.x, game.spawn_barrier.y),
            GetRandomValue(game.spawn_barrier.z, game.spawn_barrier.w)
        };
        bool collision = true;
        while (collision)
        {
            collision = false;
            for (Planet& planet : game.planets)
            {
                if (CheckCollisionCircles(planet_position, planet_texture.width / 2.0f, planet.position, planet_texture.width / 2.0f))
                {
                    collision = true;
                    planet_position = {
                        GetRandomValue(game.spawn_barrier.x, game.spawn_barrier.y),
                        GetRandomValue(game.spawn_barrier.z, game.spawn_barrier.w)
                    };
                    break;
                }
            }

            if (CheckCollisionCircleRec(planet_position, planet_texture.width / 2.0f,
                {game.game_plr->position.x, game.game_plr->position.y,
                (float)game.game_plr->texture.width, (float)game.game_plr->texture.height}))
            {
                collision = true;
                planet_position = {
                    GetRandomValue(game.spawn_barrier.x, game.spawn_barrier.y),
                    GetRandomValue(game.spawn_barrier.z, game.spawn_barrier.w)
                };
            }
        }

        Planet new_planet = {
            planet_texture,
            planet_position,
            (float)GetRandomValue(1, 4),
            (float)GetRandomValue(1, 5),
            (float)GetRandomValue(1, 5),
        };
        game.planets.push_back(new_planet);

        spawn_delay = 0;
    }
}

void DrawPlanets()
{
    for (Planet& planet : game.planets)
    {
        DrawTextureV(planet.texture, planet.position, WHITE);
    }
    DrawRectangleLines(game.game_plr->position.x, game.game_plr->position.y, 50,50, GREEN);
}

/*
struct Planet
{
    Texture2D texture;
    Vector2 position;
    float pull;
    int worth;
    int strength;
};
*/

#endif