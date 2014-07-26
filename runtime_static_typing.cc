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

class HandlingClass {
  public:
    void operator()(const BaseClass& x) const {
        std::cout << "HandlingClass()(BaseClass)" << std::endl;
    }

    void operator()(const DerivedClassOne& x) const {
        std::cout << "HandlingClass()(DerivedClassOne)" << std::endl;
    }

    void operator()(const DerivedClassTwo& x) const {
        std::cout << "HandlingClass()(DerivedClassTwo)" << std::endl;
    }
};

void p(const BaseClass& x) {
    if (const DerivedClassOne* d1 = dynamic_cast<const DerivedClassOne*>(&x)) {
        std::cout << "p(DerivedClassOne)" << std::endl;
    } else if (const DerivedClassTwo* d2 = dynamic_cast<const DerivedClassTwo*>(&x)) {
        std::cout << "p(DerivedClassTwo)" << std::endl;
    } else {
        std::cout << "p(BaseClass)" << std::endl;
    }
}

void StaticCase() {
    std::cout << "StaticCase()" << std::endl;

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

    std::cout << "HandlingClass()" << std::endl;
    HandlingClass()(base);
    HandlingClass()(one);
    HandlingClass()(two);

    std::cout << "p()" << std::endl;
    p(base);
    p(one);
    p(two);

    std::cout << std::endl;
}

template<typename T_BASE, typename T_DERIVED, typename... T_TAIL> class RuntimeDispatcher {
  public:
    template<typename T, typename C> static void DispatchCall(const T& x, C c) {
        if (const T_DERIVED* d = dynamic_cast<const T_DERIVED*>(&x)) {
            c(*d);
        } else {
            RuntimeDispatcher<T_BASE, T_TAIL...>::DispatchCall(x, c);
        }
    }
};

template<typename T_BASE, typename T_DERIVED> class RuntimeDispatcher<T_BASE, T_DERIVED> {
  public:
    template<typename T, typename C> static void DispatchCall(const T& x, C c) {
        if (const T_DERIVED* d = dynamic_cast<const T_DERIVED*>(&x)) {
            c(*d);
        } else {
            c(x);
        }
    }
};

void RuntimeCase() {
    std::cout << "DynamicCase()" << std::endl;

    typedef class RuntimeDispatcher<BaseClass, DerivedClassOne, DerivedClassTwo> dispatcher;

    BaseClass base;
    DerivedClassOne one;
    DerivedClassTwo two;

    const BaseClass *pbase = &base;
    const BaseClass *pone = &one;
    const BaseClass *ptwo = &two;

    std::cout << "HandlingClass()()" << std::endl;
    HandlingClass instance;
    dispatcher::DispatchCall(*pbase, instance);
    dispatcher::DispatchCall(*pone, instance);
    dispatcher::DispatchCall(*ptwo, instance);
    
    std::cout << "HandlingClass()() with generic lambda" << std::endl;
    dispatcher::DispatchCall(*pbase, [instance](auto a) { instance(a); });
    dispatcher::DispatchCall(*pone, [instance](auto a) { instance(a); });
    dispatcher::DispatchCall(*ptwo, [instance](auto a) { instance(a); });

    std::cout << std::endl;
}

int main() {
    StaticCase();
    RuntimeCase();
}
