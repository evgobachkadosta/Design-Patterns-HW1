#include <iostream>
#include <ctime>
#include <vector>

#include "AbstractFactory.h"

int main() {
    std::srand(std::time(0));
    std::cout << "Enter your preferred method of creating figures [Random/STDIN/File] :" << "\n";
    AbstractFactory af = AbstractFactory();
    std::string input_type;
    std::cin >> input_type;

    if (input_type == "Random") {
        std::unique_ptr<figure_factory> ff = af.create_factory(input_type);
        std::cout << "Choose the number of random figures created: " << "\n";
        int n;
        std::cin >> n;
        std::vector<std::unique_ptr<figure>> figures;
        for (int i = 0; i < n; ++i) {
            figures.push_back(ff->create());
        }
        std::cout << "Choose where to print the figures [STDOUT/File] :" << "\n";
        std::string output_type;
        std::cin >> output_type;
        if (output_type == "STDOUT") {
            for (int i = 0; i < figures.size(); ++i) {
                std::cout << figures[i]->to_string() << "\n";
            }
        }
        if (output_type == "File") {
            std::ofstream file("output.txt");
            for (int i = 0; i < figures.size(); ++i) {
                file << figures[i]->to_string() << "\n";
            }
        }
    }

    if (input_type == "STDIN") {
        std::unique_ptr<figure_factory> ff = af.create_factory(input_type);
        std::cout << "Enter the amount of figures you want: " << "\n";
        int n;
        std::cin >> n;
        std::cin.ignore();
        std::vector<std::unique_ptr<figure>> figures;
        for (int i = 0; i < n; ++i) {
            try {
                std::unique_ptr<figure> fig = ff->create();

                if (fig) {
                    figures.push_back(std::move(fig));
                } else {
                    std::cerr << "Error: Invalid input format or empty line. Skipping." << std::endl;
                    i--;
                }
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Error creating figure: " << e.what() << ". Skipping." << std::endl;
            }

        }
        std::cout << "Choose where to print the figures [STDOUT/File] :" << "\n";
        std::string output_type;
        std::cin >> output_type;
        if (output_type == "STDOUT") {
            for (int i = 0; i < figures.size(); ++i) {
                std::cout << figures[i]->to_string() << "\n";
            }
        }
        if (output_type == "File") {
            std::ofstream file("output.txt");
            for (int i = 0; i < figures.size(); ++i) {
                file << figures[i]->to_string() << "\n";
            }
        }
    }

    if (input_type == "File") {
        std::unique_ptr<figure_factory> ff = af.create_factory(input_type);
        std::vector<std::unique_ptr<figure>> figures;
        std::unique_ptr<figure> figure;
        while ((figure = ff->create()) != nullptr) {
            figures.push_back(std::move(figure));
        }
        std::cout << "Choose where to print the figures [STDOUT/File] :" << "\n";
        std::string output_type;
        std::cin >> output_type;
        if (output_type == "STDOUT") {
            for (int i = 0; i < figures.size(); ++i) {
                std::cout << figures[i]->to_string() << "\n";
            }
        }
        if (output_type == "File") {
            std::ofstream file("output.txt");
            for (int i = 0; i < figures.size(); ++i) {
                file << figures[i]->to_string() << "\n";
            }
        }

    }


    return 0;
}