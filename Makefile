EXEC=lab_01
SOURCE=lab_01.c++  
LIBS  = -lgsl  
all: 
	@echo "Start compining"
	c++ -Wall -o $(EXEC) $(SOURCE) -lgsl -lm 

run:$(EXEC)
	./$(EXEC)
