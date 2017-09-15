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
	g++ -std=c++11 -c -O1  $< -o $@ -g 
	

clean:FORCE
	rm -f *.o 
	rm -f *.exe
	@echo ok..
FORCE:
