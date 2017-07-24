calc: calc.c formating.c 
	gcc -g -o calc calc.c formating.c calc_main.c -lm

install: calc
	cp calc /usr/bin/

clean:
	rm calc

uninstall:
	rm /usr/bin/calc
