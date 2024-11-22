#include <stdio.h>
#include <stdlib.h>
#include "search.c"

struct User
{
    int uid;
    char username[50];
    char password[50];
};
struct Node
{
    struct User data;
    struct Node *next;
};
void add_place(char *name, int cord_x, int cord_y)
{
    FILE *ptr = NULL;
    ptr = fopen("places.txt", "a");
    fprintf(ptr, "%s,%d,%d\n", name, cord_x, cord_y);
    fclose(ptr);
}

struct Node *file_to_linkedlist(struct Node *head)
{
    FILE *fp;
    fp = fopen("users.txt", "r");
    char line[100];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        struct User u;
        sscanf(line, "%d,%[^,],%s\n", &u.uid, u.username, u.password);
        struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
        new_node->data.uid = u.uid;
        strcpy(new_node->data.username, u.username);
        strcpy(new_node->data.password, u.password);
        new_node->next = head;
        head = new_node;
    }
    fclose(fp);
    return head;
}

void delete_place(char *name)
{
    FILE *ptr = NULL;
    FILE *temp = NULL;
    ptr = fopen("places.txt", "r");
    temp = fopen("temp.txt", "w");
    char line[100];
    while (fgets(line, sizeof(line), ptr) != NULL)
    {
        if (strstr(line, name) == NULL)
        {
            fprintf(temp, "%s", line);
        }
    }
    fclose(ptr);
    fclose(temp);
    remove("places.txt");
    rename("temp.txt", "places.txt");
}

struct Node *delete_user(int uid, struct Node *head)
{
    FILE *ptr = fopen("users.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    char line[100];
    while (fgets(line, sizeof(line), ptr) != NULL)
    {
        int user_id;
        sscanf(line, "%d,", &user_id);
        if (user_id != uid)
        {
            fprintf(temp, "%s", line);
        }
    }
    fclose(ptr);
    fclose(temp);
    remove("users.txt");
    rename("temp.txt", "users.txt");

    struct Node *n = head;
    struct Node *c = head->next;
    if (n->data.uid == uid)
    {
        n = n->next;
        c = c->next;
        free(n);
    }
    n->next = c->next;
    return head;
}

struct Node *search_user(int uid, struct Node *head)
{
    head = file_to_linkedlist(head);
    struct Node *start = head;
    while (start != NULL)
    {
        if (start->data.uid == uid)
        {
            return start;
        }
        start = start->next;
    }
    return NULL;
}

void view_user_data()
{
    FILE *ptr = NULL;
    ptr = fopen("users.txt", "r");
    char line[100];
    while (fgets(line, sizeof(line), ptr) != NULL)
    {
        printf("%s", line);
    }
    fclose(ptr);
}

// int main()
// {
//     struct Node *a = file_to_linkedlist(NULL);
//     delete_user(1003, a);
//     return 0;
// }