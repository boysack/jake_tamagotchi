#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "../timer/timer.h"
#include "./logic.h"
#include "../render/textures.h"

uint8_t t[3];; //timeInfo => h,m,s
//char timeString[8]; //DEFINITO NELL'HEADER
//char happiness = 5;	//DECRESCE OGNI TOT SECONDI
//char satiety = 5;

void logicInit() {
	happiness = 5;
	satiety = 5;
	t[0]=0;
	t[1]=0;
	t[2]=0;
	updateTimeString();
	canReplay = 0;
}
void decreaseStat(uint8_t type) {
	//nessun comportamento standard, solo tanto rigore
	//ha senso implementarle come tipi diversi?
	if(type == 0) {
		happiness--;
		decreaseHappiness();
	}else if(type == 1) {
		satiety--;
		decreaseSatiety();
	}
}
void increaseStat(uint8_t type) {
	if(type == 0) {
		if(happiness<5){
			happiness++;
			increaseHappiness();
		}
	}else if(type == 1) {
		if(satiety<5) {
			satiety++;
			increaseSatiety();
		}
	}
}

void increaseTime() {
	t[2]++;
	if(t[2] == 60) {
		t[2] = 0;
		t[1]++;
		if(t[1] == 60) {
			t[1] = 0;
			t[0]++;
		}
	}
}
void updateTimeString() {
	char tmp[2];
	uint8_t i;
	char tmpTimeString[8];
	for(i=0;i<3;i++) {
		if(t[i]<10){
			sprintf(tmp, "0%d", t[i]);
		}else{
			sprintf(tmp, "%d", t[i]);
		}
		tmpTimeString[3*i] = tmp[0];
		tmpTimeString[3*i+1] = tmp[1];
		if(i<3){
			tmpTimeString[3*i+2] = ':';
		}
	}
	for(i=0; i<8;i++) {
		timeString[i] = tmpTimeString[i];
	}
}
uint8_t isDead() {
	if(happiness==0 || satiety==0) {
		return 1;
	}
	return 0;
}
void eatMeal() {
	if(satiety<5) {
		satiety++;
	}
}
void eatSnack() {
	if(happiness<5){
		happiness++;
	}
}
