#pragma once

#include <SDL2/SDL.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../Utils/Math.h"

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 4
#define BOARD_ORIGIN_X 128
#define BOARD_ORIGIN_Y 256

#define STASH_WIDTH 4
#define STASH_HEIGHT 8
#define STASH_ORIGIN_X 512
#define STASH_ORIGIN_Y BOARD_ORIGIN_Y

#define BLOCK_SIZE 32

class Actor;
class Table;
class DrawComponent;
class Block;

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
    virtual SDL_Texture *LoadTexture(const std::string&TextureFile) const = 0;
    virtual void LoadLevel(const std::string&LevelFile) = 0;
    virtual Block *GetCursor() const = 0;
    virtual const Table *GetBoard() const = 0;
    virtual const Table *GetStash() const = 0;
    virtual const std::vector<Block*> &GetWalls() const = 0;
    virtual bool GetAction() const = 0;
    virtual bool IsOnBoard(const Vector2 &pos) const = 0;

private:
    /* PRIVATE METHODS */
    virtual void ProcessInput() = 0;
    virtual void UpdateGame() = 0;
    virtual void GenerateOutput() = 0;
    virtual void InitActors() = 0;
    virtual void UpdateActors(float DeltaTime) = 0;
};