#include "Cursor.h"
#include "Table.h"
#include "Wall.h"
#include "../Components/DrawComponents/DrawAnimatedComponent.h"
#include "../Components/DrawComponents/DrawPolygonComponent.h"

Cursor::Cursor(InterfaceGame *game, float x, float y, bool enable):
    Block(game, x, y, enable)
{
    std::string SpriteSheet = "../Assets/Sprite/NodeDebug/DebugSpriteSheet.jpg";
    std::string SpriteData  = "../Assets/Sprite/NodeDebug/DebugSpriteSheet.json";

    mDrawAnimComponent = new DrawAnimatedComponent(this, SpriteSheet, SpriteData, (IsEnabled() ? 9 : 0));
    mDrawAnimComponent->AddAnimation("idle", {0});
    mDrawAnimComponent->AddAnimation("cursor", {1});
    mDrawAnimComponent->SetAnimation( IsEnabled() ? "cursor" : "idle" );
    mDrawAnimComponent->SetAnimationFPS(1);

    mAABBColliderComponent = new AABBColliderComponent(this, Vector2(0,0), BLOCK_SIZE, BLOCK_SIZE, ColliderLayer::BLOCK);
}

void Cursor::OnUpdate(float DeltaTime){
    if(IsEnabled()){
        mCanProcessInput = !mGame->GetAction();
        mDrawAnimComponent->SetAnimation("cursor");
        
        /* check if is for walls */
        std::vector<AABBColliderComponent*> colliders;
        for(auto wall : mGame->GetWalls()){
            colliders.push_back( wall->GetComponent<AABBColliderComponent>() );
        }
        mAABBColliderComponent->DetectCollision(colliders);
        
    } else{
        mCanProcessInput = false;
        mDrawAnimComponent->SetAnimation("idle");
    }
}

void Cursor::OnProcessInput(const Uint8 *KeyState){
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
    if(KeyState[SDL_SCANCODE_SPACE])
        GrabPiece();
}

void Cursor::OnCollision(const std::vector<Actor*>&responses){
    if(responses.empty())
        return;
    this->Disable();
    static_cast<Piece*>(responses[0])->Enable();
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