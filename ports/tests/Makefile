CXX ?= c++
CXXFLAGS ?= -std=c++98 -O2 -Wall -Wextra -ffp-contract=off
CPPFLAGS ?= -I../include
BIN := vector_math_fallbacks
SAN := $(BIN)_san
CALLBACK_BIN := item_factory_callbacks
CALLBACK_SAN := $(CALLBACK_BIN)_san
LOADER_BIN := loader_transfer
LOADER_SAN := $(LOADER_BIN)_san
LOADER_SOURCES := loader_transfer.cpp ../../src/pso/unk/text_8042E8C4.cpp

GINJA_BIN := ginja_parameter_callbacks
GINJA_SAN := $(GINJA_BIN)_san

EXI_BIN := exi_ethernet_fallbacks
EXI_SAN := $(EXI_BIN)_san

.PHONY: all run sanitize clean musyx game-kernels

all: $(BIN) $(CALLBACK_BIN) $(LOADER_BIN) $(GINJA_BIN) $(EXI_BIN)

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

# The original MusyX layouts require a compiler and runtime with 32-bit pointers and longs.
musyx: musyx_fallbacks
	./musyx_fallbacks

GAME32_CPPFLAGS := -I../../include -I../../src -I../../libs/dolphin/include
GAME32_CXXFLAGS := -m32 -msse2 -mfpmath=sse -fno-builtin -ffunction-sections -fdata-sections
GAME32_LDFLAGS := -Wl,--gc-sections

game-kernels: matrix_vector_kernels adx_encoder_residuals
	./matrix_vector_kernels
	./adx_encoder_residuals

matrix_vector_kernels: matrix_vector_kernels.cpp ../../src/pso/math/MatrixVector.cpp ../../include/pso/math/MatrixVector.h ../../libs/dolphin/include/libc/math.h
	$(CXX) $(CPPFLAGS) $(GAME32_CPPFLAGS) $(CXXFLAGS) $(GAME32_CXXFLAGS) $(GAME32_LDFLAGS) -o $@ $(filter %.cpp,$^) -lm

adx_encoder_residuals: adx_encoder_residuals.cpp ../../src/pso/audio/AdxEncoder.cpp ../../include/pso/audio/AdxEncoder.h
	$(CXX) $(CPPFLAGS) $(GAME32_CPPFLAGS) $(CXXFLAGS) $(GAME32_CXXFLAGS) $(GAME32_LDFLAGS) -o $@ $<

MUSYX_RUNTIME := ../../src/musyx/runtime
MUSYX_SOURCES := musyx_fallbacks.cpp $(MUSYX_RUNTIME)/Chorus/chorus_fx.c $(MUSYX_RUNTIME)/StdReverb/reverb.c
musyx_fallbacks: $(MUSYX_SOURCES) $(MUSYX_RUNTIME)/musyx_runtime_b.h $(MUSYX_RUNTIME)/musyx_dspvoice.h \
		../../include/pso/audio/SoundReverb.h ../../include/pso/audio/SoundMixVoice.h ../../include/types.h
	$(CXX) $(CPPFLAGS) $(GAME32_CPPFLAGS) $(CXXFLAGS) $(GAME32_CXXFLAGS) $(GAME32_LDFLAGS) -o $@ $(MUSYX_SOURCES)

clean:
	rm -f matrix_vector_kernels adx_encoder_residuals musyx_fallbacks $(BIN) $(SAN) $(CALLBACK_BIN) $(CALLBACK_SAN) $(LOADER_BIN) $(LOADER_SAN) $(GINJA_BIN) $(GINJA_SAN) $(EXI_BIN) $(EXI_SAN)
