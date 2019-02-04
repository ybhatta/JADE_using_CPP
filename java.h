#pragma once
#include "product.h"
#include <vector>
#include <ostream>

enum Darkness {Blonde, Light, Medium, Dark, Extra_dark};
const std::vector<std::string> darkness_to_string =
        {"Blonde", "Light", "Medium", "Dark", "Extra Dark"};

enum Shot {None, Chocolate, Vanilla, Peppermint, Hazelnut, Caramel};
const std::vector<std::string> shot_to_string =
    {"None", "Chocolate", "Vanilla", "Peppermint", "Hazelnut", "Caramel"};

class Java : public Product {
  public:
    Java(std::string name, double price, double cost, Darkness darkness);
    void add_shot(Shot shot);
    std::string to_string() override;
  protected:
    Darkness _darkness;
    std::vector<Shot> _shots;
};
    
