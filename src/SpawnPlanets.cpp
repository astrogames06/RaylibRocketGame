#include "SpawnPlanets.hpp"

#include <raylib.h>
#include <string>

#include "Game/Game.hpp"

extern Game game;

int spawn_delay;

std::vector<Texture2D> planet_texs;

void InitPlanetTextures()
{

}
void SpawnPlanets()
{
    spawn_delay++;

    if (spawn_delay >= GetFPS()*2)
    {
        int random_planet = GetRandomValue(0, 9);
        Texture2D planet_texture = LoadTexture(("assets/planets/planet" + std::to_string(random_planet) + ".png").c_str());//planet_texs[random_planet];
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
            GetRandomValue(game.spawn_barrier.x, game.spawn_barrier.y)+PLANET_RADIUS,
            GetRandomValue(game.spawn_barrier.z, game.spawn_barrier.w)+PLANET_RADIUS
        };
        bool collision = true;
        while (collision)
        {
            collision = false;
            for (Planet& planet : game.planets)
            {
                if (CheckCollisionCircles(planet_position, PLANET_RADIUS, planet.position, PLANET_RADIUS))
                {
                    collision = true;
                    planet_position = {
                        GetRandomValue(game.spawn_barrier.x, game.spawn_barrier.y)+PLANET_RADIUS,
                        GetRandomValue(game.spawn_barrier.z, game.spawn_barrier.w)+PLANET_RADIUS
                    };
                    break;
                }
            }

            if (CheckCollisionCircleRec(planet_position, PLANET_RADIUS,
                {game.game_plr->position.x, game.game_plr->position.y,
                (float)game.game_plr->texture.width, (float)game.game_plr->texture.height}))
            {
                collision = true;
                planet_position = {
                    GetRandomValue(game.spawn_barrier.x, game.spawn_barrier.y)+PLANET_RADIUS,
                    GetRandomValue(game.spawn_barrier.z, game.spawn_barrier.w)+PLANET_RADIUS
                };
            }
        }
        std::cout << "Planet position set: " << planet_position.x << ", " << planet_position.y << std::endl;

        Planet new_planet = {
            planet_texture,
            planet_position,
            GetRandomValue(1, 4),
            GetRandomValue(1, 5),
            GetRandomValue(1, 5)
        };
        game.planets.push_back(new_planet);

        spawn_delay = 0;
    }
}

void DrawPlanets()
{
    for (Planet& planet : game.planets)
    {
        DrawTexturePro(planet.texture, 
            {0, 0, (float)planet.texture.width, (float)planet.texture.height},
            {planet.position.x, planet.position.y, (float)planet.texture.width, (float)planet.texture.height},
            {(float)planet.texture.width/2, (float)planet.texture.height/2},
            0.f,
        WHITE);
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