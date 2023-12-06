#include "../Utils/Parser.h"
#include "Piece.h"
#include "Table.h"
#include "Block.h"
#include "Cursor.h"
#include "Peg.h"

Piece::Piece(InterfaceGame *game, float x, float y, char PieceType, float rotation, bool flip):
    Actor(game),
    mCurrentTable(PieceTable::BOARD),
    mDrawSpriteComponent(nullptr),
    mCanProcessInput(false),
    mPieceType(PieceType),
    mIsEnabled(false),
    mCanPlace(false),
    mWidth(BLOCK_SIZE), 
    mHeight(BLOCK_SIZE),
    mFront(true)
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
    float CurrRot   = GetRotation();

    /* calculate the next position */
    Vector2 NewPos = CurrPos + UnitVec*BLOCK_SIZE;

    /* Check if the player wants to go to stash
        or to board */
    bool GoToStash = CurrPos.x + mFront*mWidth + !mFront*BLOCK_SIZE == BLOCK_SIZE*BOARD_WIDTH+BOARD_ORIGIN_X;
    bool GoToBoard = CurrPos.x + (!mFront)*(-(int)mWidth+BLOCK_SIZE) == STASH_ORIGIN_X;

    if( UnitVec.x > 0 && GoToStash ){ /* Move to STASH */
        
        while(mRotation != 0){
            Rotate(PIECE_ROTATION_ANGLE);
        }
        NewPos = Vector2(STASH_ORIGIN_X, NewPos.y);
        while(mRotation != CurrRot){
            Rotate(PIECE_ROTATION_ANGLE);
        }
    } 
    else if( UnitVec.x < 0 && GoToBoard ){ /* Move to BOARD */
        
        while(mRotation != 0){
            Rotate(PIECE_ROTATION_ANGLE);
        }
        NewPos = Vector2(
            BOARD_ORIGIN_X+(BOARD_WIDTH-1)*BLOCK_SIZE,
            (int)(NewPos.y)%(BOARD_HEIGHT*BLOCK_SIZE)+BOARD_ORIGIN_Y
        );
        while(mRotation != CurrRot){
            Rotate(PIECE_ROTATION_ANGLE);
        }
    }

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
    
    if(abs(mRotation) == 0 || abs(mRotation) == 90){
        mFront = true;
    } else{
        mFront = false;
    }
}

void Piece::Place(){

    std::vector<AABBColliderComponent*> other;

    for(Piece *piece : mGame->GetBoard()->GetPieces()){
        for(AABBColliderComponent *collider : piece->GetColliders()){
            other.push_back(collider);
        }
    }
    for(Piece *piece : mGame->GetStash()->GetPieces()){
        for(AABBColliderComponent *collider : piece->GetColliders()){
            other.push_back(collider);
        }
    }
    for(Peg *peg : mGame->GetBoard()->GetPegs()){
        other.push_back( peg->GetComponent<AABBColliderComponent>() );
    }
    
    /* check collision for piece multiple colliders */
    for(AABBColliderComponent *collider : mColliders){
        collider->DetectCollision(other);
        /* if at least one collided, break */ 
        if(mCanPlace == false){
            return;
        } 
    }
 
    if(mCanPlace){
        
        Vector2 PiecePos = this->GetPosition();

        /* update current board state */
        if(mGame->IsOnBoard(PiecePos)){
            mCurrentTable = PieceTable::BOARD;
        } else{
            mCurrentTable = PieceTable::STASH;
        }
        
        Cursor *cursor = mGame->GetCursor();
        cursor->Enable();
        cursor->SetPosition(PiecePos);
        this->Disable();

        mGame->IsLevelComplete();
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

void Piece::SetPieceTable(const PieceTable table){
    mCurrentTable = table;
}

PieceTable Piece::GetPieceTable() const{
    return mCurrentTable;
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