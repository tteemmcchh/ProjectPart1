#include <iostream>
#include <mutex>
#include <thread>
#include "./internal/methods.h"


int main() {
    srand(time(NULL));
    Account account;
    account.howMach();
    for (int i = 0; i < 6; i++) {
        std::thread th1(&Account::scoreUp, &account, mySrand());
        std::thread th2(&Account::scoreDown, &account, mySrand());
        th1.join();
        th2.join();

    }
    account.howMach();

    return 0;
}
