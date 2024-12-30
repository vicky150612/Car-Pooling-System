#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <time.h>
#include "project.h"
#include "logic.c"
#include "admin.c"
#include "login_logic.c"
#include "rides.c"
#include "search.c"
#include "final_map.c"
int naaistam = 0;

#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"

int get_terminal_width()
{
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
    {
        return 80; // Default width if terminal size can't be determined
    }
    return w.ws_col;
}

void pr_log(char *str)
{
    FILE *f = fopen("log.txt", "a");
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char s[100];
    strftime(s, sizeof(s), "%p", t);
    int i = t->tm_hour;
    if (i > 12)
    {
        i = i - 12;
    }
    fprintf(f, "%s %d:%d %s %d/%d/%d\n", str, i, t->tm_min, s, t->tm_mday, t->tm_mon, t->tm_year + 1900);
    fclose(f);
}

void print_centered(const char *text)
{
    int width = get_terminal_width();
    int text_length = strlen(text);
    int padding = (width - text_length) / 2;

    // Ensure padding is non-negative
    if (padding < 0)
        padding = 0;

    // Print padding spaces, then the text
    printf("%*s%s\n", padding, "", text);
}

void view_rides_of_user()
{
    system("clear");
    print_centered("[#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#]\n");
    print_centered("Enter the username of the user to view their rides \n\n");
    char username[100];
    scanf("%s", username);
    int uid = finduser(username);
    int found = 0;
    if (uid == 69)
    {
        print_centered("User not found\n");
        print_centered("Press enter to continue");
        getchar();
        getchar();
        return;
    }
    else
    {
        FILE *file = fopen("rides.txt", "r");
        char line[100];
        while (fgets(line, sizeof(line), file) != NULL)
        {
            int ride_id, route_no, passenger_count, status;
            int passengers[4];
            sscanf(line, "Ride ID: %d, Route No: %d, Passenger Count: %d, Status: %d, Passengers: %d, %d, %d, %d", &ride_id, &route_no, &passenger_count, &status, &passengers[0], &passengers[1], &passengers[2], &passengers[3]);
            for (int i = 0; i < passenger_count && i < 4; i++)
            {
                if (passengers[i] == uid)
                {
                    found = 1;
                    printf("Ride ID: %d, Route No: %d, Passenger Count: %d, Status: %d, Passengers:", ride_id, route_no, passenger_count, status);
                    for (int j = 0; j < passenger_count; j++)
                    {
                        printf("%d ", passengers[j]);
                    }
                }
            }
        }
        fclose(file);
        if (!found)
        {
            printf("No rides found for the user\n");
        }
        printf("\n");
    }
    print_centered("\n");
    print_centered("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    print_centered("\n");
    print_centered("Press Enter to continue");
    getchar();
    getchar();
}
void view_total_revenue()
{
    system("clear");
    FILE *fp = fopen("fare.txt", "r");
    int total_revenue = 0;
    int total_rides = 0;
    char line[100];
    int rideid, passenger_count, fare;
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        sscanf(line, "Ride ID: %d Passenger Count: %d Total Fare : %d", &rideid, &passenger_count, &fare);
        total_revenue += fare;
        total_rides++;
    }
    print_centered("\n");
    print_centered("Total number of Rides are ");
    char text[20];
    sprintf(text, "%d\n", total_rides);
    text[strlen(text) - 1] = ' ';
    print_centered(text);
    print_centered("Total Revenue is ");
    char text1[10];
    sprintf(text1, "%d\n", total_revenue);
    text1[strlen(text1) - 1] = ' ';
    print_centered(text1);
    print_centered("\n");
    fclose(fp);
    print_centered("Press Enter to continue ");
    getchar();
    getchar();
    admin_page();
}

void user_log()
{
    system("clear");
    print_centered("\n");
    print_centered("<><><><><><><><><><><><><><><><><><><><><><><\n");
    print_centered("User Log\n");
    FILE *file = fopen("log.txt", "r");
    char line[100];
    int count = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        print_centered(("%s\n", line));
    }
    fclose(file);
    print_centered("\n");
    print_centered("<><><><><><><><><><><><><><><><><><><><><><><\n");
    print_centered("\n");
    print_centered("Press Enter to continue");
    getchar();
    getchar();
}

void admin_or_user()
{
    system("clear");
    char option;

    printf("                                    %s   _______________________________________________________________________________________________________%s\n\n", GREEN, RESET);
    printf("                                    %s  / _______________________________________________________________________________________________________\\ %s\n\n", GREEN, RESET);
    printf("                                    %s  | |                                                                                                     | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |     _____________                                                                                   | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |     |           |%s", GREEN, RESET);
    printf("%s                              WELCOME                                              %s", CYAN, RESET);
    printf("%s| |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |     |%s", GREEN, RESET);
    printf("%s  Press e  %s", RED, RESET);
    printf("%s|                              ^^^^^^^                                              | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |     |%s", GREEN, RESET);
    printf("%s  to exit  %s", RED, RESET);
    printf("%s|%s", GREEN, RESET);
    printf("%s                                TO%s", CYAN, RESET);
    printf("%s                                                 | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |     |___________|                                ^^                                                 | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |%s", GREEN, RESET);
    printf("%s                                    SHANKS CARPOOLING PVT LTD.%s", CYAN, RESET);
    printf("%s                                       | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |                                               ^^^^^^^^^                                             | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |            ____________                                                    ___________              | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |            |          |                                                    |         |              | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |            |%s", GREEN, RESET);
    printf("%s   USER%s", RED, RESET);
    printf("%s   |                                                    |%s", GREEN, RESET);
    printf("%s  ADMIN%s", RED, RESET);
    printf("%s  |              | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |            |__________|                                                    |_________|              | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |                                                                                                     | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |%s", GREEN, RESET);
    printf("%s             Type u and                                                      Type a and%s", CYAN, RESET);
    printf("%s              | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |%s", GREEN, RESET);
    printf("%s             Press Enter                                                     Press Enter             %s", CYAN, RESET);
    printf("%s| |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |_____________________________________________________________________________________________________| |%s\n\n", GREEN, RESET);
    printf("                                    %s  \\_________________________________________________________________________________________________________/%s\n\n", GREEN, RESET);
    printf("                                                                                       %s||   ||%s\n", GREEN, RESET);
    printf("                                                                                       %s||   ||%s\n", GREEN, RESET);
    printf("                                                                                      %s_________%s\n", YELLOW, RESET);
    printf("                                                                                    %s/__|___|___\\__%s\n", YELLOW, RESET);
    printf("                                                                                    %s|--(o)---(o)---|%s\n", YELLOW, RESET);
    printf("                                                                                    %s^^^^^^^^^^^^^^^^%s\n\n", YELLOW, RESET);

    option = getchar();
    getchar(); // Clear the newline character from the buffer

    if (option == 'u')
    {
        main_screen();
    }
    else if (option == 'a')
    {
        admin_login();
    }
    else if (option == 'e')
    {
        system("clear");
        exit(0);
    }
    else
    {
        print_centered("********************************\n");
        print_centered("ERROR\n");
        print_centered("PLEASE ENTER A VALID OPTION\n");
        print_centered("********************************\n");
        print_centered("Press Enter to retry\n");
        getchar(); // Wait for Enter key
        admin_or_user();
    }
}

void main_screen()
{
    system("clear");
    char option;

    printf("                                    %s   ________________________________________________________________________________________________________%s\n\n", GREEN, RESET);
    printf("                                    %s  / _______________________________________________________________________________________________________\\ %s\n\n", GREEN, RESET);
    printf("                                    %s  | |  ________________                                                                                   | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |  |              |%s", GREEN, RESET);
    printf("%s                              WELCOME%s", CYAN, RESET);
    printf("%s                                              | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |  |%s", GREEN, RESET);
    printf("%s   PRESS b %s", RED, RESET);
    printf("%s   |                              ^^^^^^^                                              | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |  |%s", GREEN, RESET);
    printf("%s  to go back %s", RED, RESET);
    printf("%s |                                %s", GREEN, RESET);
    printf("%sTO%s", CYAN, RESET);
    printf("%s                                                 | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |  |______________|                                ^^                                                 | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |%s", GREEN, RESET);
    printf("%s                                     SHANKS CARPOOLING PVT LTD.                                      %s", CYAN, RESET);
    printf("%s| |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |                                               ^^^^^^^^^                                             | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |%s", GREEN, RESET);
    printf("%s                 TO                                                             TO%s", BLUE, RESET);
    printf("%s                   | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |            ____________                                                    ___________              | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |            |          |                                                    |         |              | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |            |%s", GREEN, RESET);
    printf("%s REGISTER%s", RED, RESET);
    printf("%s |                                                    |%s", GREEN, RESET);
    printf("%s SIGN-IN%s", RED, RESET);
    printf("%s |              | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |            |__________|                                                    |_________|              | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |                                                                                                     | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |%s", GREEN, RESET);
    printf("%s             Type r and                                                      Type s and%s", CYAN, RESET);
    printf("%s              | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |%s", GREEN, RESET);
    printf("%s             Press Enter                                                     Press Enter%s", CYAN, RESET);
    printf("%s             | |%s\n\n", GREEN, RESET);
    printf("                                    %s  | |_____________________________________________________________________________________________________| |%s\n\n", GREEN, RESET);
    printf("                                    %s  \\_________________________________________________________________________________________________________/%s\n\n", GREEN, RESET);
    printf("                                    %s                                                        ||   ||%s\n", GREEN, RESET);
    printf("                                    %s                                                        ||   ||%s\n", GREEN, RESET);
    printf("                                    %s                                                       ________%s\n", YELLOW, RESET);
    printf("                                    %s                                                      /___|__|_\\___%s\n", YELLOW, RESET);
    printf("                                    %s                                                      |--(o)---(o)--|%s\n", YELLOW, RESET);
    printf("                                    %s                                                      ^^^^^^^^^^^^^^^%s\n\n", YELLOW, RESET);

    option = getchar();
    getchar(); // Clear the newline character from the buffer

    if (option == 'r')
    {
        user_register();
    }
    else if (option == 's')
    {
        user_login();
    }
    else if (option == 'b')
    {
        admin_or_user();
    }
    else
    {
        print_centered("********************************\n");
        print_centered("ERROR\n");
        print_centered("PLEASE ENTER A VALID OPTION\n");
        print_centered("********************************\n");
        print_centered("Press Enter to retry\n");
        getchar(); // Wait for Enter key
        main_screen();
    }
}

void admin_login()
{
    system("clear");
    char pass[100];

    print_centered("/////////////////////////////////////////////\n");
    print_centered("Press b to go back\n");
    print_centered("\n");
    print_centered("PLEASE ENTER YOUR ADMIN CREDENTIALS\n");
    print_centered("\n");
    print_centered("ADMIN PASSWORD:\n");
    scanf("%s", pass);
    getchar(); // Clear the newline character from the buffer

    if (strcmp(pass, "b") == 0)
    {
        admin_or_user();
    }
    else if (strcmp(pass, admin_password) == 0)
    {
        pr_log(("Admin login successful "));
        print_centered("Login is successful\n");
        print_centered("/////////////////////////////////////////////\n");
        print_centered("Press enter to continue\n");
        getchar();
        admin_page();
    }
    else
    {
        pr_log(("Admin login failed "));
        print_centered("********************************\n");
        print_centered("ERROR\n");
        print_centered("INVALID ADMIN CREDENTIALS\n");
        print_centered("********************************\n");
        print_centered("Press Enter to retry\n");
        getchar(); // Wait for Enter key
        admin_login();
    }
}
void user_register()
{
    system("clear");
    char username[100], password[100], confirm_password[100];
    print_centered("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\n");
    print_centered("Press b to go back\n");
    print_centered("\n");
    print_centered("REGISTER A NEW USER\n");
    print_centered("\n");
    print_centered("NOTE:\n");
    print_centered("1) While entering Username and Password please don't use spaces and commas\n");
    print_centered("2) Username and Password should be between 6 to 100 characters\n");
    print_centered("\n");
    print_centered("Please enter your desired username:\n");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';
    if (strcmp(username, "b") == 0)
    {
        main_screen();
        return;
    }
    int valid = 1;
    for (int i = 0; i < strlen(username); i++)
    {
        if (username[i] == ' ' || username[i] == ',')
        {
            valid = 0;
            break;
        }
    }
    if (!valid || strlen(username) < 6 || strlen(username) > 100)
    {
        print_centered("Invalid username. Please follow the guidelines.\n");
        print_centered("Press Enter to retry\n");
        getchar(); // Wait for Enter key
        user_register();
        return;
    }
    print_centered("\n");
    print_centered("Please enter your desired password:\n");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';
    print_centered("\n");
    print_centered("Please re-enter your password:\n");
    fgets(confirm_password, sizeof(confirm_password), stdin);
    confirm_password[strcspn(confirm_password, "\n")] = '\0';
    if (strcmp(password, confirm_password) != 0 || strlen(password) < 6 || strlen(password) > 100)
    {
        print_centered("********************************\n");
        print_centered("ERROR\n");
        if (strcmp(password, confirm_password) != 0)
        {
            print_centered("PASSWORDS DO NOT MATCH\n");
        }
        else
        {
            print_centered("Invalid password. Please follow the guidelines.\n");
        }
        print_centered("********************************\n");
        print_centered("Press Enter to retry\n");
        getchar(); // Wait for Enter key
        user_register();
        return;
    }
    int r = registration(username, password);
    print_centered("\n");
    if (r == 1)
    {
        char text[100] = "New registration: ";
        strcat(text, username);
        pr_log(text);
        print_centered("You have successfully registered\n");
        print_centered("You can now login with your new credentials\n");
        print_centered("\n");
        print_centered("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\n");
        print_centered("Press Enter to continue\n");
        getchar(); // Wait for Enter key
        main_screen();
    }
    else
    {
        print_centered("********************************\n");
        print_centered("ERROR\n");
        print_centered("USERNAME ALREADY EXISTS\n");
        print_centered("********************************\n");
        print_centered("Press Enter to retry\n");
        getchar(); // Wait for Enter key
        user_register();
    }
}
void user_login()
{
    system("clear");

    char username[100], password[100];
    int login = 0;

    print_centered("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\n");
    print_centered("Press b to go back\n");
    print_centered("\n");
    print_centered("USER LOGIN\n");
    print_centered("\n");
    print_centered("PLEASE ENTER YOUR USERNAME AND PASSWORD\n");
    print_centered("\n");
    print_centered("Username:\n");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';
    if (strcmp(username, "b") == 0)
    {
        main_screen();
        return;
    }
    int valid = 1;
    for (int i = 0; i < strlen(username); i++)
    {
        if (username[i] == ' ')
        {
            valid = 0;
            break;
        }
    }
    if (!valid || strlen(username) < 6 || strlen(username) > 100)
    {
        print_centered("Wrong username\n");
        print_centered("Press Enter to retry\n");
        getchar(); // Wait for Enter key
        user_login();
        return;
    }
    print_centered("\n");
    print_centered("Password:\n");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';
    login = login_check(username, password);
    if (login == 1)
    {
        char text[100] = "Login attempt success : ";
        strcat(text, username);
        pr_log(text);
        print_centered("LOGIN WAS SUCCESSFUL\n");
        print_centered("\n");
        print_centered("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\n");
        print_centered("Press Enter to continue\n");
        getchar(); // Wait for Enter key
        user_page(username, password, 1);
    }
    else if (login == 0)
    {
        char text[100] = "Login attempt failed : ";
        strcat(text, username);
        pr_log(text);
        print_centered("********************************\n");
        print_centered("INCORRECT USERNAME OR PASSWORD\n");
        print_centered("********************************\n");
        print_centered("Press Enter to retry\n");
        getchar(); // Wait for Enter key
        user_login();
    }
    else if (login == 3)
    {
        print_centered("********************************\n");
        print_centered("USER DOES NOT EXIST\n");
        print_centered("********************************\n");
        print_centered("Press Enter to retry\n");
        getchar(); // Wait for Enter key
        user_login();
    }
}
void user_page(char username[], char password[], int a)
{

    system("clear");
    print_centered("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    print_centered("USER PAGE\n");
    print_centered("\n");
    print_centered("\n");
    print_centered("PLEASE SELECT AN OPTION BELOW\n");
    print_centered("(Type the serial number of the option you want to select)\n");
    print_centered("\n");
    print_centered("1. View User Profile\n");
    print_centered("\n");
    print_centered("2. Book a Ride");
    print_centered("\n");
    print_centered("3. Previous Car Bookings\n");
    print_centered("\n");
    print_centered("4. View Map\n");
    print_centered("\n");
    print_centered("5. Logout\n");
    print_centered("\n");
    print_centered("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    if (a == 0)
    {
        print_centered("********************************\n");
        print_centered("ERROR\n");
        print_centered("PLEASE ENTER A VALID OPTION\n");
        print_centered("********************************\n");
        print_centered("Press Enter to retry\n");
    }
    char choice;
    scanf("%c", &choice);
    if (choice == '1')
    {
        view_profile(username, password);
    }
    else if (choice == '2')
    {
        int uid = finduser(username);
        if (check_rides(uid))
        {
            ongoing_ride(uid, username, password);
        }
        else
        {
            book_ride(username, password);
        }
    }
    else if (choice == '3')
    {
        previous_bookings(username, password);
    }
    else if (choice == '4')
    {
        view_map(username, password);
    }
    else if (choice == '5')
    {
        system("clear");
        char text[100] = "User has logged out : ";
        strcat(text, username);
        pr_log(text);
        print_centered("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
        print_centered("\n");
        print_centered("YOU HAVE LOGGED OUT SUCCESSFULLY");
        print_centered("\n");
        print_centered("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
        print_centered("Press Enter to continue\n");
        getchar(); // Wait for Enter key
        main_screen();
    }
    else if (choice == '\n')
    {
        user_page(username, password, 1);
    }
    else
    {

        print_centered("********************************\n");
        print_centered("ERROR\n");
        print_centered("PLEASE ENTER A VALID OPTION\n");
        print_centered("********************************\n");
        print_centered("Press Enter to retry\n");
        getchar();
        // getchar(); // Wait for Enter key
        user_page(username, password, 0);
    }
}
void view_profile(char username[], char password[])
{
    int user_id = finduser(username);
    system("clear");
    print_centered("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    print_centered("Type b to go back");
    print_centered("\n");
    print_centered("PROFILE\n");
    print_centered("\n");
    print_centered(("USERNAME: %s\n", username));
    print_centered("\n");
    // more features to be filled
    // delete account
    print_centered("DELETE ACCOUNT :\n");
    print_centered("Type d to delete your account");
    print_centered("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    print_centered("\n");
    char back;
    getchar();
    scanf("%c", &back);
    // getchar(); // Consume the newline character left in the input buffer
    if (back == 'd')
    {
        // confirm delete
        print_centered("Are you sure you want to delete this account");
        print_centered("\n");
        print_centered("Type y to confirm deletion");
        char c = getchar();
        if (c == 'y')
        {
            delete_user(user_id);
            print_centered("Account deleted successfully");
            print_centered("\n");
            print_centered("Press Enter to continue\n");
            getchar(); // Wait for Enter key
            main_screen();
            return;
        }
    }
    else if (back == 'b')
    {
        user_page(username, password, 1);
    }
    else
    {
        // user should be shown an error if he enters anything except numbers  1 to 6

        print_centered("********************************\n");
        print_centered("ERROR\n");
        print_centered("PLEASE ENTER A VALID OPTION\n");
        print_centered("********************************\n");
        print_centered("Press Enter to retry\n");
        view_profile(username, password);
        getchar(); // Wait for Enter key
    }
}
void book_ride(char username[], char password[])
{
    system("clear");
    print_centered("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    print_centered("Type b to go back");
    print_centered("\n");
    print_centered("RIDE BOOKING\n");
    print_centered("\n");
    print_centered("Please enter your pickup location: \n");

    char pickup[100];
    struct places data[37] = {};
    int xsa, xea, ysa, yea;

    while (1)
    {
        foundexact = 0;
        k = 0;

        scanf("%s", pickup);
        if (pickup[0] == 'b' && strlen(pickup) == 1)
        {
            user_page(username, password, 1);
        }
        else
        {
            func(pickup, data);

            if (!foundexact)
            {
                if (k == 0)
                {
                    print_centered("No similar locations found\n");
                }
                else
                {
                    print_centered("Matches Found \n");
                    print_centered("Please enter any of the following \n");
                    for (int i = 0; i < k; i++)
                    {
                        printf("%s\n", data[i].name);
                    }
                    printf("\n\n");
                }
            }
            else
            {
                xsa = data[0].cord_x;
                ysa = data[0].cord_y;
                break;
            }
        }
    }
    print_centered("Please enter your drop location: \n");
    char drop[100];
    foundexact = 0;
    k = 0;
    while (1)
    {
        foundexact = 0;
        k = 0;

        scanf("%s", drop);
        if (drop[0] == 'b' && strlen(drop) == 1)
        {
            user_page(username, password, 1);
        }
        else
        {
            func(drop, data);

            if (!foundexact)
            {
                if (k == 0)
                {
                    print_centered("No similar locations found\n");
                }
                else
                {
                    print_centered("Matches Found \n");
                    print_centered("Please enter any of the following \n");
                    for (int i = 0; i < k; i++)
                    {
                        printf("%s\n", data[i].name);
                    }
                    printf("\n\n");
                }
            }
            else
            {
                xea = data[0].cord_x;
                yea = data[0].cord_y;
                break;
            }
        }
    }
    // return status of booking

    if (strcmp(drop, pickup) == 0)
    {
        // system("clear");
        char text[100] = "User ";
        strcat(text, username);
        strcat(text, " Booking attempt failed ");
        // pr_log(text);
        print_centered("********************************\n");
        // print_centered("ERROR\n");
        print_centered("Pickup and drop locations cannot be the same\n");
        print_centered("********************************\n");
        print_centered("Press Enter to retry\n");
        getchar();
        getchar(); // Wait for Enter key
        book_ride(username, password);
    }
    int booking;
    int uid = finduser(username);
    struct Passenger p = {uid, xsa, xea, ysa, yea};
    booking = assign_passenger(p);

    if (booking == 1)
    {
        system("clear");
        char text[100] = "User ";
        strcat(text, username);
        strcat(text, " has booked a ride from ");
        strcat(text, pickup);
        strcat(text, " to ");
        strcat(text, drop);
        pr_log(text);
        print_centered("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
        print_centered("\n");
        print_centered("BOOKING SUCCESSFUL\n");
        print_centered("\n");
        // here give the driver and car details etcstrcat
        print_centered("Press enter to view ride details\n");
        print_centered("\n");
        print_centered("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
        getchar();
        getchar(); // Wait for Enter key
        user_page(username, password, 1);
    }
    else if (booking == 0)
    {
        // system("clear");
        char text[100] = "User ";
        strcat(text, username);
        strcat(text, " Booking attempt failed ");
        // pr_log(text);
        print_centered("********************************\n");
        // print_centered("ERROR\n");
        // print_centered("Pickup and drop locations cannot be the same\n");
        print_centered("********************************\n");
        print_centered("Press Enter to retry\n");
        getchar();
        getchar(); // Wait for Enter key
        book_ride(username, password);
    }
}
void previous_bookings(char username[], char password[])
{
    system("clear");
    print_centered("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    print_centered("Type b and press enter to go back\n");
    print_centered("\n");
    prev_rides(username);
    print_centered("\n");
    print_centered("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    print_centered("\n");
    char back;
    getchar();
    scanf("%c", &back);
    if (back == 'b')
    {
        user_page(username, password, 1);
    }
    else
    {
        print_centered("********************************\n");
        print_centered("ERROR\n");
        print_centered("PLEASE ENTER A VALID OPTION\n");
        print_centered("********************************\n");
        print_centered("Press Enter to retry\n");
        getchar(); // Wait for Enter key
        previous_bookings(username, password);
    }
}
void view_map(char username[], char password[])
{
    system("clear");
    map();
    print_centered("\n");
    print_centered("Type b and press enter to go back\n");
    char back;
    getchar();
    scanf("%c", &back);
    if (back == 'b')
    {
        user_page(username, password, 1);
    }
    else
    {
        print_centered("********************************\n");
        print_centered("ERROR\n");
        print_centered("PLEASE ENTER A VALID OPTION\n");
        print_centered("********************************\n");
        print_centered("Press Enter to retry\n");
        getchar();
        view_map(username, password);
    }
}
void admin_page()
{
    system("clear");
    print_centered("[#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#]\n");
    print_centered("\n");
    print_centered("ADMIN PAGE\n");
    print_centered("\n");
    print_centered("Please choose an option:\n");
    print_centered("\n");
    print_centered("1. View all users\n");
    print_centered("\n");
    print_centered("2. Delete a User\n");
    print_centered("\n");
    print_centered("3. View all rides\n");
    print_centered("\n");
    print_centered("4. View rides of a specific user\n");
    print_centered("\n");
    print_centered("5. View Total Revenue till now\n");
    print_centered("\n");
    print_centered("6. View Log\n");
    print_centered("\n");
    print_centered("7. Logout\n");
    print_centered("\n");
    print_centered("[#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#]\n");
    char option;
    scanf("%c", &option);
    if (option == '1')
    {
        pr_log(("Admin accesed user data "));
        view_all_users();
    }
    else if (option == '2')
    {
        system("clear");
        print_centered("[#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#]\n");
        print_centered("Enter the Username to delete: \n");
        char username[100];
        scanf("%s", username);
        int uid = finduser(username);
        if (uid == 69)
        {
            print_centered("User not found\n");
            print_centered("Press Enter to continue\n");
            getchar();
            getchar();
            admin_page();
        }
        print_centered("ARE YOU SURE YOU WANT TO DELETE THIS ?(y/n) \n");
        char confirm;
        getchar();
        scanf("%c", &confirm);
        if (confirm == 'y')
        {
            delete_user(uid);
            char text[100] = "Admin deleted user : ";
            strcat(text, username);
            pr_log(text);
            print_centered("User deleted successfully\n");
            print_centered("Press Enter to continue\n");
            getchar();
            getchar();
            admin_page();
        }
        else
        {
            print_centered("Deletion Cancelled\n");
            print_centered("Press Enter to continue\n");
            getchar();
            admin_page();
        }
    }
    else if (option == '3')
    {
        pr_log(("Admin acssesed ride data "));
        system("clear");
        print_centered("[#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#]\n");
        print_centered("ALL Rides\n");
        print_centered("[#][#][#][#][#][#][#][#][#][#][#][#][#]");
        print_centered("---------------------------------\n");
        view_all_rides();
        print_centered("[#][#][#][#][#][#][#][#][#][#][#][#][#]\n");
        print_centered("Press Enter to continue\n");
        getchar();
        getchar();
        admin_page();
    }
    else if (option == '4')
    {
        pr_log(("Admin acssesed ride data "));
        view_rides_of_user();
        admin_page();
    }
    else if (option == '5')
    {
        view_total_revenue();
    }
    else if (option == '6')
    {
        user_log();
        admin_page();
    }
    else if (option == '7')
    {
        pr_log(("Admin logged out "));
        system("clear");
        print_centered("[#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#]\n");
        print_centered("\n");
        print_centered("YOU HAVE LOGGED OUT SUCCESSFULLY");
        print_centered("\n");
        print_centered("[#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#]\n");
        print_centered("Press Enter to continue\n");
        getchar(); // Wait for Enter key
        admin_or_user();
    }
    else
    {
        print_centered("********************************\n");
        print_centered("ERROR\n");
        print_centered("PLEASE ENTER A VALID OPTION\n");
        print_centered("********************************\n");
        print_centered("Press Enter to retry\n");
        getchar();
        getchar();
        admin_page();
    }
}

void ongoing_ride(int uid, char username[], char password[])
{
    system("clear");
    print_centered("\n");
    print_centered("Type b and press enter to go back\n");
    print_centered("\n");
    int ride_id = check_rides(uid);
    struct Ride ride = ride_data(ride_id);
    print_centered("Ride Details:");
    print_centered("\n");
    print_centered(("%s", drives[ride.route_no - 1]));
    print_centered("\n");
    if (ride.passenger_count > 1)
    {
        print_centered(("Your copassengers are \n\n"));
        for (int i = 0; i < ride.passenger_count; i++)
        {
            char copassenger_username[100];
            if (uid != ride.passengers[i].uid)
            {
                user(ride.passengers[i].uid, copassenger_username);
                print_centered(("%s\n", copassenger_username));
            }
        }
        print_centered("\n");
        print_centered("Type s to start the ride \n\n");
        char x;
        scanf("%c", &x);
        scanf("%c", &x);
        if (x == 's')
        {
            getchar();
            print_centered("Your ride has been started\n");
            print_centered("Press c to complete the ride\n");
            scanf("%c", &x);
            // getchar();
            if (x == 'c')
            {
                complete_ride(&ride);
                int fare = cal_fare(ride_id, uid);
                printf("\n");
                char text[100] = "User completed ride : ";
                strcat(text, username);
                pr_log(text);
                printf("User completed ride\n");
                printf("Fare: %d\n", fare);
                print_centered("Press Enter to go back to user page\n");
                getchar();
                // getchar();
                user_page(username, password, 1);
            }
            else
            {
                print_centered("Invalid option");
                print_centered("Press Enter to retry");
                getchar();
                ongoing_ride(uid, username, password);
            }
        }
        if (x == 'b')
        {
            user_page(username, password, 1);
        }
    }
    else
    {
        print_centered("No co-passengers are currently on this ride\n");
    }
    getchar();
    char a = getchar();
    if (a == 'b')
    {
        user_page(username, password, 1);
    }
    else
    {
        print_centered("Invalid input\n");
        print_centered("Press Enter to continue\n");
        getchar();
        ongoing_ride(uid, username, password);
    }
}

void view_all_users()
{
    system("clear");
    print_centered("All users are:");
    print_centered("\n");
    view_user_data();
    print_centered("\n");
    print_centered("Search a specific user (b to go back): ");
    // search for the user with username
    char username[100];
    scanf("%s", username);
    if (username[0] == 'b' && strlen(username) == 1)
    {
        admin_page();
    }
    system("clear");
    printf("User details are:\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    print_user(username);
    getchar();
    print_centered("\n");
    print_centered("Press Enter to continue\n");
    getchar();
    admin_page();
}

int main()
{
    FILE *file1 = fopen("users.txt", "a");
    fclose(file1);
    FILE *file2 = fopen("rides.txt", "a");
    fclose(file2);
    FILE *file3 = fopen("passengers.txt", "a");
    fclose(file3);
    FILE *file4 = fopen("log.txt", "a");
    fclose(file4);
    FILE *file5 = fopen("places.txt", "w");
    fprintf(file5, "%s", "Kalyanpuram,10,0\n");
    fprintf(file5, "%s", "Rudragarh,20,0\n");
    fprintf(file5, "%s", "Khansaar,30,0\n");
    fprintf(file5, "%s", "KirrinIsland,40,0\n");
    fprintf(file5, "%s", "Arrakis,50,0\n");
    fprintf(file5, "%s", "DragonStone,60,0\n");
    fprintf(file5, "%s", "Shambala,70,0\n");
    fprintf(file5, "%s", "UdayagiriHills,90,0\n");
    fprintf(file5, "%s", "Padhaghattam,80,0\n");
    fprintf(file5, "%s", "FortAgarwal,-10,0\n");
    fprintf(file5, "%s", "Pandora,-20,0\n");
    fprintf(file5, "%s", "Gotham,-30,0\n");
    fprintf(file5, "%s", "ViceCity,-40,0\n");
    fprintf(file5, "%s", "Valyria,-50,0\n");
    fprintf(file5, "%s", "Dharmasthali,-60,0\n");
    fprintf(file5, "%s", "Helheim,-70,0\n");
    fprintf(file5, "%s", "RedSea,-80,0\n");
    fprintf(file5, "%s", "MaalavaIslands,-90,0\n");
    fprintf(file5, "%s", "KamatNilayam,0,10\n");
    fprintf(file5, "%s", "ELDorado,0,20\n");
    fprintf(file5, "%s", "Hogwarts,0,30\n");
    fprintf(file5, "%s", "Hogsmeade,0,40\n");
    fprintf(file5, "%s", "LosSantos,0,50\n");
    fprintf(file5, "%s", "Essos,0,60\n");
    fprintf(file5, "%s", "Wakanda,0,70\n");
    fprintf(file5, "%s", "ChocolateFactory,0,80\n");
    fprintf(file5, "%s", "Kunthala,0,90\n");
    fprintf(file5, "%s", "SIIT,0,-10\n");
    fprintf(file5, "%s", "Atlantis,0,-20\n");
    fprintf(file5, "%s", "NewAsgard,0,-30\n");
    fprintf(file5, "%s", "KingsLanding,0,-40\n");
    fprintf(file5, "%s", "Agrabah,0,-50\n");
    fprintf(file5, "%s", "Olympus,0,-60\n");
    fprintf(file5, "%s", "Elbaf,0,-70\n");
    fprintf(file5, "%s", "Dholakpur,0,-80\n");
    fprintf(file5, "%s", "ShooraniForest,0,-90\n");
    fprintf(file5, "%s", "HANKSSJunction,0,0\n");
    fclose(file5);
    FILE *file6 = fopen("fare.txt", "a");
    fclose(file6);
    system("clear");
    admin_or_user();
}
