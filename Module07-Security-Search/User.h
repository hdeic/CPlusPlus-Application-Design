#ifndef USER_H
#define USER_H

#include <string>
#include "Inventory.h"

class User {
protected:
    std::string username;
    void denyAccess(const std::string &action) const;

public:
    User(const std::string &name);
    virtual ~User() = default;

    std::string getUsername() const;
    virtual std::string getRole() const = 0;
    virtual bool canModifyRecords() const;

    void viewRecords(const Inventory &inventory) const;
    void searchRecord(const Inventory &inventory, int productId) const;

    virtual bool addRecord(Inventory &inventory, const Product &product);
    virtual bool deleteRecord(Inventory &inventory, int productId);
};

class Admin : public User {
public:
    Admin(const std::string &name);

    std::string getRole() const override;
    bool canModifyRecords() const override;

    bool addRecord(Inventory &inventory, const Product &product) override;
    bool deleteRecord(Inventory &inventory, int productId) override;
};

class RegularUser : public User {
public:
    RegularUser(const std::string &name);

    std::string getRole() const override;
};

#endif
