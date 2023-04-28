#include "sdlLib.hpp"

Player::Player(std::string name, RenderWindow window, vector2 pos, float scaler) : Sprite(name, window), moving(false), shouldmove(false)
{
    this->pos.x = pos.x;
    this->pos.y = pos.y;
    this->pos.w = 32 * scaler;
    this->pos.h = 32 * scaler;

    this->srcRect.x = 0;
    this->srcRect.y = 0;
    this->srcRect.w = 32;
    this->srcRect.h = 32;
}

vector2 Player::GetPos()
{
    return vector2(this->pos.x, this->pos.y);
}

void Player::Move(std::map<int, std::map<int, bool>> mapBounds)
{
    if (shouldmove && !mapBounds[posY2 / this->pos.w + this->ny][this->posX2 / this->pos.h + this->nx])
    {
        if (!moving)
        {
            this->Timep = std::chrono::steady_clock::now();
            this->lx = int(this->pos.x);
            this->ly = int(this->pos.y);
            moving = true;
        }
        else
        {
            auto end = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - this->Timep).count();
            float ratio = float(duration) / milliseconds;
            if (ratio <= 1.0f)
            {
                this->pos.x = lx + nx * this->pos.w * ratio;
                this->pos.y = ly + ny * this->pos.h * ratio;

                if (duration > milliseconds / 4.0f * (this->srcRect.x / 32 + 1))
                {
                    srcRect.x += 32;
                }
            }
            else
            {
                this->pos.x = lx + nx * this->pos.w;
                this->pos.y = ly + ny * this->pos.h;
                this->moving = false;
                posX2 = pos.x;
                posY2 = pos.y;
                this->shouldmove = false;
                // animation related shenanigans
                srcRect.x = 0;
            }
        }
    }
}
void Player::interact(std::map<int, std::map<int, std::string>> interactible, RenderWindow window)
{
    window.renderText(interactible[posY2 / this->pos.w + this->ny][this->posX2 / this->pos.h + this->nx], 255,255,255, 100, 100);
}

void Player::Travel(int x, int y, uint32_t m)
{
    if (!moving)
    {
        this->shouldmove = true;
        this->nx = x;
        this->ny = y;
        posX2 = pos.x;
        posY2 = pos.y;
        this->milliseconds = m;

        // this part deals with animation (d u r l)
        if (nx == 0)
        { // this means I am moving on the y axis
            if (ny == 1)
            { // down
                this->srcRect.y = 0;
            }
            else
            { // up
                this->srcRect.y = 32;
            }
        }
        else
        { // this means I am moving in the x axis
            if (nx == 1)
            { // right
                this->srcRect.y = 64;
            }
            else
            { // left
                this->srcRect.y = 96;
            }
        }
    }
}

void Player::Draw(RenderWindow wind)
{
    SDL_Rect srcRect2=pos;
    srcRect2.y-=32;
    wind.render(*this, this->srcRect, srcRect2);
}
