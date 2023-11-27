#include "Block.h"
#include "Table.h"
#include "../Components/DrawComponents/DrawAnimatedComponent.h"


Block::Block(InterfaceGame *game, bool enabled, float x, float y, uint xMax, uint yMax):
    Piece(game,enabled, x, y, xMax, yMax)
{
 
}

void Block::OnUpdate(float DeltaTime){
    if(IsEnabled()){
        mCanProcessInput = !mGame->GetAction();
        mDrawComponent->SetAnimation("cursor");
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
        Withdraw();
}

void Block::DetectCollision(){
    
    std::vector<AABBColliderComponent*> colliders;

    for(auto piece : mGame->GetBoard()->GetPieces()){
        colliders.push_back( piece->GetComponent<AABBColliderComponent>() );
    }

    for(auto piece : mGame->GetStash()->GetPieces()){
        colliders.push_back( piece->GetComponent<AABBColliderComponent>() );
    }
    
    this->GetComponent<AABBColliderComponent>()->DetectCollision(colliders);
}

void Block::OnCollision(const std::vector<Actor*>&responses){
    Block *cursor = mGame->GetCursor();
    cursor->Disable();
    responses[0]->Enable();
}

void Block::Withdraw(){
    DetectCollision();
}
