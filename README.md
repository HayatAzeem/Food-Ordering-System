# 🍽️ Food Ordering System

A console-based **Food Ordering System** implemented in C++ that allows users to:
- Browse menus by cuisine and meal time
- Place orders from selected restaurants
- Track past orders using an AVL Tree
- Undo last orders
- Generate bills with payment methods

Made it to get better understanding of data sructures used in programming.
---

## 🚀 Features

- 🗂 **Menu Tree**: Organized by cuisine (Indian, Chinese, Italian) and meals (Breakfast, Lunch, Dinner)
- 🛒 **Order System**: Add multiple items, view order history, undo last order
- 🧾 **Billing**: Total calculation with payment method choice (Card/Cash)
- 📁 **Data Structures**:
  - AVL Tree for managing and retrieving past orders by Order ID
  - Stack for undo functionality
  - Linked List for order tracking
- 📅 **UI Enhancements**:
  - Real-time clock display
  - Loading screen animation
  - ASCII-based interface

---

## 🧠 Concepts Used

- Object-Oriented Programming (OOP)
- Trees (AVL Tree, Menu Tree)
- Linked Lists
- Stacks
- Hash Maps
- System-specific cursor handling (via `windows.h`)

---

## 💻 How to Run

### Requirements
- Windows OS (due to use of `windows.h` and `SetConsoleCursorPosition`)
- C++ compiler (e.g., g++ via MinGW)

### Compile and Run
```bash
g++ proj.cpp -o food_app
./food_app
```

> ⚠️ Make sure to compile on a Windows terminal or use Wine if running on Linux/Mac.

---

## 📝 Usage

1. **Enter your name**
2. **Choose a cuisine** (Indian/Chinese/Italian)
3. **Select a restaurant and meal type**
4. **Add items to your cart**
5. **View your bill and choose payment**
6. **Undo or redo orders if needed**
7. **View past orders by entering order ID**

---

## 📷 Preview

```
WELCOME TO THE FOOD ORDERING SYSTEM

1. Indian
2. Chinese
3. Italian

--> Select Cuisine
--> Select Meal
--> Place Order
--> View Bill
```

---

## 📌 Notes

- The system supports both numeric and text-based input (e.g., `1` or `indian`)
- `goto` is used for flow control (though not recommended in production code)
- All orders are stored in-memory; data is not persistent after closing the program
