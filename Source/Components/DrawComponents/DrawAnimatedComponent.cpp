#include "DrawAnimatedComponent.h"
#include "../../Actors/Actor.h"
#include "../../Game/ConcreteGame.h"
#include "../../Utils/Json.h"
#include <fstream>

DrawAnimatedComponent::DrawAnimatedComponent(Actor *owner, const std::string&SpriteSheetPath, const std::string&SpriteSheetData, int DrawOrder):
    DrawSpriteComponent(owner,SpriteSheetPath,0,0,DrawOrder),
    mAnimTimer(0.0f),
    mAnimFPS(10),
    mIsPaused(false)
{
    LoadSpriteSheet(SpriteSheetPath, SpriteSheetData);
}

DrawAnimatedComponent::~DrawAnimatedComponent(){
    for(const auto& rect : mSpriteSheetData){
        delete rect;
    }
    mSpriteSheetData.clear();
}

void DrawAnimatedComponent::Draw(SDL_Renderer *renderer){

    int SpriteIdx = mAnimations[mAnimName][(int)mAnimTimer];

    Vector2 pos = mOwner->GetPosition();
    float scale = mOwner->GetScale();
    float angle = mOwner->GetRotation();
    SDL_Point center = {BLOCK_SIZE/2, BLOCK_SIZE/2};

    if(SpriteIdx < mSpriteSheetData.size()){


        SDL_Rect *clipRect = mSpriteSheetData[SpriteIdx];
        SDL_Rect renderQuad = {static_cast<int>(pos.x),
                               static_cast<int>(pos.y),
                               static_cast<int>(clipRect->w*scale),
                               static_cast<int>(clipRect->h*scale)
                            };

        SDL_RendererFlip flip = SDL_FLIP_NONE;

        // if(mOwner->GetDirection().y < .0f && mIsFlippedVertically) {
        //     flip = SDL_FLIP_VERTICAL;
        // }
        // else if (mOwner->GetDirection().x < .0f && mIsFlippedHorizontally) {
        //     flip = SDL_FLIP_HORIZONTAL;
        // }

        SDL_RenderCopyEx(renderer, mSpriteSheetSurface, clipRect, &renderQuad, angle, &center, flip);
    }
}

void DrawAnimatedComponent::Update(float DeltaTime){
    if (mIsPaused) {
        return;
    }

    mAnimTimer += mAnimFPS * DeltaTime;
    if((int)mAnimTimer >= mAnimations[mAnimName].size()) {
        while ((int)mAnimTimer >= mAnimations[mAnimName].size()) {
            mAnimTimer -= (float)mAnimations[mAnimName].size();
        }
    }
}


void DrawAnimatedComponent::SetAnimation(const std::string&name){
    mAnimName = name;
    Update(0.0f);
}

void DrawAnimatedComponent::AddAnimation(const std::string&name, const std::vector<int>&images){
    mAnimations.emplace(name, images);
}

void DrawAnimatedComponent::LoadSpriteSheet(const std::string&TextureFile, const std::string&DataFile){

    mSpriteSheetSurface = mOwner->GetGame()->LoadTexture(TextureFile);

    std::ifstream file(DataFile);
    nlohmann::json SpriteSheetData = nlohmann::json::parse(file);

    SDL_Rect *rect = nullptr;

    for(const auto &frame : SpriteSheetData["frames"]){
        int x = frame["frame"]["x"].get<int>();
        int y = frame["frame"]["y"].get<int>();
        int w = frame["frame"]["w"].get<int>();
        int h = frame["frame"]["h"].get<int>();
        rect = new SDL_Rect({x, y, w, h});

        mSpriteSheetData.emplace_back(rect);
    }

}
