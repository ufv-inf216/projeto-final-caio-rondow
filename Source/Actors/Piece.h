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
    inline const std::vector<AABBColliderComponent*> &GetColliders() const{
        return mColliders;
    }

    /* Enable/Disable piece functions */
    inline void Disable(){ mIsEnabled = false; }
    inline void Enable(){ mIsEnabled = true; }
    inline bool IsEnabled() const{ return mIsEnabled; }

protected:
    /* piece components */
    AABBColliderComponent *mAABBColliderComponent;
    DrawAnimatedComponent *mDrawComponent;

    std::vector<AABBColliderComponent*> mColliders;
    DrawPolygonComponent *mDrawPolygonComponent; /* DEBUG ONLY */
    
    bool mCanProcessInput;
    bool mIsEnabled;
    char mPieceType;
private:
    DrawSpriteComponent *mDrawSpriteComponent;
    std::vector<DrawPolygonComponent*> mDrawPolygons; /* DEBUG ONLY */
    /* piece actions */
    void Rotate(float theta);
    void Flip();
    void Place();
    /* Change collider based on rotation and flip */
    void RotateCounterClockWise(double& x, double& y, double cx, double cy, double theta);
};