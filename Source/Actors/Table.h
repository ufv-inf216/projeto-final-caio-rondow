#pragma once

#include "Actor.h"

class Piece;
class Block;

class Table : public Actor{
public:
    explicit Table(InterfaceGame *game, const Vector2&origin, uint TableWidth, uint TableHeight);

    inline uint GetTableWidth() const{ return mTableWidth; }
    inline uint GetTableHeight() const{ return mTableHeight; }
    inline void AddPiece(Piece *p){ mPieces.emplace_back(p); }
    inline const std::vector<Piece*> &GetPieces() const{ return mPieces; }
    inline const std::vector<Block*> &GetBlocks() const{ return mTable; }

private:
    uint mTableWidth, mTableHeight;
    std::vector<Block*> mTable;     /* this is the table cells */
    std::vector<Piece*> mPieces;    /* this is the pieces on the table */
};