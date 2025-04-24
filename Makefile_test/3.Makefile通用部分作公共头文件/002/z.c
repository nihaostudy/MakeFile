#include <stdio.h>
extern void func_x(void);
extern void func_y(void);

int main()
{
    printf("This is module z\n");
    func_x();
    func_y();
}