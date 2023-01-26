#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BLOCK_SIZE 10
#define STRING_SIZE 10
#define MAX_NUM 9999999999

void allocateBuffer(char *** ptr, int blockAmount){
    *ptr = (char **) realloc(*ptr, blockAmount * sizeof(char **));

    // Check if the memory has been successfully allocated
    if (*ptr == NULL) {
        printf("Memoria no guardada.\n");
        exit(1);
    }
     
     // Allocate memory for each number
    for( int i = blockAmount - BLOCK_SIZE; i < blockAmount; i++ ){

          (*ptr)[i] = (char *) calloc( STRING_SIZE + 1, sizeof(char) );

          // Check if the memory has been successfully allocated
          if ((*ptr)[i] == NULL) {
               printf("Memoria no guardada.\n");
               exit(1);
          }
    }
}

void freeBuffer(char *** ptr,int currentSize){
     for(int i = 0; i < currentSize; i++){
          free((*ptr)[i]);
     }
     free(*(ptr));
}

// Transforms long into string and writes it into buffer 
void writeLongIntoBuffer(char ** buffer,int currentAmount,long currNumber){
     char bridgeBuffer[STRING_SIZE + 1];
     int numLen,i;

     // Convert long into String
     sprintf(bridgeBuffer, "%ld", currNumber);
     numLen = strlen(bridgeBuffer);
     
     // Complete with '0'
     for(i = 0; i < (STRING_SIZE - numLen);i++){
          buffer[currentAmount][i] = '0';
     }
     
     // Copy the number into the saving Buffer
     strcpy(&(buffer[currentAmount][i]), bridgeBuffer);

}

// Saves numbers into file
// Return -1 if error, else 0
int saveNumbersToFile(char * filePath,char ** buffer,int currentAmount){
     FILE *fptr;
     fptr = fopen(filePath,"w");

     if (fptr == NULL)
     {
          printf("Error abriendo el archivo!\n");   
          return -1;             
     }

     for (int i = 0; i < currentAmount; i++){
          if( fprintf( fptr, "%s\r\n", buffer[i] ) < 0 ){
               printf("\nHubo un error al escribir el archivo.\n");
               return -1;
          }
     }
     
     fclose(fptr);
     printf("\nArchivo guardado con éxito\n");
}

int main() {

     char ** buffer = NULL;
     int currentAmount = 0,currentSize = 0;
     long currNumber;
     bool stopFlag = false;
     char * filePath;
     
     printf("\n\nPor favor, ingrese números de hasta 10 dígitos.\n");
     printf("Al finalizar, ingrese el número \"0\"\n\n");
     
     while (!stopFlag) {
          
          // Check if there is enough space to save another number
          if(currentAmount == currentSize){
               allocateBuffer(&buffer,currentAmount + BLOCK_SIZE);
               currentSize += BLOCK_SIZE;
          }

          // Get next number
          printf("Ingrese el próximo número: ");
          scanf("%ld", &currNumber);  


          // Check if its stop flag (=0)
          if(currNumber == 0){
               stopFlag = true;
               continue;
          }

          // Check if it has more than 10 digits
          if(currNumber > MAX_NUM){
               printf("\nError. El número debe contar con hasta 10 dígitos.\n");
               continue;
          }

          writeLongIntoBuffer(buffer,currentAmount,currNumber);
          currentAmount++;
     }
     
      // Get next number
     printf("\nIngrese la dirección donde desea guardar los números: ");
     scanf("%s", filePath); 

     saveNumbersToFile(filePath,buffer,currentAmount);

     freeBuffer(&buffer,currentSize);
    return 0;
}