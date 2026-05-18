#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <kepek.h>
#include <animations.h>

void drawBeer(Kobanyai k[], int m) {
    canvas.fillSprite(TFT_BLACK);

    for (int i = 0; i < m ; i++) {
        if ((k[i].x > xmax && k[i].dirX > 0) || (k[i].x < xmin && k[i].dirX < 0)){
            k[i].dirX = k[i].dirX * -1;
        }
        if ((k[i].y > ymax && k[i].dirY > 0) || (k[i].y < ymin && k[i].dirY < 0)) {
            k[i].dirY = k[i].dirY * -1;
        }
        k[i].x += k[i].dirX;
        k[i].y += k[i].dirY;

        canvas.pushImage(k[i].x,k[i].y,beerw,beerh,beer);
    }
    while(digitalRead(9) == LOW);
    canvas.pushSprite(0,0);
}

void drawLogo(TTAT t[], int m) {
    canvas.fillSprite(TFT_BLACK);

    for (int i = 0; i < m ; i++) {
        if ((t[i].x > xmaxlogo && t[i].dirX > 0) || (t[i].x < xmin && t[i].dirX < 0)){
            t[i].dirX = t[i].dirX * -1;
        }
        if ((t[i].y > ymax && t[i].dirY > 0) || (t[i].y < ymin && t[i].dirY < 0)) {
            t[i].dirY = t[i].dirY * -1;
        }
        t[i].x += t[i].dirX;
        t[i].y += t[i].dirY;

        logoCanvas.pushToSprite(&canvas, t[i].x, t[i].y, 0x1FF8);
    }
    while(digitalRead(9) == LOW);
   canvas.pushSprite(0,0);
}

void drawMatrix(Matrix mat[], int m) {
    canvas.fillSprite(TFT_BLACK);
    canvas.setTextSize(2);
    for (int i = 0; i < m ; i++) {
        for (int j = 0; j < mat[i].length ; j++) {
            uint16_t green = ( (63 - (j * (60 / mat[i].length))) << 5 );
            if (j == 0) {
                canvas.setTextColor(TFT_WHITE, TFT_BLACK);
            } else {
                canvas.setTextColor(green, TFT_BLACK);
            }
            canvas.setCursor(mat[i].x, mat[i].y - 10*j);
            canvas.print(letters[random(0,36)]);
        }
        mat[i].y = mat[i].y + mat[i].speed;
        if (mat[i].y - (mat[i].length * 10) > 170) {
            mat[i].y = 0;
            mat[i].speed = random(3,15);
            mat[i].length = random(6,11);
        }

    }
    while(digitalRead(9) == LOW);
    canvas.pushSprite(0, 0);

}

void drawText(TextAnim &t) {
    canvas.fillSprite(TFT_BLACK);
    canvas.setTextSize(5);
    int textWidth = strlen(t.text) * 30;
    if (t.x > -textWidth) {
        t.x -= t.speed;
    } else {
        t.x = 320;
    }
    canvas.setCursor(t.x, t.y);
    canvas.setTextColor(TFT_WHITE, TFT_BLACK);
    canvas.setTextWrap(false);
    canvas.print(t.text);
    while(digitalRead(9) == LOW);
    canvas.pushSprite(0,0);

}

void drawTempus(TTAT t[], int m) {
    canvas.fillSprite(TFT_BLACK);

    for (int i = 0; i < m ; i++) {
        if ((t[i].x > (320 - tempusw) && t[i].dirX > 0) || (t[i].x < xmin && t[i].dirX < 0)){
            t[i].dirX = t[i].dirX * -1;
        }
        if ((t[i].y > (170 - tempush) && t[i].dirY > 0) || (t[i].y < ymin && t[i].dirY < 0)) {
            t[i].dirY = t[i].dirY * -1;
        }
        t[i].x += t[i].dirX;
        t[i].y += t[i].dirY;

        canvas.pushImage(t[i].x, t[i].y, tempusw, tempush, tempus);
    }
    while(digitalRead(9) == LOW);
    canvas.pushSprite(0,0);
}

const uint16_t dvdColors[] = { TFT_RED, TFT_GREEN, TFT_BLUE, TFT_YELLOW, TFT_CYAN, TFT_MAGENTA, TFT_WHITE, 0xFD20, 0x7BEF };
static uint16_t dvdColor = TFT_RED;

void drawDVD(TTAT t[], int m) {
    canvas.fillSprite(TFT_BLACK);

    for (int i = 0; i < m ; i++) {
        bool bounced = false;
        if ((t[i].x > (320 - dvdw) && t[i].dirX > 0) || (t[i].x < 0 && t[i].dirX < 0)){
            t[i].dirX = t[i].dirX * -1;
            bounced = true;
        }
        if ((t[i].y > (170 - dvdh) && t[i].dirY > 0) || (t[i].y < 0 && t[i].dirY < 0)) {
            t[i].dirY = t[i].dirY * -1;
            bounced = true;
        }
        t[i].x += t[i].dirX;
        t[i].y += t[i].dirY;

        if (bounced) {
            uint16_t newColor;
            do {
                newColor = dvdColors[random(0, 9)];
            } while (newColor == dvdColor);
            dvdColor = newColor;
        }

        canvas.drawBitmap(t[i].x, t[i].y, dvd, dvdw, dvdh, dvdColor);
    }
    while(digitalRead(9) == LOW);
    canvas.pushSprite(0,0);
}



