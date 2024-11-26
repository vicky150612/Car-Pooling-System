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

void view_ride(struct User *user)
{
    FILE *ptr = fopen("rides.txt", "r");
    if (ptr == NULL)
    {
        printf("Error opening rides.txt\n");
        return;
    }

    int found = 0;
    char line[256];

    while (fgets(line, sizeof(line), ptr) != NULL)
    {
        int ride_id, route_no, passenger_count, status;
        int passengers[4];

        sscanf(line, "Ride ID: %d, Route No: %d, Passenger Count: %d, Status: %d, Passengers: %d, %d, %d, %d", &ride_id, &route_no, &passenger_count, &status, &passengers[0], &passengers[1], &passengers[2], &passengers[3]);

        if (user == NULL)
        {
            printf("Ride ID: %d, Route No: %d, Passenger Count: %d, Status: %d, Passengers: ", ride_id, route_no, passenger_count, status);
            for (int i = 0; i < passenger_count && i < 4; i++)
            {
                printf("%d", passengers[i]);
                if (i < passenger_count - 1)
                {
                    printf(", ");
                }
            }
            printf("\n");
            found = 1;
        }
        else
        {
            for (int i = 0; i < passenger_count && i < 4; i++)
            {
                if (passengers[i] == user->uid)
                {
                    printf("Ride ID: %d, Route No: %d, Passenger Count: %d, Status: %d, Passengers: ", ride_id, route_no, passenger_count, status);
                    for (int j = 0; j < passenger_count && j < 4; j++)
                    {
                        printf("%d", passengers[j]);
                        if (j < passenger_count - 1)
                        {
                            printf(", ");
                        }
                    }
                    printf("\n");
                    found = 1;
                    break;
                }
            }
        }
    }

    if (!found)
    {
        if (user == NULL)
        {
            printf("No rides available.\n");
        }
        else
        {
            printf("No rides found for user with UID: %d\n", user->uid);
        }
    }

    fclose(ptr);
}

// int main()
// {
//     struct Node *a = file_to_linkedlist(NULL);
//     delete_user(1003, a);
//     return 0;
// }
// int main()
// {
//     struct User a = {10, "a", "b"};
//     view_ride(&a);
//     return 0;
// }