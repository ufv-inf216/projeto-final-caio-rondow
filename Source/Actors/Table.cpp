#include "Table.h"
#include "Piece.h"
#include "Block.h"

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
            mTable.emplace_back(new Block(game, x, y, false) );
        }
    }

    /* CREATE DOWN WALL */
    // Vector2 down    = Vector2(origin.x, origin.y+TableHeight*BLOCK_SIZE);
    // Block *DownWall = new Block(game,down.x,down.y,false,ColliderLayer::WALL, BLOCK_SIZE*TableWidth, BLOCK_SIZE*TableHeight);
    // mWalls.emplace_back(DownWall);   

    // /* CREATE TOP WALL */

    // Vector2 top    = Vector2(origin.x,origin.y-4*BLOCK_SIZE);
    // Block *TopWall = new Block(game,top.x,top.y,false,ColliderLayer::WALL, BLOCK_SIZE*TableWidth, BLOCK_SIZE*TableHeight);
    // mWalls.emplace_back(TopWall);     
    
    // /* CREATE LEFT WALL */
    // Vector2 left  = Vector2(origin.x-4*BLOCK_SIZE, origin.y);
    // Block *LeftWall = new Block(game,left.x,left.y,false,ColliderLayer::WALL);
    // LeftWall->GetComponent<AABBColliderComponent>()->SetWidth(TableHeight*BLOCK_SIZE);
    // LeftWall->GetComponent<AABBColliderComponent>()->SetHeight(TableWidth*BLOCK_SIZE);
    // mWalls.emplace_back(LeftWall);   
    
    // /* CREATE RIGHT WALL */
    // Vector2 right = Vector2(origin.x+TableWidth*BLOCK_SIZE, origin.y);
    // Block *RightWall = new Block(game,right.x,right.y,false,ColliderLayer::WALL);
    // RightWall->GetComponent<AABBColliderComponent>()->SetWidth(TableHeight*BLOCK_SIZE);
    // RightWall->GetComponent<AABBColliderComponent>()->SetHeight(TableWidth*BLOCK_SIZE);
    // mWalls.emplace_back(RightWall); 
}