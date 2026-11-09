CXX ?= c++
CXXFLAGS ?= -std=c++98 -O2 -Wall -Wextra -ffp-contract=off
CPPFLAGS ?= -I../include
BIN := vector_math_fallbacks
SAN := $(BIN)_san
CALLBACK_BIN := item_factory_callbacks
CALLBACK_SAN := $(CALLBACK_BIN)_san

.PHONY: all run sanitize clean

all: $(BIN) $(CALLBACK_BIN)

$(BIN): vector_math_fallbacks.cpp ../include/pso/port/VectorMathFallbacks.h ../include/pso/port/PortCompat.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $<

$(CALLBACK_BIN): item_factory_callbacks.cpp ../../include/pso/item/ItemCreateFunction.h
	$(CXX) $(CPPFLAGS) -I../../include $(CXXFLAGS) -o $@ $<

run: $(BIN) $(CALLBACK_BIN)
	./$(BIN)
	./$(CALLBACK_BIN)

sanitize: vector_math_fallbacks.cpp ../include/pso/port/VectorMathFallbacks.h ../include/pso/port/PortCompat.h
	$(CXX) $(CPPFLAGS) -std=c++98 -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer -o $(SAN) $<
	./$(SAN)
	$(CXX) $(CPPFLAGS) -I../../include -std=c++98 -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer -o $(CALLBACK_SAN) item_factory_callbacks.cpp
	./$(CALLBACK_SAN)

clean:
	rm -f $(BIN) $(SAN) $(CALLBACK_BIN) $(CALLBACK_SAN)
