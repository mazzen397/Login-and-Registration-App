#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <unordered_map>
#include <string>

using namespace std;

struct UserInfo {
    string password;
    string email;
};

class UserManager {
public:
    void registerUser();
    void registerPassword();
    void registerEmail();
    void FirstTimeUser();
    bool loginUser();

private:
    unordered_map<string, UserInfo> userDatabase;
};

#endif // USER_MANAGER_H
