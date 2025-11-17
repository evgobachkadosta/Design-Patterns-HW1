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
    // This smart pointer will *own* the file stream, if one is created.
    // This is crucial because StreamFigureFactory only holds a *reference*
    // to a stream, so the stream must not be destroyed while the factory is in use.
    std::unique_ptr<std::ifstream> file_stream;

public:
    // This function matches the description in Step 6
    // It returns a unique_ptr as specified in Step 8 [cite: 1049]
    std::unique_ptr<figure_factory> create_factory(const std::string& input_type) {

        if (input_type == "Random") {
            // User wants random figures [cite: 882]
            return std::make_unique<RandomFigureFactory>();
        }

        else if (input_type == "STDIN") {
            // User wants figures from standard input [cite: 883]
            // We pass std::cin, which is a global istream
            return std::make_unique<StreamFigureFactory>(std::cin);
        }

        else if (input_type == "File") {
            // User wants figures from a file [cite: 884]
            std::string filename;
            std::cout << "Please enter the filename: ";

            // Read filename from user
            // Note: This assumes the app (Step 7) runs in a console.
            std::cin >> filename;

            // Create the file stream and store it in our smart pointer
            file_stream = std::make_unique<std::ifstream>(filename);

            if (!file_stream->is_open()) {
                throw std::runtime_error("Could not open file: " + filename);
            }

            // Pass the reference to the opened stream to the factory
            return std::make_unique<StreamFigureFactory>(*file_stream);
        }

        else {
            throw std::invalid_argument("Unknown factory type: " + input_type);
        }
    }
};



#endif //ABSTRACTFACTORY_H
