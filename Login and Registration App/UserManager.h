#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <unordered_map>
#include <string>

class UserManager {
public:
    void registerUser();
    bool loginUser();

private:
    std::unordered_map<std::string, std::string> userDatabase;
};

#endif // USER_MANAGER_H
