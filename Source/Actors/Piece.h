#pragma once

#include "Actor.h"
#include "../Game/InterfaceGame.h"

class DrawAnimatedComponent;
class AABBColliderComponent;

class Piece : public Actor{
public:
    explicit Piece(InterfaceGame *game, bool enabled=false, float x=0, float y=0, uint xMax=BLOCK_SIZE, uint yMax=BLOCK_SIZE, char PieceType='\0', float rotation=0.0f, bool flip=false);
    
    /* piece actions */
    void Move(const Vector2&UnitVec);

    void OnCollision(const std::vector<Actor*>&responses) override;
    void OnProcessInput(const Uint8 *KeyState) override;
    void OnUpdate(float DeltaTime) override;
    void DetectCollision() override;

    inline int GetPieceWidth() const { return mPieceWidth; }
    inline int GetPieceHeight() const { return mPieceHeight; }

protected:
    AABBColliderComponent *mAABBColliderComponent;
    DrawAnimatedComponent *mDrawComponent;
    int mPieceWidth, mPieceHeight;
    bool mCanProcessInput;

private:
    /* piece actions */
    inline void Rotate(float theta){
        std::swap(mPieceWidth, mPieceHeight);
        mAABBColliderComponent->SwapSize();
        float rot = GetRotation() + theta;
        SetRotation(rot);
        Move(Vector2::Zero);
    }
    inline void Flip(){
        SetFlip(!mFlip);
    }
    void Place();
    char mPieceType;
};