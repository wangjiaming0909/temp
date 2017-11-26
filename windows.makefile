TARGET = a.exe
HEADERS = boost_test.h\
			coursera_algorithms.h\
			ds.h\
			e_algorithms.h\
			main_functions.h\
			stl.h\
			\
			bintree/avl_implement.h\
			bintree/avl.h\
			bintree/bst_header.h\
			bintree/bst_implement.h\
			bintree/bst.h\
			bintree/btnode.h\
			bintree/btree_implement.h\
			bintree/btree.h\
			bintree/redblack.h\
			bintree/search.h\
			bintree/splay_implement.h\
			bintree/splay.h\
			\
			graph/graph.h\
			graph/graph_headers.h\
			graph/graph_matrix.h
SOURCES = main.cpp	
LIB = 
OBJECTS = main.o
INCLUDES = D:/boost_1_64_0/
CPPFLAGS = -Wall -Wextra -std=c++11 -O0 -c -g2 -ggdb -Wfatal-errors -Og

all:$(TARGET)

$(TARGET): $(OBJECTS)
	@echo linking...
	g++ $^ -o $@
	@echo ok...
	rm $(OBJECTS)

$(OBJECTS): $(SOURCES) $(HEADERS)
	@rm -f $(TARGET)
	g++ $(CPPFLAGS) -I $(INCLUDES) $< -o $@ 
	
clean: FORCE
	rm -f *.o 
	rm -f *.exe
	rm -f *.out
	@echo ok..
FORCE: