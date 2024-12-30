void write_ride_to_file(struct Ride ride)
{
    FILE *file = fopen("rides.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (file != NULL && temp != NULL)
    {
        int a, b, c, d;
        int arr[4];
        int found = 0;

        while (fscanf(file, "Ride ID: %d, Route No: %d, Passenger Count: %d, Status: %d, Passengers: ", &a, &b, &c, &d) == 4)
        {
            for (int j = 0; j < c && j < 4; j++)
            {
                fscanf(file, "%d", &arr[j]);
                if (j < c - 1)
                {
                    fgetc(file);
                }
            }
            fgetc(file);

            if (a == ride.ride_id)
            {
                found = 1;
                fprintf(temp, "Ride ID: %d, Route No: %d, Passenger Count: %d, Status: %d, Passengers: ",
                        ride.ride_id, ride.route_no, ride.passenger_count, ride.status);
                for (int j = 0; j < ride.passenger_count; j++)
                {
                    fprintf(temp, "%d", ride.passengers[j].uid);
                    if (j < ride.passenger_count - 1)
                    {
                        fprintf(temp, ", ");
                    }
                }
                fprintf(temp, "\n");
            }
            else
            {
                fprintf(temp, "Ride ID: %d, Route No: %d, Passenger Count: %d, Status: %d, Passengers: ",
                        a, b, c, d);
                for (int j = 0; j < c && j < 4; j++)
                {
                    fprintf(temp, "%d", arr[j]);
                    if (j < c - 1 && j < 3)
                    {
                        fprintf(temp, ", ");
                    }
                }
                fprintf(temp, "\n");
            }
        }

        if (!found)
        {
            fprintf(temp, "Ride ID: %d, Route No: %d, Passenger Count: %d, Status: %d, Passengers: ",
                    ride.ride_id, ride.route_no, ride.passenger_count, ride.status);
            for (int j = 0; j < ride.passenger_count; j++)
            {
                fprintf(temp, "%d", ride.passengers[j].uid);
                if (j < ride.passenger_count - 1)
                {
                    fprintf(temp, ", ");
                }
            }
            fprintf(temp, "\n");
        }

        fclose(file);
        fclose(temp);
        remove("rides.txt");
        rename("temp.txt", "rides.txt");
    }
}

int check_rides(int uid)
{
    FILE *file = fopen("rides.txt", "r");
    int found = 0;
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        int ride_id, route_no, passenger_count, status;
        int passengers[4];
        sscanf(line, "Ride ID: %d, Route No: %d, Passenger Count: %d, Status: %d, Passengers: %d, %d, %d, %d", &ride_id, &route_no, &passenger_count, &status, &passengers[0], &passengers[1], &passengers[2], &passengers[3]);
        for (int i = 0; i < passenger_count && i < 4; i++)
        {
            if (passengers[i] == uid && status == 1)
            {
                found = ride_id;
                break;
            }
        }
    }

    fclose(file);
    return found;
}

int assign_passenger(struct Passenger passenger)
{
    int route_no = route(passenger.xsa, passenger.ysa, passenger.xea, passenger.yea);
    FILE *file = fopen("rides.txt", "r");
    int rideid = 0;
    if (file != NULL)
    {
        int a, b, c, d;
        int arr[4];
        while (fscanf(file, "Ride ID: %d, Route No: %d, Passenger Count: %d, Status: %d, Passengers: ", &a, &b, &c, &d) == 4)
        {
            rideid = a;
            if (b == route_no)
            {
                int passenger_exists = 0;
                for (int j = 0; j < c; j++)
                {
                    fscanf(file, "%d", &arr[j]);
                    if (arr[j] == passenger.uid)
                    {
                        passenger_exists = 1;
                        break;
                    }
                    if (j < c - 1)
                    {
                        fgetc(file);
                    }
                }
                fgetc(file);
                if (passenger_exists)
                {
                    fclose(file);
                    return 0;
                }
                if (d == 1 && c < 4)
                {
                    struct Ride ride;
                    ride.ride_id = a;
                    ride.route_no = b;
                    ride.passenger_count = c + 1;
                    ride.status = d;
                    ride.passengers[0] = passenger;
                    for (int j = 0; j < c; j++)
                    {
                        ride.passengers[j + 1] = (struct Passenger){arr[j], 0, 0, 0, 0};
                    }
                    fclose(file);
                    add_passenger(passenger, ride.ride_id);
                    write_ride_to_file(ride);
                    return 1;
                }
            }
        }
        fclose(file);
    }

    struct Ride ride;
    ride.ride_id = rideid + 1;
    ride.route_no = route_no;
    ride.passenger_count = 1;
    ride.status = 1;
    ride.passengers[0] = passenger;
    add_passenger(passenger, ride.ride_id);
    write_ride_to_file(ride);
    return 1;
}

int complete_ride(struct Ride *ride)
{
    // status = 1 ongoing
    // status = 0 completed
    if (ride->status == 1)
    {
        ride->status = 0;
        struct Ride ride1;
        ride1.ride_id = ride->ride_id;
        ride1.route_no = ride->route_no;
        ride1.passenger_count = ride->passenger_count;
        for (int i = 0; i < ride->passenger_count; i++)
        {
            ride1.passengers[i] = ride->passengers[i];
        }
        ride1.status = ride->status;
        write_ride_to_file(ride1);
    }
}

struct Ride ride_data(int ride_id)
{
    FILE *file = fopen("rides.txt", "r");
    struct Ride ride;
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        int ride_id1, route_no, passenger_count, status;
        int passengers[4];
        sscanf(line, "Ride ID: %d, Route No: %d, Passenger Count: %d, Status: %d, Passengers: %d, %d, %d, %d", &ride_id1, &route_no, &passenger_count, &status, &passengers[0], &passengers[1], &passengers[2], &passengers[3]);
        if (ride_id1 == ride_id)
        {
            ride.ride_id = ride_id1;
            ride.route_no = route_no;
            ride.passenger_count = passenger_count;
            ride.status = status;
            for (int i = 0; i < passenger_count && i < 4; i++)
            {
                ride.passengers[i].uid = passengers[i];
            }
            fclose(file);
            return ride;
        }
    }
    fclose(file);
    return ride;
}

void add_passenger(struct Passenger passenger, int ride_id)
{
    FILE *file = fopen("passengers.txt", "r");
    FILE *file2 = fopen("temp.txt", "w");
    struct Passenger passengers[4];
    int i = 0;
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        int passenger_count = 0;
        int id = 0;
        int index = 0;
        int numchars = 0;
        sscanf(line, "Ride ID: %d Passenger_count: %d Passengers: %n", &id, &passenger_count, &numchars);
        index += numchars;
        if (id == ride_id)
        {
            i++;
            for (int j = 0; j < passenger_count; j++)
            {
                sscanf(&line[index], "%d %n", &passengers[j].uid, &numchars);
                index += numchars;
            }
            index += 7;
            for (int j = 0; j < passenger_count; j++)
            {
                sscanf(&line[index], "%d %d %d %d %n", &passengers[j].xea, &passengers[j].xsa, &passengers[j].yea, &passengers[j].ysa, &numchars);
                index += numchars;
            }
            fprintf(file2, "Ride ID: %d Passenger_count: %d Passengers: ", id, passenger_count + 1);
            for (int j = 0; j < passenger_count; j++)
            {
                fprintf(file2, "%d ", passengers[j].uid);
            }
            fprintf(file2, "%d ", passenger.uid);
            fprintf(file2, "Cords: ");
            for (int j = 0; j < passenger_count; j++)
            {
                fprintf(file2, "%d %d %d %d ", passengers[j].xea, passengers[j].xsa, passengers[j].yea, passengers[j].ysa);
            }
            fprintf(file2, "%d %d %d %d \n", passenger.xea, passenger.xsa, passenger.yea, passenger.ysa);
        }
        else
        {
            fprintf(file2, "%s", line);
        }
        break;
    }
    if (i == 0)
    {
        fprintf(file2, "Ride ID: %d Passenger_count: 1 Passengers: %d Cords: %d %d %d %d \n", ride_id, passenger.uid, passenger.xea, passenger.xsa, passenger.yea, passenger.ysa);
    }
    fclose(file);
    fclose(file2);
    remove("passengers.txt");
    rename("temp.txt", "passengers.txt");
}

void view_all_rides()
{
    FILE *ptr = fopen("rides.txt", "r");
    char line[100];
    int i = 1;
    while (fgets(line, sizeof(line), ptr))
    {
        printf("%d. %s", i, line);
        i++;
    }
    fclose(ptr);
}

void prev_rides(char *username)
{
    int uid = finduser(username);
    FILE *file = fopen("rides.txt", "r");
    FILE *file2 = fopen("fare.txt", "r");
    struct Ride ride;
    char line[100];
    int f = 0;
    int ride_id_set = 0;
    int ride_id, route_no, passenger_count, status;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        int passengers[4];
        sscanf(line, "Ride ID: %d, Route No: %d, Passenger Count: %d, Status: %d, Passengers: %d, %d, %d, %d", &ride_id, &route_no, &passenger_count, &status, &passengers[0], &passengers[1], &passengers[2], &passengers[3]);
        int i;
        for (i = 0; i < passenger_count; i++)
        {
            if (passengers[i] == uid)
            {
                f++;
                ride_id_set = ride_id;
                printf("Ride ID: %d, Route No: %d, Passenger Count: %d, Status: ", ride_id, route_no, passenger_count);
                if (status == 0)
                {
                    printf("Completed ");
                }
                else
                {
                    printf("Not Completed \n");
                }
                int fare[5];
                while (fgets(line, sizeof(line), file2) != NULL)
                {
                    int ride_id1, passengercount;
                    int index, numchars;
                    sscanf(line, "Ride ID: %d Passenger Count: %d Total Fare : %n", &ride_id1, &passengercount, &numchars);
                    index = numchars;
                    if (ride_id1 == ride_id_set)
                    {
                        for (int i = 0; i < passengercount + 1; i++)
                        {
                            sscanf(&line[index], "%d %n", &fare[i], &numchars);
                            index += numchars;
                        }
                        printf("Fare: %d\n", fare[1]);
                    }
                }
                break;
            }
        }
    }
    if (f == 0)
    {
        printf("No previous rides\n");
    }
    fclose(file);
    fclose(file2);
}
