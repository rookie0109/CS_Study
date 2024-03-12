#include <iostream>
#include <string>

// 基类 Animal
class Animal {
protected:
    std::string name;
    int age;

public:
    Animal(const std::string& _name, int _age) : name(_name), age(_age) {}

    virtual void speak() const {
        std::cout << "An animal speaks." << std::endl;
    }
    void test() const {
      this->speak();
    }
};

// 派生类 Dog
class Mammal : public Animal {
public:
    Mammal(const std::string& _name, int _age) : Animal(_name, _age) {}

};

// 派生类 Cat
class Cat : public Mammal {
public:
    Cat(const std::string& _name, int _age) : Mammal(_name, _age) {}

    void speak() const {
        std::cout << "Cat " << name << " meows." << std::endl;
    }
};

int main() {
    Mammal* a2 = new Cat("Whiskers", 5);
    // Animal* a1 = new Cat("Whiskers", 5);

    a2->test();  // 调用 Cat 的 speak 函数

    delete a2;

    return 0;
}
