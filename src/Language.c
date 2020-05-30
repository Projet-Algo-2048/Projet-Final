/**
 * @file language.c
 * @brief This file enable to have different language for the game.
 * For each language a new file must be create and redeclare in it all message corresponding to the id
 *
 * @author Brisset J.
 */

#include "headers/Language.h"
Cell * Data = NULL;

/**
 * @fn int unloadLanguage()
 * @brief Unregister all translation
 */
int unloadLanguage() {

    //FREE ALL MALLOC
    foreach(i, Data) {          //iterate i throught the list
        free(i->value);
    }
    freeAll(Data);              //free the whole list

    Data = NULL;                //reset header
    return 0;
}

/**
 * @fn int loadLanguage(const char * lang)
 * @brief This function register all message of the specified lang in Data 
 *
 * @param lang is the language to load (i.e. "en_us" for american translation)
 */
int loadLanguage(const char * lang) {

    if (Data != NULL) unloadLanguage();                                                     // Unload previously loaded language 

    char fileName[256] = "";
    sprintf(fileName, "%s%s.%s", LANG_DIRECTORY, lang, LANG_FILE_EXTENTION);                // set filename with format
    FILE* stream = fopen(fileName, "r");                                                    // get stream from file in read only if it exist

    if (stream == NULL && lang == DEFAULT_LANG) {                                           // DEFAULT LANG FILE DOES NOT EXIST
        Data = NULL;                                                                        // not necessary just a security
        return -1;
    }
    if (stream == NULL) {                                                                   // FILE NOT FOUND
        loadLanguage(DEFAULT_LANG);
        return -1;
    }

    char buffer[1024] = { 0 };                                                              // buffer which will get line by line the file
    while (fgets(buffer, sizeof(buffer), stream) != NULL) {                                 // READING THE WHOLE FILE
        if ( !strcmp(buffer, "\n") || buffer[0] == '#') continue;                           // ignore comments and empty line

        Translation * translate = malloc( sizeof(Translation) );                            // creating a new translation unit

        char id[TRANSLATION_LENGHT], message[TRANSLATION_LENGHT];
        sscanf(buffer, "%s = %s", id, message);

        sprintf(translate->id, id);
        sprintf(translate->message, message);                                               // setting var of the translation unit
        addValue(&Data, translate);                                                         // adding the translation unit to the translation list
    }

    fclose(stream);
    return 0;
}

/**
 * @fn char * getTranslatedText(const char * id)
 * @brief This function give the translation of the message in the current language
 *
 * @char id is the id of the message to translate (i.e. "game.title" )
 *
 * @return the translated message as string
 */
char * getTranslatedText(char * id) {
    foreach(i, Data) {                                                                                  //iterate i throught the list
        if (!strcmp( ((Translation*)i->value)->id, id ) ) return ((Translation *)i->value)->message;    // return the translation char * if translation id  and id are the same
    }
    return id;
}

/**
 * @fn int printfTranslationList()
 * @brief print all translation registered
 * @deprecated intend for debug uses
 */
int printfTranslationList() {
    foreach(i, Data) {                                                                                  //iterate i throught the list
        printf("%s : %s\n", ((Translation*)i->value)->id, ((Translation*)i->value)->message);
    }
    printf("\n");

    return 0;
} 