#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
using namespace std;
enum Category {
	electronics, clothingItem, schoolSupplies
};

struct Product {
	string name;
	double price;
	Category category;
	int quantity;
	Product() {};

	Product(string name, double price, Category c, int quantity)
	{
		this->name = name;
		this->price = price;
		this->category = c;
		this->quantity = quantity;
	}

	bool operator<(const Product& other) const
	{
		return price < other.price; // Max heap based on price
	}


};

struct cartItem {
public:
	Product product;
	int quantity;

	cartItem(Product p, int qty)
	{

		this->product = p;
		this->quantity = qty;
	}
	// Max heap comparison based on total price operator overloading
	bool operator<(const cartItem& other) const
	{
		return product.price * quantity < other.product.price * other.quantity;
	}

	bool operator>(const cartItem& other) const
	{
		return other < *this;
	}
};






class maxHeap
{
private:
	vector<cartItem> heap;

	int leftChild(int index)
	{
		return 2 * index + 1; // 2*index +1
	}

	int rightChild(int index)
	{
		return 2 * index + 2; // 2*index +2
	}

	int parent(int index)
	{
		return (index - 1) / 2; // (index -1) /2
	}

	void swap(int index1, int index2)
	{
		cartItem temp = heap[index1];
		heap[index1] = heap[index2];
		heap[index2] = temp;
	}


public:
	void printHeap()
	{
		cout << endl;
		for (size_t i = 0; i < heap.size(); i++)
		{
			cout << "Product: " << heap[i].product.name << ", Quantity: " << heap[i].quantity
				<< ", Total Price: " << heap[i].product.price * heap[i].quantity << endl;
		}
		cout << endl;

	}

	void clear() {
		heap.clear();
	}



	bool isEmpty() {
		return heap.empty();
	}



	void insert(cartItem item)
	{
		heap.push_back(item);
		size_t current = heap.size() - 1;

		while (current > 0 && heap[current] > heap[parent(current)])
		{
			swap(current, parent(current));
			current = parent(current);
		}
	}


	cartItem peekMax() const
	{
		if (heap.empty())
		{
			throw out_of_range("Heap is empty");
		}

		return heap[0];
	}


	void sinkDown(int index)
	{
		int maxIndex = index;

		while (true)
		{
			int leftIndex = leftChild(index);
			int rightIndex = rightChild(index);

			if (leftIndex < heap.size() && heap[leftIndex] > heap[maxIndex])
			{
				maxIndex = leftIndex;
			}

			if (rightIndex < heap.size() && heap[rightIndex] > heap[maxIndex])
			{
				maxIndex = rightIndex;
			}

			if (maxIndex != index)
			{
				swap(index, maxIndex);
				index = maxIndex;
			}
			else
			{
				return;
			}

		}
	}



	cartItem removeMax()
	{
		if (heap.empty())
		{
			throw out_of_range("cart is already empty");
		}

		cartItem maxValue = heap.front();
		if (heap.size() == 1)
		{
			heap.pop_back();
		}
		else
		{
			heap[0] = heap.back();
			heap.pop_back();
			sinkDown(0);
		}
		return maxValue;
	}

	void deleteItem(const string& productName) {
		// Find the item in the heap
		int indexToRemove = -1;
		for (int i = 0; i < heap.size(); i++) {
			if (heap[i].product.name == productName) {
				indexToRemove = i;
				break;
			}
		}

		if (indexToRemove == -1) {
			cout << "Item not found in the cart!" << endl;
			return;
		}

		// Remove the item
		heap[indexToRemove] = heap.back();
		heap.pop_back();

		// Restore heap property
		if (indexToRemove < heap.size()) {
			if (indexToRemove > 0 && heap[indexToRemove] > heap[parent(indexToRemove)]) {
				// If the new item is larger than its parent, heapify up
				int current = indexToRemove;
				while (current > 0 && heap[current] > heap[parent(current)]) {
					swap(current, parent(current));
					current = parent(current);
				}
			}
			else {
				// Otherwise, sink down
				sinkDown(indexToRemove);
			}
		}

		cout << "Item removed successfully!" << endl;
	}
};
class Cart {

public:
	maxHeap heap;
	vector<cartItem>items;
	Cart() = default;
	Cart(const vector<cartItem>items) {
		for (const auto& item : items) {
			heap.insert(item);
		}
		this->items = items;
	}

	/*bool isEmpty() {
		return items.empty() && heap.isEmpty();
	}*/
	void addItem(Product product, int quantity) {

		for (int i = 0; i < items.size(); ++i) {
			if (items[i].product.name == product.name) {
				items[i].quantity += quantity;
				heap.insert(items[i]);
				cout << "Quantity of " << product.name << " after updating is:  " << items[i].quantity << endl;
				return;
			}
		}
		cartItem newItem(product, quantity);
		heap.insert(newItem);
		items.push_back(newItem);
		//heap.printHeap();
		cout << "The " << product.name << "is added with quantity " << quantity << " to the cart." << endl;
	}
	void printHeap() {
		heap.printHeap();
	}
	string categoryToString(Category cat) {
		switch (cat) {
		case electronics: return "electronics";
		case clothingItem: return "clothingItem";
		case schoolSupplies: return "schoolSupplies";
		}
		return "unknown";
	}

	Category stringToCategory(const string& str) {
		if (str == "electronics") return electronics;
		if (str == "clothingItem") return clothingItem;
		if (str == "schoolSupplies") return schoolSupplies;
		//cout << "Invalid category string";

	}

	void removeItem(string productName) {
		if (items.empty()) {
			cout << "Error: The cart is empty! Cannot remove items." << endl;
			return;
		}

		for (int i = 0; i < items.size(); ++i) {
			if (items[i].product.name == productName) {
				int quantityToRemove;
				cout << "Enter the quantity of you want to remove: ";
				cin >> quantityToRemove;

				if (quantityToRemove <= 0) {
					cout << "Error: Invalid quantity!" << endl;
					return;
				}

				if (quantityToRemove < items[i].quantity) {
					items[i].quantity -= quantityToRemove;
					cout << "Quantity is reduced by " << quantityToRemove
						<< ". The remaining quantity is: " << items[i].quantity << endl;
				}
				else {
					heap.deleteItem(productName);
					items.erase(items.begin() + i);
					heap.printHeap();
					cout << productName << " removed entirely from the cart." << endl;
				}

				return;
			}
		}

		cout << "Error: Product '" << productName << "' not found in the cart." << endl;
	}




	double calculateTotal() const {
		double total = 0.0;
		for (int i = 0; i < items.size(); i++) {
			total += items[i].product.price * items[i].quantity;
		}
		return total;
	}


	void clearCart() {




		if (heap.isEmpty() && items.empty()) {
			cout << "The cart is already empty!" << endl;

			return;
		}
		items.clear();
		heap.clear();
		while (!heap.isEmpty()) {
			heap.removeMax();
		}


	}

	void saveToFile(const string& filename) {
		ofstream outputFile(filename, ios::trunc); // Open in truncate mode to overwrite the file
		if (!outputFile) {
			cout << "Error opening file for saving cart!" << endl;
			return;
		}

		// Loop through the current items and save them to the file
		for (const auto& item : items) {
			string categoryStr;
			try {
				categoryStr = categoryToString(item.product.category);
			}
			catch (const invalid_argument& e) {
				cout << "Error: " << e.what() << " for product: " << item.product.name << endl;
				categoryStr = "unknown"; // Provide a fallback value
			}

			outputFile << item.product.name << ","
				<< item.product.price << ","
				<< item.quantity << ","
				<< categoryStr << endl;
		}

		outputFile.close();
	}


	void loadFromFile(const string& filename) {
		items.clear();
		heap.clear();
		ifstream inFile(filename);
		if (!inFile) {
			cout << "No previous cart found. Starting with an empty cart." << endl;
			return;
		}

		string line;
		while (getline(inFile, line)) {
			stringstream ss(line);
			string name, categoryStr;
			double price;
			int quantity;
			Category cat;

			if (!getline(ss, name, ',') || !(ss >> price) || !getline(ss, categoryStr, ',') || !(ss >> quantity)) {
				continue; // Skip invalid lines
			}

			cat = stringToCategory(categoryStr);
			Product product(name, price, cat, quantity);
			cartItem newItem(product, quantity);
			items.push_back(newItem);
			heap.insert(newItem);
		}
		inFile.close();
	}
	void removeMostExpensiveItem() {
		if (heap.isEmpty()) {
			cout << "Cart is empty, cannot remove most expensive item!" << endl;
			return;
		}

		// Get the most expensive item (root of the heap)
		cartItem mostExpensiveItem = heap.peekMax();
		cout << "Removing most expensive item: " << mostExpensiveItem.product.name << endl;

		// Remove the item from cartItems and MaxHeap
		removeItem(mostExpensiveItem.product.name);
		heap.removeMax();
	}

};

class Order {
public:
	string shippingAddress;
	string paymentMethod;
	double totalAmount;
	string deliveryInstructions;

	Order(const string& address, const string& method, double amount, const string& instructions)
		: shippingAddress(address), paymentMethod(method), totalAmount(amount), deliveryInstructions(instructions) {}
};




class User {

private:
	string username;
	string password;
	Cart cart; // Each user has their own cart
	bool loggedIn;
	maxHeap heap;

public:
	User() : loggedIn(false) {} // Default constructor

	User(string username, string password) : username(username), password(password), loggedIn(false) {}


	static void registerUser(const string& username, const string& password) {
		// Open the users file for reading
		ifstream userFile("users.txt");
		string line;

		// Check if the username already exists
		while (getline(userFile, line)) {
			int commaPos = line.find(',');
			if (commaPos != string::npos) {
				string storedUsername = line.substr(0, commaPos);
				if (storedUsername == username) {
					cout << "Username already exists. Choose another name." << endl;
					return;
				}
			}
		}
		userFile.close(); // Close the file after checking

		// Open the users file for appending and add the new user
		ofstream outputFile("users.txt", ios::app);
		if (outputFile.is_open()) {
			outputFile << username << "," << password << endl; // Save username,password
			outputFile.close();
			cout << "User registered successfully!" << endl;
		}
		else {
			cout << "Error opening users file!" << endl;
		}
	}
	void removeMostExpensiveItem() {
		cart.removeMostExpensiveItem();
		cart.saveToFile(username + "userr.txt");  // Save after modification
		cout << "Item removed from cart and saved successfully." << endl;
	}


	// Login function: This now opens the user's specific file (e.g., username.txt)
	bool loginUser(const string& username, const string& password) {
		ifstream userFile("users.txt");
		string line;

		while (getline(userFile, line)) {
			int commaPos = line.find(',');
			if (commaPos != string::npos) {
				string storedUsername = line.substr(0, commaPos);
				string storedPassword = line.substr(commaPos + 1);

				if (storedUsername == username && storedPassword == password) {
					this->username = username;
					this->password = password;
					loggedIn = true;
					cout << "Login successful!" << endl;

					// Load the user's cart from their specific cart file
					cart.loadFromFile(username + "userr.txt");
					return true;
				}
			}
		}

		cout << "Invalid username or password!" << endl;
		return false;
	}


	// Function to log out the user
	void logout() {
		if (loggedIn) {

			cout << "User " << username << " has logged out." << endl;
			loggedIn = false; // Set session state to logged out
		}
		else {
			cout << "No user is currently logged in." << endl;
		}
	}

	void addToCart(Product product, int quantity) {
		//cart.loadFromFile(username + "userr.txt");
		cart.addItem(product, quantity);
		cart.saveToFile(username + "userr.txt");
		cout << "Item added to cart and saved successfully." << endl;
	}

	// Remove an item from the cart
	void removeFromCart(const string& productName) {
		cart.loadFromFile(username + "userr.txt"); // Always load the latest state
		cart.removeItem(productName);
		cart.saveToFile(username + "userr.txt");  // Save after modification
		//cout << "Item removed from cart and saved successfully." << endl;
	}

	// Clear the entire cart
	void clearCart() {
		cart.loadFromFile(username + "userr.txt"); // Always load the latest state
		cart.clearCart();
		cart.saveToFile(username + "userr.txt");  // Save after modification
		cout << "Cart cleared for user " << username << "." << endl;
	}

	//void viewCart() {
	//	cart.loadFromFile(username + "userr.txt");
	//	if (cart.items.empty()) {
	//		cout << "Your cart is empty." << endl;
	//		return;
	//	}

	//	// Display cart contents
	//	cout << "Cart contents for user " << username << ":" << endl;
	//	for (const auto& item : cart.items) {
	//		cout << "Product: " << item.product.name
	//			<< ", Price per unit: " << item.product.price
	//			<< ", Quantity: " << item.quantity
	//			<< ", Total: " << (item.product.price * item.quantity) << endl;
	//	}

	//	// Display the total price
	//	cout << "Total price: " << cart.calculateTotal() << endl;
	//}

	void viewCart() {
		// Load the cart from the user's specific cart file
		cart.loadFromFile(username + "userr.txt");

		// Check if the cart is empty
		if (cart.items.empty()) {
			cout << "Your cart is empty." << endl;
			return;
		}

		// Temporary vector to hold the items while we extract them
		vector<cartItem> tempItems;

		cout << "Items in your cart (sorted by total price):" << endl;

		// Extract items from the heap and print them
		while (!cart.heap.isEmpty()) {
			cartItem maxItem = cart.heap.removeMax(); // Get the item with the highest total price
			tempItems.push_back(maxItem); // Store it in the temporary vector
			cout << "Product: " << maxItem.product.name
				<< ", Price per unit: " << maxItem.product.price
				<< ", Quantity: " << maxItem.quantity
				<< ", Total: " << (maxItem.product.price * maxItem.quantity) << endl;
		}

		// Reinsert the items back into the heap to restore its state
		for (const auto& item : tempItems) {
			cart.heap.insert(item);
		}

		// Calculate and display the total price of the cart
		double total = cart.calculateTotal(); // Assuming calculateTotal is accessible in this context
		cout << "Total price: $" << total << endl;
	}




	// Function to calculate the total price of items in the cart
	double calculateTotal() {
		return cart.calculateTotal();
	}

	void checkout() {
		double total = calculateTotal();
		if (total > 0) {
			string shippingAddress;
			string paymentMethod;

			// Collect shipping information
			cout << "Please enter your shipping address: ";
			cin.ignore(); // Clear any leftover newline character from previous input
			getline(cin, shippingAddress); // Now this will correctly capture the shipping address

			// Collect payment method
			cout << "Select payment method (1: Credit Card, 2: PayPal, 3: Cash): ";
			int choice;
			cin >> choice;
			cin.ignore(); // Clear the newline character from the input buffer after reading choice

			if (choice == 1) {
				paymentMethod = "Credit Card";
				string cardNumber;
				cout << "Please enter your credit card number: ";
				getline(cin, cardNumber);
				// Here you could implement card validation logic
			}
			else if (choice == 2) {
				paymentMethod = "PayPal";
				string paypalEmail;
				cout << "Please enter your PayPal email: ";
				getline(cin, paypalEmail);
				// Here you could implement PayPal validation logic
			}
			else if (choice == 3) {
				paymentMethod = "Cash";
				cout << "You have selected Cash as your payment method." << endl;

				// Additional logic for cash payments
				cout << "Please note that you will need to pay the total amount of $" << total << " in cash upon delivery." << endl;
				cout << "Make sure to have the exact amount ready for the delivery person." << endl;
				cout << "If you have any special instructions for the delivery, please let us know: ";

				string deliveryInstructions;
				getline(cin, deliveryInstructions); // This will now correctly capture delivery instructions

				// Create an Order object to store the order details
				Order order(shippingAddress, paymentMethod, total, deliveryInstructions);

				// Optionally, you can store the delivery instructions for processing
				cout << "Thank you! Your delivery instructions have been noted: " << deliveryInstructions << endl;
			}
			else {
				cout << "Invalid payment method selected." << endl;
				return;
			}

			// Final confirmation
			cout << "Payment successful!" << endl;
			cout << "Your order will be shipped to: " << shippingAddress << endl;
			cout << "Thank you for your purchase!" << endl;
			cart.clearCart();
			cart.saveToFile(username + ".txt");
		}
		else {
			cout << "Your cart is empty. Please add items to your cart before checking out." << endl;
		}
	}




};

int main() {
	vector<Product> catalog = {
		Product("Laptop", 90000.99,electronics,75),
		Product("Phone", 70000,electronics,80),
		Product("Headphones", 300,electronics,200),
		Product("Tablets", 45000,electronics,50),
		Product("Earbuds", 10000,electronics,100),
		Product("Speakers", 1100,electronics,40),
		Product("Digital cameras", 15000,electronics,25),
		Product("Hoodies", 1250,clothingItem,150),
		Product("T-shirts", 650.99,clothingItem,200),
		Product("Denims", 1500,clothingItem,40),
		Product("Coats", 2500,clothingItem,25),
		Product("Skirts", 650,clothingItem,40),
		Product("Jackets", 2050.45,clothingItem,30),
		Product("Pens", 25,schoolSupplies,80),
		Product("Pencils", 15,schoolSupplies,100),
		Product("Crayons and colored pencils", 500,schoolSupplies,85),
		Product("Notebooks", 400,schoolSupplies,35),
		Product("Sticky notes", 350,schoolSupplies,50),
		Product("Brushes", 450,schoolSupplies,45),
		Product("Planners and agendas", 650,schoolSupplies,35),
		Product("Pencil cases", 350,schoolSupplies,40),
		Product("File organizers", 500,schoolSupplies,20),
		Product("School backpacks", 850,schoolSupplies,10),











	};

	User user;
	int mainChoice;

	do {
		cout << "\n--- Main Menu ---" << endl;
		cout << "1. Login" << endl;
		cout << "2. Register" << endl;
		cout << "0. Exit" << endl;
		cout << "Enter your choice (0-2): ";

		cin >> mainChoice;


		while (cin.fail() || mainChoice < 0 || mainChoice > 2) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid choice. Please enter 0 to Exit, 1 to Login, or 2 to Register: ";
			cin >> mainChoice;
		}

		if (mainChoice == 2) {
			string username, password;
			cout << "\n--- Registration ---" << endl;
			cout << "Enter a new username: ";
			cin.ignore();
			getline(cin, username);
			cout << "Enter a new password: ";
			getline(cin, password);

			if (!username.empty() && !password.empty()) {
				User::registerUser(username, password);
				cout << "User registered successfully! Returning to the main menu..." << endl;
			}
			else {
				cout << "Registration failed. Username and password cannot be empty." << endl;
			}
		}

		if (mainChoice == 1) {
			string username, password;
			cout << "Enter username: ";
			cin.ignore();
			getline(cin, username);
			cout << "Enter password: ";
			getline(cin, password);

			if (user.loginUser(username, password)) {
				cout << "Welcome, " << username << "!" << endl;
				char userChoice;

				do {
					cout << "\n--- User Menu ---" << endl;
					cout << "1. Add item to cart" << endl;
					cout << "2. View cart" << endl;
					cout << "3. Remove item from cart" << endl;
					cout << "4. Calculate total" << endl;
					cout << "5. Clear cart" << endl;
					cout << "6. Checkout" << endl;
					cout << "7. Log out" << endl;
					cout << "8. View our products" << endl;
					cout << "9. Remove the most expensive item in your cart" << endl;
					cout << "Enter your choice (1-8): ";
					cin >> userChoice;

					switch (userChoice) {
					case '1': {
						string productName;
						int quantity;

						cout << "Enter product name: ";
						cin.ignore();
						getline(cin, productName);

						cout << "Enter quantity: ";
						while (!(cin >> quantity) || quantity <= 0) {
							cout << "Invalid input. Please enter a positive integer for quantity: ";
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}

						bool found = false;
						for (size_t i = 0; i < catalog.size(); i++) {
							if (catalog[i].name == productName) {
								user.addToCart(catalog[i], quantity);
								found = true;
								break;
							}
						}

						if (!found) {
							cout << "Product not found in catalog!" << endl;
						}
						break;
					}
					case '2':
						user.viewCart();
						break;
					case '3': {
						string productName;
						cout << "Enter product name to remove: ";
						cin.ignore();
						getline(cin, productName);

						user.removeFromCart(productName);
						break;
					}
					case '4': {
						double total = user.calculateTotal();
						cout << "Total price of items in the cart: $" << total << endl;
						break;
					}
					case '5':
						user.clearCart();
						break;
					case '6':
						user.checkout();
						break;
					case '7':
						user.logout();
						break;
					case '8': {
						cout << "Choose one of the following categories:" << endl;

						cout << "1.Electronics" << endl;
						cout << "2. Clothing Items" << endl;
						cout << "3. School Supplies" << endl;
						char choice2;
						cin >> choice2;
						switch (choice2) {
						case '1': {
							for (const auto& item : catalog) {
								if (item.category == 0) {
									cout << "Product Name:" << item.name << ", " << item.price << endl;
								}
								else
									continue;
							}
							break;
						}
						case '2': {
							for (const auto& item : catalog) {
								if (item.category == 1) {
									cout << "Product Name:" << item.name << ", " << item.price << endl;
								}
								else
									continue;
							}
							break;
						}
						case '3': {
							for (const auto& item : catalog) {
								if (item.category == 2) {
									cout << "Product Name:" << item.name << ", " << item.price << endl;
								}
								else
									continue;
							}
							break;
						}


						}
						break;
					}
					case'9': {
						user.removeMostExpensiveItem();
					}
						   break;
					default:
						cout << "Invalid choice. Please enter a number between 1 and 8." << endl;
						break;
					}
				} while (userChoice != '7'); // Loop until the user logs out
			}
		}

	} while (mainChoice != 0); // Loop until the user exits

	cout << "Thank you for using the system!" << endl;
	return 0;
}