#include <stdio.h>
extern void func_a(void);
extern void func_b(void);

int main()
{
    printf("This is module c\n");
    func_a();
    func_b();
}