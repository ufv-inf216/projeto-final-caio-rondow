#include "Block.h"
#include "../Game/ConcreteGame.h"
#include "../Components/DrawComponents/DrawAnimatedComponent.h"
#include "../Components/ColliderComponents/AABBColliderComponent.h"

#define BLOCK_SIZE 32

Block::Block(InterfaceGame *game, int dx, int dy, ColliderLayer layer):
    Actor(game),
    mIsSelected(false),
    mAdjacents(std::vector<Block*>(4, nullptr)) // up, down, left, right
{
    std::string spritesheet = "../Assets/Sprite/NodeDebug/DebugSpriteSheet.jpg";
    std::string spritedata  = "../Assets/Sprite/NodeDebug/DebugSpriteSheet.json";

    mDrawComponent = new DrawAnimatedComponent(this, spritesheet, spritedata, 0);
    mDrawComponent->AddAnimation("idle", {0});
    mDrawComponent->AddAnimation("cursor", {1});
    mDrawComponent->SetAnimation("idle");
    mDrawComponent->SetAnimationFPS(10);

    mAABBColliderComponent = new AABBColliderComponent(this, Vector2(0,0), dx-1, dy-1, layer);

}

void Block::OnUpdate(float DeltaTime){
    if(mIsSelected){
        // std::cout << GetPosition().x << " " << GetPosition().y << "\n";
        mDrawComponent->SetAnimation("cursor");
    } else{
        mDrawComponent->SetAnimation("idle");
    }
}

void Block::OnCollision(std::vector<AABBColliderComponent::Overlap>&responses){
    
    

}