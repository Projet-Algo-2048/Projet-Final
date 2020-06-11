#include "test.c"
#include "../src/headers/Logger.h"


int main(void) {

	printf("trying to log when log is not enable \n");
	testInt(log(INFO, "test"), LOGGER_NOT_ENABLED);

	printf("Trying to set Logger mode with invalid mode \n");
	testInt(setLogger(4, INFO, NULL, NULL), LOGGER_UNKNOW_LOGMODE);

	printf("Trying to set Logger level with invalid level \n");
	testInt(setLogger(FILE_LOGGING, -1, NULL, NULL), LOGGER_UNKNOW_LOGLEVEL);

	printf("Trying to set logger path with invalid path \n");
	testInt(setLogger(FILE_LOGGING, INFO, NULL, "test"), LOGGER_ILLEGAL_DIRECTORY);

	printf("Trying to setLogger with default value\n");
	testInt(setLogger(0, 0, NULL, NULL), LOGGER_SUCCESS);
	printf("LoggerMode : %d \n",LoggerMode);
	printf("LoggerLevel : %d \n", LoggerLevel);
	printf("LoggerFile : %s \n", LoggerFile);
	printf("\n");

	printf("Trying to log message when level is not high enough \n");
	testInt(log(DEBUG, "test"), LOGGER_LEVEL_NOT_HIGH_ENOUGH);

	setLogger(CONSOLE_LOGGING | FILE_LOGGING, 0, NULL, NULL);
	printf("trying to log in console \n");
	log(WARN, "test");
	printf("\n");

	printf("Trying to log in console with new format \n");
	setLogFormat("<{LEVEL}> : {MESSAGE}");
	log(WARN, "test");

}