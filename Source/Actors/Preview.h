#pragma once

#include "Actor.h"

class DrawAnimatedComponent;

class Preview : public Actor{
public:
    Preview(InterfaceGame *game, char PieceType=char());

    void OnUpdate(float DeltaTime) override; 

private:
    char mOnPreview;
    DrawAnimatedComponent *mPreview;
};