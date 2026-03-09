#include "Component.h"



void NewClock::StartClock() {
	clock.start();
}

void NewClock::StopClock() {
	clock.stop();
}

void NewClock::ResetClock() {
	clock.reset();
}

