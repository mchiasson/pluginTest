#include <dlfcn.h>
#include <stdio.h>

#include "if.h"

// called by libplugin.so
int foo() { return 42; }

typedef int bar_func_ptr();

int main(int argc, char** argv) {
  void* handle = dlopen(argv[1], RTLD_LAZY);

  if (handle == NULL) {
    fprintf(stderr, "Could not open '%s' plugin: %s\n", argv[1], dlerror());
    return 1;
  }

  bar_func_ptr* bar = dlsym(handle, "bar");
  if (bar == NULL) {
    fprintf(stderr, "Could not find bar: %s\n", dlerror());
    return 1;
  }

  printf("Calling plugin\n");
  int ret = bar();
  printf("Plugin returned %d\n", ret);

  if (dlclose(handle) != 0) {
    fprintf(stderr, "Could not close plugin: %s\n", dlerror());
    return 1;
  }

  return 0;
}
