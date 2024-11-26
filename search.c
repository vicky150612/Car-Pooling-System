struct places *pla()
{
    FILE *ptr = NULL;
    static struct places arr[no_of_places];
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

int k = 0;
int foundexact = 0;
struct places *func(char *path, struct places *data)
{
    struct places *arr;
    arr = malloc(no_of_places * sizeof(struct places));
    arr = pla();
    foundexact = 0;
    int len = strlen(path);
    for (int i = 0; i < len; i++)
    {
        path[i] = tolower(path[i]);
    }
    path[len] = '\0';
    for (int i = 0; i < no_of_places; i++)
    {
        char og_name[50];
        strcpy(og_name, arr[i].name);
        int len = strlen(arr[i].name);
        for (int j = 0; j < len; j++)
        {
            arr[i].name[j] = tolower(arr[i].name[j]);
        }
        arr[i].name[len] = '\0';
        if (strcmp(arr[i].name, path) == 0)
        {
            strcpy(arr[i].name, og_name);
            data[k] = arr[i];
            k++;
            foundexact = 1;
            break;
        }
    }
    if (!foundexact)
    {
        for (int i = 0; i < no_of_places; i++)
        {
            char og_name[50];
            strcpy(og_name, arr[i].name);
            int len = strlen(arr[i].name);
            for (int j = 0; j < len; j++)
            {
                arr[i].name[j] = tolower(arr[i].name[j]);
            }
            arr[i].name[len] = '\0';
            if (strstr(arr[i].name, path))
            {
                strcpy(arr[i].name, og_name);
                data[k] = arr[i];
                k++;
            }
        }
    }

    return data;
}

void user(int uid, char *username)
{
    FILE *file = fopen("users.txt", "r");
    char line[100];
    while (fgets(line, 100, file))
    {
        int id;
        char name[50];
        char password[50];
        sscanf(line, "%d,%[^,],%s\n", &id, name, password);
        if (id == uid)
        {
            strcpy(username, name);
            break;
        }
    }
    fclose(file);
}

void print_user(char username[])
{
    // print user details from users.txt
    FILE *file = fopen("users.txt", "r");
    char line[100];
    int found = 0;
    while (fgets(line, 100, file))
    {
        int id;
        char name[50];
        char password[50];
        sscanf(line, "%d,%[^,],%s\n", &id, name, password);
        if (strcmp(name, username) == 0)
        {
            found = 1;
            printf("ID: %d\nUsername: %s\n", id, name);
            break;
        }
    }
    if (!found)
    {
        printf("User not found\n");
    }
}

// int main()
// {
//     struct places *arr = pla();
// struct places data[37];
//     char path[50];
//     printf("Enter the path: ");
//     scanf("%s", path);
//     func(path, arr, data, 37);
//     printf("Places found: \n");
// if (!foundexact)
// {
//     for (int i = 0; i < k; i++)
//     {
//         printf("%s\n", data[i].name);
//     }
// }
// else
// {
//     printf("Exact match found: %s , %d,%d\n", data[0].name, data[0].cord_x, data[0].cord_y);
// }
// }