//
// Created by user on 10.11.2025 г..
//

#ifndef FIGURE_FACTORY_H
#define FIGURE_FACTORY_H
#include "Figures.h"
#include "string_to_figure.h"


class figure_factory {
public:
    virtual figure* create() = 0;
    virtual ~figure_factory() = default;
};

class RandomFigureFactory : public figure_factory {
public:
    figure* create() override {
        std::srand(std::time(0));
        int rand = std::rand();
        if (rand % 2 == 0) {
            int a = rand % 100 + 1;
            int b = rand % 1000 + 1;
            int c_min = std::abs(a - b) + 1;
            int c_max = a + b - 1;
            int c = rand % (c_max - c_min + 1) + c_min;
            return new triangle(a, b, c);
        }else if (rand % 3 == 0) {
            int r = rand % 100 + 1;
            return new circle(r);
        }else {
            int a = rand % 100 + 1;
            int b = rand % 1000 + 1;
            return new rectangle(a, b);
        }
        return nullptr;
    }
};

class StreamFigureFactory : public figure_factory {
private:
    std::istream& input;
public:
    StreamFigureFactory(std::istream& input) : input(input) {}

    figure* create() override {
        string_to_figure converter;
        std::string representation;
        std::getline(input, representation);
        figure* figure = converter.create_from(representation);
        if (figure) {
            return figure;
        }
        return nullptr;
    }
};


#endif //FIGURE_FACTORY_H
