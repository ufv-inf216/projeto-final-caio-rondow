#pragma once

#include "Actor.h"
#include "../Game/InterfaceGame.h"
#include <stack>

class DrawSpriteComponent;
class AABBColliderComponent;
class DrawPolygonComponent;

class Piece : public Actor{
public:
    explicit Piece(InterfaceGame *game, float x, float y, char PieceType=char(), float rotation=0.0f, bool flip=false);
    
    /* piece actions */
    void Move(const Vector2&UnitVec);
    void Rotate(float theta);
    void Place();
    void Flip();
    void Cancel();

    void OnCollision(Actor *response) override;
    void OnProcessInput(const Uint8 *KeyState) override;
    void OnUpdate(float DeltaTime) override;

    void DetectWall();
    bool DetectCollision() override;

    const std::vector<AABBColliderComponent*> &GetColliders() const;
    char GetPieceType() const;
    
    /* return piece index of the piece type */
    static int ToIndex(const char PieceType);

    /* mIsEnabled state makes the piece freeze or move */
    bool IsEnabled() const;
    void Disable();
    void Enable();

    void SetWidth(const uint width);
    uint GetWidth() const;

    void SetHeight(const uint height);
    uint GetHeight() const;
    
protected:
    std::vector<AABBColliderComponent*> mColliders;
    bool mCanProcessInput;
    bool mIsEnabled;
    char mPieceType;
    bool mCanPlace;
    uint mHeight;
    uint mWidth;

private:
    /* piece components */
    std::vector<DrawPolygonComponent*> mDrawPolygons; /* DEBUG ONLY */
    DrawSpriteComponent *mDrawSpriteComponent;
    
    /* Change collider based on rotation and flip */
    void RotateCounterClockWise(double& x, double& y, double cx, double cy, double theta);
    void RotateClockWise(double& x, double& y, double cx, double cy, double theta);
    
    bool IsMovingToStash(const Vector2 &dir, const float pos) const;
    bool IsMovingToBoard(const Vector2 &dir, const float pos) const;

    /* cancel operations */
    void UpdatePreviousState();
    Vector2 mPreviousPos;
    std::stack<int> mUndoStack;

    /* piece SFXs */
    const std::vector<std::vector<std::string>> mSFX = {
        {
            "Rotate0.WAV", "Rotate1.WAV",
            "Rotate2.WAV", "Rotate2.WAV",
            "Rotate4.WAV", "Rotate5.WAV"
        },
        {
            "Place0.WAV", "Place1.WAV"
        }
    };
};