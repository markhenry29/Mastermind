# ______________ parametres de compilation
CFLAGS= -Wall --pedantic

# ______________ excecutables
all: mastermind-demo.exe

# mastermind-demo
mastermind-demo.exe: main_vue_mastermind.o vue_mastermind.o mastermind.o stat-essai.o combinaison.o 
	gcc $^ -o $@ `pkg-config --cflags --libs gtk+-2.0`

mastermind-demo.o: mastermind-demo.c mastermind.h combinaison.h stat-essai.h
	gcc -c $< -o $@ $(CFLAGS) 

# ______________ objets bibliothèque

# mastermind
mastermind.o: mastermind.c mastermind.h combinaison.h stat-essai.h
	gcc -c $< -o $@ $(CFLAGS)

# combinaison
combinaison.o: combinaison.c combinaison.h
	gcc -c $< -o $@ $(CFLAGS)

# stat-essai
stat-essai.o: stat-essai.c stat-essai.h
	gcc -c $< -o $@ $(CFLAGS) 

vue_mastermind.o: vue_mastermind.c vue_mastermind.h
	gcc -c $< -o $@ $(CFLAGS) `pkg-config --cflags --libs gtk+-2.0`

main_vue_mastermind.o: main_vue_mastermind.c vue_mastermind.h
	gcc -c $< -o $@ $(CFLAGS) `pkg-config --cflags --libs gtk+-2.0`
# vue_mastermind


# ______________ nettoyage
clean:
	rm -rf *.o


