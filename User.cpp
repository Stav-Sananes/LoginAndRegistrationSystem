#include "user.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

User::User(const std::string& user, const std::string& pass) : username(user), password(pass) {}

bool User::registerUser() {
    string hashedPassword = hashPassword(password);

    // Check if user file already exists
    if (fs::exists("users/" + username + ".txt")) {
        cout << "Error: Username already taken. Try a different one." << endl;
        return false;
    }

    // Create and open user file
    ofstream userFile("users/" + username + ".txt");
    if (userFile.is_open()) {
        userFile << username << endl;
        userFile << hashedPassword << endl;
        userFile.close();
        cout << "User registered successfully!" << endl;
        return true;
    }
    else {
        cout << "Error: Could not create user file." << endl;
        return false;
    }
}

bool User::loginUser() {
    string hashedPassword = hashPassword(password);

    // Check if user file exists
    if (!fs::exists("users/" + username + ".txt")) {
        cout << "Error: User does not exist." << endl;
        return false;
    }

    // Open user file and verify password
    ifstream userFile("users/" + username + ".txt");
    string storedUsername, storedPassword;

    if (userFile.is_open()) {
        getline(userFile, storedUsername);
        getline(userFile, storedPassword);
        userFile.close();

        if (storedPassword == hashedPassword) {
            cout << "Login successful!" << endl;
            return true;
        }
        else {
            cout << "Error: Incorrect password." << endl;
            return false;
        }
    }
    else {
        cout << "Error: Could not open user file." << endl;
        return false;
    }
}
