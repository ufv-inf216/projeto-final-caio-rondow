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
    
    SDL_Rect dstrect;
    dstrect.w = mWidth;
    dstrect.h = mHeight;
    dstrect.x = pos.x - 16;
    dstrect.y = pos.y - 16;
    
    SDL_RendererFlip flip = (angle == Math::Pi ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

    SDL_RenderCopyEx(renderer, mSpriteSheetSurface, nullptr, &dstrect, angle, nullptr, flip);
}