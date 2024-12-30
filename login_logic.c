struct Node *head = NULL;

void set_userdata()
{
    FILE *ptr = fopen("users.txt", "r");
    struct Node *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }

    head = NULL;
    struct Node *current = NULL;

    while (1)
    {
        struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
        if (fscanf(ptr, "%d,%[^,],%s\n", &new_node->data.uid, new_node->data.username, new_node->data.password) == 3)
        {
            new_node->next = NULL;
            if (head == NULL)
            {
                head = new_node;
                current = head;
            }
            else
            {
                current->next = new_node;
                current = new_node;
            }
        }
        else
        {
            free(new_node);
            break;
        }
    }

    fclose(ptr);
}

int finduser(char *username)
{
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

void delete_user(int uid)
{
    FILE *ptr = fopen("users.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    char line[100];
    while (fgets(line, sizeof(line), ptr))
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
    set_userdata();
}

int registration(char *username, char *password)
{
    set_userdata();

    if (finduser(username) == 69)
    {
        int max_uid = 1000;
        struct Node *current = head;

        while (current != NULL)
        {
            if (current->data.uid > max_uid)
            {
                max_uid = current->data.uid;
            }
            current = current->next;
        }

        int unique_uid = max_uid + 1;

        FILE *ptr = fopen("users.txt", "a");
        fprintf(ptr, "%d,%s,%s\n", unique_uid, username, password);
        fclose(ptr);

        set_userdata();
        return 1;
    }
    else
    {
        return 0;
    }
}

int login_check(char *username, char *password)
{
    set_userdata();
    int userid = finduser(username);
    struct Node *current = head;

    while (current != NULL)
    {
        if (current->data.uid == userid)
        {
            if (strcmp(current->data.password, password) == 0)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        current = current->next;
    }
    return 3;
}

void view_user_data()
{
    set_userdata();
    struct Node *current = head;
    while (current != NULL)
    {
        printf("UID: %d, Username: %s\n", current->data.uid, current->data.username);
        current = current->next;
    }
}