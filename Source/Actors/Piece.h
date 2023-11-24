#pragma once

#include "Actor.h"

class InterfaceGame;

enum class PieceState{
    MOVE,
    ROTATE,
    FLIP,
    PLACE,
    IDLE
};

class DrawComponent;
class AABBColliderComponent;

class Piece : public Actor{
public:
    explicit Piece(InterfaceGame *game, char type, const Vector2&origin, float rotation, bool flip);

    /* PUBLIC METHODS */
    void OnUpdate(float DeltaTime) override;
    void OnProcessInput(const Uint8 *KeyState) override;
    void OnCollision() override;
    /* Piece methods */
    void Rotate();
    void Flip();
    void Move();
    void Place();

    std::vector<AABBColliderComponent*> GetCollider() const{
        return mColliders;
    }

    void DetectCollision();
    

private:
    bool mFlip;
    char mType;
    bool mIsPieceSelected;
    PieceState mState;
    DrawComponent *mDrawComponent;
    std::vector<AABBColliderComponent*> mColliders;
};