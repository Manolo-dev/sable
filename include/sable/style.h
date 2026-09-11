#pragma once
#include <sable/util.h>
#include <sable/mat.h>
#include <sable/div.h>

#define STYLE_INIT                 \
    (Style){                       \
        .color = 0,                \
        .left = 0,                 \
        .top = 0,                  \
        .antialiasing = 1.0f,      \
        .alpha = 1.0f,             \
        .transform = MAT_IDENTITY, \
        .anchor = LEFT_TOP,        \
    }                              \

typedef enum {
    LEFT_TOP      = 0,
    LEFT_CENTER   = 1,
    LEFT_BOTTOM   = 2,
    CENTER_TOP    = 3,
    CENTER        = 4,
    CENTER_BOTTOM = 5,
    RIGHT_TOP     = 6,
    RIGHT_CENTER  = 7,
    RIGHT_BOTTOM  = 8,
} Anchor;

typedef struct {
    int color;
    Unit left;
    Unit top;
    float alpha;
    float antialiasing;
    Mat transform;
    Anchor anchor;
} Style;