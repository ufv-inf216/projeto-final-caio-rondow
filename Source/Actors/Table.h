#pragma once

#include "Actor.h"

class Piece;
class Block;
class Peg;

class Table : public Actor{
public:
    explicit Table(InterfaceGame *game, const Vector2&origin, uint TableWidth, uint TableHeight);

    inline uint GetTableWidth() const{ return mTableWidth; }
    inline uint GetTableHeight() const{ return mTableHeight; }
    
    void AddPiece(Piece *piece);
    void AddPeg(Peg *peg);

    const std::vector<Piece*> &GetPieces() const;
    const std::vector<Block*> &GetBlocks() const;
    const std::vector<Peg*> &GetPegs() const;

private:
    uint mTableWidth, mTableHeight;
    std::vector<Block*> mTable;     /* this is the table cells */
    std::vector<Piece*> mPieces;    /* this is the pieces on the table */
    std::vector<Peg*> mPegs;      /* this is the fixed pegs on the table */  
};