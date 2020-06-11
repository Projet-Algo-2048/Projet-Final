#include <stdio.h>
#include <string.h>

#include "headers/Game.h"
#include "headers/Logger.h"

int main(int argc, char** argv) {
	setLogger(FILE_LOGGING, INFO, NULL, NULL);
	
	for (int i = 1; i < argc; i++) {
		log(INFO, "Program start with argument >> %s", argv[i]);
		// execution argument
	}
	
	log(INFO, "Starting game");
	game();
	log(INFO, "End game");
}