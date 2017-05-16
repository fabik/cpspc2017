CPPFLAGS = -O2 -Wall -std=c++11

all: sol sol-20

clean-sol:
	rm sol sol-20

clean-test:
	find test/ -name '*.out' -exec rm {} \;

clean: clean-sol clean-test

.PHONY: all clean clean-sol clean-test
