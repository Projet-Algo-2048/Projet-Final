#include "test.c"

#include "../src/Logger.c"

int fn() {
	log(INFO, "AN info log");
}

int main(void) {
	initLogger(LOG_FILE, INFO, "test.log");
	log(INFO, "start program");
	fn();

}