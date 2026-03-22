#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

#define MAX_LINE_LENGTH 1024
#define MAX_WORD_LENGTH 256
#define MAX_FILES 10

void toLowerCase(char *str);
int countWordInLine(const char *line, const char *word, int exactMatch);
// logFile parametresi eklendi
int searchInSingleFile(const char *filename, const char *searchWord, int exactMatch, FILE *logFile);

#endif
