#include "java.h"

Java::Java(std::string name, double price, double cost, Darkness darkness)
    : Product{name, price, cost}, _darkness{darkness} { }

void Java::add_shot(Shot shot) {_shots.push_back(shot);}

std::string Java::to_string() {
    std::string result =  Product::to_string() + " (" + darkness_to_string[_darkness]
        + ")";
    std::string separator = " with ";
    for (auto s : _shots) {result += separator + shot_to_string[s]; separator = ", ";}
    return result;
}
