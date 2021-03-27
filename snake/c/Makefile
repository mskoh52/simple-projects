snake: *.c
	gcc $^ -g -o snake $$(pkg-config --cflags --libs sdl2) -lSDL2_ttf

test_point: tests/test_point.c point.c 
	@mkdir -p tests/bin
	@echo -n "test_point: "
	@gcc $^ -g -o tests/bin/test_point
	@./tests/bin/test_point

test_list: tests/test_list.c point.c list.c
	@mkdir -p tests/bin
	@echo -n "test_list: "
	@gcc $^ -g -o tests/bin/test_list
	@./tests/bin/test_list

test_state: tests/test_state.c state.c point.c list.c dirqueue.c
	@mkdir -p tests/bin
	@echo -n "test_state: "
	@gcc $^ -g -o tests/bin/test_state
	@./tests/bin/test_state

.PHONY: test
test : test_point test_list test_state
	rm tests/bin/*
