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

static const int PieceShape[9][3]{
/*  @params:
    width           height          number of colliders */
    {2*BLOCK_SIZE,  3*BLOCK_SIZE,   4}, // RED L
    {2*BLOCK_SIZE,  3*BLOCK_SIZE,   4}, // RED Z
    {2*BLOCK_SIZE,  2*BLOCK_SIZE,   3}, // GREEN c
    {3*BLOCK_SIZE,  2*BLOCK_SIZE,   4}, // GREEN T
    {2*BLOCK_SIZE,  3*BLOCK_SIZE,   5}, // BLUE b
    {BLOCK_SIZE,    4*BLOCK_SIZE,   4}, // BLUE I
    {BLOCK_SIZE,    3*BLOCK_SIZE,   3}, // YELLOW i
    {3*BLOCK_SIZE,  3*BLOCK_SIZE,   5}, // YELLOW f
    {BLOCK_SIZE,    BLOCK_SIZE,     1}  // PEG
};

static const int PieceOffset[8][36] = {
    /*  @params:
        i collider offset.x, i collider offset.y, Does the collider have a hole? */
    {   
        0,0,true,
        0,BLOCK_SIZE,false,
        0,2*BLOCK_SIZE,true,
        BLOCK_SIZE,2*BLOCK_SIZE,false
    }, // RED L

    {
        0,0,false,
        0,BLOCK_SIZE,false,
        BLOCK_SIZE,BLOCK_SIZE,true,
        BLOCK_SIZE,2*BLOCK_SIZE,false
    }, // RED Z

    {
        0,0,false,
        0,BLOCK_SIZE,true,
        BLOCK_SIZE,BLOCK_SIZE,true
    }, // GREEN c
    
    {
        BLOCK_SIZE,0,true,
        0,BLOCK_SIZE,true,
        BLOCK_SIZE,BLOCK_SIZE,false,
        2*BLOCK_SIZE, BLOCK_SIZE,false
    }, // GREEN T

    {
        0,0,false,
        0,BLOCK_SIZE,false,
        BLOCK_SIZE,BLOCK_SIZE,true,
        0,2*BLOCK_SIZE,false,
        BLOCK_SIZE,2*BLOCK_SIZE,true
    }, // BLUE b

    {
        0,0,false,
        0,BLOCK_SIZE,false,
        0,2*BLOCK_SIZE,true,
        0,3*BLOCK_SIZE,false
    }, // BLUE I

    {
        0,0,true,
        0,BLOCK_SIZE,false,
        0,2*BLOCK_SIZE,false,
    }, // YELLOW i
    
    {
        BLOCK_SIZE,0,true,
        2*BLOCK_SIZE,0,true,
        0,BLOCK_SIZE,true,
        BLOCK_SIZE,BLOCK_SIZE,false,
        BLOCK_SIZE,2*BLOCK_SIZE,false
    }, // YELLOW f
};

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

    static void LoadPiece(Piece *piece, std::vector<AABBColliderComponent*>&colliders, std::vector<DrawPolygonComponent*>&polygons, float rotation){
        
        int idx = piece->ToIndex();
        
        uint width  = PieceShape[idx][0];
        uint height = PieceShape[idx][1];
        uint NumColliders = PieceShape[idx][2];

        piece->SetWidth(width);
        piece->SetHeight(height);
        piece->Rotate(rotation);
        
        std::string PieceTexture = "../Assets/Sprite/Pieces/" + 
                                    std::string(1,piece->GetPieceType()) + ".png";
        new DrawSpriteComponent(piece, PieceTexture, piece->GetWidth(), piece->GetHeight(), PIECE_DRAW_ORDER);
        
        for(int i=0; i<NumColliders; i++){
            
            float x = (float)PieceOffset[idx][i*3];
            float y = (float)PieceOffset[idx][i*3 + 1];
            bool IsHollow = PieceOffset[idx][i*3 + 2];

            Vector2 offset = Vector2(x,y);

            std::cout << x << " " << y << " " << IsHollow << "\n";

            AABBColliderComponent *collider = new AABBColliderComponent(
                piece, offset, BLOCK_SIZE, BLOCK_SIZE, ColliderLayer::PIECE,
                PIECE_UPDATE_ORDER, IsHollow
            );

            colliders.emplace_back(collider);

            /* PIECE COLLIDER - DEBUG ONLY */
            std::vector<Vector2> vertices;
            vertices.push_back(Vector2(x,y));
            vertices.push_back(Vector2(x+BLOCK_SIZE,y));
            vertices.push_back(Vector2(x+BLOCK_SIZE,y+BLOCK_SIZE));
            vertices.push_back(Vector2(x,y+BLOCK_SIZE));
            DrawPolygonComponent *polygon = new DrawPolygonComponent(piece, vertices);
            polygon->SetColor(255,255,0,255);
            polygons.emplace_back(polygon);
            /* PIECE COLLIDER - DEBUG ONLY */
        }
    }   
};