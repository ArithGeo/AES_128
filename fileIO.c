#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "aes128.h"

#define PAGESIZE 1024 // may be different

static uint8_t gKey         [16      ];
static uint8_t gRoundKey    [4 * 44  ];
static uint8_t gInitVect    [16      ];

static FILE*   gInputFp;
static int     gInputSize;
static uint8_t gInputBuf    [PAGESIZE];

static FILE*   gOutputFp;
static uint8_t gOutputBuf   [PAGESIZE];

static int checkFileSize(FILE* fp){
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return size;
}

int initKey(char* keyFileName){
    FILE* fp = fopen(keyFileName, "rb");
    if(fp == NULL){
        printf("setkey(): cannot open %s\n", keyFileName);
        return -1;
    }
    int size = checkFileSize(fp);
    if(size != 16){
        printf("setkey(): expected key size %10d, got %10d\n", 16, size);
        fclose(fp);
        return -2;
    }
    fread(gKey, 1, 16, fp);
    fclose(fp);

    expandKey(gRoundKey, gKey);
    return 0;
}

int initInitVect(char* initVectName){
    FILE* fp = fopen(initVectName, "rb");
    if(fp == NULL){
        printf("setInitVect(): cannot open %s\n", initVectName);
        return -1;
    }
    int size = checkFileSize(fp);
    if(size != 16){
        printf("setInitVect(): expected init vector size %10d, got %10d\n", 16, size);
        fclose(fp);
        return -2;
    }
    fread(gInitVect, 1, 16, fp);
    fclose(fp);
    return 0;
}

void updateInitVect(const uint8_t* lastCipherBlock){
    for(int i = 0; i < 16; i++){
        gInitVect[i] = lastCipherBlock[i];
    }
}

int initInputStream(char* inputFileName){
    gInputFp = fopen(inputFileName, "rb");
    if(gInputFp == NULL){
        printf("setInputStream: cannot open %s\n", inputFileName);
        return -1;
    }
    gInputSize = checkFileSize(gInputFp);
    return 0;
}

void termInputStream(){
    fclose(gInputFp);
}

int initOutputStream(char* outputFileName){
    gOutputFp = fopen(outputFileName, "wb");
    if(gOutputFp == NULL){
        printf("setOutputStream: cannot open %s\n", outputFileName);
        return -1;
    }
    return 0;
}

void termOutputStream(){
    fclose(gOutputFp);
}

/*** operations ***/
int aes128Stream(int mode){
    int inputSize = gInputSize;
    int outputSize = 0;

    int toRead;
    int padding;

    if((mode == ECB_DEC || mode == CBC_DEC) && (inputSize % 16 != 0)){
        printf("decryption requires fileSize %% 16 == 0\n");
        return -1;
    }

    while(inputSize > 0){
        if(inputSize > PAGESIZE){
            toRead = PAGESIZE;
            padding = 0;
        } else {
            toRead = inputSize;
            padding = 1;
        }

        inputSize -= toRead;
        fread(gInputBuf, 1, toRead, gInputFp);
        
        int ret = 0;
        if(mode == ECB_ENC){
            ret = aes128EcbEnc(gOutputBuf, gInputBuf, gRoundKey, toRead, padding);
        } else if(mode == ECB_DEC){
            ret = aes128EcbDec(gOutputBuf, gInputBuf, gRoundKey, toRead, padding);
        } else if(mode == CBC_ENC){
            ret = aes128CbcEnc(gOutputBuf, gInputBuf, gRoundKey, toRead, gInitVect, padding);
            updateInitVect(&gOutputBuf[toRead - 16]);
        } else if(mode == CBC_DEC){
            ret = aes128CbcDec(gOutputBuf, gInputBuf, gRoundKey, toRead, gInitVect, padding);
            updateInitVect(&gInputBuf[toRead - 16]);
        } else {
            printf("aes128Stream: mode %10d is not correct\n", mode);
            return -2;
        }

        fwrite(gOutputBuf, 1, ret, gOutputFp);
        outputSize += ret;
    }

    return outputSize;
}





