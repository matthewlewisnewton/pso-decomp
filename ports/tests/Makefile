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

GINJA_BIN := ginja_parameter_callbacks
GINJA_SAN := $(GINJA_BIN)_san

EXI_BIN := exi_ethernet_fallbacks
EXI_SAN := $(EXI_BIN)_san

SOCKET_BIN := socket_queue
SOCKET_SAN := socket_queue_san
SOCKET_SOURCES := socket_queue.cpp ../../src/pso/network/SocketProtocolRuntime.cpp
SOCKET_HEADERS := ../include/pso/port/SocketQueue.h $(wildcard ../../include/pso/network/*.h) ../../include/pso/protocol/NetworkRuntime.h ../../include/types.h
SOCKET_FLAGS := -iquote ../../include -DPSO_SOCKET_QUEUE_PORT -Wno-unknown-pragmas

.PHONY: all run sanitize clean

all: $(BIN) $(CALLBACK_BIN) $(LOADER_BIN) $(GINJA_BIN) $(EXI_BIN) $(SOCKET_BIN)

$(SOCKET_BIN): $(SOCKET_SOURCES) $(SOCKET_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SOCKET_FLAGS) -o $@ $(SOCKET_SOURCES)

$(BIN): vector_math_fallbacks.cpp ../include/pso/port/VectorMathFallbacks.h ../include/pso/port/PortCompat.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $<

$(CALLBACK_BIN): item_factory_callbacks.cpp ../../include/pso/item/ItemCreateFunction.h
	$(CXX) $(CPPFLAGS) -I../../include $(CXXFLAGS) -o $@ $<

$(GINJA_BIN): ginja_parameter_callbacks.cpp ../../include/pso/system/GinjaParameterHandler.h
	$(CXX) $(CPPFLAGS) -I../../include $(CXXFLAGS) -o $@ $<

$(EXI_BIN): exi_ethernet_fallbacks.cpp ../include/pso/port/ExiEthernetFallbacks.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $<

$(LOADER_BIN): $(LOADER_SOURCES) ../include/pso/port/LoaderTransfer.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(LOADER_SOURCES)

run: all
	./$(SOCKET_BIN)
	./$(BIN)
	./$(CALLBACK_BIN)
	./$(LOADER_BIN)
	./$(GINJA_BIN)
	./$(EXI_BIN)

sanitize: vector_math_fallbacks.cpp ../include/pso/port/VectorMathFallbacks.h ../include/pso/port/PortCompat.h
	$(CXX) $(CPPFLAGS) -std=c++98 -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer -o $(SAN) $<
	./$(SAN)
	$(CXX) $(CPPFLAGS) -I../../include -std=c++98 -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer -o $(CALLBACK_SAN) item_factory_callbacks.cpp
	./$(CALLBACK_SAN)
	$(CXX) $(CPPFLAGS) -std=c++98 -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer -o $(LOADER_SAN) $(LOADER_SOURCES)
	./$(LOADER_SAN)
	$(CXX) $(CPPFLAGS) -I../../include -std=c++98 -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer -o $(GINJA_SAN) ginja_parameter_callbacks.cpp
	./$(GINJA_SAN)
	$(CXX) $(CPPFLAGS) -std=c++98 -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer -o $(EXI_SAN) exi_ethernet_fallbacks.cpp
	./$(EXI_SAN)
	$(CXX) $(CPPFLAGS) $(SOCKET_FLAGS) -std=c++98 -O1 -g -fsanitize=address,undefined,bounds -fno-omit-frame-pointer -o $(SOCKET_SAN) $(SOCKET_SOURCES)
	./$(SOCKET_SAN)

clean:
	rm -f $(BIN) $(SAN) $(CALLBACK_BIN) $(CALLBACK_SAN) $(LOADER_BIN) $(LOADER_SAN) $(GINJA_BIN) $(GINJA_SAN) $(EXI_BIN) $(EXI_SAN) $(SOCKET_BIN) $(SOCKET_SAN)
