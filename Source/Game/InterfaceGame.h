#pragma once

#include <SDL2/SDL.h>

#include <algorithm>

#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <map>

#include "../Utils/Math.h"

#define BLOCK_SIZE 32

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 4
#define BOARD_ORIGIN_X 128
#define BOARD_ORIGIN_Y 96

#define STASH_WIDTH 4
#define STASH_HEIGHT 8
#define STASH_ORIGIN_X 544
#define STASH_ORIGIN_Y BOARD_ORIGIN_Y

#define PIECE_ROTATION_DEGREE 90.0f

#define BLOCK_UPDATE_ORDER 0
#define PEG_UPDATE_ORDER 1
#define PIECE_UPDATE_ORDER 2
#define CURSOR_UPDATE_ORDER 3

#define BACKGROUND_DRAW_LAYER -1
#define BLOCK_DRAW_LAYER 0
#define PEG_DRAW_LAYER 1
#define PIECE_DRAW_LAYER 2
#define CURSOR_DRAW_LAYER 3

#define RED_L_INDEX 0x0
#define RED_Z_INDEX 0x1

#define GREEN_c_INDEX 0x2
#define GREEN_T_INDEX 0x3

#define BLUE_b_INDEX 0x4
#define BLUE_I_INDEX 0x5

#define YELLOW_i_INDEX 0x6
#define YELLOW_f_INDEX 0x7

#define PEG_INDEX 0x9

#define NUMBER_OF_PIECES 8

/* this map is just to make it easier to 
create levels */
const std::map<char, int> PieceToIndex = {
    {'L',   RED_L_INDEX},
    {'Z',   RED_Z_INDEX},
    {'c',   GREEN_c_INDEX},
    {'T',   GREEN_T_INDEX},
    {'b',   BLUE_b_INDEX},
    {'I',   BLUE_I_INDEX},
    {'i',   YELLOW_i_INDEX},
    {'f',   YELLOW_f_INDEX},
    {'P',   PEG_INDEX},
};

class DrawComponent;
class AudioSystem;
class Actor;
class Table;
class Cursor;
class Wall;

class InterfaceGame{ /* this is the game interface */
public:
    virtual ~InterfaceGame() = default;

    /* PUBLIC METHODS */
    virtual bool InitGame() = 0;
    virtual void EnterMainLoop() = 0;
    virtual void ShutDown() = 0;
    virtual void Quit() = 0;
    
    virtual uint GetWindowWidth() const = 0;
    virtual uint GetWindowHeight() const = 0;
    
    virtual void AddActor(Actor *actor) = 0;
    virtual void RemoveActor(Actor *actor) = 0;
    
    virtual void AddDrawable(DrawComponent *drawable) = 0;
    virtual void RemoveDrawable(DrawComponent *drawable) = 0;
    virtual void DrawLast(DrawComponent *drawable) = 0;
    
    virtual SDL_Texture *LoadTexture(const std::string&TextureFile) const = 0;
    virtual void LoadLevel(const std::string&StartLevel, const std::string&EndLevel) = 0;
    
    virtual AudioSystem* GetAudio() const = 0;

    virtual Cursor *GetCursor() const = 0;
    virtual Table *GetBoard() const = 0;
    virtual Table *GetStash() const = 0;
    virtual const std::vector<Wall*> &GetWalls() const = 0;
    
    virtual bool GetAction() const = 0;
    virtual bool IsOnBoard(const Vector2 &pos) const = 0;

    virtual bool IsLevelComplete() const = 0;

private:
    /* PRIVATE METHODS */
    virtual void ProcessInput() = 0;
    virtual void UpdateGame() = 0;
    virtual void GenerateOutput() = 0;
    virtual void InitActors() = 0;
    virtual void UpdateActors(float DeltaTime) = 0;
};