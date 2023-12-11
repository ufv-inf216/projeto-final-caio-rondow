#pragma once

#include "Block.h"

class Wall : public Block{
public:
    explicit Wall(InterfaceGame *game, float x, float y, uint WallWidth, uint WallHeight);

    void OnUpdate(float DeltaTime) override;
    void OnCollision(Actor *response) override;
};