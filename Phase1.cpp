/*Phase 1: Basic Thread Operations
• Create threads that perform concurrent operations
• Demonstrate proper thread creation and management
• Show basic thread safety principles*/
#include <thread>
#include <iostream>

int applePrice = 5;

void ApplePriceChange(int amount) {
    applePrice += amount;
}

int main(){
    std::thread worker1(ApplePriceChange, 3);
    std::thread worker2(ApplePriceChange, -2);
    worker1.join();
    worker2.join();
    std::cout << "Apple final price: $" << applePrice << std::endl;
    return 0;
}

