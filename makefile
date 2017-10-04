target = a.exe
objects = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
LIB = a

all:$(target)

$(target):$(objects) 
	@echo linking...
#	g++ -O1 $^ -L. -la -o $@ 
	g++ -O1 $^ -o $@ 
	@echo ok...
	rm *.o

$(objects):%.o:%.cpp
# @echo compiling...
	@rm -f *.exe
	@rm -f *.out
	g++ -Wall -Wextra -std=c++11 -c -O1  $< -o $@ -g -Wfatal-errors
	

clean:FORCE
	rm -f *.o 
	rm -f *.exe
	rm -f *.out
	@echo ok..
FORCE:
