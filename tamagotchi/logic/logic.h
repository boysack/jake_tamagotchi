#include <stdint.h>

extern char timeString[8];
extern uint8_t satiety;
extern uint8_t happiness;
extern uint8_t canReplay;

void logicInit();
void decreaseStat(uint8_t type);
void increaseStat(uint8_t type);
void increaseTime();
void updateTimeString();
uint8_t isDead();
void eatMeal();
void eatSnack();
