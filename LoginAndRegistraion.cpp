#include <iostream>
#include <string>
#include "user.h"
#include <filesystem>
using namespace std;

void showMenu() {
    cout << "Login and Registration System\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;
    string username, password;

    if (!filesystem::exists("users")) {
        filesystem::create_directory("users");
    }

    while (true) {
        showMenu();
        cin >> choice;

        if (cin.fail() || choice < 1 || choice  > 3) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input. Please enter a number (1, 2, or 3)." << endl;
            continue; // Repeat the loop
        }

        if (choice == 3) {
            cout << "Exiting system. Goodbye!" << endl;
            break; 
        }

        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        User user(username, password);

        if (choice == 1) { 
            user.registerUser();
        }
        else if (choice == 2) { 
            user.loginUser();
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}