#include <stdio.h>
#include <assert.h>
#define do_test(f) printf("test : %s ... ",#f);f();
void isPositive();
void isNegative();
int main()
{
    printf("Start unit tests\n");
    do_test(isPositive);
    do_test(isPositive);
    do_test(isPositive);
    do_test(isNegative);
    do_test(isPositive);
    return 0;
}
void isPositive(){
    int i=1;
    assert(1==i);
    printf("passed\n");
}
void isNegative(){
    int i=1;
    assert(0==i);
    printf("passed\n");
}
