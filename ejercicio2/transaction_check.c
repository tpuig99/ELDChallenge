#include <stdio.h>
#include <stdlib.h>
#include<math.h>  
#include <ctype.h>
#include <string.h>
#include "socket_handler.h"
#include "card_recognizer.h"

#define BUFFER_SIZE 100
#define REQUEST_SIZE 4 + 2 + 100 + 12 + 3


void validateCard(char *cardNumber)
{
     char * auxiliar = cardNumber;
     char cardLabel[BUFFER_SIZE];
     
     if(strlen(cardNumber) < 13){
          printf("La tarjeta tiene menos de 13 dígitos. Formato no valido.\n");
          printf("TARJETA NO SOPORTADA\n");
          exit(1);
     }

     while (*cardNumber) {
          if (isdigit(*cardNumber++) == 0){
               printf("La tarjeta contiene caracteres que no son números. Formato no valido.\n");
               exit(1);
          }
     }

     cardNumber = auxiliar;     
     if( !getCardLabel(cardNumber,cardLabel) ){
          printf("\nTARJETA NO SOPORTADA\n");
          exit(1);
     }

     printf("\n%s\n",cardLabel);
}

int generateRequest(float amount,char* cardNumber,char* code,char request[REQUEST_SIZE]){
     char * auxiliar = request;
     
     strncpy(auxiliar,"0200",4);
     auxiliar += 4;

     int len = strlen(cardNumber);
     sprintf(auxiliar, "%2d", len);
     auxiliar += 2;

     strncpy(auxiliar,cardNumber,len);
     auxiliar += len;

     char auxAmount[12];
     
     sprintf(auxAmount, "%d", (int) (100 * amount));
     int amountLen = strlen(auxAmount);

     for(int i = 0; i < (12 - amountLen);i++){
          *auxiliar++ = '0';
     }
     
     strncpy(auxiliar, auxAmount,amountLen);
     auxiliar += amountLen;

     strncpy(auxiliar, code,3);
     auxiliar += 3;

     *auxiliar = 0;

     return strlen(request);
}

void sendRequest(char * request,int reqLen){
     int port;
     char ip [20];
     printf("\n\nPor favor, ingrese ip \n");
     scanf("%s", ip); 

     printf("\n\nPor favor, ingrese el puerto \n");
     scanf("%d", &port); 

     int sock = 0;
     if( (sock = socketCreate()) == -1) {
          printf("ERROR DE COMUNICACIÓN\n");
          exit(1);
     }

     if( socketConnect(sock,ip,port) == -1) {
          printf("ERROR DE COMUNICACIÓN\n");
          exit(1);
     }

     if( socketWrite(sock,request) == -1) {
          printf("ERROR DE COMUNICACIÓN\n");
          exit(1);
     }
          
     char buffer[1024] = { 0 };
     
     if(socketRead(sock,buffer,5) == -1){
          printf("ERROR DE COMUNICACIÓN\n");
          exit(1);
     }
     
     if(strcmp(buffer + 4,"00") == 0){
          printf("APROBADA\n");
          return;
     }
     printf("RECHAZADA\n");
     
     socketClose(sock);
}

int main() {
     float amount;
     char cardNumber[BUFFER_SIZE], code[4];
     char request[REQUEST_SIZE];

     printf("\n\nPor favor, ingrese el monto de la compra. Se consideran solo dos decimales ###.## \n");
     scanf("%f", &amount); 
     
     printf("\n\nPor favor, ingrese el número de tarjeta (Mínimo 13 dígitos)\n");
     scanf("%s", cardNumber); 
     validateCard(cardNumber);

     printf("\n\nPor favor, ingrese el código de seguridad (3 dígitos)\n");
     scanf("%3s", code); 

     int reqLen = generateRequest(amount,cardNumber,code,request);

     sendRequest(request,reqLen);

     return 0;
}