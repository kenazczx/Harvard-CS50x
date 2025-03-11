#include <stdio.h>
#include <cs50.h>

bool valid_triangle(int a, int b, int c);
int main(void)
{
    valid_triangle(1, 2, 3);
}
s
bool valid_triangle(int a, int b, int c)
{
    if (!((a > 1) || (b > 1) || (c > 1)))
    {
        return false;
    }
    if (!((a+b>=c) || (b+c>=a) || (a+c>=b) ))
    {
        return false;
    }
    return true;
}
