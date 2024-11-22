#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logic.c"

struct Passenger
{
    int uid;
    int xsa;
    int xea;
    int ysa;
    int yea;
};

struct Ride
{
    int ride_id;
    int route_no;
    struct Passenger passengers[4];
    int passenger_count;
    int status;
};

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
    ride.status = 1; // marking the current status as ongoing
    ride.passengers[0] = passenger;
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

int main()
{

    return 0;
}