#ifndef __AES128__
#define __AES128__

// block
void expandKey(uint8_t* roundKey, const uint8_t* key);

void aes128BlockEnc(uint8_t* dest, const uint8_t* source, const uint8_t* roundKey);
void aes128BlockDec(uint8_t* dest, const uint8_t* source, const uint8_t* roundKey);


// opMode
int aes128EcbEnc(uint8_t* cipher, const uint8_t* plain, const uint8_t* roundKey, int len, int padding);
int aes128EcbDec(uint8_t* plain, const uint8_t* cipher, const uint8_t* roundKey, int len, int padding);
int aes128CbcEnc(uint8_t* cipher, const uint8_t* plain, const uint8_t* roundKey, int len, const uint8_t* initVect, int padding);
int aes128CbcDec(uint8_t* plain, const uint8_t* cipher, const uint8_t* roundKey, int len, const uint8_t* initVect, int padding);


// fileIO
int initKey(char* keyFileName);
int initInitVect(char* initVectName);
void updateInitVect(const uint8_t* lastCipherBlock);

int initInputStream(char* inputFileName);
void termInputStream();

int initOutputStream(char* outputFileName);
void termOutputStream();

int aes128Stream(int mode);

typedef enum{
    ECB_ENC,
    ECB_DEC,
    CBC_ENC,
    CBC_DEC,
} Mode;


// test
void checkInteger(int result, int expected);
void checkResult(const uint8_t* result, const uint8_t* expected, int len, char* message);
void testBlock();
void testOpMode();

#endif