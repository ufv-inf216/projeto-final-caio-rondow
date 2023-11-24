#pragma once

#include "DrawSpriteComponent.h"
#include <unordered_map>
#include <vector>

class DrawAnimatedComponent : public DrawSpriteComponent{
public:
    
    DrawAnimatedComponent(Actor *owner, const std::string&SpriteSheetPath, const std::string&SpriteSheetData, int DrawOrder=10);
    ~DrawAnimatedComponent() override;

    void Draw(SDL_Renderer *renderer) override;
    void Update(float DeltaTime) override;
    
    inline void SetAnimationFPS(float FPS){
        mAnimFPS = FPS;
    }
    void SetAnimation(const std::string&name);
    inline void ResetAnimation(){
        mAnimTimer = 0.0f;
    }
    inline void SetIsPaused(bool pause){
        mIsPaused = pause;
    }
    void AddAnimation(const std::string&name, const std::vector<int>&images);
private:
    void LoadSpriteSheet(const std::string&TextureFile, const std::string&DataFile);

    std::vector<SDL_Rect*> mSpriteSheetData;
    std::unordered_map<std::string, std::vector<int> > mAnimations;
    std::string mAnimName;
    float mAnimTimer;
    float mAnimFPS;
    bool mIsPaused;
};