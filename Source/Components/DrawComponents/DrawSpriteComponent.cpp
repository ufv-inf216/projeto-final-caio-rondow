#include "DrawSpriteComponent.h"
#include "../../Actors/Actor.h"
#include "../../Game/InterfaceGame.h"
#include "../../Actors/Piece.h"

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
    float angle = (int)mOwner->GetRotation()%360;
    bool IsFlipped = mOwner->GetFlip();
    float scale = mOwner->GetScale();

    SDL_Point center = {BLOCK_SIZE/2, BLOCK_SIZE/2};
    SDL_Rect dstrect;
    dstrect.w = (int)(mWidth*scale);
    dstrect.h = (int)(mHeight*scale);
    dstrect.x = pos.x;
    dstrect.y = pos.y;

    SDL_RendererFlip flip = (IsFlipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    SDL_RenderCopyEx(renderer, mSpriteSheetSurface, nullptr, &dstrect, angle, &center, flip);
}