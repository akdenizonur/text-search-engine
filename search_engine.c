#include "search_engine.h"

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int countWordInLine(const char *line, const char *word, int exactMatch) {
    int count = 0;
    const char *tmp = line;
    int wordLen = strlen(word);

    while ((tmp = strstr(tmp, word)) != NULL) {
        if (exactMatch) {
            int isStartBoundary = (tmp == line) || !isalnum((unsigned char)*(tmp - 1));
            int isEndBoundary = !isalnum((unsigned char)*(tmp + wordLen));
            if (isStartBoundary && isEndBoundary) count++;
        } else {
            count++;
        }
        tmp += wordLen;
    }
    return count;
}

int searchInSingleFile(const char *filename, const char *searchWord, int exactMatch, FILE *logFile) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf(COLOR_RED "Hata: '%s' dosyasi okunamadi.\n" COLOR_RESET, filename);
        if(logFile) fprintf(logFile, "Hata: '%s' dosyasi okunamadi.\n", filename);
        return 0;
    }

    char buffer[MAX_LINE_LENGTH];
    int lineNumber = 1;
    int fileOccurrences = 0;
    char lowerSearchWord[MAX_WORD_LENGTH];
    strcpy(lowerSearchWord, searchWord);
    toLowerCase(lowerSearchWord);

    printf(COLOR_YELLOW "\n--- [%s] Dosyasi Taraniyor ---\n" COLOR_RESET, filename);
    if(logFile) fprintf(logFile, "\n--- [%s] Dosyasi Taraniyor ---\n", filename);

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char lowerLine[MAX_LINE_LENGTH];
        strcpy(lowerLine, buffer);
        toLowerCase(lowerLine);

        int occurrencesInLine = countWordInLine(lowerLine, lowerSearchWord, exactMatch);

        if (occurrencesInLine > 0) {
            buffer[strcspn(buffer, "\n")] = 0;
            // Ekrana yazdirma
            printf(COLOR_CYAN "Satir %-4d " COLOR_RESET "| " COLOR_GREEN "(%d kez) " COLOR_RESET "-> %s\n", lineNumber, occurrencesInLine, buffer);
            // Dosyaya yazdirma (renk kodsuz)
            if(logFile) fprintf(logFile, "Satir %-4d | (%d kez) -> %s\n", lineNumber, occurrencesInLine, buffer);
            
            fileOccurrences += occurrencesInLine;
        }
        lineNumber++;
    }

    fclose(file);
    printf("[%s] icinde toplam %d eslesme bulundu.\n", filename, fileOccurrences);
    if(logFile) fprintf(logFile, "[%s] icinde toplam %d eslesme bulundu.\n", filename, fileOccurrences);
    return fileOccurrences;
}
