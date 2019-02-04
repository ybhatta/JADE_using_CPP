#include "store.h"
#include "to_string.h"
#include <sstream>
#include <stdexcept>

Store::Store(std::string store_name) : _name{store_name}, _cash_register{1000.0} { }
std::string Store::name() {return _name;}
double Store::cash() {return _cash_register;} // Returns the cash in the register

void Store::add_product(Product* product) {_products.push_back(product);}
int Store::number_of_products() {return _products.size();}
Product* Store::get_product(int product) {return _products[product];}
std::string Store::product_to_string(int product) {
    std::ostringstream oss;
    oss << _products[product]->to_string();
    return oss.str();
}

void Store::add_customer(Customer* customer) {_customers.push_back(customer);}
int Store::number_of_customers() {return _customers.size();}
std::string Store::customer_to_string(int customer) {
    std::ostringstream oss;
    oss << *_customers[customer];
    return oss.str();
}

Store::Order_pair& Store::find_order_pair(int order_number) {
    for (Order_pair& o : _orders) if (o.first.order_number() == order_number) return o;
    throw std::runtime_error{"Order " + std::to_string(order_number) + " not found"};
} // Return an order pair the specified order
void Store::place_order(Order order, int customer) {_orders[order] = *_customers[customer];} // Places a new order
int Store::number_of_orders() {return _orders.size(); } // # of orders defined
std::string Store::order_to_string(int order_number) {
    Order_pair& op = find_order_pair(order_number);
    return to_string(op.first) + "\n" + to_string(op.second);
} // string version of an order

void Store::pay_order(int order_number) {
    Order_pair& p = find_order_pair(order_number);
    Order o = p.first;
    Customer c = p.second;
    _orders.erase(p.first);
    o.pay();
    _orders[o] = p.second;
    _cash_register += o.profit();
}  // Customer is paying for the order
bool Store::order_is_paid(int order_number) {
    Order_pair& p = find_order_pair(order_number);
    return p.first.paid();
}  // Customer has paid for the order
void Store::fill_order(int order_number) {
    Order_pair& p = find_order_pair(order_number);
    Order o = p.first;
    Customer c = p.second;
    _orders.erase(p.first);
    o.fill();
    _orders[o] = p.second;
}  // Server is filling the order
bool Store::order_is_filled(int order_number) {
    Order_pair& p = find_order_pair(order_number);
    return p.first.filled();
}  // Server has filled the order
void Store::discard_order(int order_number) {
    Order_pair& p = find_order_pair(order_number);
    Order o = p.first;
    Customer c = p.second;
    if (o.paid()) _cash_register -= o.profit(); // refund
    _orders.erase(p.first);
    o.discard();
    _orders[o] = p.second;
} // Customer is discarding the order
bool Store::order_is_discarded(int order_number) {
    Order_pair& p = find_order_pair(order_number);
    return p.first.discarded();
} // Customer has discarded the order
bool Store::order_is_pending(int order_number) {
    Order_pair& p = find_order_pair(order_number);
    return p.first.pending();
} // Order is both filled and paid for
bool Store::order_is_completed(int order_number) {
    Order_pair& p = find_order_pair(order_number);
    return p.first.completed();
} // Order is both paid and filled

std::ostream& operator<<(std::ostream& ost, Store& store) {
    ost << "Store " << store._name << std::endl << std::endl;
    ost << "Products: " << std::endl;
    for (auto p : store._products) ost << "  " << p->to_string() << std::endl;
    return ost;
}
