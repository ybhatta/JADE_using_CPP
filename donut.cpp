#include "donut.h"

Donut::Donut(std::string name, double price, double cost, Frosting frosting, bool sprinkles, Filling filling)
    : Product{name, price, cost}, _frosting{frosting}, _sprinkles{sprinkles}, _filling{filling} { }

std::string Donut::to_string() {
    std::string result = Product::to_string();
    std::string separator = " (";
    std::string terminator = "";
    if (_frosting != Unfrosted) {
        result += separator + "frosted with " + frosting_to_string[_frosting];
        if (_sprinkles) result += " and sprinkles";
        separator = ", ";
        terminator = ")";
    }
    if (_filling != Unfilled) {
        result += separator + "filled with " + filling_to_string[_filling];
        terminator = ")";
    }
    result += terminator;
    return result;
}
