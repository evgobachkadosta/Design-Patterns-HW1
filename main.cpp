#include <iostream>
#include <ctime>
#include "AbstractFactory.h"

int main() {
    std::srand(std::time(0));
    AbstractFactory af = AbstractFactory();
    std::unique_ptr<figure_factory> ff = af.create_factory("File");
    for (int i = 0; i < 3; i++) {
        std::unique_ptr<figure> fig = ff->create();
        std::cout << fig->to_string() << std::endl;
    }


    return 0;
}