#pragma once

#include "Actor.h"
#include "../Game/InterfaceGame.h"
#include <stack>

class DrawSpriteComponent;
class AABBColliderComponent;
class DrawPolygonComponent;

enum class PieceTable{
    BOARD,
    STASH
};

class Piece : public Actor{
public:
    explicit Piece(InterfaceGame *game, float x, float y, char PieceType=char(), float rotation=0.0f, bool flip=false);
    
    /* piece actions */
    void Move(const Vector2&UnitVec);
    void Rotate(float theta);
    void Place();
    void Flip();
    void Cancel();

    void OnCollision(const std::vector<Actor*>&responses) override;
    void OnProcessInput(const Uint8 *KeyState) override;
    void OnUpdate(float DeltaTime) override;

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

    void SetPieceTable(const PieceTable table);
    PieceTable GetPieceTable() const;
    
protected:
    bool mCanProcessInput;
    bool mIsEnabled;
    char mPieceType;
    bool mCanPlace;
    uint mHeight;
    uint mWidth;
    bool mFront;

private:
    /* piece components */
    std::vector<DrawPolygonComponent*> mDrawPolygons; /* DEBUG ONLY */
    std::vector<AABBColliderComponent*> mColliders;
    DrawSpriteComponent *mDrawSpriteComponent;
    
    /* Change collider based on rotation and flip */
    void RotateCounterClockWise(double& x, double& y, double cx, double cy, double theta);
    void RotateClockWise(double& x, double& y, double cx, double cy, double theta);
    void UpdatePreviousState();
    
    /* cancel operations */
    Vector2 mPreviousPos;
    std::stack<int> mUndoStack;

    /* Which board the piece is in it */
    PieceTable mCurrentTable;
};