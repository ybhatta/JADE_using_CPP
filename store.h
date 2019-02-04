#pragma once
#include "product.h"
#include "customer.h"
#include "order.h"
#include <vector>
#include <map>

class Store {
  public:
    Store(std::string store_name);
    std::string name(); // Returns the store name
    double cash(); // Returns the cash in the register

    void add_product(Product* product); // Add a new product to stock
    int number_of_products(); // # of products defined
    Product* get_product(int product);  // Return pointer to selected product
    std::string product_to_string(int product); // string version of a product

    void add_customer(Customer* customer); // Add a new customer to the list
    int number_of_customers();  // # of customers on the list
    std::string customer_to_string(int customer); // string version of a customer

    void place_order(Order order, int customer); // Places a new order
    int number_of_orders(); // # of orders defined
    std::string order_to_string(int order_number); // string version of an order

    void pay_order(int order_number);  // Customer is paying for the order
    bool order_is_paid(int order_number);  // Customer has paid for the order
    void fill_order(int order_number);  // Server is filling the order
    bool order_is_filled(int order_number);  // Server has filled the order
    void discard_order(int order_number);  // Customer is discarding the order
    bool order_is_discarded(int order_number);  // Customer has discarded the order

    bool order_is_completed(int order_number); // Order is both paid and filled
    bool order_is_pending(int order_number); // Order is neither completed nor discarded

    friend std::ostream& operator<<(std::ostream& ost, Store& store); 
  private:
    std::string _name;
    double _cash_register;
    std::vector<Product*> _products;
    std::vector<Customer*> _customers;
    typedef std::pair<const Order, Customer> Order_pair;
    typedef std::map<const Order, Customer> Orders;
    Orders _orders;
    Order_pair& find_order_pair(int order_number); // Return a reference to the specified order pair
};
