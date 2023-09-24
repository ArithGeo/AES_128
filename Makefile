all:
	gcc -o aes128 test.c aes128Block.c opMode.c fileIO.c main.c

test:
	./aes128 ecb enc testFiles/key.txt testFiles/loremIpsum.txt testFiles/ecbEncOut.bin 
	diff testFiles/ecbEncOut.bin testFiles/ecb.bin

	./aes128 ecb enc testFiles/key.txt testFiles/LoremIpsumLong.txt testFiles/ecbEncLongOut.bin 
	diff testFiles/ecbEncLongOut.bin testFiles/ecbLong.bin

	./aes128 ecb dec testFiles/key.txt testFiles/ecb.bin testFiles/ecbDecOut.bin
	diff testFiles/ecbDecOut.bin testFiles/loremIpsum.txt

	./aes128 ecb dec testFiles/key.txt testFiles/ecbLong.bin testFiles/ecbDecLongOut.bin
	diff testFiles/ecbDecLongOut.bin testFiles/loremIpsumLong.txt

	./aes128 cbc enc testFiles/key.txt testFiles/loremIpsum.txt testFiles/cbcEncOut.bin testFiles/initVect.txt
	diff testFiles/cbcEncOut.bin testFiles/cbc.bin

	./aes128 cbc enc testFiles/key.txt testFiles/loremIpsumLong.txt testFiles/cbcEncLongOut.bin testFiles/initVect.txt
	diff testFiles/cbcEncLongOut.bin testFiles/cbcLong.bin

	./aes128 cbc dec testFiles/key.txt testFiles/cbc.bin testFiles/cbcDecOut.bin testFiles/initVect.txt
	diff testFiles/cbcDecOut.bin testFiles/loremIpsum.txt

	./aes128 cbc dec testFiles/key.txt testFiles/cbcLong.bin testFiles/cbcDecLongOut.bin testFiles/initVect.txt
	diff testFiles/cbcDecLongOut.bin testFiles/loremIpsumLong.txt

clean:
	rm testFiles/*Out.bin
	rm aes128

