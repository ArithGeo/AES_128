#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "aes128.h"

int main(int argc, char** argv){
#if 0  // TOBEDEL
    uint8_t inputBuf[21931];
    FILE* inputFp = fopen("testFiles/loremIpsumLong.txt", "rb");
    fread(inputBuf, 1, 21931, inputFp);
    fclose(inputFp);
    char* key       = "0123456789abcdef";
    char* initVect  = "fedcba9876543210";
    uint8_t roundKey[4 * 44];
    expandKey(roundKey, key);

    uint8_t ecbBuf[21936];
    int ecbRet = aes128EcbEnc(ecbBuf, inputBuf, roundKey, 21931, 1);

    uint8_t cbcBuf[21936];
    int cbcRet = aes128CbcEnc(cbcBuf, inputBuf, roundKey, 21931, initVect, 1);

    FILE* ecbFp = fopen("testFiles/ecbLong.bin", "wb");
    fwrite(ecbBuf, 1, ecbRet, ecbFp);
    fclose(ecbFp);
    
    FILE* cbcFp = fopen("testFiles/cbcLong.bin", "wb");
    fwrite(cbcBuf, 1, cbcRet, cbcFp);
    fclose(cbcFp);

    return 0;
#endif

    int mode = -1;

    if(argc == 2 && strncmp(argv[1], "test", 4) == 0){
        testBlock();
        testOpMode();
        return 0;
    } else if(argc == 6 && strncmp(argv[1], "ecb", 3) == 0 && strncmp(argv[2], "enc", 3) == 0){
        mode = ECB_ENC;
    } else if(argc == 6 && strncmp(argv[1], "ecb", 3) == 0 && strncmp(argv[2], "dec", 3) == 0){
        mode = ECB_DEC;
    } else if(argc == 7 && strncmp(argv[1], "cbc", 3) == 0 && strncmp(argv[2], "enc", 3) == 0){
        mode = CBC_ENC;
    } else if(argc == 7 && strncmp(argv[1], "cbc", 3) == 0 && strncmp(argv[2], "dec", 3) == 0){
        mode = CBC_DEC;
    } else {
        printf("<usages>\n");
        printf("./aes128 help\n");
        printf("./aes128 test\n");
        printf("./aes128 ecb enc keyFileName inputFileName outputFileName\n");
        printf("./aes128 ecb dec keyFileName inputFileName outputFileName\n");
        printf("./aes128 cbc enc keyFileName inputFileName outputFileName initVectName\n");
        printf("./aes128 cbc dec keyFileName inputFileName outputFileName initVectName\n");
        return 0;
    }

    if(mode == ECB_ENC || mode == ECB_DEC || mode == CBC_ENC || mode == CBC_DEC){
        int ret;

        ret = initKey(argv[3]);
        if(ret < 0){
            return ret - 10;
        }

        if(mode == CBC_ENC || mode == CBC_DEC){
            ret = initInitVect(argv[6]);
            if(ret < 0){
                return ret - 20;
            }
        }

        ret = initInputStream(argv[4]);
        if(ret < 0){
            return ret - 30;
        }

        ret = initOutputStream(argv[5]);
        if(ret < 0){
            termInputStream();
            return ret - 40;
        }

        ret = aes128Stream(mode);
        if(ret < 0){
            return ret - 50;
        }

        termInputStream();
        termOutputStream();
    }

    return 0;
}




