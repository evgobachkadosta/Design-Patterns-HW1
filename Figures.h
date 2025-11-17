//
// Created by user on 10.11.2025 г..
//

#ifndef FIGURES_H
#define FIGURES_H
#include <stdexcept>
#include <cmath>
#include <limits>
#include <memory>

class string_convertible {
public:
    virtual std::string to_string() const = 0;
    virtual ~string_convertible() = default;
};


class figure : public string_convertible {
public:
    virtual double perimeter() const = 0;
    virtual ~figure() = default;
    virtual std::unique_ptr<figure> clone() const = 0;
};

class circle : public figure {
private:
    double radius;
public:
    circle(double radius) {
        if (radius <= 0) {
            throw std::invalid_argument("Perimeter must be positive");
        }
        if (std::isinf(2*radius*M_PI)) {
            throw std::invalid_argument("Radius is too big, integer overflow possible");
        }
        this-> radius = radius;

    }
    double perimeter() const override {
        return radius*M_PI*2;
    }
    std::string to_string() const override {
        std::string result = "Circle";
        result += " " + std::to_string(radius);
        return result;
    }
    std::unique_ptr<figure> clone() const override {
        return std::make_unique<circle>(*this);
    }
};

class rectangle : public figure {
private:
    double a;
    double b;
public:
    rectangle(double a, double b) {
        if (a <= 0 || b <= 0) {
            throw std::invalid_argument("Sides must be positive");
        }
        if ((std::isinf(2*(a+b)))) {
            throw std::invalid_argument("Side are too big, integer overflow possible");
        }
        this-> a = a;
        this-> b = b;

    }
    double perimeter() const override {
        return 2*(a + b);
    }
    std::string to_string() const override {
        std::string result = "Rectangle";
        result += " " + std::to_string(a);
        result += " " + std::to_string(b);
        return result;
    }
    std::unique_ptr<figure> clone() const override {
        return std::make_unique<rectangle>(*this);
    }
};

class triangle : public figure {
private:
    double a;
    double b;
    double c;
public:
    triangle(double a, double b, double c) {
        if (a <= 0 || b <= 0 || c <= 0) {
            throw std::invalid_argument("Sides must be positive");
        }
        if (a + b <= c || a + c <= b || b + c <= a) {
            throw std::invalid_argument("Invalid triangle sides");
        }
        if (std::isinf(a + b + c)) {
            throw std::invalid_argument("Sides are too big, integer overflow possible");
        }
        this-> a = a;
        this-> b = b;
        this-> c = c;
    }
    double perimeter() const override {
        return a + b + c;
    }
    std::string to_string() const override {
        std::string result = "Triangle";
        result += " " + std::to_string(a);
        result += " " + std::to_string(b);
        result += " " + std::to_string(c);
        return result;
    }
    std::unique_ptr<figure> clone() const override {
        return std::make_unique<triangle>(*this);
    }
};


#endif //FIGURES_H
