/*Phase 2: Resource Protection
• Implement mutex locks for shared resource protection
• Demonstrate proper lock acquisition and release
• Show synchronized access to shared resources*/
#include <thread>
#include <iostream>
#include <mutex>

int applePrice = 5;
std::mutex priceMutex;

void ApplePriceChange(int amount) {
    std::lock_guard<std:: mutex> lock(priceMutex);
    applePrice += amount;
    std::cout << "Apple price: $" << applePrice << std::endl;
}

int main(){
    std::thread worker1(ApplePriceChange, 3);
    std::thread worker2(ApplePriceChange, -2);
    worker1.join();
    worker2.join();
    std::cout << "Apple final price: $" << applePrice << std::endl;
    return 0;
}
