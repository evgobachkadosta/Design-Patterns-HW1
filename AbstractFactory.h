//
// Created by user on 10.11.2025 г..
//

#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H
#include "figure_factory.h"
#include <fstream>
#include <iostream>



class AbstractFactory {
private:
    std::unique_ptr<std::ifstream> file_stream;

public:

    std::unique_ptr<figure_factory> create_factory(const std::string& input_type) {

        if (input_type == "Random") {
            return std::make_unique<RandomFigureFactory>();
        }

        else if (input_type == "STDIN") {
            return std::make_unique<StreamFigureFactory>(std::cin);
        }

        else if (input_type == "File") {
            std::string filename;
            std::cout << "Please enter the filename: ";

            std::cin >> filename;

            file_stream = std::make_unique<std::ifstream>(filename);

            if (!file_stream->is_open()) {
                throw std::runtime_error("Could not open file: " + filename);
            }

            return std::make_unique<StreamFigureFactory>(*file_stream);
        }

        else {
            throw std::invalid_argument("Unknown factory type: " + input_type);
        }
    }
};



#endif //ABSTRACTFACTORY_H
