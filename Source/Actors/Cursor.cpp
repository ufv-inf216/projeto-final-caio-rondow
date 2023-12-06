#include "Cursor.h"
#include "Table.h"
#include "Wall.h"
#include "../Components/DrawComponents/DrawAnimatedComponent.h"
#include "../Components/DrawComponents/DrawPolygonComponent.h"

Cursor::Cursor(InterfaceGame *game, float x, float y, bool enable):
    Block(game, x, y, enable)
{
    std::string SpriteSheet = "../Assets/Sprite/Table/table.png";
    std::string SpriteData  = "../Assets/Sprite/Table/table.json";

    mDrawAnimComponent = new DrawAnimatedComponent(this, SpriteSheet, SpriteData, CURSOR_DRAW_ORDER);
    mDrawAnimComponent->AddAnimation("idle", {0});
    mDrawAnimComponent->AddAnimation("cursor", {1});
    mDrawAnimComponent->SetAnimation("cursor");
    mDrawAnimComponent->SetAnimationFPS(1);

    mAABBColliderComponent = new AABBColliderComponent(
        this, Vector2(0,0), BLOCK_SIZE, BLOCK_SIZE, ColliderLayer::BLOCK,
        CURSOR_UPDATE_ORDER    
    );
}

void Cursor::OnUpdate(float DeltaTime){
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
    mDrawAnimComponent->SetComponentState(false);
    
    Piece *piece = static_cast<Piece*>(responses[0]);
    piece->Enable();
    /* put piece at upper layer */
    mGame->DrawLast(piece->GetComponent<DrawSpriteComponent>());

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