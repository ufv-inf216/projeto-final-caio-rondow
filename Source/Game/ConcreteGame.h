#pragma once

#include "InterfaceGame.h"
#include "../Actors/Block.h"
#include "../Utils/AudioSystem.h"

class ConcreteGame : public InterfaceGame{
public:
    /* PUBLIC METHODS */
    
    /* Constructors */
    ConcreteGame(uint WindowWidth, uint WindowHeight);
    
    /* Game Loop */
    bool InitGame() override;
    void EnterMainLoop() override;
    void ShutDown() override;
    void Quit() override;
    
    /* Game Window */
    uint GetWindowWidth() const override;
    uint GetWindowHeight() const override;
    
    /* Actors */
    void AddActor(Actor *actor) override;
    void RemoveActor(Actor *actor) override;
    
    /* Drawables */
    void AddDrawable(DrawComponent *drawable) override;
    void RemoveDrawable(DrawComponent *drawable) override;
    
    /* Load methods */
    SDL_Texture *LoadTexture(const std::string&TextureFile) const override;
    void LoadLevel(const std::string&LevelFile) override;
    void LoadAnwser(const std::string&AnwserFile) override;
    
    /* Game specific */
    inline Cursor *GetCursor() const override{
        return mCursor;
    }
    inline const Table *GetBoard() const override{
        return mBoard;
    }
    inline const Table *GetStash() const override{
        return mStash;
    }
    inline const std::vector<Wall*> &GetWalls() const{ 
        return mWalls; 
    }
    inline bool GetAction() const override{
        return mAction;
    }
    inline bool IsOnBoard(const Vector2 &pos) const override{
        return (pos.x < BOARD_WIDTH*BLOCK_SIZE + BOARD_ORIGIN_X);
    }
    bool IsLevelComplete() const override;

private:
    /* PRIVATE METHODS */
    void ProcessInput() override;
    void UpdateGame() override;
    void GenerateOutput() override;
    void InitActors() override;
    void UpdateActors(float DeltaTime) override;

    /* PRIVATE ATTRIBUTES */

    /* Game properties */
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    uint mWindowWidth, mWindowHeight;
    bool mIsRunning, mUpdatingActors;
    bool mAction;
    Uint32 mTicksCount;

    /* Game Actors */
    std::vector<Actor*> mActors;
    std::vector<Actor*> mPendingActors;
    /* Game Drawables */
    std::vector<DrawComponent*> mDrawables;
    /* Game Specific */
    Table *mBoard;
    Table *mStash;
    Cursor *mCursor;
    std::vector<Wall*> mWalls; /* this is the wall cells around the table */
    std::vector<Vector2> mAnwser;
};