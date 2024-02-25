# makefile for A1
# target : dependencies ....
# 		gcc -Wall -std=c99 -c fileName.c .

# replace A1.c with elmiHamzaA1... before submission

elmiHamzaA1: elmiHamzaA1.o elmiHamzaA1Main.o 
	gcc -Wall -std=c99 elmiHamzaA1.o elmiHamzaA1Main.o -o elmiHamzaA1 -lm

elmiHamzaA1.o: elmiHamzaA1.c
	gcc -Wall -std=c99 -c elmiHamzaA1.c

elmiHamzaA1Main.o: elmiHamzaA1Main.c
	gcc -Wall -std=c99 -c elmiHamzaA1Main.c

clean: # this is useful for removes the generated object files and the executable
	rm *.o elmiHamzaA1

# we can run it by ./elmiHamzaA1, and use make clean to clean the object files generated as desired



