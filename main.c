#include <time.h>
#include <stdio.h>
#include "search_engine.h"

int main() {
    char searchWord[MAX_WORD_LENGTH];
    char fileList[MAX_FILES][MAX_LINE_LENGTH];
    int fileCount = 0;
    char tempFilename[MAX_LINE_LENGTH];
    int searchMode = 1;

    // Sonuclarin kaydedilecegi dosyayi aciyoruz
    FILE *logFile = fopen("sonuclar.txt", "w");
    if (logFile == NULL) {
        printf("Rapor dosyasi olusturulamadi!\n");
    }

    printf("================================================\n");
    printf("               METIN ARAMA SISTEMI          \n");
    printf("================================================\n\n");

    printf("Aranacak kelimeyi giriniz: ");
    scanf("%255s", searchWord);

    printf("\nArama Modu Seciniz:\n");
    printf("1 - Normal Arama\n2 - Tam Eslesme\nSeciminiz (1/2): ");
    
    if (scanf("%d", &searchMode) != 1 || (searchMode != 1 && searchMode != 2)) {
        searchMode = 1;
        int c;
        while ((c = getchar()) != '\n' && c != EOF); 
    }

    int exactMatch = (searchMode == 2) ? 1 : 0;

    printf("\nTaranacak dosya adlarini giriniz ('bitir' yazana kadar):\n");
    while (fileCount < MAX_FILES) {
        printf("%d. Dosya adi: ", fileCount + 1);
        scanf("%255s", tempFilename);
        if (strcmp(tempFilename, "bitir") == 0) break;
        strcpy(fileList[fileCount++], tempFilename);
    }

    if (fileCount == 0) return 0;

    printf("\n================ SONUCLAR ==================\n");
    if(logFile) fprintf(logFile, "================ ARAMA SONUCLARI ==================\n");

    clock_t startTime = clock();
    int grandTotalOccurrences = 0;

    for (int i = 0; i < fileCount; i++) {
        // Fonksiyona logFile gonderiliyor
        grandTotalOccurrences += searchInSingleFile(fileList[i], searchWord, exactMatch, logFile);
    }

    clock_t endTime = clock();
    double timeSpent = (double)(endTime - startTime) / CLOCKS_PER_SEC * 1000.0;

    // Final raporunu hem ekrana hem dosyaya yazdiriyoruz
    printf("\n================ PROJE RAPORU ==================\n");
    printf("Aranan Kelime    : %s\n", searchWord);
    printf("Arama Modu       : %s\n", exactMatch ? "Tam Eslesme" : "Normal Arama");
    printf("Taranan Dosya    : %d adet\n", fileCount);
    printf("Toplam Frekans   : %d\n", grandTotalOccurrences);
    printf("Arama Suresi     : %.2f ms\n", timeSpent);

    if(logFile) {
        fprintf(logFile, "\n================ PROJE RAPORU ==================\n");
        fprintf(logFile, "Aranan Kelime    : %s\n", searchWord);
        fprintf(logFile, "Arama Modu       : %s\n", exactMatch ? "Tam Eslesme" : "Normal Arama");
        fprintf(logFile, "Taranan Dosya    : %d adet\n", fileCount);
        fprintf(logFile, "Toplam Frekans   : %d\n", grandTotalOccurrences);
        fprintf(logFile, "Arama Suresi     : %.2f ms\n", timeSpent);
        fclose(logFile); // Dosyayi kapatmayi unutma
        printf("\nTum sonuclar 'sonuclar.txt' dosyasina kaydedildi.\n");
    }

    return 0;
}
