OBJ= main.o wave.o screen.o #comm.o (to be added later hashtag for comment)
APPNAME = sound.a

$(APPNAME): $(OBJ)
	gcc -o $(APPNAME) $(OBJ) -lm

%.o : %.c
	gcc -c -o $@ $< -std=c99

clean:
	rm $(OBJ) $(APPNAME)	

archive:
	 tar cf sound.tar *.c *.h makefile
