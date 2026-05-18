#pragma once
#ifndef VISELHETOLILYGO_DATATYPES_H
#define VISELHETOLILYGO_DATATYPES_H


enum Animation {
    ANIMATION_BEER,
    ANIMATION_MATRIX,
    ANIMATION_TTAT,
    ANIMATION_TEXT,
    ANIMATION_TEMPUS,
    ANIMATION_DVD
};

enum Status {
    MENU,
    ANIMATIONS,
    DICE
};

struct Kobanyai {
    int x;
    int y;
    int dirX;
    int dirY;
};

struct TTAT {
    int x;
    int y;
    int dirX;
    int dirY;
};

struct Matrix{
    int x;
    int y;
    int speed;
    int length;
};

struct TextAnim {
    int x;
    int y;
    int speed;
    const char* text;
};

struct Dice {
    int x;
    int y;
    int side;
};

const int xmax = 300;
const int xmaxlogo = 265;
const int ymax = 110;
const int xmin = -20;
const int ymin = 0;

#endif //VISELHETOLILYGO_DATATYPES_H