# AES_128
This is an implementation of AES-128 encryption &amp; decryption, operating in EBC or CBC mode.
The padding rule follows PKCS#7.


# Install
Required: GCC in the Linux environment.

```bash
git clone https://github.com/ArithGeo/AES_128.git
cd AES_128
make all
```

# Usage
```bash
./aes128 ecb enc keyFileName inputFileName outputFileName
./aes128 ecb dec keyFileName inputFileName outputFileName
./aes128 cbc enc keyFileName inputFileName outputFileName initVectName
./aes128 cbc dec keyFileName inputFileName outputFileName initVectName
```
Depending on the operating mode, give the first argument `ecb`(for ECB) or `cbc`(for CBC). Choose encryption or decryption by the next argument, i.e. `enc` or `dec`. Key, input message, init vector(in the CBC case) must be given by binary files. Also, name of the output file must be given.

If all the arguments are given correctly, result of the encryption or decryption will be stored as a file with name given by `outputFileName`.


# Testing (for developers)
If one changes some APIs in `aes128.h`, please run the block test by the following command:
```bash
./aes128 test
```

Also, file I/O can be tested by the following command:
```bash
make test
```
If no error results in, then it is OK.

