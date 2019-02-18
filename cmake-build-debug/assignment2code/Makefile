CC = gcc

CFLAGS = -O2 -std=c99 -pedantic -Wall -o -lm

scan: mainScan.c scanner.c
	$(CC) $(CFLAGS) $^ -o $@

recog: mainRecog.c scanner.c recognizeExp.c
	$(CC) $(CFLAGS) $^ -o $@

eval: scanner.c recognizeExp.c evalExp.c mainEvalExp.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -f eval recog scan
