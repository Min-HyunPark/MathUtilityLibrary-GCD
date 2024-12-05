#include <stdio.h>
#include "gcd.h"

int main() {
    int a, b;
    printf("두 정수를 입력하세요: ");
    scanf("%d %d", &a, &b);

    int result = gcd(a, b);
    printf("%d와 %d의 GCD는: %d\n", a, b, result);

    return 0;
}

