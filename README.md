# Carpooling Manager

## Overview

The Carpooling Manager is a system designed to optimize carpooling by assigning the same car and driver to users traveling along similar routes (as determined by the map). It ensures fair fare calculation, proportionate to the distance traveled by each user.

## Instructions to Run the Project

1. Use the `makefile` to compile the project by running the command:
   ```bash
   make
   ```
2. Start the application by executing:
   ```bash
   ./run
   ```
3. Workflow Overview:
   - Register as a new user.
   - Log in to the account you just created.
   - Book a ride.
   - Wait for other users to book rides along the same route.
   - Enjoy the cost advantage of shared travel compared to traveling alone.

### Admin Capabilities

The administrator has access to additional functionalities, including:

- User management (e.g., deleting a user).
- Monitoring login/logout history.

## Team Responsibilities

- **Shashank Peddi (BT2024210):** Search functionality, overall control flow.
- **Pennam Nikhil (IMT2024070):** Carpooling logic, map display, and error handling.
- **Chagari Saketh Kumar Reddy (BT2024183):** User interface design.
- **Kulkarni Keyur (BT2024025):** File management and user interface support.
- **Penumarti Hanish (BT2024190):** Core carpooling logic (including fare calculation) and error handling support.
- **Amara Jithamanyu (BT2024069):** Registration and login features, account implementation, and administrative functionalities.

## Note

This project is exclusively designed for **Linux-based systems** and is incompatible with other operating systems.
