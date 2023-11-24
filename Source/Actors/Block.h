#pragma once 

#include "Actor.h"

#define UP 0
#define DOWN 1
#define LEFT 2 
#define RIGHT 3 

class DrawAnimatedComponent; 
class AABBColliderComponent;

class Block : public Actor{
public:
    explicit Block(InterfaceGame *game, int dx=32, int dy=32, ColliderLayer layer=ColliderLayer::BLOCK);

    /* Add adjacenct blocks */
    inline void Link(Block *adj, uint dir){
        if(dir >= 0 && dir < 4)
            mAdjacents[dir] = adj;
        else{
            std::cerr << "invalid position.\n";
            exit(EXIT_FAILURE);
        }
    }
    Block *operator[](uint dir) const{
        return mAdjacents[dir];
    }
    inline void SetSelected(const bool state){
        mIsSelected = state;
    }
    void OnUpdate(float DeltaTime) override;
    void OnCollision(std::vector<AABBColliderComponent::Overlap>& responses) override;
 
private:
    std::vector<Block*> mAdjacents;
    bool mIsSelected;

    DrawAnimatedComponent *mDrawComponent;
    AABBColliderComponent *mAABBColliderComponent;
};