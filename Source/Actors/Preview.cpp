#include "Preview.h"
#include "Cursor.h"
#include "../Game/InterfaceGame.h"
#include "../Components/DrawComponents/DrawAnimatedComponent.h"

Preview::Preview(InterfaceGame *game, char PieceType):
    Actor(game),
    mOnPreview(PieceType),
    mPreview(nullptr)
{

    std::string SpriteSheet = "../Assets/Sprite/Preview/b/b-wireframe.png";
    std::string SpriteData = "../Assets/Sprite/Preview/b/b-wireframe.json";

    mPreview = new DrawAnimatedComponent(this, SpriteSheet, SpriteData, 1);
    
    std::vector<int> images;
    for(int i=4; i>=0; i--){
        images.push_back(i);
    }
    for(int i=0; i<4; i++){
        images.push_back(i);
    }

    mPreview->AddAnimation("spin", images);
    mPreview->SetAnimation("spin");
    mPreview->SetAnimationFPS(10);
    mScale = 0.60;
    // mRotation = 30.0f;
}

void Preview::OnUpdate(float DeltaTime){

    Cursor *cursor = mGame->GetCursor();
    const Piece *piece = cursor->PieceSelected();
    
    if(piece != nullptr){
        mPreview->EnableComponent();
    } else{
        mPreview->DisableComponent();
    }

}