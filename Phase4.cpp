/*Phase 4: Deadlock Resolution
• Implement timeout mechanisms
• Add proper resource ordering
• Show deadlock prevention and recovery*/
#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>

int applePrice = 5;
int orangePrice = 5;
std::timed_mutex appleMutex;
std::timed_mutex orangeMutex;

void priceChange(int orangeAmount, int appleAmount) {
    auto timeout = std::chrono::milliseconds(100);

    while (true) {
        if (appleMutex.try_lock_for(timeout)) {
            if (orangeMutex.try_lock_for(timeout)) {

                applePrice += appleAmount;
                orangePrice += orangeAmount;
                std::cout << "Apple price: $" << applePrice << std::endl;
                std::cout << "Orange price: $" << orangePrice << std::endl;

                orangeMutex.unlock();
                appleMutex.unlock();
                break;
            } else {
                appleMutex.unlock();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void priceChange2(int orangeAmount, int appleAmount) {
    auto timeout = std::chrono::milliseconds(100);
    while (true) {
        if (orangeMutex.try_lock_for(timeout)) {
            if (appleMutex.try_lock_for(timeout)) {
                applePrice += appleAmount;
                orangePrice += orangeAmount;
                std::cout << "Apple price: $" << applePrice << std::endl;
                std::cout << "Orange price: $" << orangePrice << std::endl;

                appleMutex.unlock();
                orangeMutex.unlock();
                break;
            } else {
                orangeMutex.unlock();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() {
    std::thread worker1(priceChange, 3, 3);
    std::thread worker2(priceChange, -2, 9);
    worker1.join();
    worker2.join();

    std::thread worker3(priceChange, 3, 3);
    std::thread worker4(priceChange2, 3, 3);
    worker3.join();
    worker4.join();

    std::cout << "Final orange price: $" << orangePrice << " Final apple price: $" << applePrice << std::endl;
    return 0;
}