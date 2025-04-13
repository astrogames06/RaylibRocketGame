#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>

class Game;

class Entity
{
public:
    Texture2D texture;
    Vector2 position;
    virtual ~Entity() = default;

    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0; 
};

#endif