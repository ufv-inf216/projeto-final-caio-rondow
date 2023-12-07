#include "AABBColliderComponent.h"
#include "../../Actors/Actor.h"
#include <unordered_map>
#include <algorithm>
#include "../../Actors/Piece.h"
#include "../../Game/InterfaceGame.h"
#include "../../Actors/Table.h"
#include "../../Actors/Block.h"

AABBColliderComponent::AABBColliderComponent(Actor *owner, const Vector2&offset, uint width, uint height, ColliderLayer layer, int UpdateOrder, bool IsHollow):
    Component(owner,UpdateOrder),
    mWidth(width),
    mHeight(height),
    mOffset(offset),
    mLayer(layer),
    mIsHollow(IsHollow)
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
    
    Actor* responses = nullptr;

    // Check collision against each target collider
    for(auto other : colliders){

        if(other == nullptr || other == this || !other->IsComponentEnabled())
            continue;
        
        if(Intersect(other)){
            
            if(other->GetLayer() == ColliderLayer::PIECE){
                responses = &other->GetOwner();
                break;
            }
            else if(other->GetLayer() == ColliderLayer::PEG && !mIsHollow){
                responses = &other->GetOwner();
                break;
            } 
            else if(other->GetLayer() == ColliderLayer::WALL){
                ResolveCollisions(GetMinOverlap(other));
                return;
            }
        }
    }
    /* resolve collision */
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
    
    InterfaceGame *game = mOwner->GetGame();
    
    Vector2 position = mOwner->GetPosition();
    position += minOverlap.distance;

    // if(GetMin().x < STASH_ORIGIN_X && !game->IsOnBoard(position)){
    //     int x = BOARD_ORIGIN_X+(BOARD_WIDTH-1)*BLOCK_SIZE;
    //     int y = (int)(position.y)%(BOARD_HEIGHT*BLOCK_SIZE)+BOARD_ORIGIN_Y;
    //     position = Vector2(x,y);
    // } else if(GetMax().x >= BLOCK_SIZE*BOARD_WIDTH+BOARD_ORIGIN_X && game->IsOnBoard(position)){
    //     std::cout << "ir para o stash\n";
    //     int x = STASH_ORIGIN_X+BLOCK_SIZE;
    //     int y = STASH_ORIGIN_Y+2*BLOCK_SIZE;
    //     position = Vector2(x,y);
    // } 

    mOwner->SetPosition(position);
}