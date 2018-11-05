#include <cstdio>

extern "C" void on_load()
{
    puts(__PRETTY_FUNCTION__);
}

extern "C" void fun()
{
    puts(__PRETTY_FUNCTION__);
    puts(">>>>");
}
