#include <string>
#include <iostream>
#include <algorithm>
#include <numeric>

#include "MenuItem.h"
#include "Menu.h"

using namespace std;


//************************************************************************
//  Helper variables and functions for test harness
//************************************************************************

// Exception classes for test harness
class SyntaxError {
};

class BadIndex {
};

class NoMenu {
public:
    NoMenu(int index) : index_(index) { }

    int index() const { return index_; }

private:
    int index_;
};

//  test harness commands
enum Op {
    NONE, MENU, ITEM, AddC, Remove, Print, DONE
};

struct Order {
    MenuComponent *component;
    int num;

    Order(MenuComponent *component) : component(component), num(1) { };
};

// parse input command
Op convertOp(string opStr) {
    switch (opStr[0]) {
        case 'm':
            return MENU;
        case 'i':
            return ITEM;
        case 'a':
            return AddC;
        case 'r':
            return Remove;
        case 'p':
            return Print;
        case 'd':
            return DONE;
        default:
            return NONE;
    }
}

// try to clean up the stream after fail() bit of istream is set
void sinCleanup(istream &sin) {
    cin.clear();
    string junk;
    getline(sin, junk);
}


// read an index form the istream (to determine menu that is to be operated on)
int readIndex(istream &sin) {
    int index = -1;
    sin >> index;
    if (index >= 0 && index <= 9) return index;

    // try to fix sin
    sinCleanup(sin);

    throw BadIndex();
}

// read a quoted string from the istream (to determine the name of a menu)
string readName(istream &sin) {
    char quotes;
    string name;

    sin >> quotes;
    getline(sin, name, '\"');

    if (sin.fail()) {
        sinCleanup(sin);
        throw SyntaxError();
    }

    return name;
}



//*******************
// main()
//*******************

int main() {
    cout << "Test harness for Menu Composite and Iterator" << endl << endl;

    // create a collection of menus to manipulate
    MenuComponent *menus[10] = {0};

    // enable reading of boolean values "true" and "false"
    cin >> boolalpha;

    // get input command
    cout << "Command: ";
    string command;
    cin >> command;

    Op op = convertOp(command);

    //**********************************
    // Populate the Composite Menu
    //**********************************
    while (!cin.eof() && (op != DONE)) {
        try {
            switch (op) {

                // new menu; delete old menu
                case MENU: {
                    int index = readIndex(cin);
                    string name = readName(cin);
                    delete menus[index];
                    menus[index] = new Menu(name);
                    break;
                }

                    // add a new menu item
                case ITEM: {
                    int index = readIndex(cin);
                    string name = readName(cin);

                    float price;
                    int calories;
                    bool veg;
                    cin >> price >> calories >> veg;
                    if (cin.fail()) {
                        sinCleanup(cin);
                        throw SyntaxError();
                    }

                    delete menus[index];
                    menus[index] = new MenuItem(name, price, calories, veg);
                    break;
                }

                    // add a menu/menuitem (index2) to be a child of a menu (index)
                case AddC: {
                    int index = readIndex(cin);
                    int index2 = readIndex(cin);
                    if (!menus[index]) throw NoMenu(index);
                    if (!menus[index2]) throw NoMenu(index2);
                    menus[index]->add(menus[index2]);
                    menus[index2] = NULL;
                    break;
                }

                    // print all elements of a menu
                case Print: {
                    int index = readIndex(cin);
                    if (!menus[index]) throw NoMenu(index);

                    for (auto it = menus[index]->begin(); it != menus[index]->end(); ++it) {
                        cout << *it << endl;
                    }

                    break;
                }

                    // remove a menuitem or submenu (name) from a menu (index)
                case Remove: {
                    int index = readIndex(cin);
                    if (!menus[index]) throw NoMenu(index);

                    string name = readName(cin);
                    menus[index]->remove(name);
                    break;
                }

                default: {
                    cout << "Invalid command." << endl;
                    break;
                }
            }// switch command
        } // try

        catch (NoMenu &e) {
            cout << "Menu Element " << e.index() << " does not exist." << endl;
        }
        catch (BadIndex &) {
            cout << "Invalid name of menu!" << endl;
        }
        catch (SyntaxError &) {
            cout << "Command has syntax errors. No change to menu." << endl;
        }
        catch (MenuComponent::InvalidOp &) {
            cout << "Command is invalid on Menu Items. No change to menus." << endl;
        }

        cout << endl << "Command: ";
        cin >> command;
        op = convertOp(command);


    } // while cin OK

    cout.precision(2);
    cout.setf(ios::fixed, ios::floatfield);

    MenuComponent *main = menus[0];
    vector<Order *> orders;
    command = "";
    string name;

    cout << "\nMay I take your order?\n> ";
    if (main == NULL) {
        cout << "\nMenu Element 0 does not exist." << endl;
    } else {
        while (true) {
            cin >> command;
            if (command == "t") {
                break;
            } else if (command == "o") {
                name = readName(cin);

                // Find the menu item matching the name
                auto it = std::find_if(main->begin(), main->end(), [name](const MenuComponent& m) {
                    return m.name() == name && m.isLeaf();
                });

                // Check our vector of orders for the menu item, and if it exists increment the number of the order
                // Else create a new order and add it to our orders vector
                if (it != main->end()) {
                    auto it_order = std::find_if(orders.begin(), orders.end(),
                                                 [name](Order *o) { return o->component->name() == name; });
                    if (it_order != orders.end()) {
                        (*it_order)->num++;
                    } else {
                        orders.push_back(new Order(it.operator->()));
                    }
                }
            } else {
                cout << "Invalid order." << endl;
            }
            cout << "> ";
        }

        // Print out all the orders
        std::for_each(orders.begin(), orders.end(), [](Order *order) {
            cout << "(" << order->num << ") " << order->component->name()
            << ", $" << order->component->price() << " = $"
            << order->component->price() * order->num << endl;
        });

        // Sum up the orders and print a total
        float init = 0;
        float total = std::accumulate(orders.begin(), orders.end(), init, [](float total, Order *order) {
            return total + order->component->price() * order->num;
        });

        // Remove allocated memory
        cout << "TOTAL = $" << total << endl;
        for (auto it = orders.begin(); it != orders.end(); ++it) {
            delete *it;
        }
    }


    for (int i = 0; i < 10; i++) {
        if (menus[i])
            delete menus[i];
    }
}