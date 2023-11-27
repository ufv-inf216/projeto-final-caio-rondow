#include "DrawSpriteComponent.h"
#include "../../Actors/Actor.h"
#include "../../Game/InterfaceGame.h"

/* CONSTRUCTOR */
DrawSpriteComponent::DrawSpriteComponent(Actor *owner, const std::string&TextureFile, int width, int height, int DrawOrder):
    DrawComponent(owner, DrawOrder),
    mWidth(width),
    mHeight(height)
{
    InterfaceGame *game = mOwner->GetGame();
    mSpriteSheetSurface = game->LoadTexture(TextureFile);
}

/* draw sprite */
void DrawSpriteComponent::Draw(SDL_Renderer *renderer){
    
    Vector2 pos = mOwner->GetPosition();
    float angle = mOwner->GetRotation();
    bool IsFlipped = mOwner->GetFlip();
    
    SDL_Rect dstrect;
    dstrect.w = mWidth;
    dstrect.h = mHeight;
    dstrect.x = pos.x - BLOCK_SIZE/2.0f;
    dstrect.y = pos.y - BLOCK_SIZE/2.0f;
    
    SDL_RendererFlip flip = (IsFlipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

    SDL_RenderCopyEx(renderer, mSpriteSheetSurface, nullptr, &dstrect, angle, nullptr, flip);
}