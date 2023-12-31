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
    void DrawLast(DrawComponent *drawable) override;
    
    /* Load methods */
    SDL_Texture *LoadTexture(const std::string&TextureFile) const override;
    void LoadLevel(const std::string&StartLevel, const std::string&EndLevel) override;
    
    AudioSystem* GetAudio() const{ return mAudio; }

    /* Game specific */
    inline Cursor *GetCursor() const override{
        return mCursor;
    }
    inline Table *GetBoard() const override{
        return mBoard;
    }
    inline Table *GetStash() const override{
        return mStash;
    }
    inline const std::vector<Wall*> &GetWalls() const{ 
        return mWalls; 
    }
    inline bool GetAction() const override{
        return mAction;
    }
    bool IsOnBoard(const Vector2 &pos) const override;
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
    AudioSystem *mAudio;

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
    char mAnswer[BOARD_HEIGHT][BOARD_WIDTH];
};