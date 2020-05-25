#ifndef Logger
#define Logger

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef enum {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    RAW,
    NONE,
} LogLevel;

typedef enum {
    LOG_FILE = 1,
    LOG_CONSOLE = 2,
} LogMode;


LogLevel LoggerLevel = NONE;
LogMode LoggerMode = 0;

char LoggerFile[32] = { 0 };
char LogFormat[128] = "[{LEVEL}]<{FUNCTION}> in {FILE} >> {MESSAGE}";

#define log(level, ... ) logg(level, __FUNCTION__, __FILE__, __VA_ARGS__)

int logInConsole(char* str);
int logInFile(char* str);
int formatLogMsg(LogLevel, const char*, const char*, const char*, char*);
int logg(LogLevel, const char*, const char*, const char*, ...);
int setLoggerFile(char* filename);
int setLoggerFormat(char* format);
int initLogger(LogMode mode, LogLevel level, char* filename);

#endif