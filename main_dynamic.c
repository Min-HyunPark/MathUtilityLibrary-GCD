#include <stdio.h>
#include <dlfcn.h>

int main() {
    void *handle;
    int (*gcd)(int, int);
    char *error;

    handle = dlopen("./libgcd.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    dlerror();

    *(void **)(&gcd) = dlsym(handle, "gcd");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        dlclose(handle);
        return 1;
    }

    int a, b;
    printf("두 정수를 입력하세요: ");
    scanf("%d %d", &a, &b);

    printf("%d와 %d의 GCD는: %d\n", a, b, gcd(a, b));

    dlclose(handle);

    return 0;
}

