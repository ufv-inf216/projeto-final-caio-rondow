#include "../Utils/Parser.h"
#include "Piece.h"
#include "Table.h"
#include "Block.h"
#include <map>


static const std::map<char, Vector2> PieceDim = {
    {'L' , Vector2(64,96)},
    {'Z' , Vector2(64,96)},
    {'I' , Vector2(32,128)},
    {'b' , Vector2(64,96)},
    {'c' , Vector2(64,64)},
    {'T' , Vector2(96,64)},
    {'f' , Vector2(96,96)},
    {'i' , Vector2(32,96)}
}; 

Piece::Piece(InterfaceGame *game, float x, float y, char PieceType, float rotation, bool flip):
    Actor(game),
    mCanProcessInput(false),
    mPieceType(PieceType),
    mIsEnabled(false),
    mAABBColliderComponent(nullptr),
    mDrawSpriteComponent(nullptr),
    mDrawPolygonComponent(nullptr),
    mDrawComponent(nullptr)
{
    SetPosition(Vector2(x,y));

    /* Load Piece Components */
    if(PieceType != char()){ /* if not a block */

        auto it = PieceDim.find(PieceType);
        if(it == PieceDim.end()){
            std::cerr << "Invalid type of piece : " << PieceType << "\n";
            std::cerr << "valid types are: L,Z,I,b,c,T,f,i\n";
            exit(EXIT_FAILURE);
        }

        this->SetWidth(PieceDim.at(PieceType).x);
        this->SetHeight(PieceDim.at(PieceType).y);
   
        std::cout << mWidth << " " << mHeight << "\n";
        /* Ajust piece */
        this->Rotate(rotation);

        uint width  = this->GetWidth();
        uint height = this->GetHeight();
        std::cout << mWidth << " " << mHeight << "\n";

        std::string PieceTexture = "../Assets/Sprite/Pieces/" + std::string(1,PieceType) + ".png";

        std::cout << PieceTexture << "\n";

        /* PIECE COLLIDER - DEBUG ONLY */
        std::vector<Vector2> vertices;
        vertices.push_back(Vector2(0,0));
        vertices.push_back(Vector2(width,0));
        vertices.push_back(Vector2(width,height));
        vertices.push_back(Vector2(0,height));
        /* PIECE COLLIDER - DEBUG ONLY */

        mAABBColliderComponent = new AABBColliderComponent(this, Vector2(0,0), width, height, ColliderLayer::PIECE);
        mDrawSpriteComponent   = new DrawSpriteComponent(this, PieceTexture, width, height, 10);
        mDrawPolygonComponent  = new DrawPolygonComponent(this, vertices);

        mDrawPolygonComponent->SetColor(255,0,0,255);
    }
}

void Piece::Move(const Vector2&UnitVec){
    Vector2 CurrPos = GetPosition();
    /* calculate the next position */
    Vector2 NewPos = CurrPos + UnitVec*BLOCK_SIZE;
    SetPosition(NewPos);
}

void Piece::Rotate(float theta){
    SetRotation( GetRotation() - theta );
}

void Piece::Flip(){
    SetFlip(!mFlip);
}

void Piece::OnUpdate(float DeltaTime){

    if(IsEnabled()){
        mCanProcessInput = !mGame->GetAction();
        /* check if is for walls */
        std::vector<AABBColliderComponent*> colliders;
        for(auto wall : mGame->GetWalls()){
            colliders.push_back( wall->GetComponent<AABBColliderComponent>() );
        }
        mAABBColliderComponent->DetectCollision(colliders);
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

    std::vector<AABBColliderComponent*> colliders;

    for(auto piece : mGame->GetBoard()->GetPieces()){
        colliders.push_back( piece->GetComponent<AABBColliderComponent>() );
    }
    for(auto piece : mGame->GetStash()->GetPieces()){
        colliders.push_back( piece->GetComponent<AABBColliderComponent>() );
    }
    for(auto block : mGame->GetBoard()->GetBlocks()){
        colliders.push_back( block->GetComponent<AABBColliderComponent>() );
    }
    for(auto block : mGame->GetStash()->GetBlocks()){
        colliders.push_back( block->GetComponent<AABBColliderComponent>() );
    }

    /* ATENTION! Also need to test collision with pegs */  
    
    this->GetComponent<AABBColliderComponent>()->DetectCollision(colliders);
}

 void Piece::OnCollision(const std::vector<Actor*>&responses){

    if(responses.empty())
        return;

    for(auto res : responses){ /* also check for pegs */
        if(res->GetComponent<AABBColliderComponent>()->GetLayer() == ColliderLayer::PIECE)
            return;
    }
    Block *cursor = mGame->GetCursor();
    cursor->Enable();
    cursor->SetPosition(GetPosition());
    this->Disable();
}