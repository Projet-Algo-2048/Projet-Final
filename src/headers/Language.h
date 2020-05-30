#ifndef Language
#define Language

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"

#define LANG_DIRECTORY "ressources/lang/"
#define LANG_FILE_EXTENTION "lang"
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
    char id[TRANSLATION_LENGHT];            /*<id of the message >*/
    char message[TRANSLATION_LENGHT];       /*<translated message >*/
} Translation;

/**
 * @def Data
 * @brief A LinkedList that contain as value a pointer to a Translation struct
 */
extern Cell* Data;

int unloadLanguage();
int loadLanguage(const char*);
char* getTranslatedText(char*);
int printfTranslationList();

#endif