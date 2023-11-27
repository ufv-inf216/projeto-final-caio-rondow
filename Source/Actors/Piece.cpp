#include "Piece.h"
#include "../Components/DrawComponents/DrawAnimatedComponent.h"
#include "../Components/ColliderComponents/AABBColliderComponent.h"
#include "Table.h"
#include "Block.h"

#define PIECE_L_WIDTH 64
#define PIECE_L_HEIGHT 96

Piece::Piece(InterfaceGame *game, bool enabled, float x, float y, uint xMax, uint yMax, char PieceType, float rotation, bool flip):
    Actor(game),
    mCanProcessInput(false),
    mPieceType(PieceType)
{

    SetPosition(Vector2(x,y));
    SetFlip(flip);
    enabled ? Enable() : Disable();
    
    switch (PieceType)
    {
    case 'L':
        mPieceWidth = PIECE_L_WIDTH;
        mPieceHeight = PIECE_L_HEIGHT;
        new DrawSpriteComponent(this, "../Assets/Sprite/Pieces/L.png", mPieceWidth, mPieceHeight, 10);
        mAABBColliderComponent = new AABBColliderComponent(this, Vector2(0,0), xMax, yMax, ColliderLayer::PIECE);
        break;
    default: /* simple block */

        mPieceWidth  = BLOCK_SIZE;
        mPieceHeight = BLOCK_SIZE;

        std::string spritesheet = "../Assets/Sprite/NodeDebug/DebugSpriteSheet.jpg";
        std::string spritedata  = "../Assets/Sprite/NodeDebug/DebugSpriteSheet.json";

        mDrawComponent = new DrawAnimatedComponent(this, spritesheet, spritedata, mIsEnabled ? 10 : 0);
        mDrawComponent->AddAnimation("idle", {0});
        mDrawComponent->AddAnimation("cursor", {1});
        mDrawComponent->SetAnimation( IsEnabled() ? "cursor" : "idle" );
        mDrawComponent->SetAnimationFPS(1);

        mAABBColliderComponent = new AABBColliderComponent(this, Vector2(0,0), xMax, yMax, ColliderLayer::BLOCK);
        break;
    }
}

void Piece::Move(const Vector2&UnitVec){
    
    Vector2 CurrPos = GetPosition();
    
    /* Check if the player wants to go to the adjacent table */
    if((CurrPos.x-BOARD_ORIGIN_X)/BLOCK_SIZE == BOARD_WIDTH-1 && UnitVec.x > 0){ /* go to stash */
        SetPosition(Vector2(STASH_ORIGIN_X, STASH_ORIGIN_Y));
        return;
    } else if((CurrPos.x-STASH_ORIGIN_X) / BLOCK_SIZE == 0 && UnitVec.x < 0){ /* go to board */
        SetPosition(Vector2((BOARD_WIDTH-1)*BLOCK_SIZE+BOARD_ORIGIN_X, BOARD_ORIGIN_Y));
        return;
    }

    /* calculate the next position */
    Vector2 NewPos = CurrPos + UnitVec*BLOCK_SIZE;

    /* calculate the table with based on the current table */
    const Table *table = mGame->IsCursorOnBoard() ? mGame->GetBoard() : mGame->GetStash();
    Vector2 TablePos    = table->GetPosition();
    int TableHeight = ((int)table->GetTableHeight()-1) * BLOCK_SIZE;
    int TableWidth  = ((int)table->GetTableWidth() -1) * BLOCK_SIZE;
    
    /* limitates the cursor into the table */
    NewPos.x = Math::Clamp((int)NewPos.x, (int)TablePos.x, TableWidth +(int)TablePos.x);
    NewPos.y = Math::Clamp((int)NewPos.y, (int)TablePos.y, TableHeight+(int)TablePos.y);
    
    SetPosition(NewPos);
}

void Piece::OnUpdate(float DeltaTime){
    if(IsEnabled()){
        mCanProcessInput = !mGame->GetAction();
    } else{
        mCanProcessInput = false;
    }
}

void Piece::OnProcessInput(const Uint8 *KeyState){
    if(!IsEnabled() || !mCanProcessInput)
        return;
    if(KeyState[SDL_SCANCODE_W])
        Move(Vector2::NegUnitY);
    if(KeyState[SDL_SCANCODE_A])
        Move(Vector2::NegUnitX);
    if(KeyState[SDL_SCANCODE_S])
        Move(Vector2::UnitY);
    if(KeyState[SDL_SCANCODE_D])
        Move(Vector2::UnitX);
    if(KeyState[SDL_SCANCODE_E])
        Rotate(90.0f);
    if(KeyState[SDL_SCANCODE_Q])
        Rotate(-90.0f);
    if(KeyState[SDL_SCANCODE_F])
        Flip();
    if(KeyState[SDL_SCANCODE_SPACE])
        Place();
}

void Piece::Place(){
    DetectCollision();
}

 void Piece::OnCollision(const std::vector<Actor*>&responses){

    Block *cursor = mGame->GetCursor();
    cursor->Enable();
    cursor->SetPosition(GetPosition());
    this->Disable();

 }

void Piece::DetectCollision(){
    
    std::vector<AABBColliderComponent*> colliders;

    for(auto block : mGame->GetBoard()->GetBlocks()){
        colliders.push_back( block->GetComponent<AABBColliderComponent>() );
    }

    for(auto piece : mGame->GetBoard()->GetPieces()){
        colliders.push_back( piece->GetComponent<AABBColliderComponent>() );
    }

    /* ATENTION! Also need to test collision with pegs */  

    for(auto piece : mGame->GetStash()->GetPieces()){
        colliders.push_back( piece->GetComponent<AABBColliderComponent>() );
    }

    for(auto block : mGame->GetStash()->GetBlocks()){
        colliders.push_back( block->GetComponent<AABBColliderComponent>() );
    }
    
    this->GetComponent<AABBColliderComponent>()->DetectCollision(colliders);
}