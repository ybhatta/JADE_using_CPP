#ifndef MAINWIN_H
#define MAINWIN_H

#include <gtkmm.h>
#include "store.h"

class Mainwin : public Gtk::Window
{
    public:
        Mainwin();
        virtual ~Mainwin();
    protected:
        void on_quit_click();            // Exit the program
        void on_view_orders_click();     // Select an order to view
        void on_view_products_click();   // View all products
        void on_create_order_click();    // Create a new order
        void on_create_coffee_click();   // Create a new coffee product
        void on_create_donut_click();    // Create a new donut product
        void on_list_customers_click();  // List all customers
        void on_new_customer_click();    // Create a new customer
        void on_fill_click();            // Fill an order dialog
        void on_pay_click();             // Pay for an order dialog
        void on_discard_click();         // Discard an order dialog
        void on_about_click();           // About dialog
        void on_test_click();            // Easter egg (test data)
    private:
        Store _store;
        Gtk::Label *msg;                        // Status message display
        void set_message(std::string message);  // Set the status bar message
        Gtk::Label *cash;                       // Cash register display
        void update_cash();                     // Update status bar cash display
        Gtk::MenuItem *menuitem_new_order;      // Create -> Order
        Gtk::MenuItem *menuitem_new_coffee;     // Create -> Coffee
        Gtk::MenuItem *menuitem_new_donut;      // Create -> Donut

        enum class Action {Show, Fill, Pay, Discard};
        void process_order(Action action);      // Process an order
};
#endif 

