CXX ?= c++
CXXFLAGS ?= -std=c++98 -O2 -Wall -Wextra -ffp-contract=off
CPPFLAGS ?= -I../include
BIN := vector_math_fallbacks
SAN := $(BIN)_san

.PHONY: all run sanitize clean

all: $(BIN)

$(BIN): vector_math_fallbacks.cpp ../include/pso/port/VectorMathFallbacks.h ../include/pso/port/PortCompat.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $<

run: $(BIN)
	./$(BIN)

sanitize: vector_math_fallbacks.cpp ../include/pso/port/VectorMathFallbacks.h ../include/pso/port/PortCompat.h
	$(CXX) $(CPPFLAGS) -std=c++98 -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer -o $(SAN) $<
	./$(SAN)

clean:
	rm -f $(BIN) $(SAN)
