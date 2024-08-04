#include <stdio.h>

int main(int argc, char **argv){

    if (argc < 2){
        fprintf(stderr, "Not Enough Arguments.\n");
        return 1;
    }
    
     FILE *fptr;

    // Open the file in writing mode
    fptr = fopen("/proc/kudo_interface", "w");

    // Make sure the file opened
    if (fptr == NULL){
        fprintf(stderr, "Insufficient Permissions.\n");
        return 1;
    }

    // Write all arguments to the file
    for (int i = 1; i < argc; i++){
        fprintf(fptr, "%s", argv[i]);
        fprintf(fptr, " ");
    }

    // Close the file
    fclose(fptr); 
}
