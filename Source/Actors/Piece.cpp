#include "../Utils/Parser.h"
#include "../Utils/Random.h"
#include "../Utils/AudioSystem.h"

#include "Piece.h"
#include "Table.h"
#include "Block.h"
#include "Cursor.h"
#include "Peg.h"

#define SFX_ROTATE 0
#define SFX_PLACE 1

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
    /* Load Piece Components */
    if(PieceType != char()){ /* if not a block */
        parser::LoadPiece(this, mColliders, mDrawPolygons);
        for(int i=0; i < abs(rotation); i+=PIECE_ROTATION_ANGLE){
            this->Rotate(PIECE_ROTATION_ANGLE);
        }
        if(flip){
            this->Flip();
        }
    }
    /* piece start position */
    this->SetPosition(Vector2(x,y));
    this->UpdatePreviousState();
}

/* piece actions */
void Piece::Move(const Vector2&UnitVec){

    mGame->GetAudio()->PlaySound("Cursor.wav");

    Vector2 CurrPos = GetPosition();
    
    /* find piece left/right corner */
    float LeftCorner  = CurrPos.x;
    float RightCorner = CurrPos.x+BLOCK_SIZE;
    for(AABBColliderComponent *collider : mColliders){
        LeftCorner  = Math::Min<float>(LeftCorner, collider->GetMin().x);
        RightCorner = Math::Max<float>(RightCorner, collider->GetMax().x);
    }

    /* Move player */
    Vector2 NewPos = CurrPos + UnitVec*BLOCK_SIZE;
    if( mGame->IsOnBoard(CurrPos) && IsMovingToStash(UnitVec, LeftCorner) ){
        NewPos = Vector2(STASH_ORIGIN_X, NewPos.y);
    } 
    else if( !mGame->IsOnBoard(CurrPos) && IsMovingToBoard(UnitVec, RightCorner) ){
        NewPos = Vector2(
            BOARD_ORIGIN_X+(BOARD_WIDTH-1)*BLOCK_SIZE,
            (int)(NewPos.y)%(BOARD_HEIGHT*BLOCK_SIZE)+BOARD_ORIGIN_Y
        );
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
        // mDrawPolygons[i++]->SetVertices(Vector2(x,y));
    }
    
    /* update current width/height */
    std::swap(mWidth, mHeight);

    float NewRotation = (int)(GetRotation() - theta) % 360;
    SetRotation( (int)(GetRotation() - theta) % 360 );
}

void Piece::Place(){

    if( DetectCollision() ){
        return;
    }

    Vector2 CurrPos = this->GetPosition();

    Cursor *cursor = mGame->GetCursor();
    cursor->Enable();
    cursor->SetPosition(CurrPos);
    cursor->GetComponent<DrawAnimatedComponent>()->SetComponentState(true);

    this->Disable();
    this->UpdatePreviousState();

    /* update current board state */
    if( mGame->IsOnBoard(CurrPos) ){
        
        mGame->GetStash()->RemovePiece(this);
        mGame->GetBoard()->AddPiece(this);

        /* END GAME IF LEVEL IS COMPLETED */
        if( mGame->IsLevelComplete() ){
            mGame->Quit();
        }

    } else{

        mGame->GetStash()->AddPiece(this);
        mGame->GetBoard()->RemovePiece(this);
    }

}

void Piece::Flip(){
    
    int i = 0;
    int theta = mRotation;

    for(AABBColliderComponent *collider : mColliders){

        Vector2 offset = collider->GetOffset();
        float x = offset.x;
        float y = offset.y;

        switch (theta)
        {
        case 0:
            x = -x + mWidth - BLOCK_SIZE;
            break;
        case 90:
            y = -y + mHeight - BLOCK_SIZE;
            break;
        case -90:
            y = -y - mHeight + BLOCK_SIZE;
            break;
        case 180:
        case -180:
            x = -x - mWidth + BLOCK_SIZE;
            break;
        case 270:
            y = -y - mHeight + BLOCK_SIZE;
            break;
        case -270:
            y = -y + mHeight - BLOCK_SIZE;
            break;
        default:
            break;
        }

        collider->SetOffset(Vector2(x,y));
        // mDrawPolygons[i++]->SetVertices(Vector2(x,y));
    }

    SetFlip(!mFlip);
}

void Piece::Cancel(){

    while(!mUndoStack.empty()){
        int move = mUndoStack.top();
        mUndoStack.pop();

        if(move == PIECE_ROTATION_ANGLE){
            Rotate(-PIECE_ROTATION_ANGLE);
        } else if(move == -PIECE_ROTATION_ANGLE){
            Rotate(PIECE_ROTATION_ANGLE);
        } else if(move == 1){
            Flip();
        }
    }

    SetPosition(mPreviousPos);
    Place();
}

void Piece::OnCollision(Actor *response){
    mCanPlace = response != nullptr ? false : true;
}

void Piece::OnProcessInput(const Uint8 *KeyState){

    if(!IsEnabled() || !mCanProcessInput)
        return;

    if(KeyState[SDL_SCANCODE_W]){
        Move(Vector2::NegUnitY);
    }
    else if(KeyState[SDL_SCANCODE_A]){
        Move(Vector2::NegUnitX);
    }
    else if(KeyState[SDL_SCANCODE_S]){
        Move(Vector2::UnitY);
    }
    else if(KeyState[SDL_SCANCODE_D]){
        Move(Vector2::UnitX);
    }
    else if(KeyState[SDL_SCANCODE_E]){
        mGame->GetAudio()->PlaySound("Rotate.wav");
        mUndoStack.push(PIECE_ROTATION_ANGLE);
        Rotate(PIECE_ROTATION_ANGLE);
    }
    else if(KeyState[SDL_SCANCODE_Q]){
        mGame->GetAudio()->PlaySound("Rotate.wav");
        mUndoStack.push(-PIECE_ROTATION_ANGLE);
        Rotate(-PIECE_ROTATION_ANGLE);
    }
    else if(KeyState[SDL_SCANCODE_F]){
        mGame->GetAudio()->PlaySound("Flip.wav");
        mUndoStack.push(1);
        Flip();
    }
    else if(KeyState[SDL_SCANCODE_SPACE]){

        Place();
        if(mCanPlace){
            mGame->GetAudio()->PlaySound("Decide.wav");
        }

    } else if(KeyState[SDL_SCANCODE_ESCAPE]){
        mGame->GetAudio()->PlaySound("Cancel.wav");
        Cancel();
    }
}

void Piece::OnUpdate(float DeltaTime){
    if( this->IsEnabled() ){
        mCanProcessInput = !mGame->GetAction();
        this->DetectWall();
    } else{
        mCanProcessInput = false;
    }
}

void Piece::DetectWall(){
    std::vector<AABBColliderComponent*> other;
    for(Wall *wall : mGame->GetWalls()){
        other.push_back( wall->GetComponent<AABBColliderComponent>() );
    }
    for(AABBColliderComponent *collider : mColliders)
        collider->DetectCollision(other);
}

bool Piece::DetectCollision(){
    
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
        /* if at least one collided */ 
        if(mCanPlace == false){
            return true;
        } 
    }
    return false;
}

const std::vector<AABBColliderComponent*> &Piece::GetColliders() const{
    return mColliders;
}

char Piece::GetPieceType() const {
    return mPieceType; 
}

/* return piece index of the piece type */
int Piece::ToIndex(const char PieceType){
    auto it = PieceToIndex.find(PieceType);
    return it->second;
}

/* mIsEnabled state makes the piece freeze or move */
void Piece::Disable(){ 
    mIsEnabled = false; 
}

void Piece::Enable(){
    UpdatePreviousState();
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

bool Piece::IsMovingToStash(const Vector2 &dir, const float pos) const{
    return pos + (dir*mWidth).x >= BLOCK_SIZE*BOARD_WIDTH+BOARD_ORIGIN_X;
}

bool Piece::IsMovingToBoard(const Vector2 &dir, const float pos) const{
    return pos + (dir*mWidth).x <= STASH_ORIGIN_X;
}

void Piece::UpdatePreviousState(){
    mPreviousPos = GetPosition();
    /* remove every movement */
    while(!mUndoStack.empty())
        mUndoStack.pop();
}