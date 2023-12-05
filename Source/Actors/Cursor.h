#pragma once

#include "Block.h"

class Cursor : public Block{
public:
    explicit Cursor(InterfaceGame *game, float x, float y, bool enable);

    void OnUpdate(float DeltaTime) override;
    void OnProcessInput(const Uint8 *KeyState) override;
    void OnCollision(const std::vector<Actor*>&responses) override;

private:
    void GrabPiece();

    /* components */
    DrawAnimatedComponent *mDrawAnimComponent;
};