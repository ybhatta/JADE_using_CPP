#pragma once
#include "product.h"
#include <vector>
#include <ostream>

enum Frosting {Unfrosted, Chocolate_top, Vanilla_top, Pink_top};
const std::vector<std::string> frosting_to_string =
    {"Unfrosted", "Chocolate", "Vanilla", "Pink"};

enum Filling {Unfilled, Creme, Bavarian, Strawberry};
const std::vector<std::string> filling_to_string =
    {"Unfilled", "Creme", "Bavarian", "Strawberry"};

class Donut : public Product {
  public:
    Donut(std::string name, double price, double cost, Frosting frosting, bool sprinkles, Filling filling);
    std::string to_string() override;
  protected:
    Frosting _frosting;
    bool _sprinkles;
    Filling _filling;
};
