#include "Block.h"
#include "Table.h"
#include "Cursor.h"
#include "../Components/DrawComponents/DrawAnimatedComponent.h"
#include "../Components/ColliderComponents/AABBColliderComponent.h"

/* create a block */
Block::Block(InterfaceGame *game, float x, float y, bool enable):
    Piece(game, x, y)
{
    /* could be a cursor, instead of a static block */
    mIsEnabled = enable;

    std::string SpriteSheet = "../Assets/Sprite/Table/table.png";
    std::string SpriteData  = "../Assets/Sprite/Table/table.json";

    DrawAnimatedComponent *DrawAnimated = new DrawAnimatedComponent(this, SpriteSheet, SpriteData, BLOCK_DRAW_LAYER);
    DrawAnimated->AddAnimation("idle", {0});
    DrawAnimated->AddAnimation("cursor", {1});
    DrawAnimated->SetAnimation("idle");
    DrawAnimated->SetAnimationFPS(1);

    new AABBColliderComponent(this,Vector2(0,0),BLOCK_SIZE,BLOCK_SIZE,ColliderLayer::BLOCK);
}

Block::Block(InterfaceGame *game):
    Piece(game, 0, 0)
{
    
}

void Block::OnUpdate(float DeltaTime){

    std::vector<AABBColliderComponent*> others;
    Cursor *cursor = mGame->GetCursor();
    const Piece *piece = cursor->PieceSelected();

    if(piece != nullptr){
        for(AABBColliderComponent *collider : piece->GetColliders()){
            others.push_back(collider);
        }
    }

    this->GetComponent<AABBColliderComponent>()->DetectCollision(others);
}

void Block::OnCollision(Actor *response){

    if(response == nullptr){
        this->GetComponent<DrawAnimatedComponent>()->SetAnimation("idle");
        return;
    }
    
    Piece *piece = static_cast<Piece*>(response);
    this->GetComponent<DrawAnimatedComponent>()->SetAnimation("cursor");
}