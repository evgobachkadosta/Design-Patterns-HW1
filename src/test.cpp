#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <sstream>
#include <iostream>

#include "Figures.h"
#include "string_to_figure.h"
#include "figure_factory.h"


TEST_CASE("Circle Logic") {
    SECTION("Valid Construction and Perimeter") {
        circle c(10.0);
        REQUIRE_THAT(c.perimeter(), Catch::Matchers::WithinRel(62.83185, 0.0001));
        REQUIRE(c.to_string().find("Circle") != std::string::npos);
    }
    SECTION("Overflow") {
        REQUIRE_THROWS_AS(circle(std::numeric_limits<double>::infinity()), std::invalid_argument);
    }
    SECTION("Negative radius") {
        REQUIRE_THROWS_AS(circle(-1.0), std::invalid_argument);
        REQUIRE_THROWS_AS(circle(0.0), std::invalid_argument);
    }
}

TEST_CASE("Rectangle Logic") {
    SECTION("Valid Construction and Perimeter") {
        rectangle r(10.0, 20.0);
        REQUIRE_THAT(r.perimeter(), Catch::Matchers::WithinRel(60.0, 0.0001));
        REQUIRE(r.to_string().find("Rectangle") != std::string::npos);
    }

    SECTION("Invalid Construction") {
        REQUIRE_THROWS_AS(rectangle(-10, 20), std::invalid_argument);
        REQUIRE_THROWS_AS(rectangle(10, -20), std::invalid_argument);
        REQUIRE_THROWS_AS(rectangle(0, 20), std::invalid_argument);
    }
}

TEST_CASE("Triangle Logic") {
    SECTION("Valid Construction and Perimetr") {
        triangle t(3.0, 4.0, 5.0);
        REQUIRE_THAT(t.perimeter(), Catch::Matchers::WithinRel(12.0, 0.0001));
    }

    SECTION("Triangle Inequality") {
        REQUIRE_THROWS_AS(triangle(1, 2, 10), std::invalid_argument);
        REQUIRE_THROWS_AS(triangle(10, 1, 2), std::invalid_argument);
        REQUIRE_THROWS_AS(triangle(1, 10, 2), std::invalid_argument);
    }

    SECTION("Negative Sides") {
        REQUIRE_THROWS_AS(triangle(-3, 4, 5), std::invalid_argument);
    }
}


TEST_CASE("String Parsing Logic") {
    string_to_figure parser;

    SECTION("Valid Strings") {
        auto c = parser.create_from("Circle 5");
        REQUIRE(c != nullptr);
        REQUIRE_THAT(c->perimeter(), Catch::Matchers::WithinRel(31.4159, 0.001));

        auto r = parser.create_from("Rectangle 2 3");
        REQUIRE(r != nullptr);
        REQUIRE_THAT(r->perimeter(), Catch::Matchers::WithinRel(10.0, 0.001));
    }

    SECTION("Unknown Figures") {
        auto fig = parser.create_from("Hexagon 10");
        REQUIRE(fig == nullptr);
    }

    SECTION("Empty Strings") {
        auto fig = parser.create_from("");
        REQUIRE(fig == nullptr);
    }

    SECTION("Invalid Params") {
        REQUIRE_THROWS_AS(parser.create_from("Circle -5"), std::invalid_argument);
    }

    SECTION("Extra Junk") {
        auto fig = parser.create_from("Circle 5 klfnaewlf KFnqefl");
        REQUIRE(fig == nullptr);
    }
}


TEST_CASE("StreamFigureFactory Logic", "[Factory][Stream]") {
    auto file_content = std::make_unique<std::stringstream>();
    *file_content << "Circle 10\n"<< "Rectangle 5 5\n" << "Triangle 3 4 5";


    StreamFigureFactory factory(std::move(file_content));

    SECTION("Reads figures sequentially") {
        auto fig1 = factory.create();
        REQUIRE(fig1 != nullptr);
        REQUIRE_THAT(fig1->perimeter(), Catch::Matchers::WithinRel(62.8318, 0.001));

        auto fig2 = factory.create();
        REQUIRE(fig2 != nullptr);
        REQUIRE_THAT(fig2->perimeter(), Catch::Matchers::WithinRel(20.0, 0.001));

        auto fig3 = factory.create();
        REQUIRE(fig3 != nullptr);
        REQUIRE_THAT(fig3->perimeter(), Catch::Matchers::WithinRel(12.0, 0.001));
    }

    SECTION("Returns null at End of Stream") {
        factory.create();
        factory.create();
        factory.create();
        auto fig4 = factory.create();
        REQUIRE(fig4 == nullptr);
    }
}

