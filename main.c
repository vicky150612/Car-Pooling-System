#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

int get_terminal_width()
{
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
    {
        return 80; // Default width if terminal size can't be determined
    }
    return w.ws_col;
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
    print_centered("%*s%s\n", padding, "", text);
}

void admin_or_user();
void main_screen();
void admin_login();
void user_register();
void user_login();
void admin_page();
void user_page();
void view_profile();
void book_ride();
void previous_bookings();
void view_map();

void admin_or_user()
{
    system("clear");
    char option;

    print_centered("   _________________________________________________________________________________________________________\n");
    print_centered("  / _______________________________________________________________________________________________________ \\ \n");
    print_centered("  | |     _____________                                                                                   | |\n");
    print_centered("  | |     |           |                              WELCOME                                              | |\n");
    print_centered("  | |     |  Press e  |                              ^^^^^^^                                              | |\n");
    print_centered("  | |     |  to exit  |                                TO                                                 | |\n");
    print_centered("  | |     |___________|                                ^^                                                 | |\n");
    print_centered("  | |                                               HERMEAZEY                                             | |\n");
    print_centered("  | |                                               ^^^^^^^^^                                             | |\n");
    print_centered("  | |                                                                                                     | |\n");
    print_centered("  | |                                                                                                     | |\n");
    print_centered("  | |            ____________                                                    ___________              | |\n");
    print_centered("  | |            |          |                                                    |         |              | |\n");
    print_centered("  | |            |   USER   |                                                    |  ADMIN  |              | |\n");
    print_centered("  | |            |__________|                                                    |_________|              | |\n");
    print_centered("  | |                                                                                                     | |\n");
    print_centered("  | |             Type u and                                                      Type a and              | |\n");
    print_centered("  | |             Press Enter                                                     Press Enter             | |\n");
    print_centered("  | |_____________________________________________________________________________________________________| |\n");
    print_centered("  \\_________________________________________________________________________________________________________/\n");
    print_centered("                                                    ||   ||\n");
    print_centered("                                                    ||   ||\n");
    print_centered("                                                    _________\n");
    print_centered("                                                   /__|__|___\\__\n");
    print_centered("                                                  |--(o)---(o)--|\n");
    print_centered("                                                  ^^^^^^^^^^^^^^^\n");

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

    print_centered("   _________________________________________________________________________________________________________\n");
    print_centered("  / _______________________________________________________________________________________________________ \\ \n");
    print_centered("  | |  _______________                                                                                    | |\n");
    print_centered("  | |  |             |                               WELCOME                                              | |\n");
    print_centered("  | |  |   PRESS b   |                               ^^^^^^^                                              | |\n");
    print_centered("  | |  |  to go back |                                 TO                                                 | |\n");
    print_centered("  | |  |_____________|                                 ^^                                                 | |\n");
    print_centered("  | |                                               HERMEAZEY                                             | |\n");
    print_centered("  | |                                               ^^^^^^^^^                                             | |\n");
    print_centered("  | |                                                                                                     | |\n");
    print_centered("  | |                 TO                                                             TO                   | |\n");
    print_centered("  | |            ____________                                                    ___________              | |\n");
    print_centered("  | |            |          |                                                    |         |              | |\n");
    print_centered("  | |            | REGISTER |                                                    | SIGN-IN |              | |\n");
    print_centered("  | |            |__________|                                                    |_________|              | |\n");
    print_centered("  | |                                                                                                     | |\n");
    print_centered("  | |             Type r and                                                      Type s and              | |\n");
    print_centered("  | |             Press Enter                                                     Press Enter             | |\n");
    print_centered("  | |_____________________________________________________________________________________________________| |\n");
    print_centered("  \\_________________________________________________________________________________________________________/\n");
    print_centered("                                                    ||   ||\n");
    print_centered("                                                    ||   ||\n");
    print_centered("                                                    _________\n");
    print_centered("                                                   /__|__|___\\__\n");
    print_centered("                                                  |--(o)---(o)--|\n");
    print_centered("                                                  ^^^^^^^^^^^^^^^\n");

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
    else if (strcmp(pass, "admin123") == 0)
    {
        print_centered("Login is successful\n");
        print_centered("/////////////////////////////////////////////\n");
        print_centered("Press enter to continue\n");
        getchar();
        admin_page();
    }
    else
    {
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
    int registration = 0;

    print_centered("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\n");
    print_centered("Press b to go back\n");
    print_centered("\n");
    print_centered("REGISTER A NEW USER\n");
    print_centered("\n");
    print_centered("NOTE:\n");
    print_centered("1)While entering Username and Password please don't use spaces and commas\n");
    print_centered("2)Username and Password should be between 6 to 100 characters\n");
    print_centered("\n");
    print_centered("Please enter your desired username:\n");
    scanf("%s", username);
    getchar(); // Clear the newline character from the buffer

    if (strcmp(username, "b") == 0)
    {
        main_screen();
        return;
    }

    print_centered("\n");
    print_centered("Please enter your desired password:\n");
    scanf("%s", password);
    getchar(); // Clear the newline character from the buffer

    print_centered("\n");
    print_centered("Please re-enter your password:\n");
    scanf("%s", confirm_password);
    getchar(); // Clear the newline character from the buffer

    if (strcmp(password, confirm_password) == 0)
    {
        registration = 1; // Dummy logic for successful registration
    }
    else
    {
        registration = 0; // Dummy logic for unsuccessful registration
    }

    print_centered("\n");
    if (registration == 1)
    {
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
    scanf("%s", username);
    getchar(); // Clear the newline character from the buffer

    if (strcmp(username, "b") == 0)
    {
        main_screen();
        return;
    }

    print_centered("\n");
    print_centered("Password:\n");
    scanf("%s", password);
    getchar(); // Clear the newline character from the buffer

    if (login == 1)
    { // Dummy logic for successful login
        print_centered("LOGIN WAS SUCCESSFUL\n");
        print_centered("\n");
        print_centered("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\n");
        print_centered("Press Enter to continue\n");
        getchar(); // Wait for Enter key
        user_page();
    }
    else
    {
        user_login();
    }
}
void user_page()
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
    int choice;
    scanf("%d", &choice);
    if (choice == 1)
    {
        view_profile();
    }
    else if (choice == 2)
    {
        book_ride();
    }
    else if (choice == 3)
    {
        previous_bookings();
    }
    else if (choice == 4)
    {
        view_map();
    }
    else if (choice == 5)
    {
        system("clear");
        print_centered("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
        print_centered("\n");
        print_centered("YOU HAVE LOGGED OUT SUCCESSFULLY");
        print_centered("\n");
        print_centered("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
        print_centered("Press Enter to continue\n");
        getchar(); // Wait for Enter key
        user_login();
    }
    else
    {
        print_centered("********************************\n");
        print_centered("ERROR\n");
        print_centered("PLEASE ENTER A VALID OPTION\n");
        print_centered("********************************\n");
        print_centered("Press Enter to retry\n");
        getchar(); // Wait for Enter key
        user_page();
    }
}
void view_profile()
{
    system("clear");
    print_centered("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    previous_bookings("Type b and press enter to go back");
    print_centered("\n");
    print_centered("PROFILE\n");
    print_centered("\n");
    print_centered("USERNAME: %s\n", username);
    print_centered("\n");
    // more features to be filled
    print_centered("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    print_centered("\n");
    char back;
    scanf("&c", &back);
    if (back == 'b')
    {
        user_page();
    }
    else
    {
        print_centered("********************************\n");
        print_centered("ERROR\n");
        print_centered("PLEASE ENTER A VALID OPTION\n");
        print_centered("********************************\n");
        print_centered("Press Enter to retry\n");
        getchar(); // Wait for Enter key
        view_profile();
    }
}
void book_ride()
{
    system("clear");
    print_centered("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    previous_bookings("Type b and press enter to go back");
    print_centered("\n");
    print_centered("RIDE BOOKING\n");
    print_centered("\n");
    printf_centered("Please enter your pickup location: \n");
    char pickup[100];
    scanf("%s", &pickup);
    // give search results and confirm the pickup location
    if (pickup == 'b')
    {
        user_page();
    }
    printf_centered("Please enter your drop location: \n");
    char drop[100];
    scanf("%s", &drop);
    // give search results and confirm the drop location
    if (drop == 'b')
    {
        user_page();
    }
    // return status of booking
    int booking;
    if (booking == 1)
    {
        system("clear");
        print_centered("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
        print_centered("\n");
        printf_centered("BOOKING SUCCESSFUL\n");
        print_centered("\n");
        // here give the driver and car details etc
        print_centered("Press enter to proceed back to the main menu\n");
        print_centered("\n");
        print_centered("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
        getchar(); // Wait for Enter key
    }
    else if (booking == 0)
    {
        system("clear");
        print_centered("********************************\n");
        print_centered("ERROR\n");
        print_centered("BOOKING FAILED\n");
        print_centered("********************************\n");
        print_centered("Press Enter to retry\n");
        getchar(); // Wait for Enter key
    }
}
void previous_bookings()
{
    system("clear");
    print_centered("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    previous_bookings("Type b and press enter to go back\n");
    previous_bookings("\n");
    // connect this with the database created by keyur
    previous_bookings("\n");
    print_centered("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    previous_bookings("\n");
    char back;
    scanf("&c", &back);
    if (back == 'b')
    {
        user_page();
    }
    else
    {
        print_centered("********************************\n");
        print_centered("ERROR\n");
        print_centered("PLEASE ENTER A VALID OPTION\n");
        print_centered("********************************\n");
        print_centered("Press Enter to retry\n");
        getchar(); // Wait for Enter key
        previous_bookings();
    }
}
void view_map()
{
    system("clear");
    // print the map
    print_centered("\n");
    print_centered("Type b and press enter to go back\n");
    char back;
    scanf("&c", &back);
    if (back == 'b')
    {
        user_page();
    }
    else
    {
        print_centered("********************************\n");
        print_centered("ERROR\n");
        print_centered("PLEASE ENTER A VALID OPTION\n");
        print_centered("********************************\n");
        print_centered("Press Enter to retry\n");
        getchar();
        view_map();
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
    print_centered("6. View User Log\n");
    print_centered("\n");
    print_centered("7. Logout\n");
    print_centered("\n");
    print_centered("[#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#]\n");
    char option;
    scanf("&c", &option);
    if (option == '1')
    {
        view_all_users();
    }
    else if (option == '2')
    {
        delete_user();
    }
    else if (option == '3')
    {
        view_all_rides();
    }
    else if (option == '4')
    {
        view_rides_of_user();
    }
    else if (option == '5')
    {
        view_total_revenue();
    }
    else if (option == '6')
    {
        user_log();
    }
    else if (option == '7')
    {
        system("clear");
        print_centered("[#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#]\n");
        print_centered("\n");
        print_centered("YOU HAVE LOGGED OUT SUCCESSFULLY");
        print_centered("\n");
        print_centered("[#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#]\n");
        print_centered("Press Enter to continue\n");
        getchar(); // Wait for Enter key
        main_screen();
    }
    else
    {
        print_centered("********************************\n");
        print_centered("ERROR\n");
        print_centered("PLEASE ENTER A VALID OPTION\n");
        print_centered("********************************\n");
        print_centered("Press Enter to retry\n");
        getchar();
        admin_page();
    }
}