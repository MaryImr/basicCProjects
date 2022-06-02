//
//  main.c
//  ScanPathAnalyser
//
//  Created by Maryam Imran on 11/01/2022.
//

#include <stdio.h>

struct AOI {
    char name;
    int top_left;
    int top_right;
    int bottom_left;
    int bottom_right;
};

int main() {
    
    char filename_aois[35], filename_fixations[40], ch;
    int totalAOIs = 0;
    
    printf("Enter AOIs file name: ");
    scanf("%s", filename_aois);
    
    printf("\n\naois: %s\n\n", filename_aois);
    
    printf("Enter scanpaths file name: ");
    scanf("%s", filename_fixations);
    
    printf("fix: %s\n\n", filename_fixations);
    printf("\n\naois: %s\n\n", filename_aois);
    
    FILE *outFile;
    outFile = fopen(filename_aois,"r");
    
    if (outFile == NULL) {    //checking if file is found
        printf("File not opened successfully!\n");
        //exit(1);
    }
    
    do {
        ch = fgetc(outFile);
        if(ch >= 'A' && ch <= 'Z')
            totalAOIs++;
    }
    while(ch != EOF);
    fclose(outFile);
    
    return 0;
}
