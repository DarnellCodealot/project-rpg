#define SDL_MAIN_HANDLED
#include "sdlLib.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// this will need further encapsulation
bool Collide(Sprite &a, Sprite &b, vector2 &ap, vector2 &bp)
{
    return (ap.x + a.width >= bp.x && bp.x + b.width >= ap.x && ap.y + a.height >= bp.y && bp.y + b.height >= ap.y);
}

// to do list:
// encapsulate SDL_Rect better
// draw the level using a function that is part of the window class
// maybe remove texture (seems unnecessary)

int main()
{
    // init library
    RenderWindow::InitAll();

    // create window
    RenderWindow window("MARIOANA EROINA COCAINA CRACK", 1280, 720);
    window.setFps(60);

    // Load the sprite
    Player Unt("E:/Aseprite/saved/allPablo.png", window, vector2(512, 512), 2);
    level a("untitled3.json", window, 2);
    vector2 suppos;

    // Main loop
    while (window.run())
    {
        Unt.Move();
        // Get the current state of the keyboard
        const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

        // Check the state of the arrow keys and w a s d
        if (!Unt.interacting)
        {
            if (keyboardState[SDL_SCANCODE_LEFT] || window.keyPressed('a'))
            {
                Unt.Travel(-1, 0, 750,a.mapBounds);
            }
            else if (keyboardState[SDL_SCANCODE_RIGHT] || window.keyPressed('d'))
            {
                Unt.Travel(1, 0, 750,a.mapBounds);
            }
            else if (keyboardState[SDL_SCANCODE_UP] || window.keyPressed('w'))
            {
                Unt.Travel(0, -1, 750,a.mapBounds);
            }
            else if (keyboardState[SDL_SCANCODE_DOWN] || window.keyPressed('s'))
            {
                Unt.Travel(0, 1, 750,a.mapBounds);
            }
        }

        vector2 ppos = Unt.GetPos();
        float distance = sqrt((ppos.x - suppos.x) * (ppos.x - suppos.x) + (ppos.y - suppos.y) * (ppos.y - suppos.y));

        Unt.Move();

        window.clear();
        // Unt.interact(a.interactible,window);
        a.renderLVL(window);
        Unt.Draw(window);
        a.renderLVL2(window);

        if (window.keyPressedDown(SDL_SCANCODE_Z) && Unt.frontObject(a.interactible, window))
        {
            Unt.interacting = !Unt.interacting;
        }

        if (Unt.interacting)
        {
            Unt.interact(a.interactible, window,100);
        }

        // window.renderText("I am here", 255,255,255, 100, 200);
        window.display();
    }

    // Clean up
    RenderWindow::QuitAll();
    return 0;
}
