#pragma once

class Player : public Sprite{
    public:
    Player(std::string name, RenderWindow window, Vector2 pos, float scaler = 1.0f);
    void interact(std::map<int, std::map<int, std::string>> interactible, RenderWindow window, int ms);//this function gets the text that should be drawn and prepares it to be drawn
    //public part of the stuff that deals with player movement
    void Travel(int x, int y, uint32_t m, std::map<int, std::map<int, bool>> mapBounds);//basically used when you have the initiative of moving to a tile
    void Move();//and this is used because travel is only executed when you press a button but after you press that button the player has to move 32 pixels without needing you to press anything
    Vector2 GetPos();//if you don't get what this does I bet you won't get it even if I explain it here

    //public part of the stuff that deals with player animation
    void Draw(RenderWindow wind);

    private:
    //private part of the stuff that deals with player movement
    SDL_Rect pos;//...
    bool moving, shouldmove;//obviously used for the characters movement 
    std::chrono::steady_clock::time_point Timep;//timepoint used to make the characters walk smoothly instead of just teleporting an entire tile when you press a button
    int lx,ly,nx,ny;//keeping track of his whereabouts
    uint32_t milliseconds;//keeping treack of how much time he needs to move 1 tile
    int textindex;//keeping track of the letters you draw
    std::string lasttext;//this is the last message you encountered
    std::chrono::steady_clock::time_point ttp;//stands for text time point and it is used to draw a string sequentially

    //private part of the stuff that deals with player animation and stuff
    SDL_Rect srcRect;
};
