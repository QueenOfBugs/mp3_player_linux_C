play_test: play_test.o
	gcc -o play_test play_test.o -lmpg123 -lpulse -lpulse-simple
paly_test.o:play_test.c
	gcc play_text.c -o play_test.o
clean:
	rm play.o play
