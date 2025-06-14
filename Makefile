CXX_FLAGS = -std=c++20 -O3 -g -fsanitize=address -Iinclude
SOURCES = src/diary.cpp

.PHONY: all
all:
	echo "Available targets: build, run, test, clean, format_all"

.PHONY: setup
setup:
	mkdir -p build

.PHONY: format_all
format_all:
	pre-commit run --all-files

.PHONY: build
build: setup
	g++ $(CXX_FLAGS) $(SOURCES) -o build/output_exec

.PHONY: run
run: build
	build/output_exec

.PHONY: test
test: setup
	g++ $(CXX_FLAGS) $(SOURCES) tests/test.cpp -o build/test_target
	build/test_target

.PHONY: clean
clean:
	rm -rf build
