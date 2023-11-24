#pragma once

#include "Actor.h"

class Block;
class Piece;

class Table : public Actor{
public:
    Table(InterfaceGame *game, uint width, uint height);
    void OnUpdate(float DeltaTime) override;
    void OnProcessInput(const Uint8 *KeyState) override;
    void SetTablePosition(const Vector2&pos);
    inline Block *GetCursor(const Vector2&cell){
        if(cell.x >= 0 && cell.x < mTableWidth || cell.y >= 0 && cell.y < mTableHeight)
            return mTable[cell.x][cell.y];
        return nullptr;
    }
    void Link(Table *other, uint side);
    void AddPiece(Piece *piece);
    void RemovePiece(Piece *piece);
    // void DetectCollision();
    inline const std::vector<Block*>&GetWalls() const{
        return mWalls;
    }
    inline const std::vector<Piece*>&GetPieces() const{
        return mPieces;
    }
    inline const std::vector<std::vector<Block*>>&GetBlocks() const{
        return mTable;
    }

private:
    
    /* table attributes */
    std::vector<std::vector<Block*>>mTable;
    std::vector<Block*> mWalls;
    uint mTableWidth, mTableHeight;

    /* pieces on the table */
    std::vector<Piece*> mPieces;

    /* controller attributes */
    float mTimesPassed;
    bool mCanProcessInput;
    bool mIsAction;
};