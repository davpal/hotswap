.PHONY: all

all: hotswap plugin.so

CXXFLAGS=-Wall -Werror
INITFUN=on_load

plugin.so: plugin.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) -shared $< -o $@ -Wl,-init,$(INITFUN)

hotswap: hotswap.cpp

.PHONY: clean
clean:
	rm -rf plugin.so hotswap
