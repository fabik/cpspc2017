CPPFLAGS = -O2 -Wall -std=c++11

all: gen sol sol-10 sol-30

clean-sol:
	rm gen sol sol-10 sol-30

clean-test:
	find test/ -name '*.in' -not -name '00.sample.*' -exec rm {} \;
	find test/ -name '*.out' -exec rm {} \;

clean: clean-sol clean-test

.PHONY: all clean clean-sol clean-test
