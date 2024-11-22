#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct places
{
    char name[100];
    int cord_x;
    int cord_y;
};
struct places *pla()
{
    FILE *ptr = NULL;
    static struct places arr[37];
    int line = 0;
    int read = 0;
    ptr = fopen("places.txt", "r");
    do
    {
        read = fscanf(ptr, "%49[^,],%d,%d\n", arr[line].name, &arr[line].cord_x, &arr[line].cord_y);
        if (read == 3)
        {
            line++;
        }
    } while (!feof(ptr));
    fclose(ptr);
    return arr;
}
int main()
{
    struct places *locations;
    locations = pla();
    printf("%d\n", locations[1].cord_x);
}