/*Phase 3: Deadlock Creation
• Create scenarios requiring multiple resource locks
• Demonstrate how deadlocks can occur
• Implement deadlock detection*/
#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>

int applePrice = 5;
int orangePrice = 5;
std::mutex appleMutex;
std::mutex orangeMutex;

void priceChange(int orangeAmount, int appleAmount) {
    appleMutex.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    orangeMutex.lock();
    applePrice += appleAmount;
    orangePrice += orangeAmount;
    std::cout << "Apple price: $" << applePrice << std::endl;
    std::cout << "Orange price: $" << orangePrice << std::endl;
    orangeMutex.unlock();
    appleMutex.unlock();
}

void priceChange2(int orangeAmount, int appleAmount) {
    orangeMutex.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    appleMutex.lock();
    applePrice += appleAmount;
    orangePrice += orangeAmount;
    std::cout << "Apple price: $" << applePrice << std::endl;
    std::cout << "Orange price: $" << orangePrice << std::endl;
    appleMutex.unlock();
    orangeMutex.unlock();
}

int main() {
    std::thread worker1(priceChange, 3, 3);
    std::thread worker2(priceChange2, -2, 9);

    worker1.join();
    worker2.join();

    std::cout << "Final orange price: $" << orangePrice << " Final apple price $:" << applePrice << std::endl;
    return 0;
}