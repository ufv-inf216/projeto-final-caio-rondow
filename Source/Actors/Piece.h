#pragma once

#include "Actor.h"
#include "../Game/InterfaceGame.h"

class DrawAnimatedComponent;
class DrawSpriteComponent;
class AABBColliderComponent;
class DrawPolygonComponent;

class Piece : public Actor{
public:
    explicit Piece(InterfaceGame *game, float x, float y, char PieceType=char(), float rotation=0.0f, bool flip=false);
    
    /* piece actions */
    void Move(const Vector2&UnitVec);

    void OnCollision(const std::vector<Actor*>&responses) override;
    void OnProcessInput(const Uint8 *KeyState) override;
    void OnUpdate(float DeltaTime) override;

    inline char GetPieceType() const { return mPieceType; }

    /* Enable/Disable piece functions */
    inline void Disable(){ mIsEnabled = false; }
    inline void Enable(){ mIsEnabled = true; }
    inline bool IsEnabled() const{ return mIsEnabled; }

protected:
    /* piece components */
    AABBColliderComponent *mAABBColliderComponent;
    DrawPolygonComponent *mDrawPolygonComponent; /* DEBUG ONLY */
    DrawAnimatedComponent *mDrawComponent;
    
    bool mCanProcessInput;
    bool mIsEnabled;
    char mPieceType;
private:
    DrawSpriteComponent *mDrawSpriteComponent;

    /* piece actions */
    void Rotate(float theta);
    void Flip();
    void Place();
};