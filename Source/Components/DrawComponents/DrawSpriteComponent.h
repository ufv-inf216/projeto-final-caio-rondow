#pragma once

#include "DrawComponent.h"

class DrawSpriteComponent : public DrawComponent{
public:
    /* CONSTRUCTOR */
    DrawSpriteComponent(Actor *owner, const std::string&TextureFile, int width, int height, int DrawOrder=10);
    /* draw sprite */
    void Draw(SDL_Renderer *renderer) override;
protected:
    /* PROTECTED ATTRIBUTES */
    SDL_Texture *mSpriteSheetSurface;
    // bool mIsFlippedHorizontally;
    // bool mIsFlippedVertically;
    int mWidth, mHeight;
};