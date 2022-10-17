EXEC=lab_01
EXEC_T=t_$(EXEC)
OBJ=lab_01.o main.o gsl_func.o
OBJ_T=lab_01.o test.o gsl_func.o 
LIBS  = -lgsl  

main: $(OBJ)
	@echo "Сборка бинарника"
	c++ -Wall -o $(EXEC) $(OBJ) -lgsl -lm  
lab_01.o: lab_01.c++ lab_01.h
	@echo "Компиляция модуля lab_01"
	c++ -Wall -c lab_01.c++
gsl_func.o: gsl_func.c++ gsl_func.h
	@echo "Компиляция модуля gsl_func"
	c++ -Wall -c gsl_func.c++
main.o: main.c++
	@echo "Компиляция main.o"
	c++ -Wall -c main.c++
clean:
	rm -f ./*.o $(EXEC) $(EXEC_T)
test.o: test.c++
	@echo "Компиляция UNIT теста"
	c++ -Wall -c test.c++
test: $(OBJ_T) 
	c++ -Wall -o $(EXEC_T) $(OBJ_T) -lgsl -lm
run:$(EXEC)
	./$(EXEC)

