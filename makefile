main.o:RecordDefinition.hpp SecondaryFunctions.hpp RecordOperations.hpp IncomeStatement_and_Ratios.hpp main.cpp
	g++ -c main.cpp
main: main.o
	g++ main.o -o main
run:
	./main
