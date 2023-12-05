#include "../Components/DrawComponents/DrawPolygonComponent.h"
#include "../Components/DrawComponents/DrawAnimatedComponent.h"
#include "../Components/ColliderComponents/AABBColliderComponent.h"
#include "../Game/InterfaceGame.h"
#include "../Actors/Table.h"
#include "../Actors/Piece.h"
#include "../Actors/Block.h"
#include "../Actors/Wall.h"
#include "../Actors/Peg.h"
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
            
            Piece *piece;
            Peg *peg;
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

                /* red peg        blue peg       green peg      yellow peg */
                if(type == 'R' || type == 'B' || type == 'G' || type == 'Y'){
                    std::cout << type << "\n";
                    peg = new Peg(board.GetGame(), x, y, type);
                    board.AddPeg(peg);
                } else{
                    piece = new Piece(board.GetGame(), x, y, type, rotation, flip);
                    board.AddPiece(piece);
                }

            } else{

                x = x*BLOCK_SIZE + STASH_ORIGIN_X;
                y = y*BLOCK_SIZE + STASH_ORIGIN_Y;
                piece = new Piece(stash.GetGame(), x, y, type, rotation, flip);
                stash.AddPiece(piece);
            }
        }
    }

    static void RaiseWalls(InterfaceGame *game, std::vector<Wall*> &walls){

        uint WindowWidth = game->GetWindowWidth();

        /* CREATE TOP WALL */
        Wall *TopWall = new Wall(game,0,0,WindowWidth,BOARD_ORIGIN_Y);
        walls.emplace_back(TopWall);
        
        /* CREATE MIDDLE WALL (BETWEEN BOARD AND STASH) */
        Wall *MidWall = new Wall(
            game,BOARD_ORIGIN_X+BLOCK_SIZE*BOARD_WIDTH,0,
            STASH_ORIGIN_X-(BOARD_ORIGIN_X+BLOCK_SIZE*BOARD_WIDTH),WindowWidth
        );
        walls.emplace_back(MidWall);

        /* CREATE BOARD-LEFT WALL */
        Wall *BoardLeftWall = new Wall(game,0,0,BOARD_ORIGIN_X, WindowWidth);
        walls.emplace_back(BoardLeftWall);

        /* CREATE BOARD-BOTTOM WALL */
        Wall *BoardBottomWall = new Wall(
            game,0,BOARD_ORIGIN_Y+BOARD_HEIGHT*BLOCK_SIZE,STASH_ORIGIN_X, WindowWidth
        );
        walls.emplace_back(BoardBottomWall);

        /* CREATE STASH-BOTTOM WALL */
        Wall *StashBottomWall = new Wall(
            game,0,STASH_ORIGIN_Y+STASH_HEIGHT*BLOCK_SIZE,WindowWidth,WindowWidth
        );
        walls.emplace_back(StashBottomWall);

        /* CREATE STASH-RIGHT WALL */
        Wall *StashRightWall = new Wall(
            game,STASH_ORIGIN_X+STASH_WIDTH*BLOCK_SIZE,0,WindowWidth,WindowWidth
        );
        walls.emplace_back(StashRightWall);
    }
};