#ifndef PLAYER_H
#define PLAYER_H

#include "../Entity/Entity.hpp"
#include <vector>

struct Laser
{
	Vector2 pos;
	float rot;
};

class Player : public Entity
{
public:
    float rotation;
    Vector2 velocity = {0, 0};
    const int PLAYER_SIZE = 50;
    const float MOVE_SPEED = 200.0f;

    std::vector<Laser> lasers;

    void Init() override;
    void Update() override;
    void Draw() override;
};

#endif