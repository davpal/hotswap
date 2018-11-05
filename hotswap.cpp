#include <cstdio>
#include <dlfcn.h>
#include "plugin.h"

int main(int argc, char * argv[])
{
    int c = 0;
    do {
        printf("Waiting for you sir: ");
        c = getchar();
    } while(c != 'q');
}
