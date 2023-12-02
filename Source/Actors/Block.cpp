#include "Block.h"
#include "Table.h"
#include "../Components/DrawComponents/DrawAnimatedComponent.h"
#include "../Components/DrawComponents/DrawPolygonComponent.h"

Block::Block(InterfaceGame *game, float x, float y, bool enable, ColliderLayer layer, uint CollisorWidth, uint CollisorHeight):
    Piece(game, x, y)
{
    mIsEnabled = enable;
    std::string spritesheet = "../Assets/Sprite/NodeDebug/DebugSpriteSheet.jpg";
    std::string spritedata  = "../Assets/Sprite/NodeDebug/DebugSpriteSheet.json";

    mDrawComponent = new DrawAnimatedComponent(this, spritesheet, spritedata, mIsEnabled ? 9 : 0);
    mDrawComponent->AddAnimation("idle", {0});
    mDrawComponent->AddAnimation("cursor", {1});
    mDrawComponent->SetAnimation( IsEnabled() ? "cursor" : "idle" );
    mDrawComponent->SetAnimationFPS(1);

    mAABBColliderComponent = new AABBColliderComponent(this, Vector2(0,0), CollisorWidth, CollisorHeight, layer);
    
    /* WALL COLLIDER - DEBUG ONLY */
    if(layer == ColliderLayer::WALL){
    
        std::vector<Vector2> vertices;
        vertices.push_back(Vector2(0,0));
        vertices.push_back(Vector2(CollisorWidth,0));
        vertices.push_back(Vector2(CollisorWidth,CollisorHeight));
        vertices.push_back(Vector2(0,CollisorHeight));
        mDrawPolygonComponent = new DrawPolygonComponent(this, vertices);
    }
    /* WALL COLLIDER - DEBUG ONLY */
    
}

void Block::OnUpdate(float DeltaTime){
    if(IsEnabled()){
        mCanProcessInput = !mGame->GetAction();
        mDrawComponent->SetAnimation("cursor");
        /* check if is for walls */
        std::vector<AABBColliderComponent*> colliders;
        for(auto wall : mGame->GetWalls()){
            colliders.push_back( wall->GetComponent<AABBColliderComponent>() );
        }
        mAABBColliderComponent->DetectCollision(colliders);
    } else{
        mCanProcessInput = false;
        mDrawComponent->SetAnimation("idle");
    }
}

void Block::OnProcessInput(const Uint8 *KeyState){
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
        Grab();
}

void Block::OnCollision(const std::vector<Actor*>&responses){
    if(responses.empty())
        return;
    Block *cursor = mGame->GetCursor();
    cursor->Disable();
    static_cast<Piece*>(responses[0])->Enable();
}

void Block::Grab(){
    std::vector<AABBColliderComponent*> colliders;

    for(auto piece : mGame->GetBoard()->GetPieces()){
        colliders.push_back( piece->GetComponent<AABBColliderComponent>() );
    }

    for(auto piece : mGame->GetStash()->GetPieces()){
        colliders.push_back( piece->GetComponent<AABBColliderComponent>() );
    }
    
    this->GetComponent<AABBColliderComponent>()->DetectCollision(colliders);
}