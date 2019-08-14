/*
  Скетч к проекту "Классический pong на oled дисплее"
  Страница проекта (схемы, описания): https://alexgyver.ru/microPong/
  Исходники на GitHub: https://github.com/AlexGyver/microPong/
  Нравится, как написан код? Поддержи автора! https://alexgyver.ru/support_alex/
  Автор: AlexGyver Technologies, 2019
  https://AlexGyver.ru/
*/

#define GAME_SPEED 100    // стандартный период движения шарика
#define II_SPEED 250      // стандартный период движения противника
#define RANDOM_BOUNCE 1   // отбивать шарик в случайном направлении

// пины
#define BTN_UP 3
#define BTN_DWN 4

// другие настройки
#define X_PLAYER_1 7
#define X_PLAYER_2 55
#define RACKET_LEN 5

int8_t ballPos[2];
int8_t ballSpeed[2];
uint32_t ballTimer, enemyTimer;
boolean btnFlag1, btnFlag2;
int8_t racketPos1, racketPos2 = 0;
int8_t prevRacketPos1, prevRacketPos2 = 0;
byte count1, count2;
byte speedIncr = 0, iiIncr = 0;

#include <Wire.h>

void setup() {
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DWN, INPUT_PULLUP);
  Wire.begin();
  oledInit();
  oledClear();
  digit(0, 0, 0);
  digit(0, 20, 0);

  randomSeed(analogRead(0));
  newRound();
  redrawRacket();
  redrawRacket2();
}

void loop() {
  ballRoutine();
  buttonTick();
  enemyTick();
}

void enemyTick() {
  if (millis() - enemyTimer >= (II_SPEED - iiIncr)) {
    enemyTimer = millis();
    if (racketPos2 + RACKET_LEN / 2 > ballPos[1]) racketPos2--;
    else racketPos2++;
    racketPos2 = constrain(racketPos2, 0, 16 - RACKET_LEN);
    redrawRacket2();
  }
}

void buttonTick() {
  if (!digitalRead(BTN_DWN) && !btnFlag1) {
    btnFlag1 = true;
    racketPos1 += 2;
    if (racketPos1 > (16 - RACKET_LEN)) racketPos1 = (16 - RACKET_LEN);
    redrawRacket();
  }
  if (digitalRead(BTN_DWN) && btnFlag1) {
    btnFlag1 = false;
  }
  if (!digitalRead(BTN_UP) && !btnFlag2) {
    btnFlag2 = true;
    racketPos1 -= 2;
    if (racketPos1 < 0) racketPos1 = 0;
    redrawRacket();
  }
  if (digitalRead(BTN_UP) && btnFlag2) {
    btnFlag2 = false;
  }
}

void redrawRacket() {
  for (byte i = prevRacketPos1; i < prevRacketPos1 + RACKET_LEN; i++) {
    dotClear(X_PLAYER_1, i);
  }
  for (byte i = racketPos1; i < racketPos1 + RACKET_LEN; i++) {
    dotSet(X_PLAYER_1, i);
  }
  prevRacketPos1 = racketPos1;
}

void redrawRacket2() {
  for (byte i = prevRacketPos2; i < prevRacketPos2 + RACKET_LEN; i++) {
    dotClear(X_PLAYER_2, i);
  }
  for (byte i = racketPos2; i < racketPos2 + RACKET_LEN; i++) {
    dotSet(X_PLAYER_2, i);
  }
  prevRacketPos2 = racketPos2;
}

void ballRoutine() {
  if (millis() - ballTimer >= (GAME_SPEED - speedIncr)) {
    ballTimer = millis();
    int8_t prevPos[2];
    for (byte i = 0; i < 2; i++) {
      prevPos[i] = ballPos[i];
      ballPos[i] += ballSpeed[i];
    }

    if (ballPos[0] < X_PLAYER_1) {
      if (!(prevPos[1] >= racketPos1 && prevPos[1] <= (racketPos1 + RACKET_LEN))) {
        count2++;
        if (count2 > 9) {
          digit(count2 / 10, 20, 0);
          digit(count2 % 10, 20, 1);
        } else {
          digit(count2, 20, 0);
        }

        delay(1000);
        newRound();
        dotClear(prevPos[0], prevPos[1]);
        return;
      } else {
        ballPos[0] = prevPos[0];
        ballSpeed[0] = -ballSpeed[0];
        if (RANDOM_BOUNCE) ballSpeed[1] *= (random(0, 2)) ? 1 : -1;
      }
    }
    if (ballPos[1] < 0) {
      ballPos[1] = -ballPos[1];
      ballSpeed[1] = -ballSpeed[1];
    }

    if (ballPos[0] > X_PLAYER_2) {
      if (!(prevPos[1] >= racketPos2 && prevPos[1] <= (racketPos2 + RACKET_LEN))) {
        count1++;
        if (count1 > 9) {
          digit(count1 / 10, 0, 0);
          digit(count1 % 10, 0, 1);
        } else {
          digit(count1, 0, 0);
        }

        delay(1000);
        newRound();
        dotClear(prevPos[0], prevPos[1]);
        return;
      } else {
        ballPos[0] = prevPos[0];
        ballSpeed[0] = -ballSpeed[0];
        if (RANDOM_BOUNCE) ballSpeed[1] *= (random(0, 2)) ? 1 : -1;
      }
    }
    if (ballPos[1] > 15) {
      ballPos[1] = 15;
      ballSpeed[1] = -ballSpeed[1];
    }

    dotClear(prevPos[0], prevPos[1]);
    dotSet(ballPos[0], ballPos[1]);
  }
}

void newRound() {
  randomSeed(millis());
  ballPos[0] = X_PLAYER_1 + 1;
  racketPos1 = random(0, 16 - RACKET_LEN);
  ballPos[1] = racketPos1 + RACKET_LEN / 2;
  ballSpeed[0] = 2;
  ballSpeed[1] = (random(0, 2)) ? 1 : -1;
  //racketPos2 = 8;
  redrawRacket();
  redrawRacket2();
  if (count1 >= 10) {
    speedIncr = 10;
    iiIncr = 70;
  }
  if (count1 >= 20) {
    speedIncr = 25;
    iiIncr = 150;
  }
  if (count1 >= 30) {
    speedIncr = 40;
    iiIncr = 190;
  }
}
