CPPFLAGS = -O2 -Wall -std=c++11

all: wesnoth_gen wesnoth_judge wesnoth_lin wesnoth_linlog wesnoth_nm wesnoth_okmaker wesnoth_quad 

clean-sol:
	rm wesnoth_gen wesnoth_judge wesnoth_lin wesnoth_linlog wesnoth_nm wesnoth_okmaker wesnoth_quad

clean-test:
	find test/ -name '*.in' -not -name '00.sample.*' -exec rm {} \;
	find test/ -name '*.out' -exec rm {} \;

clean: clean-sol clean-test

.PHONY: all clean clean-sol clean-test


