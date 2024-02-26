all: DeepSNN

DeepSNN: DeepSNN.o functions.o
	@gcc -o DeepSNN DeepSNN.o functions.o -lm

DeepSNN.o: DeepSNN.c ./includes/functions.h
	@gcc -c DeepSNN.c

functions.o: functions.c ./includes/functions.h
	@gcc -c functions.c

clean:
	@rm -f *.o DeepSNN 