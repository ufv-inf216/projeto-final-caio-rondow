#pragma once 

#include "Piece.h"

class Block : public Piece{
public:
    /* create a block */
    explicit Block(InterfaceGame *game, float x, float y, bool enable=false);
    explicit Block(InterfaceGame *game);

    void OnUpdate(float DeltaTime) override;
    void OnCollision(Actor *response) override;
};