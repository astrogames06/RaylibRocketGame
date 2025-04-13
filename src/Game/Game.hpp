#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <vector>
#include "../Entity/Entity.hpp"
#include "../Player/Player.hpp"

class Player;

class Entity;

struct Planet
{
    Texture2D texture;
    Vector2 position;
    float pull;
    int worth;
    int strength;
};

class Game
{
public:
    int WIDTH = 840;
    int HEIGHT = 480;
    Vector2 mouse_pos;
    std::vector<std::reference_wrapper<Entity>> entities;
    Camera2D camera;

    Vector4 spawn_barrier = {
        static_cast<float>(-WIDTH),
        static_cast<float>(WIDTH),
        static_cast<float>(-HEIGHT),
        static_cast<float>(HEIGHT)
    };
    std::vector<Planet> planets;

    Player* game_plr;

    void Init();
    void Update();
    void Draw();
};

#endif