#include "card_recognizer.h"

typedef struct range_t{ 
     char rangeLow[8 + 1]; 
     char rangeHigh[8 + 1]; 
     unsigned char len; 
     int id; 
} range_t;

typedef struct card_t{ 
     char label[12 + 1]; 
     int id;
} card_t;

void generateRangesFile() {
     range_t r1 = {"10000000","20000000",15,1};
     range_t r2 = {"20000000","21000000",20,2};
     range_t r3 = {"40000000","45000000",13,3};
     range_t r4 = {"70000010","72000000",14,4};
     range_t r5 = {"50000000","60000000",13,5};

     FILE *fptr;
     fptr = fopen("./archivos/ranges.dat","w");

     if (fptr == NULL)
     {
          printf("Error abriendo el archivo!\n"); 
          return;  
     }

     fwrite(&r1,sizeof(range_t),1,fptr);
     fwrite(&r2,sizeof(range_t),1,fptr);
     fwrite(&r3,sizeof(range_t),1,fptr);
     fwrite(&r4,sizeof(range_t),1,fptr);
     fwrite(&r5,sizeof(range_t),1,fptr);
     
     fclose(fptr);
     printf("\nArchivo guardado con éxito\n");
}

void generateCardFile() {
     card_t r1 = {"Tarjeta 1",1};
     card_t r2 = {"Tarjeta 2",2};
     card_t r3 = {"Tarjeta 3",3};
     card_t r4 = {"Tarjeta 4",4};
     card_t r5 = {"Tarjeta 5",5};

     FILE *fptr;
     fptr = fopen("./archivos/cards.dat","w");

     if (fptr == NULL)
     {
          printf("Error abriendo el archivo!\n");   
          return;             
     }

     fwrite(&r1,sizeof(card_t),1,fptr);
     fwrite(&r2,sizeof(card_t),1,fptr);
     fwrite(&r3,sizeof(card_t),1,fptr);
     fwrite(&r4,sizeof(card_t),1,fptr);
     fwrite(&r5,sizeof(card_t),1,fptr);
     
     fclose(fptr);
     printf("\nArchivo guardado con éxito\n");
}

int checkRange(char * number) {
     FILE *fptr;
     char firstDigNum[9];
     range_t range;
     long lowRange,highRange;

     fptr = fopen("./archivos/ranges.dat","r");

     if (fptr == NULL)
     {
          printf("Error leyendo el archivo ranges.dat\n");   
          exit(1);
          return -1;             
     }

 
     strncpy(firstDigNum,number,8);
     firstDigNum[8] = 0;
     
     long nmbr = strtol(firstDigNum,NULL,10);
     
     if (nmbr == 0 && (errno == EINVAL || errno == ERANGE)) {
          printf("Error durante lectura del número de tarjeta\n");
          exit(1);
          return -1;
     }


     while( fread(&range,sizeof(range_t),1,fptr) ){
          
          lowRange = strtol(range.rangeLow,NULL,10);
          highRange = strtol(range.rangeHigh,NULL,10);
     
          if(nmbr > lowRange && nmbr < highRange && strlen(number) == range.len)
               return range.id;
     }

     return -1;
}

void getLabel(int id,char * label) {

     FILE *fptr;
     card_t card;

     fptr = fopen("./archivos/cards.dat","r");

     if (fptr == NULL)
     {
          printf("Error leyendo el archivo cards.dat\n");   
          exit(1);
     }
     
     while( fread(&card,sizeof(card_t),1,fptr) ){

          if(card.id == id){
               strcpy(label,card.label);
               return;
          }

     }
}

bool getCardLabel(char * number,char * label) {
     int id = checkRange(number);

     if (id == NOT_FOUND){
          return false;
     }

     getLabel(id,label);

     return true;
}