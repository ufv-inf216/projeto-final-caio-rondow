#include "Cursor.h"
#include "Table.h"
#include "Wall.h"
#include "../Components/DrawComponents/DrawAnimatedComponent.h"
#include "../Components/DrawComponents/DrawPolygonComponent.h"
#include "../Utils/AudioSystem.h"

Cursor::Cursor(InterfaceGame *game, float x, float y, bool enable):
    Block(game),
    mOnHand(nullptr)
{
    SetPosition(Vector2(x,y));
    mIsEnabled = enable;

    std::string TextureFile = "../Assets/Sprite/Table/cursor.png";
    mHighlight = new DrawSpriteComponent(this,TextureFile,BLOCK_SIZE,BLOCK_SIZE,CURSOR_DRAW_LAYER);

    AABBColliderComponent *collider = new AABBColliderComponent(
        this, Vector2(0,0), BLOCK_SIZE, BLOCK_SIZE, ColliderLayer::BLOCK,
        CURSOR_UPDATE_ORDER    
    );
    mColliders.emplace_back(collider);
}

void Cursor::OnUpdate(float DeltaTime){
    if( IsEnabled() ){

        mCanProcessInput = !mGame->GetAction();
        mOnHand = nullptr;
        
        /* check if is for walls */
        DetectWall();
        
    } else{
        mCanProcessInput = false;
    }
}

void Cursor::OnProcessInput(const Uint8 *KeyState){
    if(!IsEnabled() || !mCanProcessInput)
        return;
    if(KeyState[SDL_SCANCODE_W]){
        Move(Vector2::NegUnitY);
    }
    if(KeyState[SDL_SCANCODE_A]){
        Move(Vector2::NegUnitX);
    }
    if(KeyState[SDL_SCANCODE_S]){
        Move(Vector2::UnitY);
    }
    if(KeyState[SDL_SCANCODE_D]){
        Move(Vector2::UnitX);
    }
    if(KeyState[SDL_SCANCODE_SPACE])
        GrabPiece();
}

void Cursor::OnCollision(Actor *response){
    
    if(response == nullptr)
        return;

    this->Disable();
    mHighlight->DisableComponent();
    
    Piece *piece = static_cast<Piece*>(response);
    piece->Enable();
    
    mOnHand = piece;
    
    /* put piece at upper layer */
    mGame->DrawLast(piece->GetComponent<DrawSpriteComponent>());

    mGame->GetAudio()->PlaySound("Decide.wav");
}

const Piece *Cursor::PieceSelected() const{
    return mOnHand;
}

void Cursor::GrabPiece(){

    std::vector<AABBColliderComponent*> other;

    for(auto piece : mGame->GetBoard()->GetPieces()){
        for(auto collider : piece->GetColliders())
            other.push_back(collider);
    }

    for(auto piece : mGame->GetStash()->GetPieces()){
        for(auto collider : piece->GetColliders())
            other.push_back(collider);
    }

    this->GetComponent<AABBColliderComponent>()->DetectCollision(other);
}