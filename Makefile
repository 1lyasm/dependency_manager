all:
	mkdir -p bin
	clang -O2 -Wall -Werror -Wpedantic -fsanitize=address \
		src/main.c -o bin/gdep
	clang -O2 -Wall -Werror -Wpedantic -fsanitize=address \
		src/test.c -o bin/test
test:
	./bin/test
format:
	clang-format -i -style="{BasedOnStyle: google, IndentWidth: 4}" src/*.c
