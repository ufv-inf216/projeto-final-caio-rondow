#pragma once

#include "InterfaceGame.h"
#include "../Actors/Block.h"

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
    /* Game specific */
    inline Block *GetCursor() const override{
        return mCursor;
    }
    inline const Table *GetBoard() const override{
        return mBoard;
    }
    inline const Table *GetStash() const override{
        return mStash;
    }
    inline bool GetAction() const override{
        return mAction;
    }
    inline bool IsOnBoard(const float xPos) const override{
        return (xPos < BOARD_WIDTH*BLOCK_SIZE + BOARD_ORIGIN_X);
    }

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
    Block *mCursor;
};