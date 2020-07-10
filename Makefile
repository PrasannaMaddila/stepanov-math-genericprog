# Compiles the .cpp whenever they are changed
# and calls the resulting binaries.

SRCS = $(wildcard ./*.cpp)
OBJS = $(SRCS:.cpp=.out)

all: $(OBJS) 

%.out: %.cpp
	g++ -Wall -o $@ $<
	chmod +x $@
	./$@ ;

clean: 
	rm *.out; 

.PHONY: all clean
