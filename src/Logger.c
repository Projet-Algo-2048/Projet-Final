/**
 * @file Logger.c
 * @brief This file provide function for logging
 */

#include "headers/Logger.h"


/* Global variables */

bool LoggerEnabled = false;                 /**< If logging is enabled or not. Default : false */
LogLevel LoggerLevel = WARN;                /**< which level the logger will listen to. Default : WARN */
LogMode LoggerMode = FILE_LOGGING;          /**< in which mode the logger will work. Default FILE_LOGGING */

char LoggerFormat[LOGGER_ARRAY_LENGHT] = "[{LEVEL}]<{FUNCTION}> : {MESSAGE}";      /**< format of the logging. Default : [{LEVEL}]<{FUNCTION}> : {MESSAGE}*/
char LoggerFile[LOGGER_ARRAY_LENGHT] = "logs";                                     /**< Logger file's name. Default : logs */


/* Functions */

/**
 * @fn int setLogger(LogMode mode, LogLevel level, const char* filename, const char* directory)
 * @brief This function initialize the Logger
 * @param mode A LogMode variable which tell how the logger should work
 * @param level A LogLevel variable which tell what level to listen
 * @param filename A char * which is the name of the logger file. If LOG_IN_FILE mode was provided. A null value is allowed, in this case the logger will create a file with the current date
 * @param directory A char * which is the name of the directory where to save logger file. A null value is allowed and if filename was NULL directory will be set to logs/
 * @return 
 * @warning directory must be create before
 */
int setLogger(LogMode mode, LogLevel level, const char* filename, const char* directory) {
    time_t t = time(NULL);
    struct tm* currTime = localtime(&t);

    if (mode < 0 || mode > 3) {                                                                             // check if mode is a combination of LogMode
        printf("Error in setLogger >> Unknow LogMode : %d \n", mode);
        return LOGGER_UNKNOW_LOGMODE;
    }
    if (mode != 0) LoggerMode = mode;                                                                        // override default value

    if (level < 0 || level > 5) {                                                                           // check if level is a LogLevel
        printf("Error in setLogger >> Unknow LogLevel : %d \n", level);
        return LOGGER_UNKNOW_LOGLEVEL;
    }
    if (level != 0) LoggerLevel = level;                                                                    // override default value

    int result = 0;
    if((LoggerMode & FILE_LOGGING) == FILE_LOGGING) {                                                             // set logger file if FILE_LOGGING is specified
        if (filename == NULL) {                                                                             // check if filename is empty
            char file[LOGGER_PATH_LENGTH] = { 0 };
            sprintf(file, "%.10s %d%s", asctime(currTime), currTime->tm_year + 1900, LOG_FILE_EXTENSION);           // set file with the current date


            if (directory == NULL) {                                                                        // check if directory is empty
                result = setLoggerFile(file, LOG_DEFAULT_FOLDER);                                           // in case set directory to default
            } else {
                result = setLoggerFile(file, directory);
            }
        } else {
            result = setLoggerFile(filename, directory);
        }
    }

    if (result > LOGGER_SUCCESS) return result;

    logInFile("\n================ New Record ================\n");
    char date[LOGGER_ARRAY_LENGHT];
    sprintf(date, "Date : %s\n", asctime(currTime));
    logInFile(date);

    LoggerEnabled = true;                               //if all is right enable Logger

    return LOGGER_SUCCESS;
}

/**
 * @fn int setLogFormat(const char* format)
 * @brief set format of the logging
 * You can use some placeholders in yout format. It looks like that `{PLACEHOLDER}` 
 * Here a list of available placeholders :
 * - MESSAGE -> replace by the message
 * - DATE -> replace by the current date. Not implemented yet !
 * - TIME -> replace by the current time. Not implemented yet !
 * - FUNCTION -> replace by the current function.
 * - FILE -> replace by the current file.
 * - LINE -> replace by the current line. Not implemented yet !
 * @param format the wanted format
 * @return @see {LOGGER_ILLEGAL_FORMAT}, @see {LOGGER_ERROR}, @see {LOGGER_SUCCES}
 * @warning Some placeholder are not implemented yet
 */
int setLogFormat(const char* format) {
    if (format == NULL || strlen(format) <= 1) return LOGGER_ILLEGAL_FORMAT;    // format must be different of NULL and wider than 1
    sprintf(LoggerFormat, format);                                                 // set LogFormat
    return LOGGER_SUCCESS;
}

/**
 * @fn int setLoggerFile(const char* filename, const char* directory)
 * @brief set log file
 * @param filename the name of the file. Must not be NULL.
 * @param directory the name of the directory.
 */
int setLoggerFile(const char* filename, const char* directory) {
    char temp[LOGGER_PATH_LENGTH] = { 0 };

    if (directory != NULL) {                                    /* In case a log directory is provided */
        if (directory[strlen(directory) - 1] != '/') {          /* direcory must be a path to a directory */
            printf("Error in setLoggerFile >> Not a directory path : %s \n Could not set logger file \n", directory);
            return LOGGER_ILLEGAL_DIRECTORY;
        }
        if (strlen(directory) > sizeof(temp)) {                 /* directory's lenght must be less than temp's lenght */
            printf("Error in setLoggerFile >> Path length too long : %d instead of %d \n Could not set logger file \n", strlen(directory), sizeof(temp));
            return LOGGER_PATH_TOO_LONG;
        }
        strcat(temp, directory);
    }

    if (filename == NULL) {                                     /* In case no file is provided */
        printf("Error in setLoggerFile >> File name empty \n. Could not set logger file \n");
        return LOGGER_FILENAME_EMPTY;
    }
    if (strlen(directory) + strlen(filename) > sizeof(temp)) {  /* lof file path must be less than temp's lenght*/
        printf("Error in setLoggerFile >> Path length too long : %d instead of %d \n Could not set logger file \n", strlen(directory), sizeof(temp));
        return LOGGER_PATH_TOO_LONG;
    }
    strcat(temp, filename);

    FILE* stream = fopen(temp, "a");
    if (stream == NULL) return LOGGER_FILE_NOT_OPEN;
    fclose(stream);

    strcpy(LoggerFile, temp);                       // set LoggerFile

    return LOGGER_SUCCESS;
}

/**
 * @fn logFormatter(LogLevel level, char* message, const char* fn, const char* file, const char* line)
 * @brief format the log message
 * @internal
 * @todo implement TIME,DATE,LINE
 */
char * logFormatter(LogLevel level, char* message, const char* fn, const char* file, const int line) {
    if (level == RAW) {
        strcat(message, "\n");
        return message;
    }

    char tempMsg[LOGGER_ARRAY_LENGHT];
    strcpy(tempMsg, message);
    memset(message, 0, LOGGER_ARRAY_LENGHT);

    int i = 0; int k = 0;
    while (LoggerFormat[i] != '\0') {
        if (LoggerFormat[i] == '{') {

            int j = 1; char placeholder[16] = { 0 };
            while (j < 16 && LoggerFormat[i + j] != '}') {
                placeholder[j - 1] = LoggerFormat[i + j];
                j++;
            }

            if (!strcmp(placeholder, "LEVEL")) {
                switch (level) {
                case DEBUG: strcat(message, "DEBUG"); k += 5; break;
                case INFO: strcat(message, "INFO"); k += 4; break;
                case WARN: strcat(message, "WARN"); k += 4; break;
                case ERROR: strcat(message, "ERROR"); k += 5; break;
                }

            } else if (!strcmp(placeholder, "DATE")) {
                //<-- Not implemented yet -->

            } else if (!strcmp(placeholder, "TIME")) {
                //<-- Not implemented yet -->

            } else if (!strcmp(placeholder, "MESSAGE")) {
                strcat(message, tempMsg);
                k += strlen(tempMsg);

            } else if (!strcmp(placeholder, "FUNCTION")) {
                char temp[32];
                strcpy(temp, fn);
                strcat(message, toUpperCase(temp));
                k += strlen(temp);

            } else if (!strcmp(placeholder, "FILE")) {
                strcat(message, file);
                k += strlen(file);

            }
            i = i + j;
        } else {
            message[k++] = LoggerFormat[i];
        }
        i++;
    }
    if (k < LOGGER_ARRAY_LENGHT) { message[k] = '\n'; } else { message[LOGGER_ARRAY_LENGHT] = '\n'; }
    return message;
}

/**
 * @fn logg(LogLevel level, const char* fn, const char file, const int line, char* format, ...)
 * @brief this function log message but need special argument so use @see log(level,...)
 * @warning please use @see log instead
 */
int logg(LogLevel level, const char* fn, const char* file, const int line, char* format, ...) {
    if (!LoggerEnabled) {                                      // check if Logger is enabled
        return LOGGER_NOT_ENABLED;
    }
    if (level < LoggerLevel) {                              // check if level is Higher than LoggerLevel
        return LOGGER_LEVEL_NOT_HIGH_ENOUGH;
    }

    va_list list;                                           // initialise ellipsis arguments
    va_start(list, format);

    char msg[LOGGER_ARRAY_LENGHT] = { 0 };
    FILE* stream = fmemopen(msg, sizeof(msg), "w+");        // open msg as stream
    vfprintf(stream, format, list);                         // replace placeholder by ellipsis arguments
    fclose(stream);                                         // close stream

    va_end(list);                                           // close ellipsis argument

    char * message = logFormatter(level, msg, fn, __FILE__, __LINE__);    //format message

    logInConsole(message);                                  //log it in file
    logInFile(message);                                     //log it in console

    return LOGGER_SUCCESS;
}

/**
 * @fn int logInConsole(const char * message)
 * @brief Log message in file
 * @internal
 */
int logInConsole(const char * message) {

    if ((LoggerMode & CONSOLE_LOGGING) == CONSOLE_LOGGING) {        // Logger must be set with CONSOLE_LOGGING specified
        printf(message);
        return LOGGER_SUCCESS;
    } else {
        return LOGGER_CONSOLE_LOGGING_NOT_ENABLED;
    }
}
/**
 * @fn int logInFile(const char* message)
 * @brief Log message in console
 * @internal
 */
int logInFile(const char* message) {
    if (LoggerEnabled) {
        if ((LoggerMode & FILE_LOGGING) == FILE_LOGGING) {              // Logger must be set with FILE_LOGGING specified
            FILE* stream = fopen(LoggerFile, "a");                      // open log file
            if (stream == NULL) {                                       // handle file not open
                printf("Error in LogInFile >> Could not open log file : %s \n", LoggerFile);
                return LOGGER_FILE_NOT_OPEN;
            }

            fprintf(stream, message);
            fclose(stream);                                             // close log file

            return LOGGER_SUCCESS;
        }
        return LOGGER_FILE_LOGGING_NOT_ENABLED;
    }
}

//<--------------- UTILS ------------------->
char* toUpperCase(char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] >= 97 && str[i] <= 122) {
            str[i] = str[i] - 32;
        }
    }
    return str;
}