#pragma once

#ifndef VISELHETOLILYGO_ANIMATIONS_H
#define VISELHETOLILYGO_ANIMATIONS_H
#include "dataTypes.h"
#include <TFT_eSPI.h>

extern TFT_eSprite canvas;
extern TFT_eSprite logoCanvas;
extern char letters[];

void drawBeer(Kobanyai k[], int m);
void drawMatrix(Matrix mat[], int m);
void drawLogo(TTAT t[], int m);
void drawText(TextAnim &t);
void drawTempus(TTAT t[], int m);
void drawDVD(TTAT t[], int m);

#endif //VISELHETOLILYGO_ANIMATIONS_H