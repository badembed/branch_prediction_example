all:
	g++ -O0 -g ./predicted.c -lbenchmark -lpthread -o predicted
	g++ -O0 -g ./unpredicted.c -lbenchmark -lpthread -o unpredicted
	objdump -Sd ./predicted > predicted.asm
	objdump -Sd ./unpredicted > unpredicted.asm

clean:
	rm -f ./predicted ./predicted.asm ./unpredicted ./unpredicted.asm

run:
	perf stat ./predicted
	perf stat ./unpredicted