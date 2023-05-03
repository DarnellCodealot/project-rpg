#include "sdlLib.hpp"

Player::Player(std::string name, RenderWindow window, vector2 pos, float scaler) : Sprite(name, window), moving(false), shouldmove(false), textindex(0)
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

void Player::interact(std::map<int, std::map<int, std::string>> interactible, RenderWindow window, int ms)
{
    if (!moving)
    {
        std::string intertext = interactible[this->pos.y / this->pos.h + this->ny][this->pos.x / this->pos.w + this->nx];

        if (intertext != this->lasttext)
        {
            this->textindex = 0;
            this->lasttext = intertext;
            this->ttp = std::chrono::steady_clock::now();
        }
        else if (intertext.size() > 0)
        {
            for (int i = 0; i <= this->textindex; i++)
            {
                char letter = intertext[i];
                std::string finaltext(1, letter);
                window.renderText(finaltext, 255, 255, 255, 100 + i * window.getFontWidth(), 100);
            }
            long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - this->ttp).count();
            if (duration >= ms)
            {
                if (this->textindex < intertext.size() - 1)
                {
                    this->textindex++;
                }
                this->ttp = std::chrono::steady_clock::now();
            }
        }
    }
}

bool Player::frontObject(std::map<int, std::map<int, std::string>> interactible, RenderWindow window)
{
    if (interactible[this->pos.y / this->pos.h + this->ny][this->pos.x / this->pos.w + this->nx] == "")
    {
        return false;
    }
    else
    {
        return true;
    }
}

vector2 Player::GetPos()
{
    return vector2(this->pos.x, this->pos.y);
}

void Player::Move()
{
    if (shouldmove)
    {
        if (!moving)
        {
            // this is preparing for the movement itself
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
                this->shouldmove = false;
                // animation related shenanigans
                srcRect.x = 0;
            }
        }
    }
}

void Player::Travel(int x, int y, uint32_t m, std::map<int, std::map<int, bool>> mapBounds)
{
    if (!moving)
    {
        this->nx = x;
        this->ny = y;
        if (!mapBounds[this->pos.y / this->pos.h + this->ny][this->pos.x / this->pos.w + this->nx])
        {

            this->shouldmove = true;
            this->milliseconds = m;
        }

        // this part deals with animation (d u r l)
        if (x == 0)
        { // this means I am moving on the y axis
            if (y == 1)
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
            if (x == 1)
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
    wind.render(*this, this->srcRect, this->pos);
}
