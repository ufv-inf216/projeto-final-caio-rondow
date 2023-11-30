#include "Piece.h"
#include "../Components/DrawComponents/DrawAnimatedComponent.h"
#include "../Components/ColliderComponents/AABBColliderComponent.h"
#include "Table.h"
#include "Block.h"

#define PIECE_L_WIDTH 64
#define PIECE_L_HEIGHT 96
#define PIECE_Z_WIDTH 64
#define PIECE_Z_HEIGHT 96
#define PIECE_I_WIDTH 32
#define PIECE_I_HEIGHT 128
#define PIECE_b_WIDTH 64
#define PIECE_b_HEIGHT 96
#define PIECE_c_WIDTH 64
#define PIECE_c_HEIGHT 64
#define PIECE_T_WIDTH 96
#define PIECE_T_HEIGHT 64
#define PIECE_f_WIDTH 96
#define PIECE_f_HEIGHT 96
#define PIECE_i_WIDTH 32
#define PIECE_i_HEIGHT 96

Piece::Piece(InterfaceGame *game, bool enabled, float x, float y, uint xMax, uint yMax, char PieceType, float rotation, bool flip):
    Actor(game),
    mCanProcessInput(false),
    mPieceType(PieceType)
{

    SetPosition(Vector2(x,y));
    SetRotation(rotation);
    SetFlip(flip);
    enabled ? Enable() : Disable();
    
    switch (PieceType)
    {
    /* RED */
    case 'L':
        mPieceWidth = PIECE_L_WIDTH;
        mPieceHeight = PIECE_L_HEIGHT;
        new DrawSpriteComponent(this, "../Assets/Sprite/Pieces/L.png", mPieceWidth, mPieceHeight, 10);
        mAABBColliderComponent = new AABBColliderComponent(this, Vector2(0,0), mPieceWidth, mPieceHeight, ColliderLayer::PIECE);
        break;
    case 'Z':
        mPieceWidth = PIECE_Z_WIDTH;
        mPieceHeight = PIECE_Z_HEIGHT;
        new DrawSpriteComponent(this, "../Assets/Sprite/Pieces/Z.png", mPieceWidth, mPieceHeight, 10);
        mAABBColliderComponent = new AABBColliderComponent(this, Vector2(0,0), mPieceWidth, mPieceHeight, ColliderLayer::PIECE);
        break;
    /* BLUE */
    case 'I':
        mPieceWidth = PIECE_I_WIDTH;
        mPieceHeight = PIECE_I_HEIGHT;
        new DrawSpriteComponent(this, "../Assets/Sprite/Pieces/I.png", mPieceWidth, mPieceHeight, 10);
        mAABBColliderComponent = new AABBColliderComponent(this, Vector2(0,0), mPieceWidth, mPieceHeight, ColliderLayer::PIECE);
        break;
    case 'b':
        mPieceWidth = PIECE_b_WIDTH;
        mPieceHeight = PIECE_b_HEIGHT;
        new DrawSpriteComponent(this, "../Assets/Sprite/Pieces/b.png", mPieceWidth, mPieceHeight, 10);
        mAABBColliderComponent = new AABBColliderComponent(this, Vector2(0,0), mPieceWidth, mPieceHeight, ColliderLayer::PIECE);
        break;
    /* GREEN */
    case 'c':
        mPieceWidth = PIECE_c_WIDTH;
        mPieceHeight = PIECE_c_HEIGHT;
        new DrawSpriteComponent(this, "../Assets/Sprite/Pieces/c.png", mPieceWidth, mPieceHeight, 10);
        mAABBColliderComponent = new AABBColliderComponent(this, Vector2(0,0), mPieceWidth, mPieceHeight, ColliderLayer::PIECE);
        break;
    case 'T':
        mPieceWidth = PIECE_T_WIDTH;
        mPieceHeight = PIECE_T_HEIGHT;
        new DrawSpriteComponent(this, "../Assets/Sprite/Pieces/T.png", mPieceWidth, mPieceHeight, 10);
        mAABBColliderComponent = new AABBColliderComponent(this, Vector2(0,0), mPieceWidth, mPieceHeight, ColliderLayer::PIECE);
        break;
    /* YELLOW */
    case 'f':
        mPieceWidth = PIECE_f_WIDTH;
        mPieceHeight = PIECE_f_HEIGHT;
        new DrawSpriteComponent(this, "../Assets/Sprite/Pieces/f.png", mPieceWidth, mPieceHeight, 10);
        mAABBColliderComponent = new AABBColliderComponent(this, Vector2(0,0), mPieceWidth, mPieceHeight, ColliderLayer::PIECE);
        break;
    case 'i':
        mPieceWidth = PIECE_i_WIDTH;
        mPieceHeight = PIECE_i_HEIGHT;
        new DrawSpriteComponent(this, "../Assets/Sprite/Pieces/i.png", mPieceWidth, mPieceHeight, 10);
        mAABBColliderComponent = new AABBColliderComponent(this, Vector2(0,0), mPieceWidth, mPieceHeight, ColliderLayer::PIECE);
        break;

    default: /* simple block */

        mPieceWidth  = BLOCK_SIZE;
        mPieceHeight = BLOCK_SIZE;

        std::string spritesheet = "../Assets/Sprite/NodeDebug/DebugSpriteSheet.jpg";
        std::string spritedata  = "../Assets/Sprite/NodeDebug/DebugSpriteSheet.json";

        mDrawComponent = new DrawAnimatedComponent(this, spritesheet, spritedata, mIsEnabled ? 9 : 0);
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
    
    /* calculate the next position */
    Vector2 NewPos = CurrPos + UnitVec*BLOCK_SIZE;
    
    /* Check if the player wants to go to the adjacent table */
    if(CurrPos.x + mPieceWidth == BOARD_WIDTH*BLOCK_SIZE+BOARD_ORIGIN_X && UnitVec.x > 0){
        SetPosition(Vector2(STASH_ORIGIN_X, STASH_ORIGIN_Y));
        return;
    }
    else if(CurrPos.x == STASH_ORIGIN_X && UnitVec.x < 0){
        SetPosition(Vector2(BOARD_WIDTH*BLOCK_SIZE+BOARD_ORIGIN_X-mPieceWidth, BOARD_ORIGIN_Y));
        return;
    }

    /* calculate the limit with based on the current table */
    const Table *table = mGame->IsOnBoard(CurrPos.x) ? mGame->GetBoard() : mGame->GetStash();
    Vector2 TablePos = table->GetPosition();
    int TableHeight = ((int)table->GetTableHeight()-1) * BLOCK_SIZE;
    int TableWidth  = ((int)table->GetTableWidth() -1) * BLOCK_SIZE;
    
    /* limitates the player into the table */
    NewPos.x = Math::Clamp((int)NewPos.x, (int)TablePos.x, TableWidth + (int)TablePos.x - mPieceWidth  + BLOCK_SIZE);
    NewPos.y = Math::Clamp((int)NewPos.y, (int)TablePos.y, TableHeight+ (int)TablePos.y - mPieceHeight + BLOCK_SIZE);
    
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
 
    for(auto res : responses){ /* also check for pegs */
        if(res->GetComponent<AABBColliderComponent>()->GetLayer() == ColliderLayer::PIECE)
            return;
    }

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