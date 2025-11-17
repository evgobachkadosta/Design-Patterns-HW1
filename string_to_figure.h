//
// Created by user on 10.11.2025 г..
//

#ifndef STRING_TO_FIGURE_H
#define STRING_TO_FIGURE_H
#include "Figures.h"
#include <sstream>


class string_to_figure {
public:
    figure* create_from(std::string representation) {
        std::istringstream iss(representation);
        std::string type;
        double a, b, c;
        iss >> type;
        if (type == "Circle") {
            iss >> a;
            return new circle(a);
        } else if (type == "Rectangle") {
            iss >> a >> b;
            return new rectangle(a, b);
        } else if (type == "Triangle") {
            iss >> a >> b >> c;
            return new triangle(a, b, c);
        }
        return nullptr;
    };
};



#endif //STRING_TO_FIGURE_H
