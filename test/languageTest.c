#include <stdlib.h>
#include "../src/headers/Language.h"
#include "test.c"

int main(void) {
	printf("Open file test \n");
	testInt(loadLanguage("en_us"), 0);

	printf("Open not existing file test \n");
	testInt(loadLanguage("en_fr"), -1);

	unloadLanguage();
	printf("TranslationList Null before language change test \n");
	testPointer(TranslationList, NULL, true);

	loadLanguage("en_us");
	printf("TranslationList not Null after language change test \n");
	testPointer(TranslationList, NULL, false);

	printfTranslationList();

	printf("Language translation with existing id test \n");
	testString(getTranslatedText("test.1"), "test");

	printf("Language translation with not existing id test \n");
	testString(getTranslatedText("test.2"), "test.2");

	getAvailableLanguage("ressources/lang/");
	printf("Language Available test \n");
	testPointer(AvailableLanguage,NULL,false);

	printfAvailableLanguage();

	freeAvailableLanguage();
}

