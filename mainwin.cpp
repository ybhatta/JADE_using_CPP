#include "mainwin.h"
#include "java.h"
#include "donut.h"
#include "customer.h"
#include <ostream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <regex>

Mainwin::Mainwin() : _store{Store{"JADE"}} {

    // /////////////////
    // G U I   S E T U P
    // /////////////////

    set_title("Java and Donut Express (JADE)");
    set_icon_from_file("window_logo.png");
    set_default_size(800, 600);

    // Put a vertical box container as the Window contents
    Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*vbox);

    // ///////
    // M E N U
    // Add a menu bar as the top item in the vertical box
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar());
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

    //     F I L E
    // Create a File menu and add to the menu bar
    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);

    //         Q U I T
    // Append Quit to the File menu
    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_quit_click));
    filemenu->append(*menuitem_quit);

    //     V I E W
    // Create a View menu and add to the menu bar
    Gtk::MenuItem *menuitem_view = Gtk::manage(new Gtk::MenuItem("_View", true));
    menubar->append(*menuitem_view);
    Gtk::Menu *viewmenu = Gtk::manage(new Gtk::Menu());
    menuitem_view->set_submenu(*viewmenu);

    //         A L L   O R D E R S
    // Append All Orders to the File menu
    Gtk::MenuItem *menuitem_all_orders = Gtk::manage(new Gtk::MenuItem("All _Orders", true));
    menuitem_all_orders->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_view_orders_click));
    viewmenu->append(*menuitem_all_orders);

    //         A L L   P R O D U C T S
    // Append All Products to the File menu
    Gtk::MenuItem *menuitem_all_products = Gtk::manage(new Gtk::MenuItem("All _Products", true));
    menuitem_all_products->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_view_products_click));
    viewmenu->append(*menuitem_all_products);

    //         L I S T   C U S T O M E R S
    // Append List Customers to the View menu
    Gtk::MenuItem *menuitem_list_customers = Gtk::manage(new Gtk::MenuItem("All _Customers", true));
    menuitem_list_customers->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_list_customers_click));
    viewmenu->append(*menuitem_list_customers);

    //     C R E A T E   
    // Create a Create menu and add to the menu bar
    Gtk::MenuItem *menuitem_create = Gtk::manage(new Gtk::MenuItem("_Create", true));
    menubar->append(*menuitem_create);
    Gtk::Menu *createmenu = Gtk::manage(new Gtk::Menu());
    menuitem_create->set_submenu(*createmenu);

    //           N E W   O R D E R
    // Append New Order to the Create menu
    menuitem_new_order = Gtk::manage(new Gtk::MenuItem("_Order", true));
    menuitem_new_order->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_create_order_click));
    createmenu->append(*menuitem_new_order);

    //           N E W   C O F F E E
    // Append New Coffee to the Create menu
    menuitem_new_coffee = Gtk::manage(new Gtk::MenuItem("_Coffee", true));
    menuitem_new_coffee->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_create_coffee_click));
    createmenu->append(*menuitem_new_coffee);

    //           N E W   D O N U T
    // Append New Donut to the Create menu
    menuitem_new_donut = Gtk::manage(new Gtk::MenuItem("_Donut", true));
    menuitem_new_donut->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_create_donut_click));
    createmenu->append(*menuitem_new_donut);

    //           N E W   C U S T O M E R
    // Append New Customer to the Create menu
    Gtk::MenuItem *menuitem_new_customer = Gtk::manage(new Gtk::MenuItem("_Customer", true));
    menuitem_new_customer->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_new_customer_click));
    createmenu->append(*menuitem_new_customer);

     //     P R O C E S S
    // Create a Process menu and add to the menu bar
    Gtk::MenuItem *menuitem_process = 
        Gtk::manage(new Gtk::MenuItem("_Process", true));
    menubar->append(*menuitem_process);
    Gtk::Menu *processmenu = Gtk::manage(new Gtk::Menu());
    menuitem_process->set_submenu(*processmenu);

    //           F I L L
    // Append Fill Order to the Process menu
    Gtk::MenuItem *menuitem_fill = Gtk::manage(new Gtk::MenuItem("_Fill Order", true));
    menuitem_fill->signal_activate().connect(
        sigc::mem_fun(*this, &Mainwin::on_fill_click));
    processmenu->append(*menuitem_fill);

    //           P A Y
    // Append Pay Order to the Process menu
    Gtk::MenuItem *menuitem_pay = Gtk::manage(new Gtk::MenuItem("_Pay for Order", true));
    menuitem_pay->signal_activate().connect(
        sigc::mem_fun(*this, &Mainwin::on_pay_click));
    processmenu->append(*menuitem_pay);

    //           D I S C A R D
    // Append Discard Order to the Process menu
    Gtk::MenuItem *menuitem_discard = Gtk::manage(new Gtk::MenuItem("_Discard Order", true));
    menuitem_discard->signal_activate().connect(
        sigc::mem_fun(*this, &Mainwin::on_discard_click));
    processmenu->append(*menuitem_discard);

    //     H E L P
    // Create a Help menu and add to the menu bar
    Gtk::MenuItem *menuitem_help = 
        Gtk::manage(new Gtk::MenuItem("_Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);

    //           A B O U T
    // Append About to the Help menu
    Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("About", true));
    menuitem_about->signal_activate().connect(
        sigc::mem_fun(*this, &Mainwin::on_about_click));
    helpmenu->append(*menuitem_about);

    //           T E S T
    // Append Test to the Help menu
    Gtk::MenuItem *menuitem_test = Gtk::manage(new Gtk::MenuItem("Test", true));
    menuitem_test->signal_activate().connect(
        sigc::mem_fun(*this, &Mainwin::on_test_click));
    helpmenu->append(*menuitem_test);

    // /////////////
    // T O O L B A R
    // Add a toolbar to the vertical box below the menu
    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar);
    vbox->add(*toolbar);

    // O R D E R S
    //
    //     V I E W   A L L   O R D E R S
    // View all orders currently defined
    Gtk::Image* view_orders_image = Gtk::manage(new Gtk::Image{"list_orders.png"});
    Gtk::ToolButton *view_orders_button = Gtk::manage(new Gtk::ToolButton{*view_orders_image});
    view_orders_button->set_tooltip_markup("View all orders");
    view_orders_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_view_orders_click));
    toolbar->append(*view_orders_button);

    //     C R E A T E   O R D E R
    // Create a new order
    Gtk::Image* create_order_image = Gtk::manage(new Gtk::Image{"create_order.png"});
    Gtk::ToolButton *create_order_button = Gtk::manage(new Gtk::ToolButton{*create_order_image});
    create_order_button->set_tooltip_markup("Create a new order");
    create_order_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_create_order_click));
    toolbar->append(*create_order_button);

    Gtk::SeparatorToolItem *sep0 = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*sep0);

    //     F I L L   O R D E R
    // Fill an order
    Gtk::Image* fill_order_image = Gtk::manage(new Gtk::Image{"fill_order.png"});
    Gtk::ToolButton *fill_order_button = Gtk::manage(new Gtk::ToolButton{*fill_order_image});
    fill_order_button->set_tooltip_markup("Fill an order");
    fill_order_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_fill_click));
    toolbar->append(*fill_order_button);

    //    P A Y   F O R   O R D E R
    // Pay for an order
    Gtk::Image* pay_order_image = Gtk::manage(new Gtk::Image{"pay_for_order.png"});
    Gtk::ToolButton *pay_order_button = Gtk::manage(new Gtk::ToolButton{*pay_order_image});
    pay_order_button->set_tooltip_markup("Pay for an order");
    pay_order_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_pay_click));
    toolbar->append(*pay_order_button);

    //     D I S C A R D   O R D E R
    // Discard an order
    Gtk::Image* discard_order_image = Gtk::manage(new Gtk::Image{"discard_order.png"});
    Gtk::ToolButton *discard_order_button = Gtk::manage(new Gtk::ToolButton{*discard_order_image});
    discard_order_button->set_tooltip_markup("discard a new order");
    discard_order_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_discard_click));
    toolbar->append(*discard_order_button);

    Gtk::SeparatorToolItem *sep1 = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*sep1);

    // P R O D U C T S
    //     V I E W   A L L   P R O D U C T S
    // View all products currently defined
    Gtk::Image* view_all_image = Gtk::manage(new Gtk::Image{"list_products.png"});
    Gtk::ToolButton *view_all_button = Gtk::manage(new Gtk::ToolButton{*view_all_image});
    view_all_button->set_tooltip_markup("View all products");
    view_all_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_view_products_click));
    toolbar->append(*view_all_button);

    //     N E W   J A V A
    // Create a new Java type
    Gtk::Image* new_java_image = Gtk::manage(new Gtk::Image{"new_java.png"});
    Gtk::ToolButton *new_java_button = Gtk::manage(new Gtk::ToolButton{*new_java_image});
    new_java_button->set_tooltip_markup("Create a new Java product");
    new_java_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_create_coffee_click));
    toolbar->append(*new_java_button);

    //     N E W   D O N U T
    // Create a new Donut type
    Gtk::Image* new_donut_image = Gtk::manage(new Gtk::Image{"new_donut.png"});
    Gtk::ToolButton *new_donut_button = Gtk::manage(new Gtk::ToolButton{*new_donut_image});
    new_donut_button->set_tooltip_markup("Create a new Donut product");
    new_donut_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_create_donut_click));
    toolbar->append(*new_donut_button);

    Gtk::SeparatorToolItem *sep2 = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*sep2);

    // C U S T O M E R S
    //
    //      L I S T   C U S T O M E R S
    // List customers icon
    Gtk::Image *list_customers_image = Gtk::manage(new Gtk::Image{"list_customers.png"});
    Gtk::ToolButton *list_customers_button = Gtk::manage(new Gtk::ToolButton(*list_customers_image));
    list_customers_button->set_tooltip_markup("List all customers");
    list_customers_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_list_customers_click));
    toolbar->append(*list_customers_button);

    //     N E W   C U S T O M E R
    // Add a new customer icon
    Gtk::Image *new_customer_image = Gtk::manage(new Gtk::Image{"new_customer.png"});
    Gtk::ToolButton *new_customer_button = Gtk::manage(new Gtk::ToolButton(*new_customer_image));
    new_customer_button->set_tooltip_markup("Create a new customer");
    new_customer_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_new_customer_click));
    toolbar->append(*new_customer_button);

    // M A I N   A R E A
    Gtk::Label* main_area = Gtk::manage(new Gtk::Label);
    main_area->set_use_markup(true);
    main_area->set_hexpand(true);    
    main_area->set_vexpand(true);
    vbox->add(*main_area);

    // S T A T U S   B A R   D I S P L A Y
    // Provide a status bar for program messages
    Gtk::Box *hbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0));

    msg = Gtk::manage(new Gtk::Label());
    msg->set_use_markup(true);
    msg->set_hexpand(true);
    hbox->add(*msg);

    cash = Gtk::manage(new Gtk::Label());
    hbox->add(*cash);

    vbox->add(*hbox);
    update_cash();

    // Make the box and everything in it visible
    vbox->show_all();
}

Mainwin::~Mainwin() { }

// /////////////////
// C A L L B A C K S
// /////////////////

// /////////
// File Menu

void Mainwin::on_quit_click() {         // Exit the program
    close();
}

// /////////
// View Menu

void Mainwin::on_view_orders_click() { // Select an order to view
    process_order(Action::Show);
}

void Mainwin::on_view_products_click() { // View all products
    set_message("");
    std::ostringstream oss;
    oss << _store << std::endl;
    Gtk::MessageDialog d{*this, "List of Products"}; 
    d.set_secondary_text(oss.str());
    int result = d.run();
}

// ///////////
// Create Menu

void Mainwin::on_new_customer_click() {
    Gtk::Dialog *dialog = new Gtk::Dialog("Create a Customer", *this);

    // Name
    Gtk::HBox b_name;

    Gtk::Label l_name{"Name:"};
    l_name.set_width_chars(15);
    b_name.pack_start(l_name, Gtk::PACK_SHRINK);

    Gtk::Entry e_name;
    e_name.set_max_length(50);
    b_name.pack_start(e_name, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_name, Gtk::PACK_SHRINK);

    // Phone Number
    Gtk::HBox b_phone;

    Gtk::Label l_phone{"Phone:"};
    l_phone.set_width_chars(15);
    b_phone.pack_start(l_phone, Gtk::PACK_SHRINK);

    Gtk::Entry e_phone;
    e_phone.set_max_length(50);
    b_phone.pack_start(e_phone, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_phone, Gtk::PACK_SHRINK);

    // Show dialog
    dialog->add_button("Cancel", 0);
    dialog->add_button("Create", 1);
    dialog->show_all();

    int result;
    std::string name, phone;
    std::regex re_phone{"[(]?(\\d{3,3}[-)])?\\d{3,3}-\\d{4,4}"};
    bool fail = true;  // set to true if any data is invalid

    while (fail) {
        fail = false;  // optimist!
        result = dialog->run();
        if (result != 1) {delete dialog; return;}
        name = e_name.get_text();
        if (name.size() == 0) {
            e_name.set_text("### Invalid ###");
            fail = true;
        }
        phone = e_phone.get_text();
        if(!std::regex_match(phone,re_phone)) {
            e_phone.set_text("### Invalid ###");
            fail = true;
        }        
    }
    Customer* customer = new Customer{name, phone};
    _store.add_customer(customer);
    set_message("Created customer " + name);

    delete dialog;
}

void Mainwin::on_list_customers_click() {
    set_message("");
    std::ostringstream oss;
    for (int i=0; i<_store.number_of_customers(); ++i) {
        oss <<  _store.customer_to_string(i) << std::endl;
    }
    Gtk::MessageDialog d{*this, "List of Customers"};
    d.set_secondary_text(oss.str());
    int result = d.run();
}

// /////////
// Process Menu
void Mainwin::on_fill_click() {
    process_order(Action::Fill);
} // Fill an order dialog

void Mainwin::on_pay_click() {
    process_order(Action::Pay);
} // Pay for an order dialog

void Mainwin::on_discard_click() {
    process_order(Action::Discard);
} // Discard an order dialog

// /////////
// Help Menu

void Mainwin::on_about_click() {
    Gtk::AboutDialog dialog{};
    dialog.set_transient_for(*this);
    dialog.set_program_name("Java and Donut Express");
    auto logo = Gdk::Pixbuf::create_from_file("logo.png");
    dialog.set_logo(logo);
    dialog.set_version("Version 0.2.0");
    dialog.set_copyright("Copyright 2018");
    dialog.set_license_type(Gtk::License::LICENSE_GPL_3_0);
    std::vector< Glib::ustring > authors = {"George F. Rice"};
    dialog.set_authors(authors);
    std::vector< Glib::ustring > artists = {
        "JADE Logo is licensed under the Creative Commons Attribution Share-Alike 3.0 License by SaxDeux https://commons.wikimedia.org/wiki/File:Logo_JADE.png", 
        "Flat Coffee Cup Icon is licensed under the Creative Commons Attribution 3.0 License by superawesomevectors http://fav.me/dbf6otc",
        "Donut Icon is public domain by Hazmat2 via Hyju https://en.wikipedia.org/wiki/File:Simpsons_Donut.svg",
        "Person Icon is licensed under the Creative Commons 0 (Public Domain) License by Clker-Free-Vector-Images https://pixabay.com/en/man-user-profile-person-icon-42934/"
    };
    dialog.set_artists(artists);
    dialog.run();
}

void Mainwin::on_test_click() {
    _store.add_customer(new Customer{"Athos", "555-1212"});
    _store.add_customer(new Customer{"Aramis", "817-555-1213"});
    _store.add_customer(new Customer{"Porthos", "(817)555-1214"});
    _store.add_customer(new Customer{"D'Artagnan", "214-555-1215"});
    _store.add_product(new Donut{"Plain Donut", 0.65, 0.35, Unfrosted, false, Unfilled});
    _store.add_product(new Donut{"Chocolate Glazed Donut", 0.75, 0.38, Chocolate_top, false, Unfilled});
    _store.add_product(new Donut{"Pink Sprinkle Donut", 0.75, 0.40, Pink_top, true, Unfilled});
    _store.add_product(new Donut{"Vanilla Creme Filled Eclare", 0.95, 0.50, Vanilla_top, false, Creme});
    _store.add_product(new Donut{"Strawberry Filled Donut", 0.75, 0.50, Unfrosted, false, Strawberry});
    _store.add_product(new Java{"Black Coffee", 2.50, .20, Medium});
    Java* java = new Java{"Mocha", 3.50, .30, Dark}; java->add_shot(Chocolate); 
    _store.add_product(java);
    java = new Java{"Caramel Machiatta", 3.50, .35, Blonde}; java->add_shot(Caramel);
    _store.add_product(java);
    for (int i=0; i<4; ++i) {
        Order order;
        order.add_product(_store.get_product(i));
        _store.place_order(order,i);
    }
    set_message("Created 4 customers, 5 donuts, 3 java, and 4 orders");
};

// /////////////////
// U T I L I T I E S
// /////////////////
void Mainwin::set_message(std::string message) { 
    msg->set_text(message);
} // Set the status bar message

void Mainwin::update_cash() { 
    std::ostringstream oss;
    oss << '$' << std::setprecision(2) << std::fixed << _store.cash();
    cash->set_text(oss.str());
}    // Set the status bar cash display

void Mainwin::process_order(Action action) {
    std::map<Action, std::string> action_title;
    std::map<Action, std::string> action_button;
    std::map<Action, std::string> action_message;
    action_title[Action::Show]    = "Show Order"; 
    action_title[Action::Fill]    = "Select an Order to Fill";
        action_button[Action::Fill]    = "Fill";
        action_message[Action::Fill]    = "Filled Order ";
    action_title[Action::Pay]     = "Select an Order to Pay";
        action_button[Action::Pay]     = "Pay";
        action_message[Action::Pay]    = "Paid Order ";
    action_title[Action::Discard] = "Select an Order to Discard";
        action_button[Action::Discard] = "Discard";
        action_message[Action::Discard]    = "Discarded Order ";

    set_message("");
    Gtk::Dialog *dialog = new Gtk::Dialog{action_title[action], *this};

    // Show selected order 
    Gtk::Label l_current;
    dialog->get_vbox()->pack_start(l_current, Gtk::PACK_SHRINK);

    // List orders
    Gtk::HBox b_orders;

    Gtk::Label l_orders{"Order:"};
    l_orders.set_width_chars(15);
    b_orders.pack_start(l_orders, Gtk::PACK_SHRINK);

    std::vector<int> combo_to_order;
    Gtk::ComboBoxText c_orders;
    for(int i=0; i<_store.number_of_orders(); ++i) {
        if ((action == Action::Show)                                                                ||
            (action == Action::Fill    && _store.order_is_pending(i) && !_store.order_is_filled(i)) ||
            (action == Action::Pay     && _store.order_is_pending(i) && !_store.order_is_paid(i))   ||
            (action == Action::Discard && _store.order_is_pending(i))) 
        {
            c_orders.append(std::to_string(i));
            combo_to_order.push_back(i);
        }
    }
    if (combo_to_order.empty()) {
        l_current.set_text("No Eligible Orders");
    } else {
        b_orders.pack_start(c_orders, Gtk::PACK_SHRINK);
        dialog->get_vbox()->pack_start(b_orders, Gtk::PACK_SHRINK);
    }

    // Show dialog
    dialog->add_button("Close", 0);
    if (!combo_to_order.empty()) {
        dialog->add_button("Show", 1);
        if (action != Action::Show) dialog->add_button(action_button[action], 2);
    }
    dialog->show_all();

    int result; // of the dialog (1 = OK, 2 = Action)

    while (true) {
        result = dialog->run();
        if (result == 0) {
            delete dialog; 
            return;
        } else if (result == 1) {
            l_current.set_text(_store.order_to_string(combo_to_order[c_orders.get_active_row_number()]));
        } else if (result == 2) {
            if (action == Action::Fill)    _store.fill_order   (combo_to_order[c_orders.get_active_row_number()]);
            if (action == Action::Pay)     _store.pay_order    (combo_to_order[c_orders.get_active_row_number()]);
            if (action == Action::Discard) _store.discard_order(combo_to_order[c_orders.get_active_row_number()]);
            set_message(action_message[action] + std::to_string(combo_to_order[c_orders.get_active_row_number()]));
            update_cash();
            delete dialog;
            return;
        } else {
            throw std::runtime_error{"Invalid dialog response"};
        }
    }
}
