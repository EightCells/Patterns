#pragma once
#ifndef __ADAPTER_H__
#define __ADAPTER_H__
#include <iostream>
class Adaptee {
public:
    void specificRequest() {
        // do something
        std::cout << "Adaptee.\n\r";
    }
};

class Parent {
public:
    virtual void request() = 0;
protected:
    void specificRequest() {
        // do something else
        std::cout << "Parent.\n\r";
    }
};

class Adapter : private Adaptee, public Parent {
public:
    void request() {
        Adaptee::specificRequest();
    }
};

#endif // !__ADAPTER_H__


