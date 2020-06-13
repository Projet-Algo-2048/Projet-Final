#ifndef Language
#define Language

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "LinkedList.h"

#define LANG_DIRECTORY "ressources/lang/"
#define LANG_FILE_EXTENSION "lang"
#define DEFAULT_LANG "en_us"

/**
 * @def TRANSLATION_LENGHT max lenght of translation and id
 */
#define TRANSLATION_LENGHT 256

/**
 * @struct Translation
 * @brief This structure represente a traduction
 */
typedef struct {
    char id[TRANSLATION_LENGHT];            /**<id of the message */
    char message[TRANSLATION_LENGHT];       /**<translated message */
} Translation;

/**
 * @struct LanguageFile
 * @brief structure that store a string of which language the file translate and the corresponding filename
 */
typedef struct {
    char language[TRANSLATION_LENGHT];      /**< Language of the traduction */
    char filename[TRANSLATION_LENGHT];      /**< the name of file which hold the translate */
} LanguageFile;

/**
 * @enum LanguageException
 * @brief Hold all exception that can be return
 */
typedef enum {
    LANGUAGE_CAN_NOT_OPEN_DIRECTORY,
    LANGUAGE_CAN_NOT_OPEN_FILE,
    LANGUAGE_FILE_MALFORMATED,
    LANGUAGE_DEFAULT_LANG_FILE_NOT_FOUND,
    LANGUAGE_FILE_NOT_FOUND,
} LanguageException;


extern Cell* TranslationList;  /**< A LinkedList that contain as value a pointer to a Translation struct */
extern Cell* AvailableLanguage; /**< A LinkedList that hold as value a pointer to a LanguageFile struct */

Cell* getAvailableLanguage();
int freeAvailableLanguage();
int unloadLanguage();
int loadLanguage(const char*);
char* getTranslatedText(char*);
int printfAvailableLanguage();
int printfTranslationList();

#endif