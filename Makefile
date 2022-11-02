objects = main.o CJumpChoices.o

PegPuzzle : $(objects) 
	g++ -o PegPuzzle $(objects)
	
main.o : main.cpp
	g++ -c main.cpp

CJumpChoices.o : CJumpChoices.cpp
	g++ -c CJumpChoices.cpp

clean :
	rm  PegPuzzle $(objects) 
	
