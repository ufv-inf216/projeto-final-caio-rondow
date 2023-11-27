#include "AABBColliderComponent.h"
#include "../../Actors/Actor.h"
#include <unordered_map>
#include <algorithm>
#include "../../Actors/Piece.h"
#include "../../Game/InterfaceGame.h"
#include "../../Actors/Table.h"
#include "../../Actors/Block.h"

AABBColliderComponent::AABBColliderComponent(Actor *owner, const Vector2&offset, uint width, uint height, ColliderLayer layer, int UpdateOrder):
    Component(owner,UpdateOrder),
    mWidth(width),
    mHeight(height),
    mOffset(offset),
    mLayer(layer)
{

}

void AABBColliderComponent::Update(float DeltaTime){

}

void AABBColliderComponent::ProcessInput(const Uint8 *KeyState){

}

bool AABBColliderComponent::Intersect(AABBColliderComponent *b) const{

    Vector2 MinA = this->GetMin();
    Vector2 MaxA = this->GetMax();
    Vector2 MinB = b->GetMin();
    Vector2 MaxB = b->GetMax();

    bool IsColliding = !( (MaxA.x <= MinB.x) || (MaxB.x <= MinA.x) || (MaxA.y <= MinB.y) || (MaxB.y <= MinA.y) );
    return IsColliding;
}

void AABBColliderComponent::DetectCollision(std::vector<AABBColliderComponent*> &colliders){
    
    std::vector<Actor*> responses;

    // Check collision against each target collider
    for(auto collider : colliders){

        if(collider == nullptr || collider == this || !collider->IsComponentEnabled())
            continue;
        
        if(Intersect(collider)){
            responses.emplace_back( &collider->GetOwner() );
        }
    }
    if(!responses.empty()) /* if collision occurs, resolve */ 
        mOwner->OnCollision(responses);
}


Vector2 AABBColliderComponent::GetMin() const{
    // return mOwner->GetPosition() +Vector2(mWidth/2.0f, mHeight/2.0f) + mOffset;
    // std::cout << mOwner << " " << mOwner->GetPosition().x << " " << mOwner->GetPosition().y << "\n";
    return mOwner->GetPosition() + mOffset;

}

Vector2 AABBColliderComponent::GetMax() const{
    Vector2 MinPos = this->GetMin();
    return Vector2( MinPos.x + (float)mWidth, MinPos.y + (float)mHeight);
}

Vector2 AABBColliderComponent::GetCenter() const{
    Vector2 MinPos = this->GetMin();
    return Vector2(MinPos.x + (float)mWidth/2.0f, MinPos.y + (float)mHeight/2.0f);
}

AABBColliderComponent::Overlap AABBColliderComponent::GetMinOverlap(AABBColliderComponent *other) const{

    Vector2 aMin = GetMin(); Vector2 aMax = GetMax();
    Vector2 bMin = other->GetMin(); Vector2 bMax = other->GetMax();

    std::unordered_map<int, AABBColliderComponent::Overlap> overlaps;
    overlaps[0] = {Vector2::UnitX * (bMax.x - aMin.x), CollisionSide::left, other};
    overlaps[1] = {Vector2::UnitX * (bMin.x - aMax.x), CollisionSide::right,other};
    overlaps[2] = {Vector2::UnitY * (bMax.y - aMin.y), CollisionSide::top,  other};
    overlaps[3] = {Vector2::UnitY * (bMin.y - aMax.y), CollisionSide::down, other};

    AABBColliderComponent::Overlap MinOverlap = overlaps[0];
    for(int i = 1; i < overlaps.size(); i++) {
        if(overlaps[i].distance.LengthSq() < MinOverlap.distance.LengthSq()) {
            MinOverlap = overlaps[i];
        }
    }

    return MinOverlap;
}