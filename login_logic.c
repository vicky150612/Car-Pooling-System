#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct User
{
    int uid;
    char *username;
    char *password;
};

struct Node
{
    struct User data;
    struct Node *next;
};

struct Node *head = NULL;

void add_userdata()
{
    FILE *ptr = fopen("users.txt", "r");
    struct Node *current = NULL;
    struct Node *new_node = NULL;

    while (!feof(ptr))
    {
        new_node = (struct Node *)malloc(sizeof(struct Node));
        new_node->data.username = (char *)malloc(50 * sizeof(char));
        new_node->data.password = (char *)malloc(50 * sizeof(char));

        fscanf(ptr, "%d,%[^,],%[^,\n]", &new_node->data.uid, new_node->data.username, new_node->data.password);
        new_node->data.username = realloc(new_node->data.username, strlen(new_node->data.username) + 1);
        new_node->data.password = realloc(new_node->data.password, strlen(new_node->data.password) + 1);
        new_node->next = NULL;

        if (head == NULL)
        {
            head = new_node;
        }
        else
        {
            current = head;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = new_node;
        }
    }

    fclose(ptr);
}

int finduser(char *username)
{
    add_userdata();
    struct Node *current = head;

    while (current != NULL)
    {
        if (strcmp(current->data.username, username) == 0)
        {
            return current->data.uid;
        }
        current = current->next;
    }

    return 69;
}

int registration(char *username, char *password)
{
    if (finduser(username) == 69)
    {
        int max_uid = 0;
        struct Node *current = head;

        max_uid = 0;
        while (current->next != NULL)
        {
            if (current->data.uid > max_uid)
            {
                max_uid = current->data.uid;
            }
            current = current->next;
        }
        current = head;
        int unique_uid = max_uid + 1;
        FILE *ptr = fopen("users.txt", "a");
        fprintf(ptr, "%d,%s,%s\n", unique_uid, username, password);
        fclose(ptr);

        struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
        new_node->data.uid = unique_uid;
        new_node->data.username = malloc(strlen(username) + 1);
        strcpy(new_node->data.username, username);
        new_node->data.password = malloc(strlen(password) + 1);
        strcpy(new_node->data.password, password);
        new_node->next = head;
        head = new_node;

        return 1;
    }
    else
    {
        return 0;
    }
}

int login_check(char *username, char *password)
{
    int userid = finduser(username);
    struct Node *current = head;

    while (current != NULL)
    {
        if (current->data.uid == userid)
        {
            if (strcmp(current->data.password, password) == 0)
            {
                return 1; // success
            }
            else
            {
                return 0; // invalid password
            }
        }
        current = current->next;
    }

    return 3; // user not found
}

int main()
{
    return 0;
}
