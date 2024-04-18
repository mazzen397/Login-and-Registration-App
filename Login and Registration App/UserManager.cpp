#include "UserManager.h"
#include <iostream>

using namespace std;

void UserManager::registerUser() {
	string username = "Admin", password = "Admin";
    int UsernameAttempts = 0, PasswordAttempts = 0;
    
    while (UsernameAttempts < 3)
    {
        cout << "Please enter your username: " << endl;
        cin >> username;

        if (username.length() < 8 || username.length() > 15)
        {
            cout << "Please enter a valid username!" << endl;
            UsernameAttempts++;
            continue;
        }

        if (isdigit(username[0]) || ispunct(username[0]))
        {
            cout << "Username cannot start with a number or special character." << endl;
            UsernameAttempts++;
            continue;
        }

        bool validUsername = true;
        for (char c: username)
        {
            if (!isalpha(c))
            {
                validUsername = false;
                break;
            }
        }

        if (!validUsername)
        {
            cout << "Username must contain only alphabetic characters." << endl;
            UsernameAttempts++;
            continue;
        }
        break;
    }
    if (UsernameAttempts == 3) {
        cout << "You have exceeded the maximum number of attempts." << endl;
        return;
    }

    while (PasswordAttempts < 3)
    {
        cout << "Please enter your Password: " << endl;
        cin >> password;

        if (password.length() < 8 || password.length() > 15)
        {
            cout << "Please enter a valid password." << endl;
            PasswordAttempts++;
        }
        else
        {
            break;
        }
    }

    if (userDatabase.find(username) == userDatabase.end()) {
        userDatabase[username] = password;
        cout << "Registration successful!" << endl;
    }
    else {
        cout << "Username already exists!" << endl;
    }
}

bool UserManager::loginUser() 
{
    string username = "Admin", password = "Admin";

    cout << "Please enter your username: " << endl;
    cin >> username;
    cout << "Please enter your password: " << endl;
    cin >> password;

    if (userDatabase.find(username) != userDatabase.end())
    {   
        /* 1. Username exists in the database
           2.Check for the Password          */ 

        if (userDatabase[username] == password)
        {
            cout << "Login Successful" << endl;
            return true;
        }
        else
        {
            cout << "Invalid Password!" << endl;
            return false;
        }
    }
    /* 3. Username does not exist in the database */
    else
    {
        cout << "Invalid Username" << endl;
        return false;
    }
}

int main() {
    UserManager User;
    char choice;
    do {
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            User.registerUser();
            break;

        case '2':
            User.loginUser();
            break;

        case '3':
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Invalid Choice" << endl;
            break;
        }
    } while (choice != '3');
 
    return 0;
}