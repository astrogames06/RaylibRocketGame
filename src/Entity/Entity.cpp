#include "Entity.hpp"
#include "../Game/Game.hpp"

extern Game game;

void Entity::Init()
{
    game.entities.push_back(*this);
}

void Entity::Update(){}
void Entity::Draw(){}