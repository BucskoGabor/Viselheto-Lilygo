#include <Arduino.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <SPI.h>
#include <OneButton.h>
#include "kepek.h"
#include "dataTypes.h"
#include "animations.h"
#include "menu.h"
#include "dice.h"

#define TFT_BL 38
#define TFT_POWER 15
#define TFT_VSYNC 9

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite canvas = TFT_eSprite(&tft);
TFT_eSprite logoCanvas = TFT_eSprite(&tft);

OneButton btn;
OneButton btn2;

RTC_DATA_ATTR Animation animation = ANIMATION_BEER;
RTC_DATA_ATTR Status status = MENU;

char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const int lenght = 35;

Kobanyai beers[4];
TTAT logo[4];
Matrix mat[32];
TextAnim textAnim;
Dice kocka[2];

const int matrixSize = 32;
const int size = 4;
const int kockasize = 2;

unsigned long lastUpdate = 0;
const int refreshRate = 1000/37;

static void buttonPressed();
static void buttonLongPressed();
static void startSleep();

RTC_DATA_ATTR int currentMenu = 0;

void setup() {
    randomSeed(esp_random());

    pinMode(TFT_VSYNC,INPUT);
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
    pinMode(TFT_POWER, OUTPUT);
    digitalWrite(TFT_POWER, HIGH);

    tft.init();
    tft.setRotation(1);

    WiFi.mode(WIFI_OFF);
    btStop();

    canvas.createSprite(320,170);
    canvas.setSwapBytes(true);

    logoCanvas.createSprite(ttatw, ttath);
    logoCanvas.setSwapBytes(false);
    logoCanvas.pushImage(0, 0, ttatw, ttath, ttat);

    pinMode(14, INPUT_PULLUP);
    while (digitalRead(14) == LOW) {
        delay(10);
    }

    btn.setup(
        0,
        true,
        true
        );

    btn2.setup(
        14,
        true,
        true
        );

    btn2.attachClick(buttonPressed);
    btn2.attachLongPressStart(buttonLongPressed);
    btn.attachLongPressStart(startSleep);


    //If btn on pin 0 is nonfunctional then use this to initiate deep sleep
    //Remember to change the startSleep function at the bottom
    //btn2.attachDoubleClick(startSleep);

    for (int i = 0; i < size ; i++) {
        beers[i].x = random(xmin,xmax);
        beers[i].y = random(ymin,ymax);
        beers[i].dirX = random(-3,3);
        beers[i].dirY = random(-3,3);
        if (beers[i].dirX == 0) {
            beers[i].dirX++;
        }
        if (beers[i].dirY == 0) {
            beers[i].dirY++;
        }
    }
    for (int i = 0; i < size ; i++) {
        logo[i].x = random(xmin,xmaxlogo);
        logo[i].y = random(ymin,ymax);
        logo[i].dirX = random(-3,3);
        logo[i].dirY = random(-3,3);
        if (logo[i].dirX == 0) {
            logo[i].dirX++;
        }
        if (logo[i].dirY == 0) {
            logo[i].dirY++;
        }
    }
    for (int i = 0; i < matrixSize; i++) {
        mat[i].x = 10 * i;
        mat[i].y = random(1,150);
        mat[i].speed = random(4,15);
        mat[i].length = random(6,11);
    }

    textAnim.speed = 3;
    textAnim.x = 320;
    textAnim.y = 70;
    textAnim.text = "bALEK EKS!";

    kocka[0].x=66;
    kocka[0].y=50;
    kocka[0].side=6;

    kocka[1].x=66*3;
    kocka[1].y=50;
    kocka[1].side=6;
}


void loop() {
    unsigned long currentTime = millis();
    btn2.tick();
    btn.tick();

    if (currentTime - lastUpdate >= refreshRate) {
        switch (status) {
            case MENU:
                drawMenu();
                break;
            case ANIMATIONS:
                switch (animation) {
                case ANIMATION_BEER:
                        drawBeer(beers, size );
                        break;
                case ANIMATION_MATRIX:
                        drawMatrix(mat,matrixSize);
                        break;
                case ANIMATION_TTAT:
                        drawLogo(logo, size );
                        break;
                case ANIMATION_TEXT:
                        drawText(textAnim);
                        break;
                case ANIMATION_TEMPUS:
                        drawTempus(logo, 1);
                        break;
                case ANIMATION_DVD:
                        drawDVD(logo, 1);
                        break;
                default:
                        break;
                }
                break;
            case DICE:
                drawDice(kocka,kockasize);
                break;
            default:
             break;
        }

        lastUpdate = currentTime;

    }

}

static void buttonPressed() {
    if (status == ANIMATIONS) {
        int nextNum = ((int)animation+1) % 6;
        animation = (Animation)nextNum;
    }else if (status == MENU) {
        if (currentMenu == 0) {
            currentMenu++;
        }else {
            currentMenu--;
        }
    }else {
        for (int i = 0; i < 10; i++) {
            delay(25);
            kocka[0].side = random(1,7);
            kocka[1].side = random(1,7);
            drawDice(kocka,kockasize);
        }
    }

}

static void buttonLongPressed() {
    if (status == ANIMATIONS || status == DICE) {
        status = MENU;
    }else {
        if (currentMenu == 0) {
            status = ANIMATIONS;
        }else {
            status = DICE;
        }
    }

}

static void startSleep() {
    digitalWrite(TFT_BL, LOW);
    tft.writecommand(ST7789_SLPIN);
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_14, 0);
    delay(150);
    esp_deep_sleep_start();
}

//If double click is used, use this function instead
/*
static void startSleep() {
    digitalWrite(TFT_BL, LOW);
    tft.writecommand(ST7789_SLPIN);
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_14, 0);
    while (digitalRead(14) == HIGH) {
        delay(20);
    }
    delay(150);
    esp_deep_sleep_start();
}
*/