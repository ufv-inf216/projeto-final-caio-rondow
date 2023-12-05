#include "../Utils/Parser.h"
#include "Piece.h"
#include "Table.h"
#include "Block.h"
#include "Cursor.h"
#include "Peg.h"

Piece::Piece(InterfaceGame *game, float x, float y, char PieceType, float rotation, bool flip):
    Actor(game),
    mDrawSpriteComponent(nullptr),
    mCanProcessInput(false),
    mPieceType(PieceType),
    mIsEnabled(false),
    mCanPlace(false),
    mWidth(BLOCK_SIZE), 
    mHeight(BLOCK_SIZE)
{
    /* piece start position */
    SetPosition(Vector2(x,y));

    /* Load Piece Components */
    if(PieceType != char()){ /* if not a block */
        parser::LoadPiece(this, mColliders, mDrawPolygons, rotation);
    }
}

/* piece actions */
void Piece::Move(const Vector2&UnitVec){

    Vector2 CurrPos = GetPosition();
    /* calculate the next position */
    Vector2 NewPos = CurrPos + UnitVec*BLOCK_SIZE;
    SetPosition(NewPos);
}

void Piece::Rotate(float theta){
    
    /* no rotation case */
    if(theta == 0.0f)
        return;

    int i = 0;
    for(AABBColliderComponent *collider : mColliders){
        
        Vector2 offset = collider->GetOffset();
        double x = offset.x;
        double y = offset.y;
        
        /* calculate collider new position */
        RotateCounterClockWise(x,y,0,0,theta);
  
        /* update collider */
        collider->SetOffset(Vector2(x,y));
        mDrawPolygons[i++]->SetVertices(Vector2(x,y));
    }

    /* update current width/height */
    std::swap(mWidth, mHeight);

    float NewRotation = (int)(GetRotation() - theta) % 360;
    SetRotation(NewRotation);
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
        Vector2 PiecePos = this->GetPosition();
        cursor->Enable();
        cursor->SetPosition(PiecePos);
        this->Disable();
    }
}

void Piece::Flip(){
    SetFlip(!mFlip);
}

void Piece::OnCollision(const std::vector<Actor*>&responses){
    mCanPlace = responses.empty() ? true : false;
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
        Rotate(PIECE_ROTATION_ANGLE);
    else if(KeyState[SDL_SCANCODE_Q])
        Rotate(-PIECE_ROTATION_ANGLE);
    else if(KeyState[SDL_SCANCODE_F])
        Flip();
    else if(KeyState[SDL_SCANCODE_SPACE])
        Place();
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

const std::vector<AABBColliderComponent*> &Piece::GetColliders() const{
    return mColliders;
}

char Piece::GetPieceType() const {
    return mPieceType; 
}

/* return piece index of the piece type */
int Piece::ToIndex() const{
    auto it = PieceToIndex.find(mPieceType);
    return it->second;
}

/* mIsEnabled state makes the piece freeze or move */
void Piece::Disable(){ 
    mIsEnabled = false; 
}

void Piece::Enable(){ 
    mIsEnabled = true; 
}

bool Piece::IsEnabled() const{ 
    return mIsEnabled; 
}

void Piece::SetWidth(const uint width){
    mWidth = width;
}

uint Piece::GetWidth() const{
    return mWidth;
}

void Piece::SetHeight(const uint height){
    mHeight = height;
}

uint Piece::GetHeight() const{
    return mHeight;
}

/* Change collider based on rotation and flip */
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