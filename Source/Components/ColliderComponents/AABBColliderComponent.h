#pragma once

#include "../Component.h"
#include <vector>

enum class ColliderLayer{
    BLOCK,
    PIECE,
    BRIDGE
};

enum class CollisionSide{
    top,
    down,
    left,
    right
};

class Piece;

class AABBColliderComponent : public Component{
public:
    struct Overlap{
        Vector2 distance;
        CollisionSide side;
        AABBColliderComponent *target;
    };
    
    AABBColliderComponent(Actor *owner, const Vector2&offset, uint width, uint height, ColliderLayer layer, int UpdateOrder=10, bool isHollow);

    void Update(float DeltaTime) override;
    void ProcessInput(const Uint8 *KeyState) override;

    bool Intersect(AABBColliderComponent *other) const;
    void DetectCollision(std::vector<AABBColliderComponent*> &colliders);
    
    Vector2 GetMin() const;
    Vector2 GetMax() const;
    Vector2 GetCenter() const;
    inline ColliderLayer GetLayer() const { return mLayer; }
    inline void SwapSize(){
        std::swap(mWidth, mHeight);
    }
private:
    Overlap GetMinOverlap(AABBColliderComponent *other) const;

    ColliderLayer mLayer;
    uint mWidth, mHeight;
    Vector2 mOffset;
    bool mIsHollow; /* If a node in pice is hollow, then this actor don't collide with pegs actor*/
};