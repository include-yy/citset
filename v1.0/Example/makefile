
TARGETS = citc citcpp

.PHONY : all
all : $(TARGETS)

citc : primesum.c libcitset.a
	gcc -o $@ primesum.c libcitset.a

citcpp : primesum.cpp
	g++ -o $@ primesum.cpp

.PHONY : clean

clean :
	rm -f citc citcpp
