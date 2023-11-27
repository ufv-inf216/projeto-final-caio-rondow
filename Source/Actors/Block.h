#pragma once 

#include "Piece.h"


class Block : public Piece{
public:
    explicit Block(InterfaceGame *game, bool enabled=false, float x=0, float y=0, uint xMax=BLOCK_SIZE, uint yMax=BLOCK_SIZE);
    
    void OnUpdate(float DeltaTime) override;
    void OnProcessInput(const Uint8 *KeyState) override;
    void DetectCollision() override;
    void OnCollision(const std::vector<Actor*>&responses) override;

private:
    void Withdraw();
};