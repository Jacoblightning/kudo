#include <stdio.h>

int main(int argc, char **argv){

    if (argc < 2){
        fprintf(stderr, "Not Enough Arguments.\n");
        return 1;
    }
    
     FILE *fptr;

    // Open a file in writing mode
    fptr = fopen("/proc/kudo_interface", "w");

    if (fptr == NULL){
        fprintf(stderr, "Insufficient Permissions.\n");
        return 1;
    }

    for (int i = 1; i < argc; i++){
        fprintf(fptr, "%s", argv[i]);
        fprintf(fptr, " ");
    }

    // Close the file
    fclose(fptr); 
}
