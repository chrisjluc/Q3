#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <iostream>
#include <string>

#include "MenuComponent.h"

class MenuItem : public MenuComponent {
public:
    class MenuItemIterator : MenuComponent::Iterator {

    };

    // constructor
    MenuItem(const std::string, float, int, bool);

    // implement leaf operations
    virtual bool isVeggie() const;

    virtual float price() const;

    virtual void priceIs(float p);

    virtual int calories() const;

    virtual void caloriesIs(int c);

    virtual MenuComponent::Iterator begin();

    virtual MenuComponent::Iterator end();

protected:
    virtual void print(std::ostream &) const;

private:
    float price_;
    int calories_;
    bool isVeggie_;
};


#endif