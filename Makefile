CXX=g++
CXXFLAGS=-Wall -Wmaybe-uninitialized -pedantic -Werror -g -O0 -std=c++17
OUTFILES=comp-emu

all: $(OUTFILES)

comp-emu: comp-emu.cpp comp-emu.hpp mach-code.cpp mach-code.hpp
	$(CXX) $(CXXFLAGS) -o Computer_EMU comp-emu.cpp comp-emu.hpp mach-code.cpp mach-code.hpp

clean:
	$(RM) $(OUTFILES) *.o
