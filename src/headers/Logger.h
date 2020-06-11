#ifndef Logger
#define Logger

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdarg.h>

/**
 * @enum LogLevel
 * @brief enumerate all different level of logging
 */
typedef enum {
    DEBUG = 1,                  /**< Information for debug only */
    INFO,                       /**< Information */
    WARN,                       /**< Warning message*/
    ERROR,                      /**< Error message when an error occured*/
    RAW,                        /**< Unformatted Message. Do NOT use for LoggerLevel*/
    NONE,                       /**< Only use for LoggerLevel to log nothing*/
} LogLevel;

/**
 * @enum LogMode
 * @brief enumerate all mode of logging
 */
typedef enum {
    FILE_LOGGING = 1,           /**< Log in file. All log will be save in a file*/
    CONSOLE_LOGGING = 2,        /**< Log in Console. All log will be print on the console*/
} LogMode;

/**
 * @enum LogReturn
 * @brief Enumerate all return for Logger Function.
 */
typedef enum {
    LOGGER_SUCCESS = 0,                     /**< Returned when succes */
    LOGGER_ERROR,                           /**< Returned when an unhandled error occured */
    LOGGER_NOT_ENABLED,                     /**< Returned when attempting to log something and logger is disable */
    LOGGER_LEVEL_NOT_HIGH_ENOUGH,           /**< Returned when attempting to log something whith a level inferior than LoggerLevel */
    LOGGER_CONSOLE_LOGGING_NOT_ENABLED,     /**< Returned when attempting to log something in console when CONSOLE_LOGGING mode was not specified */
    LOGGER_FILE_LOGGING_NOT_ENABLED,        /**< Returned when attempting to log something in file when FILE_LOGGING mode was not specified */
    LOGGER_FILE_NOT_OPEN,                   /**< Returned when attempting to open log file and can not open it */
    LOGGER_ILLEGAL_FORMAT,                  /**< Returned when attempting to set formatter of logger with an unallowed format */
    LOGGER_ILLEGAL_DIRECTORY,               /**< Returned when attempting to set directory with an unallowed directory name */
    LOGGER_PATH_TOO_LONG,                   /**< Returned when path is too long */
    LOGGER_FILENAME_EMPTY,                  /**< Returned when provided an empty filename */
    LOGGER_UNKNOW_LOGMODE,                  /**< Returned when provided an unknow LogMode */
    LOGGER_UNKNOW_LOGLEVEL,                 /**< Returned when provided an unknow LogLevel */
} LogReturn;

#define LOG_FILE_EXTENSION ".log"
#define LOG_DEFAULT_FOLDER "logs/"

#define LOGGER_PATH_LENGTH 64
#define LOGGER_ARRAY_LENGHT 512

/**
 * @def log(level,...)
 * @brief send message to the logger
 * replace by logg with specific argument
 * - first parameter is the LogLevel
 * - second parameter is the message. Can contain c placeholder i.e. : %s,%d...
 * - then placeholder replacement
 * @return LogReturn
 */
#define log(level,...) logg(level, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__) //not use log(level,format,...) because '...' must not be null


extern bool LogEnabled;
extern LogLevel LoggerLevel;
extern LogMode LoggerMode;

extern char LoggerFormat[];
extern char LoggerFile[];


char* toUpperCase(char* str);
int logInFile(const char*);
int logInConsole(const char*);
char * logFormatter(LogLevel, char*, const char*, const char*, const int);
int logg(LogLevel, const char*, const char*, const int, char*, ...);
int setLoggerFile(const char*, const char*);
int setLogger(LogMode, LogLevel, const char*, const char*);
int setLogFormat(const char*);

#endif // !Logger
