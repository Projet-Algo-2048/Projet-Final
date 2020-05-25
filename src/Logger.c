/**
 * @file Logger.c
 * @brief this file will contain function to log message
 */

#include "headers/Logger.h"

/**
 * @fn int initLogger(LogMode mode, LogLevel level, char* filename)
 * @brief initialize all parameter
 */
int initLogger(LogMode mode, LogLevel level, char* filename) {
    time_t date;
    time(&date);

    LoggerMode = mode;
    LoggerLevel = level;
    char temp[32];
    if (filename == NULL) {  
        sprintf(temp, "%s/%s.%s", "logs", ctime(&date), "log");
        if (!setLoggerFile(temp)) {
            log(RAW, "################# new record #################");
            log(RAW, "DATE : %s", ctime(&date));
        }
    }
    else {
        if (!setLoggerFile(filename)) {
            log(RAW, "################# new record #################");
            log(RAW, "DATE : %s", ctime(&date));
        }
    }

}

/**
 * @fn int setLoggerFile(char* filename)
 * @brief change LoggerFile
 */
int setLoggerFile(char* filename) {
    if (filename == NULL) {
        return -1;

    } else {
        FILE* stream = fopen(filename, "w+");
        if (stream == NULL) {
            return -1;

        } else {
            sprintf(LoggerFile, filename);
            fclose(stream);
            return 0;
        }
    }
}

/**
 * @fn int setLoggerFormat(char* format)
 * @brief change format of logging
 */
int setLoggerFormat(char* format) {
    if (format != NULL && strlen(format) > 1) sprintf(LogFormat, format);
}


/**
 * @fn formatLogMsg(LogLevel lvl, const char* functionName, const char* fileName, const char* msg, char * str)
 * @brief format str whit current format logging
 */
int formatLogMsg(LogLevel lvl, const char* functionName, const char* fileName, const char* msg, char * str) {
    if (lvl == RAW) { strcpy(str, msg); strcat(str, "\n"); return -1; }

    int i = 0, j = 0, k = 0;
    while (LogFormat[i] != '\0') {

        if (LogFormat[i] == '{') {
            i++;
            char placeholder[16] = {0};
            j = 0;
            while (LogFormat[i + j] != '}') {
                placeholder[j] = LogFormat[i + j];
                j++;
            }
            
            if (!strcmp(placeholder, "LEVEL")){
                switch (lvl) {
                    case DEBUG: strcat(str, "DEBUG"); k += 5; break;
                    case INFO: strcat(str, "INFO"); k += 4; break;
                    case WARN: strcat(str, "WARN"); k += 4; break;
                    case ERROR: strcat(str, "ERROR"); k += 5; break;
                }

            } else if (!strcmp(placeholder, "DATE")) {
                strcat(str, __DATE__);
                k += strlen(__DATE__);

            } else if (!strcmp(placeholder, "TIME")) {
                strcat(str, __TIME__ );
                k += strlen(__TIME__);

            } else if (!strcmp(placeholder, "MESSAGE")) {
                strcat(str, msg);
                k += strlen(msg);
            
            }else if (!strcmp(placeholder, "FUNCTION")) {
                    strcat(str, functionName);
                    k += strlen(functionName);

            }else if (!strcmp(placeholder, "FILE")) {
                    strcat(str, fileName);
                    k += strlen(fileName);

            }
            i = i + j;

        } else {
            str[k++] = LogFormat[i];
        }
        i++;
    }

    if (k < 512) { str[k] = '\n'; } else {str[512] = '\n'; }
}

/**
 * @fn int logInFile(char* str)
 * @brief print logging message to file
 */
int logInFile(char* str) {
    if ((LoggerMode & LOG_FILE) == LOG_FILE) {
        FILE* stream = fopen(LoggerFile, "a");
        if (stream == NULL) {
            printf("[ERROR] Could not open log file \n");
            return -1;
        }

        fprintf(stream, str);
        fclose(stream);

        return 0;
    }
    return -1;
}

/**
 * @fn int logInConsole(char* str)
 * @brief print logging message to screen
 */
int logInConsole(char* str) {
    if ((LoggerMode & LOG_CONSOLE) == LOG_CONSOLE) printf(str);
}


int logg(LogLevel lvl, const char* functionName, const char* fileName, const char* format, ...) {
    if (lvl == NONE) {
        printf("[WARN] Could not use this level for logging !");
        return -1;
    }

    if (lvl >= LoggerLevel) {
        va_list list;
        va_start(list, format);

        char msg[256] = { 0 };
        FILE* stream = fmemopen(msg, 256, "w+");
        vfprintf(stream, format, list);
        fclose(stream);

        char str[512] = { 0 };
        formatLogMsg(lvl, functionName, fileName, msg, str);

        logInConsole(str);
        logInFile(str);

        va_end(list);
        return 0;
    }
    return -1;
}