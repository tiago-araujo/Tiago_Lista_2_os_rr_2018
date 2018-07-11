CC=gcc
FLAGT=lpthread
FLAGM=lm
all: primos_thread

primos_thread: primos_thread.c
	${CC} $^ -$(FLAGT) -o $@ -$(FLAGM)

clean:
	rm primos_thread