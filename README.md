# MathUtilityLibrary-GCD
본 문서는 인하대학교 시스템프로그래밍(CSE3209)교과목에서 수행된 프로젝트를 설명합니다.
정적 및 동적 라이브러리 링킹에 관한 내용을 포함합니다.

C언어에서 두 개의 Integer를 입력받았을 때 두 Integer 간의 최대공약수를 return 하는 함수를 디자인하고 정적 및 동적 라이브러리와 링킹하여 실행합니다.

### 개발환경
OS: Ubuntu 20.04 LTS

Compiler: GCC 9.4.0

## 리포지토리 구조
static:

gcd.c gcd.h gcd.o libgcd.a main_static.c main_static.o a.out

dynamic:

gcd.c gcd.h gcd.o libgcd.so main_dynamic.c main_dynamic.o main_dynamic

README.md



### 코드 설명
gcd.h: gcd 함수 프로토타입 선언
```
#ifndef GCD_H
#define GCD_H

// GCD 함수 선언
int gcd(int a, int b);

#endif // GCD_H
```

gcd.c: GCD함수의 정의

```
#include "gcd.h"

// 유클리드 알고리즘을 이용한 GCD 함수 정의
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
```

main_static.c: 정적 라이브러리를 사용하는 메인 프로그램

```
#include <stdio.h>
#include "gcd.h"

int main() {
    int a, b;

    // 사용자 입력
    printf("두 정수를 입력하세요: ");
    scanf("%d %d", &a, &b);

    // GCD 출력
    printf("%d와 %d의 GCD는: %d\n", a, b, gcd(a, b));

    return 0;
}
```

main_dynamic.c: 동적 라이브러리를 사용하는 메인 프로그램
```
#include <stdio.h>
#include <dlfcn.h>

int main() {
    void *handle;
    int (*gcd)(int, int);
    char *error;

    // 동적 라이브러리 로드
    handle = dlopen("./libgcd.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    // 기존 오류 초기화
    dlerror();

    // 동적 라이브러리에서 gcd 함수 로드
    *(void **)(&gcd) = dlsym(handle, "gcd");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        dlclose(handle);
        return 1;
    }

    // 사용자 입력
    int a, b;
    printf("두 정수를 입력하세요: ");
    scanf("%d %d", &a, &b);

    // GCD 출력
    printf("%d와 %d의 GCD는: %d\n", a, b, gcd(a, b));

    // 동적 라이브러리 언로드
    dlclose(handle);

    return 0;
}
```

1. static linking

gcc -c gcd.c main_static.c를 입력해 gcd.o, main_static.o 생성

ar -r libgcd.a gcd.o로 libgcd.a 생성.

gcc -static main_static.o -L. -lgcd로 main_static.o와 libgcd.a를 static linking함.

이로 만들어진 a.out을 실행해 두 정수를 입력하고 두 정수의 최대공약수를 return 받음.

2. dynamic linking

gcc -Og -c -fpic gcd.c main_dynamic.c를 입력해 두 파일을 컴파일해 gcd.o, main_dynamic.o를 위치 독립 코드로 생성.

gcc -shared -o libgcd.so gcd.o를 입력해 libgcd.so 생성.

gcc main_dynamic.o -L. -lgcd -ldl -o main_dynamic을 입력해 main_dynamic.o, libdl.so, libgcd.so를 dynamic linking하여 executable file main_dynamic 생성.

이로 만들어진 main_dynamic을 실행해 두 정수를 입력하고 두 정수의 최대공약수를 return 받음.
