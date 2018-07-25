#include <stdio.h>
#include <unistd.h>

size_t g_count = 0;

int main()
{
    alarm(1);
    while(1)
    {
        ++g_count;
        printf("%lu,",g_count);
    }
    return 0;
}
