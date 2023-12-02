#pragma once 

#include "Piece.h"


class Block : public Piece{
public:
    explicit Block(InterfaceGame *game, float x, float y, bool enabled=false, ColliderLayer layer=ColliderLayer::BLOCK, uint CollisorWidth=BLOCK_SIZE, uint CollisorHeight=BLOCK_SIZE);
    
    void OnUpdate(float DeltaTime) override;
    void OnProcessInput(const Uint8 *KeyState) override;
    void OnCollision(const std::vector<Actor*>&responses) override;

private:
    void Grab();
};