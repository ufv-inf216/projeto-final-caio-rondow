#include "../Components/DrawComponents/DrawPolygonComponent.h"
#include "../Components/DrawComponents/DrawAnimatedComponent.h"
#include "../Components/ColliderComponents/AABBColliderComponent.h"
#include "../Game/InterfaceGame.h"
#include "../Actors/Table.h"
#include "../Actors/Piece.h"
#include "../Actors/Block.h"
#include <iostream>
#include <sstream>
#include <fstream>

namespace parser{

    static void LoadTable(const std::string &filename, Table &board, Table&stash){

        std::ifstream ifs(filename, std::ifstream::in);
            if(!ifs.is_open()){
            std::cerr << "In void ConcreteGame::LoadLevel(const std::string&LevelFile)\n";
            std::cerr << "Could not open " << filename << ".\n";
            exit(EXIT_FAILURE);
        }

        std::string row;
        std::getline(ifs, row); /* ignore header */
        while (std::getline(ifs, row)) {
            
            Piece *p;
            float x, y;
            float rotation;
            bool flip, isBoard;
            char type, comma;
            
            std::istringstream iss(row);

            /* parse csv */
            iss   >> type     >> comma >> 
            x     >> comma    >> y     >> 
            comma >> rotation >> comma >> 
            flip  >> comma    >> isBoard;

            /* Create a new piece */
            if(isBoard){

                x = x*BLOCK_SIZE + BOARD_ORIGIN_X;
                y = y*BLOCK_SIZE + BOARD_ORIGIN_Y;
                p = new Piece(board.GetGame(), x, y, type, rotation, flip);
                board.AddPiece(p);

            } else{

                x = x*BLOCK_SIZE + STASH_ORIGIN_X;
                y = y*BLOCK_SIZE + STASH_ORIGIN_Y;
                p = new Piece(stash.GetGame(), x, y, type, rotation, flip);
                stash.AddPiece(p);
            }
        }
    }

    static void RaiseWalls(std::vector<Block*> &walls, InterfaceGame *game){

        uint WindowWidth = game->GetWindowWidth();

        /* CREATE TOP WALL */
        Block *TopWall = new Block(game,0,0,false,ColliderLayer::WALL, WindowWidth, BOARD_ORIGIN_Y);
        walls.emplace_back(TopWall);
        
        /* CREATE MIDDLE WALL (BETWEEN BOARD AND STASH) */
        Block *MidWall = new Block(game,BOARD_ORIGIN_X+BLOCK_SIZE*BOARD_WIDTH,0,
            false,ColliderLayer::WALL,STASH_ORIGIN_X - (BOARD_ORIGIN_X+BLOCK_SIZE*BOARD_WIDTH),WindowWidth);
        walls.emplace_back(MidWall);
        
        /* CREATE BOARD-LEFT WALL */
        Block *BoardLeftWall = new Block(game,0,0,false,ColliderLayer::WALL, BOARD_ORIGIN_X, WindowWidth);
        walls.emplace_back(BoardLeftWall);
        
        /* CREATE BOARD-BOTTOM WALL */
        Block *BoardBottomWall = new Block(game,0,BOARD_ORIGIN_Y+BOARD_HEIGHT*BLOCK_SIZE,false,ColliderLayer::WALL,STASH_ORIGIN_X, WindowWidth);
        walls.emplace_back(BoardBottomWall);
        
        /* CREATE STASH-BOTTOM WALL */
        Block *StashBottomWall = new Block(game,0,STASH_ORIGIN_Y+STASH_HEIGHT*BLOCK_SIZE,false,ColliderLayer::WALL,WindowWidth,WindowWidth);
        walls.emplace_back(StashBottomWall); 
        
        /* CREATE STASH-RIGHT WALL */
        Block *StashRightWall = new Block(game,STASH_ORIGIN_X+STASH_WIDTH*BLOCK_SIZE,0,false,ColliderLayer::WALL,WindowWidth,WindowWidth);
        walls.emplace_back(StashRightWall);
    }
};