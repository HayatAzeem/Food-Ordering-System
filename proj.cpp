#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <queue>
#include <memory>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <stack>
#include<windows.h>
#include<ctime>
#include <bits/stdc++.h>

using namespace std;
//ye banana hai ki nahi?
void LoadingBar();
int timeANDdate();
//done

//location function to place texts in the screen at specific co-orinates
//basically used for placing time and day at the top left of the screen

int location (int x, int y)
{
   COORD sach;
   sach.X=x;
   sach.Y=y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),sach);
}


// YE FUNCTION JO BHI VALUE USER SELECT KREGA USKO TRIM KR DEGA
string trim(const string& str) {
    int start = 0, end = str.length() - 1;

    // Find the first non-space character
    while (start <= end && str[start] == ' ') {
        start++;
    }

    // Find the last non-space character
    while (end >= start && str[end] == ' ') {
        end--;
    }

    // Return the trimmed substring
    return str.substr(start, end - start + 1);
}

// Helper function to convert string to lowercase
string toLowerCase(const std::string& str) {
    std::string lowerStr;
    for (char ch : str) {
        // Convert each character to lowercase if it's an uppercase letter
        lowerStr += (ch >= 'A' && ch <= 'Z') ? (ch + 'a' - 'A') : ch;
    }
    return lowerStr;
}



// Structure for MenuItem to hold individual item details
struct MenuItem {
    int sr;
    string name;
    int price;

    // Constructor with member assignment in the body
    MenuItem(int no, string n, int p) {
        sr=no;
        name = n;
        price = p;
    }
};


// Structure for TreeNode (for Meal types like Breakfast, Lunch, etc.)
struct TreeNode {
    string category;
    vector<MenuItem> items;
    vector<TreeNode*> subCategories;

    // Constructor with member assignment in the body
    TreeNode(string cat) {
        category = cat;
    }
};


struct Customer {
    string name;
    vector<string> orderHistory;

    // Default constructor
    Customer() {}

    // Parameterized constructor
    Customer(string n) {
        name = n;
    }
};


// Hash map for customer management
//used in generateBill function to map order to customer name
unordered_map<string, Customer> customers;

// Function to create sample menu tree for Breakfast, Lunch, and Dinner
TreeNode* createSampleMenuTree() {
    TreeNode* root = new TreeNode("Menu");

    // Indian restaurant menu
    TreeNode* indian = new TreeNode("Indian");

    TreeNode* indianBreakfast = new TreeNode("Breakfast");
    indianBreakfast->items.push_back(MenuItem(1, "Paratha", 50));
    indianBreakfast->items.push_back(MenuItem(2, "Poha", 40));
    indianBreakfast->items.push_back(MenuItem(3, "Idli", 30));
    indianBreakfast->items.push_back(MenuItem(4, "Dosa", 60));
    indianBreakfast->items.push_back(MenuItem(5, "Upma", 35));
    indian->subCategories.push_back(indianBreakfast);

    TreeNode* indianLunch = new TreeNode("Lunch");
    indianLunch->items.push_back(MenuItem(1, "Biryani", 150));
    indianLunch->items.push_back(MenuItem(2, "Paneer Butter Masala", 120));
    indianLunch->items.push_back(MenuItem(3, "Dal Makhani", 100));
    indianLunch->items.push_back(MenuItem(4, "Chole Bhature", 80));
    indianLunch->items.push_back(MenuItem(5, "Rajma Chawal", 90));
    indian->subCategories.push_back(indianLunch);

    TreeNode* indianDinner = new TreeNode("Dinner");
    indianDinner->items.push_back(MenuItem(1, "Dal Tadka", 80));
    indianDinner->items.push_back(MenuItem(2, "Roti", 10));
    indianDinner->items.push_back(MenuItem(3, "Butter Chicken", 150));
    indianDinner->items.push_back(MenuItem(4, "Palak Paneer", 120));
    indianDinner->items.push_back(MenuItem(5, "Aloo Gobi", 70));
    indian->subCategories.push_back(indianDinner);

    // Chinese restaurant menu
    TreeNode* chinese = new TreeNode("Chinese");
    TreeNode* chineseBreakfast = new TreeNode("Breakfast");
    chineseBreakfast->items.push_back(MenuItem(1, "Spring Rolls", 60));
    chineseBreakfast->items.push_back(MenuItem(2, "Dim Sum", 80));
    chineseBreakfast->items.push_back(MenuItem(3, "Baozi", 70));
    chineseBreakfast->items.push_back(MenuItem(4, "Congee", 50));
    chineseBreakfast->items.push_back(MenuItem(5, "Jianbing", 40));
    chinese->subCategories.push_back(chineseBreakfast);


    TreeNode* chineseLunch = new TreeNode("Lunch");
    chineseLunch->items.push_back(MenuItem(1, "Fried Rice", 130));
    chineseLunch->items.push_back(MenuItem(2, "Manchurian", 100));
    chineseLunch->items.push_back(MenuItem(3, "Kung Pao Chicken", 150));
    chineseLunch->items.push_back(MenuItem(4, "Sweet and Sour Pork", 140));
    chineseLunch->items.push_back(MenuItem(5, "Mapo Tofu", 120));
    chinese->subCategories.push_back(chineseLunch);

    TreeNode* chineseDinner = new TreeNode("Dinner");


    chineseDinner->items.push_back(MenuItem(1, "Noodles", 120));
    chineseDinner->items.push_back(MenuItem(2, "Sweet and Sour", 150));
    chineseDinner->items.push_back(MenuItem(3, "Peking Duck", 200));
    chineseDinner->items.push_back(MenuItem(4, "Hot Pot", 180));
    chineseDinner->items.push_back(MenuItem(5, "Szechuan Chicken", 160));
    chinese->subCategories.push_back(chineseDinner);

    // Italian restaurant menu
    TreeNode* italian = new TreeNode("Italian");

    TreeNode* italianBreakfast = new TreeNode("Breakfast");
    italianBreakfast->items.push_back(MenuItem(1, "Pizza", 200));
    italianBreakfast->items.push_back(MenuItem(2, "Frittata", 150));
    italianBreakfast->items.push_back(MenuItem(3, "Bruschetta", 100));
    italianBreakfast->items.push_back(MenuItem(4, "Panini", 120));
    italianBreakfast->items.push_back(MenuItem(5, "Cappuccino", 80));
    italian->subCategories.push_back(italianBreakfast);

    TreeNode* italianLunch = new TreeNode("Lunch");
    italianLunch->items.push_back(MenuItem(1, "Pasta", 180));
    italianLunch->items.push_back(MenuItem(2, "Lasagna", 250));
    italianLunch->items.push_back(MenuItem(3, "Risotto", 220));
    italianLunch->items.push_back(MenuItem(4, "Gnocchi", 200));
    italianLunch->items.push_back(MenuItem(5, "Minestrone", 150));
    italian->subCategories.push_back(italianLunch);

    TreeNode* italianDinner = new TreeNode("Dinner");
    italianDinner->items.push_back(MenuItem(1, "Risotto", 220));
    italianDinner->items.push_back(MenuItem(2, "Osso Buco", 300));
    italianDinner->items.push_back(MenuItem(3, "Tiramisu", 180));
    italianDinner->items.push_back(MenuItem(4, "Polenta", 160));
    italianDinner->items.push_back(MenuItem(5, "Branzino", 280));
    italian->subCategories.push_back(italianDinner);

    // Adding restaurant categories
    root->subCategories.push_back(indian);
    root->subCategories.push_back(chinese);
    root->subCategories.push_back(italian);

    return root;
}

// Order class for managing individual orders using linked list
class Order {
public:
    int orderId;
    string item;
    int quantity;
    int totalPrice;
    string restaurant;
    Order* next;

    // Constructor
    Order(int id, string i, int q, int t, string r) {
        orderId = id;
        item = i;
        quantity = q;
        totalPrice = t;
        restaurant = r;
        next = nullptr;
    }
};

struct AVLNode {
    int key;
    Order* order;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int k, Order* o) : key(k), order(o), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
    AVLNode* root;

    AVLTree() : root(nullptr) {}

    int height(AVLNode* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(AVLNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(AVLNode* node) {
        if (node) {
            node->height = 1 + max(height(node->left), height(node->right));
        }
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    AVLNode* insert(AVLNode* node, int key, Order* order) {
        if (!node) return new AVLNode(key, order);

        if (key < node->key) {
            node->left = insert(node->left, key, order);
        } else if (key > node->key) {
            node->right = insert(node->right, key, order);
        } else {
            return node;
        }

        updateHeight(node);

        int balance = balanceFactor(node);

        if (balance > 1 && key < node->left->key) {
            return rotateRight(node);
        }

        if (balance < -1 && key > node->right->key) {
            return rotateLeft(node);
        }

        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode* findMin(AVLNode* node) {
    while (node->left != nullptr) {
        node = node->left; // Traverse to the leftmost node
    }
    return node;
}

    AVLNode* deleteNode(AVLNode* root, int key) {
    if (!root) {
        return root; // Base case: If the tree is empty
    }

    // Step 1: Perform standard BST delete
    if (key < root->key) {
        root->left = deleteNode(root->left, key); // Key is in the left subtree
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key); // Key is in the right subtree
    } else {
        // Node to be deleted found
        if (!root->left || !root->right) {
            // Node has one child or no children
            AVLNode* temp = root->left ? root->left : root->right;
            delete root; // Free the current node
            return temp; // Return the non-null child or nullptr
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            AVLNode* temp = findMin(root->right);
            root->key = temp->key; // Copy the inorder successor's key
            root->order = temp->order; // Copy the order data
            root->right = deleteNode(root->right, temp->key); // Delete the inorder successor
        }
    }

    // Step 2: Update height of the current node
    updateHeight(root);

    // Step 3: Get the balance factor to check if the node became unbalanced
    int balance = balanceFactor(root);

    // Step 4: Handle the four cases of imbalance

    // Left Left Case
    if (balance > 1 && balanceFactor(root->left) >= 0) {
        return rotateRight(root);
    }

    // Left Right Case
    if (balance > 1 && balanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right Right Case
    if (balance < -1 && balanceFactor(root->right) <= 0) {
        return rotateLeft(root);
    }

    // Right Left Case
    if (balance < -1 && balanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

    AVLNode* searchNode(AVLNode* node, int key) {
    if (!node || node->key == key) {
        return node; // Return the node if it's found or if the tree is empty
    }

    if (key < node->key) {
        return searchNode(node->left, key); // Search in the left subtree
    }
    else{
    return searchNode(node->right, key); // Search in the right subtree
    }
    }

    void displayNode(AVLNode* node) {
    if (node) {
        cout << "Order ID: " << node->key 
             << ", Item: " << node->order->item 
             << ", Quantity: " << node->order->quantity 
             << ", Total Price: " << node->order->totalPrice 
             << ", Restaurant: " << node->order->restaurant << endl;
    } else {
        cout << "Node not found." << endl;
    }
}

    void insert(int key, Order* order) {
        root = insert(root, key, order);
    }

    void inOrder(AVLNode* node) {
        if (node) {
            inOrder(node->left);
            cout << "Order ID: " << node->key << ", Item: " << node->order->item << ", Quantity: " << node->order->quantity << ", Total Price: " << node->order->totalPrice << ", Restaurant: " << node->order->restaurant << endl;
            inOrder(node->right);
        }
    }

    void inOrder() {
        inOrder(root);
    }
};

AVLTree orderTree;


// Function to display menu based on selected restaurant and meal time
void displayMenu(TreeNode* node) {
    if (!node) return;
    cout << node->category << endl;
    for (const auto& item : node->items) {
        cout << item.sr<< ". " << item.name << " - " << item.price << endl;
    }
    for (TreeNode* subCat : node->subCategories) {
        displayMenu(subCat);
    }
}

// Function to take and process the order
void addOrder(Order*& head, int orderId, const string& itemName, int quantity, int price, string restaurant) {
    int total_price = quantity * price;
    auto newOrder = new Order(orderId, itemName, quantity, total_price, restaurant);
    newOrder->next = head;
    head = newOrder;
    orderTree.insert(orderId, newOrder);
}

// Function to display orders and calculate bill
void displayOrders(Order* head) {
    int grandTotal = 0;
    cout << "\n--- Your Orders ---\n";
    while (head != nullptr) {
        cout << head->quantity << " x " << head->item << " (Restaurant: " << head->restaurant << ") = Rs. " << head->totalPrice << "\n";
        grandTotal += head->totalPrice;
        head = head->next;
    }
    cout << "Total Bill: Rs. " << grandTotal << "\n";
}

// Function to generate final bill with payment method
void generateBill(Order* head, Customer& customer) {
    int grandTotal = 0;
    cout << "\n--- Final Bill ---\n";
    while (head != nullptr) {
        cout << head->quantity << " x " << head->item << " (Restaurant: " << head->restaurant << ") = Rs. " << head->totalPrice << "\n";
        grandTotal += head->totalPrice;
        head = head->next;
    }
    cout << "Total Bill with discount: Rs. " << grandTotal << "\n";
    L :
    cout << "\nChoose Payment Method [integer](1. Card / 2. Cash): ";
    int paymentChoice;
    cin >> paymentChoice;
    if (paymentChoice == 1) {
        cout << "Payment successful via card. Thank you for your purchase!\n";
    } else if(paymentChoice == 2){
        cout << "Payment successful via cash. Thank you for your purchase!\n";
    }else{
        cout << "Invalid choice. Please try again.\n";
        goto L;
    }
}

// Function to undo the last order
void undoLastOrder(Order*& head, stack<Order*>& orderStack)

 {
    if (orderStack.empty()) 
    {
        cout << "No orders to undo.\n";
        return;
    }

    Order* lastOrder = orderStack.top();
    orderStack.pop();

    if (head == lastOrder) 
    {
        head = head->next;
    } 
    else 
    {
        Order* temp = head;
        while (temp->next != lastOrder)
        {
            temp = temp->next;
        }
        temp->next = lastOrder->next;
    }
    delete lastOrder;
    cout << "Last order undone.\n";
}


// Function to display available restaurants for a given cuisine
void displayRestaurantNames(vector<string>& restaurants)
{
    for (int i = 0; i < restaurants.size(); ++i) 
    {
        cout << i + 1 << ". " << restaurants[i] << endl;
    }
}


//function to decorate the teminal window
void DecorateTopic()
{
    system("cls");//clears the screen after the loadout
    location(2,1);//location to place the time and day
    timeANDdate();//time and day
    cout << endl;
    cout << "\t\t\t  ########################################################################" << endl;
    cout << "\t\t\t  #                                                                      #" << endl;
    cout << "\t\t\t  #              WELCOME TO THE FOOD ORDERING SYSTEM                     #" << endl;
    cout << "\t\t\t  #                                                                      #" << endl;
    cout << "\t\t\t  ########################################################################" << endl;
    cout << endl;
    cout << "\t\t\t                 .-\"      \"-." << endl;
    cout << "\t\t\t                /   .    .    \\ " << endl;
    cout << "\t\t\t               |              |" << endl;
    cout << "\t\t\t                \\            /" << endl;
    cout << "\t\t\t                 '-..::::..-'" << endl;
    cout << "\t\t\t                  /  \\  /  \\ " << endl;
    cout << "\t\t\t                 |    ||    |" << endl;
    cout << "\t\t\t                 |    ||    |" << endl;
    cout << "\t\t\t                  \\__/  \\__/" << endl;
    cout << "\t\t\t                FOOD PLATTER" << endl;
    cout << endl;
    cout << "\t\t\t  ----------------------------------------------------------------------" << endl;
    cout << "\t\t\t  |  Choose from a wide variety of cuisines and place your order now!  |" << endl;
    cout << "\t\t\t  ----------------------------------------------------------------------" << endl;
    cout << endl;
}
//function to get the time and day
int timeANDdate()
{
    time_t t;
    t=time(NULL);
    cout<<asctime(localtime(&t));
}
//a simple loading bar function that prints char 219 as a loading bar
void LoadingBar()
{
    // system("color 46");
    location(2,1);
    timeANDdate();
    char des=219;
    system("cls");
    location(80,21);
    cout<<"loading...";
    for(int j=0;j<=100;j++)
    {
        location(115,22);
        cout<<j<<"%"<<endl;
        location(0,21);

        cout<<"\n\t\t\t\t\t\t\t\t\t\t";
        for(int i=1;i<=j;i++)
        {

            if(i%3==0)
            {
                cout<<des;
            }
        }
        cout<<endl;
        Sleep(1);//refresh the screen after every 0.001 second
    }
    Sleep(1000);//gap of 1 sec
}


int main() {
    string customerName;//customer name
    int firstuser=0;//to check if the user is entering first time or redoing an order
    LoadingBar();//loading bar callout
    a://callback here after undo last order and to take another order
    //callback loading page ke baad me hai taki vo loading animation baar baar na chale

    unordered_map<string, Order*> customerOrders; // Map to store orders for each customer
    unordered_map<string, int> customerOrderIds; // Map to store the next order ID for each customer

    DecorateTopic();//design callout

    
    //to check if user is entering first time
    if(firstuser==0){
    cout << "Enter your name: ";
    getline(cin, customerName);
    firstuser=1;//mark user as entered
    }
    cout << "Welcome, " << customerName << "!\n";

    
    if (customers.find(customerName) == customers.end()) {
        customers[customerName] = Customer(customerName);
        customerOrders[customerName] = nullptr;
        customerOrderIds[customerName] = 1;
    }

    // Create sample menu tree
    TreeNode* menuRoot = createSampleMenuTree();

    Order* orderList = customerOrders[customerName];
    stack<Order*> orderStack;

    // Restaurant lists for each cuisine
    vector<string> indianRestaurants = {"Tandoor Delight", "Spicy Indian Hub", "Curry Point"};
    vector<string> chineseRestaurants = {"Golden Dragon", "Szechuan Palace", "Mandarin Bistro"};
    vector<string> italianRestaurants = {"La Bella Italia", "Pasta Paradise", "Romeo's Pizzeria"};

    char choice;//user choice
    do 
    {

        n:
        cout << "\nChoose a Cuisine:\n1. Indian\n2. Chinese\n3. Italian\nEnter choice: \n";

        string cuisineChoice;//cusine choice
        cin >> cuisineChoice;
        //cin.ignore();


        string selectedCuisine;



        vector<string> selectedRestaurants;
        if (cuisineChoice == "1" || cuisineChoice == "indian") {//to handle both integer and string inputs
            selectedCuisine = "Indian";
            selectedRestaurants = indianRestaurants;
        } else if (cuisineChoice == "2"|| cuisineChoice == "chinese") {
            selectedCuisine = "Chinese";
            selectedRestaurants = chineseRestaurants;
        } else if (cuisineChoice == "3"|| cuisineChoice == "italian") {
            selectedCuisine = "Italian";
            selectedRestaurants = italianRestaurants;
        }else{
            cout << "Invalid choice. Please choose a valid cuisine.\n";
            goto n;
        }



        // Display the list of restaurants
        cout << "\nAvailable " << selectedCuisine << " Restaurants:\n";

        displayRestaurantNames(selectedRestaurants);//calling function to display restraunts of user's choice

        cout << "Enter your choice (1-" << selectedRestaurants.size() << "): ";

        int restaurantChoice;
        cin >> restaurantChoice;//inputing user's restraunt choice
        cin.ignore();



        if (restaurantChoice < 1 || restaurantChoice > selectedRestaurants.size())//validating user's choice
        {
            cout << "Invalid choice. Please try again.\n";
            continue;
        }

        string selectedRestaurant = selectedRestaurants[restaurantChoice - 1];
        cout << "\nWelcome to " << selectedRestaurant << "!\n";

        cout << "Choose Meal \n1. Breakfast \n2. Lunch \n3. Dinner\nEnter choice: \n";

        int mealChoice;
        cin >> mealChoice;//inputing user's meal choice
        cin.ignore();




        // Find selected restaurant and meal
        TreeNode* selectedRestaurantNode = nullptr;

        for (auto& restaurant : menuRoot->subCategories)
        {
            if (toLowerCase(restaurant->category) == toLowerCase(selectedCuisine)) //making case same
            {
                selectedRestaurantNode = restaurant;//assigning user's selected restraunt
                break;
            }
        }



        //meal choice
        TreeNode* selectedMealNode = nullptr;

        if (selectedRestaurantNode) 
        {
            for (auto& meal : selectedRestaurantNode->subCategories) 
            {
                if ((mealChoice == 1 && toLowerCase(meal->category) == "breakfast") ||
                    (mealChoice == 2 && toLowerCase(meal->category) == "lunch") ||
                    (mealChoice == 3 && toLowerCase(meal->category) == "dinner")) //checking choice
                {
                    selectedMealNode = meal;//assigning user's selected meal
                    break;
                }
            }
        }





        // Display menu and take orders
        if (selectedMealNode) 
        {
            displayMenu(selectedMealNode);//calling menu display function
        m:
            cout << "\nEnter item number to order: ";

            string itemName;
            getline(cin, itemName);//entering item name
            itemName = trim(itemName);//removing extra spaces




            bool itemFound = false;
            for (const auto& item : selectedMealNode->items)
            {
                if (toLowerCase(item.name) == toLowerCase(itemName)|| stoi(itemName) == item.sr) //checking if the user entered the name or the seriel no.
                {
                    itemFound = true;
                    itemName=item.name;
                    cout << "Enter quantity for " << itemName << ": ";//quantity
                    int quantity;
                    cin >> quantity;
                    cin.ignore();
                    addOrder(orderList, customerOrderIds[customerName], itemName, quantity, item.price, selectedRestaurant);
                    orderStack.push(orderList);//entering in stack
                    customers[customerName].orderHistory.push_back(itemName); // Add order to customer's order history
                    break;
                }
            }



            if (!itemFound) //if user enter wrong item
            {
                cout << "Item not found. Try again.\n";
                goto m;
            }
        }



        cout << "\nWould you like to order anything more? (Y/N): ";//asking user if they want to order something more
        cin >> choice;
        cin.ignore();
    } while (choice == 'Y' || choice == 'y');

    displayOrders(orderList);//if control comes here means user has made additions to his order and system shoukd display user's orders



    // Option to undo the last order
    cout << "\nWould you like to undo the last order? (Y/N): ";
    cin >> choice;
    cin.ignore();


    //if user chooses to undo last order the stack of order should get empty and user must be directed to home page to order again
    //otherwise if they continue with there order they should be presented with there bill and choice of payment


    if (choice == 'Y' || choice == 'y') 
    {
        undoLastOrder(orderList, orderStack);
        system("cls");
        goto a;
    }

    else{
    // Generate bill and complete payment

    generateBill(orderList, customers[customerName]);
    }

    //to start the whole process again and take another persons order without having to start the program again else ending the program with end credits
    cout << "\nWould you like to make another order? (Y/N): ";
    cin >> choice;
    cin.ignore();

    if (choice == 'Y' || choice == 'y') 
    {
        customerOrders[customerName] = orderList; // Save the current order list for the customer
        undoLastOrder(orderList, orderStack);
        system("cls");
        firstuser=0;//assign first user value as 0 so that the system recognises a new user and asks for there name 
        goto a;
    }
    else{
        char ch;
    cout<< "\nWould you like to view past orders? (y/n): ";
    cin >> ch;
    cin.ignore();
    
    if (ch == 'y' || ch == 'Y') {
        int od;
        cout<< "Enter order id to display: ";
        cin>>od;

        AVLNode* result = orderTree.searchNode(orderTree.root, od); // Search for the node in the AVL tree
        orderTree.displayNode(result); // Display the node

    }
    else{
    cout << "\nThank you for using our Food Ordering System!\n";


    //end credits----
    cout<<"PROGRAMMER....\n";
    cout<<"1. Mohd Hayat Azeem         23103382\n";
    cout<<"2. Anshuman Singh           23103399\n";
    cout<<"3. Sambhav Mishra           23103398\n";
    cout<<"4. Harshvardhan Tiwari      23103394\n";
    cout<<"...................THANK YOU...................\n";
    cout<<"Exiting in 5 second...........";
    Sleep(5000);//5 seconds timeout
    system("cls");//clear screen
    exit(0);//exit terminal
    return 0;//end
    }
    }
}