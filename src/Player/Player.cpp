#include "Player.hpp"
#include "../Game/Game.hpp"

#include <iostream>
#include <math.h>

class Game;

extern Game game;

Texture2D laser_tex;

void Player::Init()
{
    Entity::Init();
    texture = LoadTexture("assets/player.png");

    laser_tex = LoadTexture("assets/laser.png");
}

void Player::Update()
{
    rotation = atan2f(position.y-game.mouse_pos.y, position.x-game.mouse_pos.x) * RAD2DEG;
	float dir_x = cosf(rotation*DEG2RAD);
	float dir_y = sinf(rotation*DEG2RAD);

	if ((IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_W)) &&
		!CheckCollisionPointRec(game.mouse_pos, {position.x-25, position.y-25, 50, 50}))
	{
		position.x -= dir_x * 500.f * GetFrameTime();
		position.y -= dir_y * 500.f * GetFrameTime();
	}

	if (IsKeyPressed(KEY_E))
	{
		lasers.push_back(Laser{position.x, position.y, rotation});
	}

    if (position.x < game.spawn_barrier.x) game.spawn_barrier.x = position.x;
    if (position.x > game.spawn_barrier.y) game.spawn_barrier.y = position.x;
    
    if (position.y < game.spawn_barrier.z) game.spawn_barrier.z = position.y;
    if (position.y > game.spawn_barrier.w) game.spawn_barrier.w = position.y;
}

void Player::Draw()
{
    DrawTexturePro(texture,
        {0, 0, (float)texture.width, (float)texture.height},
        {position.x, position.y, (float)texture.width, (float)texture.height},
        {(float)texture.width/2, (float)texture.height/2},
        rotation - 90.f,
    WHITE);

    for (Planet& planet : game.planets)
    {DrawRectangleLines(planet.position.x, planet.position.y, planet.texture.width, planet.texture.height, BLUE);}

    for (int i = 0; i < lasers.size(); i++)
	{
        Laser& laser = lasers[i];
		laser.pos.x -= cosf(laser.rot*DEG2RAD) * 1000 * GetFrameTime();
		laser.pos.y -= sinf(laser.rot*DEG2RAD) * 1000 * GetFrameTime();

		DrawTexturePro(laser_tex,
			{0, 0, laser_tex.width, laser_tex.height},
			{laser.pos.x, laser.pos.y, laser_tex.width, laser_tex.height},
			{laser_tex.width/2, laser_tex.height/2},
			laser.rot-90.f,
		WHITE);

        DrawRectangleLines(laser.pos.x, laser.pos.y, laser_tex.width, laser_tex.height, RED);

        for (Planet& planet : game.planets)
        {
            if (CheckCollisionCircleRec(planet.position, planet.texture.width,
                {laser.pos.x, laser.pos.y, (float)laser_tex.width, (float)laser_tex.height}
            ))
            {
                planet.texture.width -= 5;
                planet.texture.height -= 5;
                lasers.erase(lasers.begin() + i);
            }
        }
	}
}