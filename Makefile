TARGET = bin/test
SRC = $(wildcard src/*.c)

default: $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f bin/*

$(TARGET): $(SRC)
	gcc -o $@ $^ -I./inc
