//array delle textures??
#include <stdint.h>

extern uint8_t animation;

void render();
void idle();
void walkAndEat(uint8_t frameCounter);
void drawMenu();
void hoverMeal(uint8_t isSelected);
void hoverSnack(uint8_t isSelected);
void drawTime();
void decreaseSatiety();
void increaseSatiety();
void decreaseHappiness();
void increaseHappiness();
void drawGameOver();
void textureInit();
