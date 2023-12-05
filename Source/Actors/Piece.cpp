#include "../Utils/Parser.h"
#include "Piece.h"
#include "Table.h"
#include "Block.h"
#include "Cursor.h"
#include "Peg.h"
#include <map>

#define RED_L 0x0
#define RED_Z 0x1

#define GREEN_c 0x2
#define GREEN_T 0x3

#define BLUE_b 0x4
#define BLUE_I 0x5

#define YELLOW_i 0x6
#define YELLOW_f 0x7

#define PEG 0x9

static const std::map<char, int> CharToIndex = {
    {'L',RED_L},
    {'Z',RED_Z},
    {'c',GREEN_c},
    {'T',GREEN_T},
    {'b',BLUE_b},
    {'I',BLUE_I},
    {'i',YELLOW_i},
    {'f',YELLOW_f},
    {'P',PEG},
};


static const std::map<char, Vector2> PieceDim = {
    {'L' , Vector2(64,96)},
    {'Z' , Vector2(64,96)},
    {'c' , Vector2(64,64)},
    {'T' , Vector2(96,64)},
    {'b' , Vector2(64,96)},
    {'I' , Vector2(32,128)},
    {'i' , Vector2(32,96)},
    {'f' , Vector2(96,96)},
    {'P' , Vector2(32,32)}
};

static const std::vector<Vector3> offset = {
    Vector3(0,0,true),
    Vector3(0,32,false),
    Vector3(0,64,true),
    Vector3(32,64,false)
};

Piece::Piece(InterfaceGame *game, float x, float y, char PieceType, float rotation, bool flip):
    Actor(game),
    mCanProcessInput(false),
    mPieceType(PieceType),
    mIsEnabled(false),
    mCanPlace(false),
    mAABBColliderComponent(nullptr),
    mDrawSpriteComponent(nullptr),
    mDrawPolygonComponent(nullptr),
    mDrawComponent(nullptr)
{
    /* piece start position */
    SetPosition(Vector2(x,y));

    /* Load Piece Components */
    if(PieceType != char()){ /* if not a block */

        parser::LoadPiece(this, mColliders, mDrawPolygons, rotation);

    }
}

void Piece::Move(const Vector2&UnitVec){

    Vector2 CurrPos = GetPosition();
    /* calculate the next position */
    Vector2 NewPos = CurrPos + UnitVec*BLOCK_SIZE;
    SetPosition(NewPos);
}

void Piece::Rotate(float theta){
    
    int i=0;
    for(auto collider : mColliders){
        
        Vector2 offset = collider->GetOffset();
        double x = offset.x;
        double y = offset.y;
        
        if(theta < 0){
            RotateClockWise(x,y,0,0,90.0f);
        }
        else{
            RotateCounterClockWise(x,y,0,0,90.0f);
        }

        collider->SetOffset(Vector2(x,y));
        mDrawPolygons[i++]->SetVertices(Vector2(x,y));
    }

    SetRotation( GetRotation() - theta );
}

void Piece::Flip(){
    SetFlip(!mFlip);
}

void Piece::OnUpdate(float DeltaTime){
    mCanProcessInput = IsEnabled() ? !mGame->GetAction() : false;

    if(IsEnabled()){
        /* check wall collision */
        std::vector<AABBColliderComponent*> other;
        for(Wall *wall : mGame->GetWalls()){
            other.push_back( wall->GetComponent<AABBColliderComponent>() );
        }
        for(AABBColliderComponent *collider : mColliders)
            collider->DetectCollision(other);
    }
}

void Piece::OnProcessInput(const Uint8 *KeyState){
    if(!IsEnabled() || !mCanProcessInput)
        return;
    if(KeyState[SDL_SCANCODE_W])
        Move(Vector2::NegUnitY);
    else if(KeyState[SDL_SCANCODE_A])
        Move(Vector2::NegUnitX);
    else if(KeyState[SDL_SCANCODE_S])
        Move(Vector2::UnitY);
    else if(KeyState[SDL_SCANCODE_D])
        Move(Vector2::UnitX);
    else if(KeyState[SDL_SCANCODE_E])
        Rotate(90.0f);
    else if(KeyState[SDL_SCANCODE_Q])
        Rotate(-90.0f);
    else if(KeyState[SDL_SCANCODE_F])
        Flip();
    else if(KeyState[SDL_SCANCODE_SPACE])
        Place();
}

void Piece::Place(){

    std::vector<AABBColliderComponent*> other;

    for(Piece *piece : mGame->GetBoard()->GetPieces()){
        other.push_back( piece->GetComponent<AABBColliderComponent>() );
    }
    for(Piece *piece : mGame->GetStash()->GetPieces()){
        other.push_back( piece->GetComponent<AABBColliderComponent>() );
    }
    for(Peg *peg : mGame->GetBoard()->GetPegs()){
        other.push_back( peg->GetComponent<AABBColliderComponent>() );
    }
    
    /* check collision for piece multiple colliders */
    for(AABBColliderComponent *collider : mColliders){
        collider->DetectCollision(other);
        if(mCanPlace == false) /* if at least one collided, break */ 
            break;
    }

    if(mCanPlace){
        Cursor *cursor = mGame->GetCursor();
        cursor->Enable();
        cursor->SetPosition(GetPosition());
        this->Disable();
    }
}

 void Piece::OnCollision(const std::vector<Actor*>&responses){
    mCanPlace = responses.empty() ? true : false;
}

void Piece::RotateCounterClockWise(double& x, double& y, double cx, double cy, double theta){
    x -= cx;
    y -= cy;
    double radianTheta = theta * M_PI / 180.0;
    int newX = x*(int)cos(radianTheta)+y*(int)sin(radianTheta);
    int newY = -x*(int)sin(radianTheta)+y*(int)cos(radianTheta);
    x = newX + cx;
    y = newY + cy;
}

void Piece::RotateClockWise(double& x, double& y, double cx, double cy, double theta){
    x -= cx;
    y -= cy;
    double radianTheta = theta * M_PI / 180.0;
    int newX = x*(int)cos(radianTheta)-y*(int)sin(radianTheta);
    int newY = x*(int)sin(radianTheta)+y*(int)cos(radianTheta);
    x = newX + cx;
    y = newY + cy;
}

int Piece::ToIndex() const{
    auto it = CharToIndex.find(mPieceType);
    return it->second;
}