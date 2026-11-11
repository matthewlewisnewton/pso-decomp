CXX ?= c++
CXXFLAGS ?= -std=c++98 -O2 -Wall -Wextra -ffp-contract=off
CPPFLAGS ?= -I../include
BIN := vector_math_fallbacks
SAN := $(BIN)_san
CALLBACK_BIN := item_factory_callbacks
CALLBACK_SAN := $(CALLBACK_BIN)_san
LOADER_BIN := loader_transfer
LOADER_SAN := $(LOADER_BIN)_san
LOADER_SOURCES := loader_transfer.cpp ../../src/pso/unk/text_8042E8C4.cpp ../../src/pso/unk/text_8042E9FC.cpp

.PHONY: all run sanitize clean

all: $(BIN) $(CALLBACK_BIN) $(LOADER_BIN)

$(BIN): vector_math_fallbacks.cpp ../include/pso/port/VectorMathFallbacks.h ../include/pso/port/PortCompat.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $<

$(CALLBACK_BIN): item_factory_callbacks.cpp ../../include/pso/item/ItemCreateFunction.h
	$(CXX) $(CPPFLAGS) -I../../include $(CXXFLAGS) -o $@ $<

$(LOADER_BIN): $(LOADER_SOURCES) ../include/pso/port/LoaderTransfer.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(LOADER_SOURCES)

run: all
	./$(BIN)
	./$(CALLBACK_BIN)
	./$(LOADER_BIN)

sanitize: vector_math_fallbacks.cpp ../include/pso/port/VectorMathFallbacks.h ../include/pso/port/PortCompat.h
	$(CXX) $(CPPFLAGS) -std=c++98 -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer -o $(SAN) $<
	./$(SAN)
	$(CXX) $(CPPFLAGS) -I../../include -std=c++98 -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer -o $(CALLBACK_SAN) item_factory_callbacks.cpp
	./$(CALLBACK_SAN)
	$(CXX) $(CPPFLAGS) -std=c++98 -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer -o $(LOADER_SAN) $(LOADER_SOURCES)
	./$(LOADER_SAN)

clean:
	rm -f $(BIN) $(SAN) $(CALLBACK_BIN) $(CALLBACK_SAN) $(LOADER_BIN) $(LOADER_SAN)
