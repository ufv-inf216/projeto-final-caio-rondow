#include "Piece.h"
#include "../Components/DrawComponents/DrawSpriteComponent.h"
#include "../Game/InterfaceGame.h"
#include "Block.h"

Piece::Piece(InterfaceGame *game, char type, const Vector2&origin, float rotation, bool flip):
    Actor(game),
    mType(type),
    mFlip(flip),
    mIsPieceSelected(false),
    mState(PieceState::IDLE)
{
    this->SetActorState(ActorState::ACTIVE);
    this->SetPosition(origin);
    this->SetRotation(rotation);
    mDrawComponent = new DrawSpriteComponent(this, "../Assets/Sprite/L.png", 64, 96, 10);

    switch (type)
    {
    case 'L':

        mColliders.emplace_back(new AABBColliderComponent(this, Vector2(0,0), 32, 96, ColliderLayer::PIECE));
        // mColliders.emplace_back(this, Vector2(0,0), );

        break;
    
    default:
        break;
    }
    
}

void Piece::OnUpdate(float DeltaTime){
    // std::cout << GetPosition().x << " " << GetPosition().y << "\n";   
}

void Piece::DetectCollision(){

    

}

void Piece::OnProcessInput(const Uint8 *KeyState){
    
    Vector2 pos = this->GetPosition();

    if(mIsPieceSelected){

        mColliders[0]->DetectCollision();

        if(KeyState[SDL_SCANCODE_Z]){
            std::cout << "STATE SELECTED: MOVE\n";
            mState = PieceState::MOVE;
            mIsPieceSelected = false;
        } else if(KeyState[SDL_SCANCODE_X]){
            std::cout << "STATE SELECTED: ROTATE\n";
            mState = PieceState::ROTATE;
            mIsPieceSelected = false;
        } else if(KeyState[SDL_SCANCODE_C]){
            std::cout << "STATE SELECTED: FLIP\n";
            mState = PieceState::FLIP;
            mIsPieceSelected = false;
        } else if(KeyState[SDL_SCANCODE_V]){
            std::cout << "STATE SELECTED: IDLE\n";
            mState = PieceState::IDLE;
            mIsPieceSelected = false;
        }
    }

    switch (mState)
    {
    case PieceState::MOVE:
        Move();
        break;
    case PieceState::ROTATE:
        Rotate();
        break;
    case PieceState::FLIP:
        Flip();
        break;
    case PieceState::PLACE:
        Place();
        break;
    default:
        break;
    }
}

/* Piece methods */
void Piece::Rotate(){
    float rotation = GetRotation();
    SetRotation(rotation+90.0f);
    mState = PieceState::IDLE;
}

void Piece::Flip(){
    // std::cout << "Flip\n";
}

void Piece::Move(){
    /* Set piece position equals to the cursor */
    Vector2 CursorPos = mGame->GetCursor()->GetPosition();
    SetPosition(CursorPos - Vector2(16,16));
}

void Piece::Place(){
    // std::cout << "Place\n";
}

void Piece::OnCollision(){
    mIsPieceSelected = true;
}