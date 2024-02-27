# makefile for A1
# target : dependencies ....
# 		gcc -Wall -std=c99 -c fileName.c .

# replace A1.c with elmiH... before submission

elmiH: elmiH.o elmiHMain.o 
	gcc -Wall -std=c99 elmiH.o elmiHMain.o -o elmiH -lm

elmiH.o: elmiH.c
	gcc -Wall -std=c99 -c elmiH.c

elmiHMain.o: elmiHMain.c
	gcc -Wall -std=c99 -c elmiHMain.c

clean: # this is useful for removes the generated object files and the executable
	rm *.o elmiH

# we can run it by ./elmiH, and use make clean to clean the object files generated as desired



