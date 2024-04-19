#include "UserManager.h"
#include <iostream>
#include <regex>
#include <cstdlib> 

using namespace std;

static string username = "Admin";
static string password = "Admin";
static string email = "Admin";
static bool newPassword = false;

void UserManager::registerUser() {
    int UsernameAttempts = 0;
    const int UsernameMin = 8;
    const int UsernameMax = 15;

    while (UsernameAttempts < 3)
    {
        cout << "Please enter your username: " << endl;
        cin >> username;

        if (username.length() < UsernameMin || username.length() > UsernameMax)
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
    if (UsernameAttempts == 3) 
    {
        cout << "You have exceeded the maximum number of attemots. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
}

void UserManager::registerPassword() {
    int PasswordAttempts = 0;
    const int PasswordLimit = 8;

    while (PasswordAttempts < 3) {
        if (newPassword)
        {
            cout << "Please enter your new password: ";
        }
        else
        {
            cout << "Please enter your password: ";
        }
        cin >> password;

        if (password.length() < PasswordLimit) {
            cout << "Password must be at least " << PasswordLimit << " characters long!" << endl;
            PasswordAttempts++;
            continue;
        }

        bool isDigit = false, isUppercase = false, isLowercase = false, isSpecialCharacter = false;

        for (char c : password) {
            if (isdigit(c)) {
                isDigit = true;
            }
            else if (ispunct(c)) {
                isSpecialCharacter = true;
            }
            else if (islower(c)) {
                isLowercase = true;
            }
            else if (isupper(c)) {
                isUppercase = true;
            }
        }

        if (!(isDigit && isSpecialCharacter && isLowercase && isUppercase)) {
            cout << "Weak Password!" << endl;
            PasswordAttempts++;
            continue;
        }

        // If the password meets the criteria, exit the loop
        break;
    }

    if (PasswordAttempts == 3) {
        cout << "You have exceeded the maximum number of attemots. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
}

void UserManager::forgetPassword()
{   
    int forgetPasswordAttempts = 0;
    while (forgetPasswordAttempts < 3)
    {
        cout << "Please enter your email address: " << endl;
        cin >> email;
        if (userDatabase.find(email) == userDatabase.end())
        {
            newPassword = true;
            registerPassword();
            break;
        }
        else
        {
            cout << "Email does not exist!" << endl;
            forgetPasswordAttempts++;
            continue;
        }
    }
}

void UserManager::registerEmail()
{
    int emailAttempts = 0;
    regex pattern(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\.com\b)");
    bool validEmail = false;

    while (emailAttempts < 3)
    {
        cout << "Please enter your email address: " << endl;
        cin >> email;

        if (regex_match(email, pattern))
        {
            break;
        }
        else
        {
            cout << "Invalid email address!" << endl;
            emailAttempts++;
            continue;
        }
    }
    if (emailAttempts == 3)
    {
        cout << "You have exceeded the maximum number of attemots. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
}

void UserManager::FirstTimeUser()
{
    UserInfo userInfo;

    if (userDatabase.find(username) == userDatabase.end() && userDatabase.find(email) == userDatabase.end()) 
    {
        userDatabase[username].password = password; 
        userDatabase[email].password = password;
        cout << "Registration successful!" << endl;
    }
    else
    {
        cout << "Username or email address already exists!" << endl;
    }
}

bool UserManager::loginUser() 
{
    string username = "Admin", password = "Admin", email= "Admin";

    cout << "Please enter your username or email address: " << endl;
    cin >> username;

    size_t atPos = username.find('@');
    if (atPos != string::npos)
    {
        email = username;
    }
    else
    {
        email = "Admin";
    }

    cout << "Please enter your password: " << endl;
    cin >> password;
    

    if (userDatabase.find(username) != userDatabase.end() || userDatabase.find(email) != userDatabase.end())
    {   
        /* 1. Username exists in the database
           2.Check for the Password          */ 

        if (userDatabase[username].password == password || userDatabase[email].password == password)
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
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Forget password" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            User.registerUser();
            User.registerPassword();
            User.registerEmail();
            User.FirstTimeUser();
            break;

        case '2':
            User.loginUser();
            break;

        case '3':
            User.forgetPassword();
            break;

        case '4':
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Invalid Choice" << endl;
            break;
        }
    } while (choice != '4');
 
    return 0;
}