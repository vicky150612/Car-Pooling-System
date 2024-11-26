#define admin_password "admin123"
#define no_of_places 37
#define price_per_unit_distance 10

char drives[12][100] = {
    "Car: Bugatti Chiron     Driver: Suhit Sharma             Car number:MS31 RD 9999",
    "Car: Bugatti Chiron     Driver: Amitabh Gupta            Car number:MS31 KV 7686",
    "Car: Bugatti Chiron     Driver: Priyadarshini Menon      Car number:MS31 KV 6498",
    "Car: Bugatti Chiron     Driver: Srinivasan Nambiar       Car number:MS31 ZY 4815",
    "Car: Bugatti Chiron     Driver: Mohammed Shafi           Car number:MS31 RX 2916",
    "Car: Bugatti Chiron     Driver: Arvind Krishnan          Car number:MS31 MN 9873",
    "Car: Bugatti Chiron     Driver: Anjali Verma             Car number:MS31 QB 5643",
    "Car: Bugatti Chiron     Driver: Meenakshi Naidu          Car number:MS31 XP 7596",
    "Car: Bugatti Chiron     Driver: Ajay Verma               Car number:MS31 JV 1458",
    "Car: Bugatti Chiron     Driver: Kunal Tiwari             Car number:MS31 PN 2376",
    "Car: Bugatti Chiron     Driver: Raghav Iyer              Car number:MS31 GH 4437",
    "Car: Bugatti Chiron     Driver: Anirudh Reddy            Car number:MS31 WF 6624",
};

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

struct places
{
    char name[50];
    int cord_x;
    int cord_y;
};

void map();
void admin_or_user();
void main_screen();
void admin_login();
void user_register();
void user_login();
void admin_page();
void user_page();
void view_profile();
void book_ride();
void previous_bookings(char username[], char password[]);
void view_map();
void view_all_users();
void view_all_rides();
void view_rides_of_user();
void view_total_revenue();
void user_log();
void add_place(char *name, int cord_x, int cord_y);
void delete_place(char *name);
void delete_user(int uid);
struct User search_user(char username[], struct Node *head);
void view_user_data();
void view_ride(struct User *user);
int route(int xsa, int ysa, int xea, int yea);
int mod(int x);
int maxarray(int *x, int n);
int minarray(int *x, int n);
int finduser(char *username);
int registration(char *username, char *password);
int login_check(char *username, char *password);
void write_ride_to_file(struct Ride ride);
int check_rides(int uid);
void ongoing_ride(int uid, char username[], char password[]);
int cal_fare(int ride_id, int uid);
int assign_passenger(struct Passenger passenger);
int complete_ride(struct Ride *ride);
struct Ride ride_data(int ride_id);
void add_passenger(struct Passenger passenger, int ride_id);
struct places *pla();
struct places *func(char *path, struct places *data);
void user(int uid, char *username);
void prev_rides(char *username);