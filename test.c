#include <stdint.h>
#include <stdio.h>

#include "aes128.h"

void checkInteger(int result, int expected){
    if(result == expected){
        printf("[PASSED] result : %10d  ==  expect: %10d\n", result, expected);
    } else {
        printf("[FAILED] result : %10d  !=  expect: %10d\n", result, expected);
    }
}

void checkResult(const uint8_t* result, const uint8_t* expected, int len, char* message){
    int pass = 1;
    for(int i = 0; i < len; i++){
        if(result[i] != expected[i]){
            pass = 0;
            break;
        }
    }
    if(pass){
        printf("[PASSED] %s\n", message);
    } else {
        printf("[FAILED] %s\n", message);
#ifdef VERBOSE
        printf("EXP: ");
        for(int i = 0; i < len; i++){
            printf("0x%02x, ", expected[i]);
        }
        printf("\n");
        printf("GOT: ");
        for(int i = 0; i < len; i++){
            printf("0x%02x, ", result[i]);
        }
        printf("\n");
#endif
    }
}


