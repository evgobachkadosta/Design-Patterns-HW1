//
// Created by user on 20.11.2025 г..
//
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Figures.h"
#include "string_to_figure.h"

// Test 1: Logic Validation (The Rust programmer in you will like TDD here)
TEST_CASE("Figures calculate perimeter correctly") {
    SECTION("Circle Perimeter") {
        circle c(10.0);
        // Use Margin for floating point comparisons
        REQUIRE_THAT(c.perimeter(), Catch::Matchers::WithinRel(62.83185, 0.001));
    }

    SECTION("Rectangle Perimeter") {
        rectangle r(10, 20);
        REQUIRE(r.perimeter() == 60.0);
    }

    SECTION("Triangle Perimeter") {
        triangle t(3, 4, 5);
        REQUIRE(t.perimeter() == 12.0);
    }
}

// Test 2: Exception Safety (Verifying your validation logic)
TEST_CASE("Invalid figures throw exceptions", "[validation]") {
    SECTION("Negative Circle Radius") {
        REQUIRE_THROWS_AS(circle(-5), std::invalid_argument);
    }

    SECTION("Impossible Triangle (Triangle Inequality)") {
        // 1 + 2 is not > 10
        REQUIRE_THROWS_AS(triangle(1, 2, 10), std::invalid_argument);
    }
}

// Test 3: Factory/Parsing Logic
TEST_CASE("String conversion factory works", "[factory]") {
    string_to_figure factory;

    SECTION("Valid Input") {
        auto fig = factory.create_from("Circle 5");
        REQUIRE(fig != nullptr);
        REQUIRE_THAT(fig->perimeter(), Catch::Matchers::WithinRel(31.4159, 0.001));
    }

    SECTION("Invalid Name Returns Nullptr") {
        auto fig = factory.create_from("Hexagon 10");
        REQUIRE(fig == nullptr);
    }

    SECTION("Case Sensitivity Check (Based on your current code)") {
        // This highlights the bug I mentioned earlier if you haven't fixed it yet
        auto fig = factory.create_from("circle 5");
        // If your code is strict "Circle", this returns null.
        // If you fixed it to be case-insensitive, this should be valid.
        // For now, assuming strict:
        CHECK(fig == nullptr);
    }
}