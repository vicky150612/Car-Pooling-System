#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int testcases;
    scanf("%d", &testcases);
    for (int i = 0; i < testcases; i++)
    {
        if (i == 0)
        {
            getchar();
        }
        char *ptr;
        ptr = malloc(50 * sizeof(char));
        fgets(ptr, 50, stdin);
        int c = strlen(ptr);
        for (int j = 0; j < c; j++)
        {
            if (ptr[j] == '\n')
            {
                ptr[j] = '\0';
            }
        }
        ptr = ptr + c - 1;
        fgets(ptr, 50, stdin);
        ptr = ptr - c;
        printf("%s", ptr);
        free(ptr);
    }
    return 0;
}
