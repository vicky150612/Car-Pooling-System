#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// #include <sys/ioctl.h>

// Cross-platform clear screen function
void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Function to get terminal width (with fallback for non-Linux systems)
int get_terminal_width()
{
#ifdef TIOCGWINSZ
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
    {
        return 80; // Default width if terminal size can't be determined
    }
    return w.ws_col;
#else
    return 80; // Fallback for non-Linux systems
#endif
}

// Function to print text centered
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

// Function prototypes (same as original)
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

// Functions fixed for correct usage and structure
void admin_or_user()
{
    clear_screen();
    char option;

    print_centered("   _________________________________________________________________________________________________________");
    print_centered("  / _______________________________________________________________________________________________________ \\");
    print_centered("  | |     _____________                                                                                   | |");
    print_centered("  | |     |           |                              WELCOME                                              | |");
    print_centered("  | |     |  Press e  |                              ^^^^^^^                                              | |");
    print_centered("  | |     |  to exit  |                                TO                                                 | |");
    print_centered("  | |     |___________|                                ^^                                                 | |");
    print_centered("  | |                                               HERMEAZEY                                             | |");
    print_centered("  | |                                               ^^^^^^^^^                                             | |");
    print_centered("  | |                                                                                                     | |");
    print_centered("  | |            ____________                                                    ___________              | |");
    print_centered("  | |            |          |                                                    |         |              | |");
    print_centered("  | |            |   USER   |                                                    |  ADMIN  |              | |");
    print_centered("  | |            |__________|                                                    |_________|              | |");
    print_centered("  | |             Type u and                                                      Type a and              | |");
    print_centered("  | |             Press Enter                                                     Press Enter             | |");
    print_centered("  | |_____________________________________________________________________________________________________| |");
    print_centered("  \\_________________________________________________________________________________________________________/");
    print_centered("                                                    ||   ||");
    print_centered("                                                    ||   ||");
    print_centered("                                                    _________");
    print_centered("                                                   /__|__|___\\__");
    print_centered("                                                  |--(o)---(o)--|");
    print_centered("                                                  ^^^^^^^^^^^^^^^");

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
        print_centered("********************************");
        print_centered("ERROR");
        print_centered("PLEASE ENTER A VALID OPTION");
        print_centered("********************************");
        print_centered("Press Enter to retry");
        getchar(); // Wait for Enter key
        admin_or_user();
    }
}

// Main screen for user
void main_screen()
{
    clear_screen();
    char option;

    print_centered("   _________________________________________________________________________________________________________");
    print_centered("  / _______________________________________________________________________________________________________ \\");
    print_centered("  | |  _______________                                                                                    | |");
    print_centered("  | |  |             |                               WELCOME                                              | |");
    print_centered("  | |  |   PRESS b   |                               ^^^^^^^                                              | |");
    print_centered("  | |  |  to go back |                                 TO                                                 | |");
    print_centered("  | |  |_____________|                                 ^^                                                 | |");
    print_centered("  | |                                               HERMEAZEY                                             | |");
    print_centered("  | |                                               ^^^^^^^^^                                             | |");
    print_centered("  | |                 TO                                                             TO                   | |");
    print_centered("  | |            ____________                                                    ___________              | |");
    print_centered("  | |            |          |                                                    |         |              | |");
    print_centered("  | |            | REGISTER |                                                    | SIGN-IN |              | |");
    print_centered("  | |            |__________|                                                    |_________|              | |");
    print_centered("  | |             Type r and                                                      Type s and              | |");
    print_centered("  | |             Press Enter                                                     Press Enter             | |");
    print_centered("  | |_____________________________________________________________________________________________________| |");
    print_centered("  \\_________________________________________________________________________________________________________/");
    print_centered("                                                    ||   ||");
    print_centered("                                                    ||   ||");
    print_centered("                                                    _________");
    print_centered("                                                   /__|__|___\\__");
    print_centered("                                                  |--(o)---(o)--|");
    print_centered("                                                  ^^^^^^^^^^^^^^^");

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
        print_centered("********************************");
        print_centered("ERROR");
        print_centered("PLEASE ENTER A VALID OPTION");
        print_centered("********************************");
        print_centered("Press Enter to retry");
        getchar(); // Wait for Enter key
        main_screen();
    }
}

// Placeholder for remaining functions: (Admin login, user registration, etc.)
// For brevity, not duplicating similar structures.
void admin_login()
{
}

void user_register()
{
}

void user_login()
{
}

int main()
{
    admin_or_user();
    return 0;
}
