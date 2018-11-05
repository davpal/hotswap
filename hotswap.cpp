#include <atomic>
#include <cstdio>
#include <dlfcn.h>
#include <functional>
#include <thread>
#include "plugin.h"

void* load_plugin();
void  unload_plugin(void*);
std::function<void()> load_function(void*, const char*);


int main(int argc, char * argv[])
{
    int c = 0;
    std::atomic<bool> running {true};
    std::thread t([&running] {
        while(running) {
            auto p = load_plugin();
            auto f = load_function(p, "fun");
            f(); // ooooo!!
            unload_plugin(p);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
 
    do {
        printf("Waiting for you sir: ");
        c = getchar();
    } while(c != 'q');

    running = false;
    t.join();
}

void* load_plugin()
{
    auto plugin = dlopen("./plugin.so", RTLD_NOW);
    if (!plugin) {
        fprintf(stderr, "Failed to load plugin %s.\n", dlerror());
    }

    return plugin;
}

std::function<void()> load_function(void* plugin, const char* f)
{
    auto fptr = reinterpret_cast<void(*)()>(dlsym(plugin, f));
    if (!fptr) {
        fprintf(stderr, "Failed to load symbol %s.\n", dlerror());
        return []{};
    }

    return std::function<void()>(fptr);
}

void unload_plugin(void* p)
{
    dlclose(p);
}
