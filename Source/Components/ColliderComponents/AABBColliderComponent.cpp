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
            if(collider->GetLayer() == ColliderLayer::WALL){
                static int i=0;
                std::cout << "colisao com a parede " << i++ << "\n"; 
                ResolveCollisions(GetMinOverlap(collider));
                return;
            }

            responses.emplace_back( &collider->GetOwner() );
        }
    }
    /* resolve collisions */
    mOwner->OnCollision(responses);
}


Vector2 AABBColliderComponent::GetMin() const{
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

AABBColliderComponent::Overlap AABBColliderComponent::GetMinOverlap(AABBColliderComponent *b) const{

    Vector2 aMin = GetMin(); Vector2 aMax = GetMax();
    Vector2 bMin = b->GetMin(); Vector2 bMax = b->GetMax();

    std::unordered_map<int, Overlap> overlaps;
    overlaps[0] = {Vector2::UnitX * (bMax.x - aMin.x), CollisionSide::left, b};
    overlaps[1] = {Vector2::UnitX * (bMin.x - aMax.x), CollisionSide::right,b};
    overlaps[2] = {Vector2::UnitY * (bMax.y - aMin.y), CollisionSide::top,  b};
    overlaps[3] = {Vector2::UnitY * (bMin.y - aMax.y), CollisionSide::down, b};

    Overlap minOverlap = overlaps[0];
    for(int i = 1; i < overlaps.size(); i++) {
        if(overlaps[i].distance.LengthSq() < minOverlap.distance.LengthSq()) {
            minOverlap = overlaps[i];
        }
    }

    return minOverlap;
}

void AABBColliderComponent::ResolveCollisions(const Overlap& minOverlap){
    
    Vector2 position = mOwner->GetPosition();
    position += minOverlap.distance;
    auto game = mOwner->GetGame();
    int width = mOwner->GetWidth();

    if(minOverlap.side == CollisionSide::right && game->IsOnBoard(position)){
        std::cout << "go to stash\n";
        position = Vector2(STASH_ORIGIN_X, STASH_ORIGIN_Y);

    } else if(minOverlap.side == CollisionSide::left && !game->IsOnBoard(position)){
        std::cout << "go to board\n";
        position = Vector2(BOARD_ORIGIN_X+BLOCK_SIZE*BOARD_WIDTH-width, BOARD_ORIGIN_Y);
    }

    mOwner->SetPosition(position);
}