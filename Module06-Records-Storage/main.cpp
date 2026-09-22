#include <iostream>
#include <iomanip>
#include "Product.h"

using namespace std;

void printDivider() {
    cout << "------------------------------------------------------------\n";
}

int main() {
    cout << "============================================================\n";
    cout << "        Product Inventory System - Classes & Objects\n";
    cout << "============================================================\n";

    Product lantern("71053", "WHITE METAL LANTERN", 6, 3.39);
    Product handWarmer("22633", "HAND WARMER UNION JACK", 6, 1.85);
    Product birdOrnament("84879", "ASSORTED COLOUR BIRD ORNAMENT", 32, 1.69);

    cout << "\n[1] Three Product objects created with the constructor:\n";
    printDivider();
    lantern.displayProduct();
    printDivider();
    handWarmer.displayProduct();
    printDivider();
    birdOrnament.displayProduct();
    printDivider();

    cout << "\n[2] Using member functions to change object state:\n";
    cout << "  restock(\"" << lantern.getDescription() << "\", 10): "
         << (lantern.restock(10) ? "OK" : "rejected") << "\n";
    cout << "  sell(\"" << handWarmer.getDescription() << "\", 4):  "
         << (handWarmer.sell(4) ? "OK" : "rejected") << "\n";
    cout << "  sell(\"" << handWarmer.getDescription() << "\", 50): "
         << (handWarmer.sell(50) ? "OK" : "rejected (not enough stock)") << "\n";

    cout << "\n[3] Using the setter to update a private data member:\n";
    cout << fixed << setprecision(2);
    cout << "  Old price of " << birdOrnament.getDescription() << ": $" << birdOrnament.getUnitPrice() << "\n";
    cout << "  setUnitPrice(1.49): " << (birdOrnament.setUnitPrice(1.49) ? "OK" : "rejected") << "\n";
    cout << "  setUnitPrice(-5.00): " << (birdOrnament.setUnitPrice(-5.00) ? "OK" : "rejected (price must be positive)") << "\n";
    cout << "  New price of " << birdOrnament.getDescription() << ": $" << birdOrnament.getUnitPrice() << "\n";

    cout << "\n[4] Updated object information:\n";
    printDivider();
    lantern.displayProduct();
    printDivider();
    handWarmer.displayProduct();
    printDivider();
    birdOrnament.displayProduct();
    printDivider();

    double totalValue = lantern.calculateStockValue()
                      + handWarmer.calculateStockValue()
                      + birdOrnament.calculateStockValue();
    int totalUnits = lantern.getQuantity() + handWarmer.getQuantity() + birdOrnament.getQuantity();

    cout << "\n============================================================\n";
    cout << "  Total Units In Stock:     " << totalUnits << "\n";
    cout << "  Total Inventory Value:    $" << totalValue << "\n";
    cout << "============================================================\n";

    return 0;
}
