#ifndef CARD_RECOGNIZER_H
#define CARD_RECOGNIZER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define NOT_FOUND -1

bool getCardLabel(char * number,char * label);

#endif