.PHONY: all

all: hotswap plugin.so

CXXFLAGS=-g -Wall -Werror -fpic -pipe
INITFUN=on_load

plugin.so: plugin.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) -shared $< -o $@ -Wl,-init,$(INITFUN)

LDFLAGS=-ldl -lpthread
hotswap: hotswap.cpp

.PHONY: clean
clean:
	rm -rf plugin.so hotswap
