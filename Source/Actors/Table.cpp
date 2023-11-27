#include "Table.h"
#include "Piece.h"
#include "Block.h"

Table::Table(InterfaceGame *game, const Vector2&origin, uint TableWidth, uint TableHeight):
    Actor(game),
    mTableWidth(TableWidth),
    mTableHeight(TableHeight)
{
    SetPosition(origin);

    for(int i=0; i<mTableWidth; i++){
        for(int j=0; j<mTableHeight; j++){
            float x = origin.x + i*BLOCK_SIZE;
            float y = origin.y + j*BLOCK_SIZE;
            mTable.emplace_back(new Block(game, false, x, y) );
        }
    }

}