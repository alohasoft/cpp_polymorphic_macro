#include <iostream>

class BaseClass {
  public:
    virtual ~BaseClass() = default;
};

class DerivedClassOne : public BaseClass {
};

class DerivedClassTwo : public BaseClass {
};

void f(const BaseClass& x) {
    std::cout << "f(BaseClass)" << std::endl;
}

void g(const BaseClass& x) {
    std::cout << "g(BaseClass)" << std::endl;
}

void g(const DerivedClassOne& x) {
    std::cout << "g(DerivedClassOne)" << std::endl;
}

void g(const DerivedClassTwo& x) {
    std::cout << "g(DerivedClassTwo)" << std::endl;
}

void p(const BaseClass& x) {
    if (const DerivedClassOne* d1 = dynamic_cast<const DerivedClassOne*>(&x)) {
        std::cout << "p(DerivedClassOne)" << std::endl;
    } else if (const DerivedClassTwo* d2 = dynamic_cast<const DerivedClassTwo*>(&x)) {
        std::cout << "p(DerivedClassTwo)" << std::endl;
    } else {
        std::cout << "p(BaseClass)" << std::endl;
    }
}

void SimpleCase() {
    BaseClass base;
    DerivedClassOne one;
    DerivedClassTwo two;

    std::cout << "f()" << std::endl;
    f(base);
    f(one);
    f(two);

    std::cout << "g()" << std::endl;
    g(base);
    g(one);
    g(two);

    std::cout << "p()" << std::endl;
    p(base);
    p(one);
    p(two);
}

int main() {
    SimpleCase();
}
