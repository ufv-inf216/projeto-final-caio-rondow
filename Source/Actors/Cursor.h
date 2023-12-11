#pragma once

#include "Block.h"

class DrawSpriteComponent;

class Cursor : public Block{
public:
    explicit Cursor(InterfaceGame *game, float x, float y, bool enable);

    void OnUpdate(float DeltaTime) override;
    void OnProcessInput(const Uint8 *KeyState) override;
    void OnCollision(Actor *response) override;

    const Piece *PieceSelected() const;

private:
    void GrabPiece();

    DrawSpriteComponent *mHighlight;
    Piece *mOnHand; // current piece enabled
};