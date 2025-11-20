//
// Created by user on 10.11.2025 г..
//

#ifndef FIGURE_FACTORY_H
#define FIGURE_FACTORY_H
#include "Figures.h"
#include "string_to_figure.h"


class figure_factory {
public:
    virtual std::unique_ptr<figure> create() = 0;
    virtual ~figure_factory() = default;
};

class RandomFigureFactory : public figure_factory {
public:
    std::unique_ptr<figure> create() override {
        int rand = std::rand();
        if (rand % 2 == 0) {
            int a = rand % 100 + 1;
            int b = rand % 1000 + 1;
            int c_min = std::abs(a - b) + 1;
            int c_max = a + b - 1;
            int c = rand % (c_max - c_min + 1) + c_min;
            return std::make_unique<triangle>(a, b, c);
        }else if (rand % 3 == 0) {
            int r = rand % 100 + 1;
            return std::make_unique<circle>(r);
        }else {
            int a = rand % 100 + 1;
            int b = rand % 1000 + 1;
            return std::make_unique<rectangle>(a, b);
        }
        return nullptr;
    }
};

class StreamFigureFactory : public figure_factory {
private:
    std::unique_ptr<std::istream> owned_stream;
    std::istream& input;
    string_to_figure converter;
public:
    StreamFigureFactory(std::istream& input) : input(input) {}
    StreamFigureFactory(std::unique_ptr<std::istream> is) :owned_stream(std::move(is)), input(*owned_stream) {}

    std::unique_ptr<figure> create() override {
        std::string representation;
        if (std::getline(input, representation)) {
            return converter.create_from(representation);
        }
        return nullptr;
    }
};


#endif //FIGURE_FACTORY_H
