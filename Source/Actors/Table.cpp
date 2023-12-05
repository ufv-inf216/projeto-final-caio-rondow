#include "Table.h"
#include "Piece.h"
#include "Block.h"
#include "Peg.h"

Table::Table(InterfaceGame *game, const Vector2&origin, uint TableWidth, uint TableHeight):
    Actor(game),
    mTableWidth(TableWidth),
    mTableHeight(TableHeight)
{
    SetPosition(origin);

    /* CREATE TABLE CELLS */
    for(int i=0; i<mTableWidth; i++){
        for(int j=0; j<mTableHeight; j++){
            float x = origin.x + i*BLOCK_SIZE;
            float y = origin.y + j*BLOCK_SIZE;
            mTable.emplace_back( new Block(game, x, y, false) );
        }
    }
}

void Table::AddPiece(Piece *piece){ 
    mPieces.emplace_back(piece); 
}

void Table::AddPeg(Peg *peg){
    mPegs.emplace_back(peg);
}

const std::vector<Piece*> &Table::GetPieces() const{ 
    return mPieces; 
}

const std::vector<Block*> &Table::GetBlocks() const{ 
    return mTable; 
}

const std::vector<Peg*> &Table::GetPegs() const{
    return mPegs;
}
