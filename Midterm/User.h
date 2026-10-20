#ifndef USER_H
#define USER_H

#include <string>

// ===========================================================================
// Class 3 of 3: User, with Admin and RegularUser derived from it
// ---------------------------------------------------------------------------
// Carries the role-based permissions. "username" is protected, so the derived
// classes can use it while code outside the family still cannot touch it.
//
// canModifyRecords() is virtual, so the menu can ask any User object what it
// is allowed to do and get the right answer for its real role.
// ===========================================================================
class User {
protected:
    std::string username;

public:
    User(const std::string &name);
    virtual ~User() = default;

    std::string getUsername() const;

    virtual std::string getRole() const = 0;        // each role names itself
    virtual bool canModifyRecords() const = 0;      // add, delete, update
};

// An Admin may change the inventory.
class Admin : public User {
public:
    Admin(const std::string &name);
    std::string getRole() const override;
    bool canModifyRecords() const override;
};

// A Regular User may only look at it.
class RegularUser : public User {
public:
    RegularUser(const std::string &name);
    std::string getRole() const override;
    bool canModifyRecords() const override;
};

#endif
