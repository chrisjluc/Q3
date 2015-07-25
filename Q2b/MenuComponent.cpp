#include <string>
#include "MenuComponent.h"

using namespace std;

MenuComponent::MenuComponent(std::string name) : name_(name), menuDepth_("") { }

void MenuComponent::menuDepthInc() {
    menuDepth_ = "\t" + menuDepth();
}


// operator<< simply calls mc->print(), and the different subclasses will override print() to specialize what is actually printed
ostream &operator<<(ostream &sout, const MenuComponent *mc) {
    mc->print(sout);
    return sout;
}

std::ostream &operator<<(ostream &sout, const MenuComponent &mc) {
    mc.print(sout);
    return sout;
}

bool operator==(const MenuComponent &a, const MenuComponent &b) {
    return a.name() == b.name() && a.menuDepth() == b.menuDepth();
}

bool operator!=(const MenuComponent &a, const MenuComponent &b) {
    return !(a == b);
}

MenuComponent::Iterator MenuComponent::begin() {
    return MenuComponent::Iterator(this);
}

MenuComponent::Iterator MenuComponent::end() {
    return MenuComponent::Iterator(NULL);
}

MenuComponent::Iterator::Iterator(MenuComponent *component) {
    istack = std::stack<IterNode *>();
    if (component != NULL) {
        istack.push(new IterNode(component, 0));
    }
}

MenuComponent::Iterator::IterNode::IterNode(MenuComponent *node) : node(node), cursor(-1) {

}

MenuComponent::Iterator::IterNode::IterNode(MenuComponent *node, int cursor) : node(node), cursor(cursor) {

}

bool operator==(const MenuComponent::Iterator &a, const MenuComponent::Iterator &b) {
    return (a.istack.size() == 0 && b.istack.size() == 0)
           || (a.istack.size() != 0 && b.istack.size() != 0
               && *(a.istack.top()->node) == *(b.istack.top()->node));
}

bool operator!=(const MenuComponent::Iterator &a, const MenuComponent::Iterator &b) {
    return !(a == b);
}

MenuComponent &MenuComponent::Iterator::operator*() {
    return *(istack.top()->node);
}

MenuComponent *MenuComponent::Iterator::operator->() {
    if(istack.size() == 0){
        return NULL;
    }
    return istack.top()->node;
}

bool MenuComponent::Iterator::hasNext() {
    while (!istack.empty()) {
        IterNode *top = istack.top();
        if (top->cursor < top->node->size()) {
            return true;
        }
        istack.pop();
        delete top;
    }
    return false;
}

MenuComponent::Iterator &MenuComponent::Iterator::operator++() {
    if (hasNext()) { // have cursors reached their limit?
        IterNode *top = istack.top();
        istack.pop();

        if (top->cursor == top->node->numChildren()) {
            return operator++();
        }

        // if cursor == -1, advance cursor and return node
        if (top->cursor == -1) {
            top->cursor += 1;
            istack.push(top); // advance cursor to first child
            return *this;
        }

        // else, advance cursor AND create new cursor for child
        MenuComponent *elem = top->node->getChild(top->cursor);
        top->cursor += 1;
        istack.push(top); // advance cursor to next child
        istack.push(new IterNode(elem)); // push new cursor
        return operator++(); // recurse
    }
    return *this;
}

MenuComponent::Iterator MenuComponent::Iterator::operator++(int i) {
    Iterator old(*this);
    ++*this;
    return old;
}