#include <cstdio>
#include <dlfcn.h>
#include "plugin.h"

void load_plugin();

int main(int argc, char * argv[])
{
    int c = 0;
    do {
        printf("Waiting for you sir: ");
        c = getchar();
        load_plugin();
    } while(c != 'q');
}

void load_plugin()
{
    auto dl = dlopen("./plugin.so", RTLD_NOW);
    if (!dl) {
        fprintf(stderr, "Failed to load plugin %s.\n", dlerror());
    }
}
