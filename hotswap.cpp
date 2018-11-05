#include <atomic>
#include <cstdio>
#include <dlfcn.h>
#include <functional>
#include <thread>
#include "plugin.h"

std::function<void()> load_plugin();

int main(int argc, char * argv[])
{
    int c = 0;
    std::atomic<bool> running {true};
    std::thread t([&running] {
        while(running) {
            auto f = load_plugin();
            f(); // ooooo!!
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

std::function<void()> load_plugin()
{
    auto plugin = dlopen("./plugin.so", RTLD_NOW);
    if (!plugin) {
        fprintf(stderr, "Failed to load plugin %s.\n", dlerror());
        return []{};
    }

    auto fptr = reinterpret_cast<void(*)()>(dlsym(plugin, "fun"));
    if (!fptr) {
        fprintf(stderr, "Failed to load symbol %s.\n", dlerror());
        return []{};
    }

    return std::function<void()>(fptr);
}
