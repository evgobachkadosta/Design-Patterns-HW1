//
// Created by user on 10.11.2025 г..
//

#ifndef STRING_TO_FIGURE_H
#define STRING_TO_FIGURE_H
#include "Figures.h"
#include <sstream>


class string_to_figure {
public:
    std::unique_ptr<figure> create_from(std::string representation) {
        std::istringstream iss(representation);
        std::string type;
        double a, b, c;
        iss >> type;
        if (type == "Circle") {
            if (!(iss >> a)) return nullptr;
            std::string extra;
            if (iss >> extra) return nullptr;
            return std::make_unique<circle>(a);
        }else if (type == "Rectangle") {
            if (!(iss >> a >> b)) return nullptr;
            std::string extra;
            if (iss >> extra) return nullptr;
            return std::make_unique<rectangle>(a, b);
        } else if (type == "Triangle") {
            if (!(iss >> a >> b >> c)) return nullptr;
            std::string extra;
            if (iss >> extra) return nullptr;
            return std::make_unique<triangle>(a, b, c);
        }
        return nullptr;
    };
};



#endif //STRING_TO_FIGURE_H
