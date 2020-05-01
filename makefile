clean:
	rm main
	rm volume

cleanHex:
	rm hex
	> hexdump_results.txt

cleanResults:
	> hexdump_results.txt

ourDriver:
	gcc fsdriver3.c low/fsLow.c tokenize/tokenize.c structs.c functions/cp/copyFile.c functions/ld/listDir.c functions/mkdir/createDir.c functions/mv/moveFile.c functions/rm/removeFile.c functions/set/setMetaData.c functions/touch/createFile.c functions/special1/special1.c functions/special2/special2.c -o main -lm

lowDriver:
	gcc fsLowDriver.c low/fsLow.c -o main -lm

hexdump:
	gcc hexdump.c -o hex

run:
	make ourDriver
	./main volume 1048576 512

runLow:
	make lowDriver
	./main volume 1048576 512

runHexdump:
	make hexdump
	(./hex volume) >> hexdump_results.txt 

bang!:
	make run
	make runHexdump

superclean!:
	make clean
	make cleanHex

