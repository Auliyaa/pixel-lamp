#pragma once

#include <animations/bmp.h>

struct evs_t: public animation_rotating_bmp_t<200>
{
    virtual animation_step_t get(size_t idx) const
    {
        return _a[idx];
    }
    virtual size_t size() const
    {
      return 1;
    }
    animation_step_t _a[1] = {
      {10,{10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,0,114,187,10,10,10,247,148,29,10,10,10,142,198,63,10,10,10,10,10,10,10,10,10,0,114,187,10,10,10,247,148,29,10,10,10,142,198,63,10,10,10,10,10,10,10,10,10,0,114,187,10,10,10,247,148,29,10,10,10,142,198,63,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,74,192,238,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,74,192,238,74,192,238,74,192,238,10,10,10,10,10,10,10,10,10,84,100,175,74,192,238,74,192,238,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,84,100,175,144,120,182,144,120,182,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,144,120,182,144,120,182,144,120,182,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,144,120,182,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,146,39,143,10,10,10,227,30,39,237,27,36,227,30,39,10,10,10,10,10,10,10,10,10,146,39,143,10,10,10,228,113,172,10,10,10,247,148,29,10,10,10,10,10,10,10,10,10,122,96,170,74,192,238,122,96,170,10,10,10,247,148,29,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,}},
    };
};