#include "../Utils/Parser.h"
#include "../Utils/AudioSystem.h"
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
        // mDrawPolygons[i++]->SetVertices(Vector2(x,y));
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

        Cursor *cursor = mGame->GetCursor();
        cursor->Enable();
        cursor->SetPosition(PiecePos);
        cursor->GetComponent<DrawAnimatedComponent>()->SetComponentState(DRAWABLE_STATE_VISIBLE);

        this->Disable();
        this->UpdatePreviousState();

        std::string sound = rand()%2 <= 0.5 ? "SW_PUSH2.WAV" : "SW_PUSH3.WAV";  
        mGame->GetAudio()->PlaySound(sound);

        /* update current board state */
        if(mGame->IsOnBoard(PiecePos)){
            
            mGame->GetStash()->RemovePiece(this);
            mGame->GetBoard()->AddPiece(this);
            
            mCurrentTable = PieceTable::BOARD;

            /* FOR NOW, IF LEVEL IS COMPLETED
            SHUT DOWN THE GAME */
            if( mGame->IsLevelComplete() ){
                mGame->Quit();
            }

        } else{
            mCurrentTable = PieceTable::STASH;
            mGame->GetStash()->AddPiece(this);
            mGame->GetBoard()->RemovePiece(this);
        }
    }
}

void Piece::Flip(){
    int i = 0;
    for(AABBColliderComponent *collider : mColliders){

        Vector2 offset = collider->GetOffset();
        float x = offset.x;
        float y = offset.y;

        int theta = abs(mRotation);
        if(theta == 0)
            x = -x + mWidth - BLOCK_SIZE;
        else if(theta == 90){
            y = -y - mHeight + BLOCK_SIZE;
        } else if(theta == 180){
            x = -x - mWidth + BLOCK_SIZE;
        } else {
            y = -y + mHeight - BLOCK_SIZE;
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

void Piece::OnCollision(const std::vector<Actor*>&responses){
    mCanPlace = responses.empty() ? true : false;
}

void Piece::OnProcessInput(const Uint8 *KeyState){

    if(!IsEnabled() || !mCanProcessInput)
        return;

    if(KeyState[SDL_SCANCODE_W]){
        mGame->GetAudio()->PlaySound("SL_CLICK.WAV");
        Move(Vector2::NegUnitY);
    }
    else if(KeyState[SDL_SCANCODE_A]){
        mGame->GetAudio()->PlaySound("SL_CLICK.WAV");
        Move(Vector2::NegUnitX);
    }
    else if(KeyState[SDL_SCANCODE_S]){
        mGame->GetAudio()->PlaySound("SL_CLICK.WAV");
        Move(Vector2::UnitY);
    }
    else if(KeyState[SDL_SCANCODE_D]){
        mGame->GetAudio()->PlaySound("SL_CLICK.WAV");
        Move(Vector2::UnitX);
    }
    else if(KeyState[SDL_SCANCODE_E]){
        mUndoStack.push(PIECE_ROTATION_ANGLE);
        Rotate(PIECE_ROTATION_ANGLE);
    }
    else if(KeyState[SDL_SCANCODE_Q]){
        mUndoStack.push(-PIECE_ROTATION_ANGLE);
        Rotate(-PIECE_ROTATION_ANGLE);
    }
    else if(KeyState[SDL_SCANCODE_F]){
        mUndoStack.push(1);
        Flip();
    }
    else if(KeyState[SDL_SCANCODE_SPACE]){

        Place();
    } else if(KeyState[SDL_SCANCODE_ESCAPE]){
        Cancel();
    }
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

void Piece::UpdatePreviousState(){
    mPreviousPos = GetPosition();
    /* remove every movement */
    while(!mUndoStack.empty())
        mUndoStack.pop();
}