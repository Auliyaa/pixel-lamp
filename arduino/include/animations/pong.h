#pragma once

#include <animation.h>
#include <board.h>

struct animation_pong_t: public cs_animation_t<500>
{
protected:
    virtual void step(led_matrix_t& leds)
    {
        if ((ball_dir_y == -1 && ball_y == 0) ||
            (ball_dir_y == 1 && ball_y == LED_ARRAY_HEIGHT-1))
        {
            // point
            reset();
            draw(leds);
            return;
        }
        else if (ball_dir_y == -1 && ball_y <= 1 &&
                 (ball_x == wx(bbar_x-1) || ball_x == bbar_x || ball_x == wx(bbar_x+1)))
        {
            // ball reached the bottom bar: reverse direction & update x movement
            ball_dir_y = 1;
            ball_dir_x = random(2) == 0 ? -1 : 1;
            draw(leds);
            return;
        }
        else if (ball_dir_y == 1 && ball_y >= LED_ARRAY_HEIGHT-2 &&
                 (ball_x == wx(tbar_x-1) || ball_x == tbar_x || ball_x == wx(tbar_x+1)))
        {
            ball_dir_y = -1;
            ball_dir_x = random(2) == 0 ? -1 : 1;
            draw(leds);
            return;
        }

        // any other case: move the ball & bars
        if (ball_dir_y == 1 && ball_x != tbar_x)
        {
            int f = (ball_x != tbar_x+1 && ball_x != tbar_x-1 ? 2 : 1);
            tbar_x = wx(tbar_x+dir(tbar_x,ball_x)*f);

            if (ball_x != bbar_x && random(4) != 0)
            {
                bbar_x = wx(bbar_x+dir(bbar_x,ball_x));
            }

        }
        else if (ball_dir_y == -1 && ball_x != bbar_x)
        {
            int f = (ball_x != bbar_x+1 && ball_x != bbar_x-1 ? 2 : 1);
            bbar_x = wx(bbar_x+dir(bbar_x,ball_x)*f);

            if (ball_x != tbar_x && random(4) != 0)
            {
                tbar_x = wx(tbar_x+dir(tbar_x,ball_x));
            }
        }

        ball_y += ball_dir_y;
        ball_x = wx(ball_x + ball_dir_x);
        if (ball_x == 0) ball_dir_x = 1;
        else if (ball_x == LED_ARRAY_WIDTH-1) ball_dir_x = -1;
        draw(leds);
        return;
    }

private:
    int tbar_x = LED_ARRAY_WIDTH/2;
    int bbar_x = LED_ARRAY_WIDTH/2;
    int ball_x = LED_ARRAY_WIDTH/2;
    int ball_y = 1;

    int ball_dir_y=1;
    int ball_dir_x=0;

    void reset()
    {
        tbar_x = 1;
        bbar_x = 1;
        ball_x = 1;
        ball_y = 1;
        ball_dir_y=1;
        ball_dir_x=0;
    }

    void draw(led_matrix_t& leds)
    {
        leds.reset();

        static auto tcolor = CRGB(255,0,20);
        static auto bcolor = CRGB(20,0,255);
        // draw bars & balls
        leds[wx(tbar_x-1)][LED_ARRAY_HEIGHT-1] = tcolor;
        leds[wx(tbar_x)][LED_ARRAY_HEIGHT-1] = tcolor;
        leds[wx(tbar_x+1)][LED_ARRAY_HEIGHT-1] = tcolor;

        leds[wx(bbar_x-1)][0] = bcolor;
        leds[wx(bbar_x)][0] = bcolor;
        leds[wx(bbar_x+1)][0] = bcolor;

        leds[ball_x][ball_y] = CRGB(255,255,255);
    }

    int wx(int x)
    {
        if (x < 0) return LED_ARRAY_WIDTH+x;
        if (x >= LED_ARRAY_WIDTH) return x-LED_ARRAY_WIDTH;
        return x;
    }

    int dir(int bar_x, int ball_x)
    {
        if (ball_x < bar_x) return -1;
        if (ball_x > bar_x) return 1;
        return 0;
    }
};