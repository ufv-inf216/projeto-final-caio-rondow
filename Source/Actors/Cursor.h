#pragma once

#include "Block.h"

class DrawAnimatedComponent;

class Cursor : public Block{
public:
    explicit Cursor(InterfaceGame *game, float x, float y, bool enable);

    void OnUpdate(float DeltaTime) override;
    void OnProcessInput(const Uint8 *KeyState) override;
    void OnCollision(Actor *response) override;

private:
    void GrabPiece();

    /* cursor components */
    DrawAnimatedComponent *mDrawAnimComponent;
    AABBColliderComponent *mAABBColliderComponent;
};