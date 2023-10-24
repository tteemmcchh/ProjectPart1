#include <iostream>
#include <mutex>
#include <thread>

/**
 * Стуктура "Account" - имитирует работу банковского счета.
 *
 * **/
struct Account {
    std::mutex mu;

    int score = 10000;

/**
 * Функция "scoreUp" осуществляет пополнение счета, при этом на время работы
 * функции блокируется доступ к "score".
 *
 * @param sum : сумма пополнения счета
 * **/
    void scoreUp(int sum) {
        mu.lock();
        std::cout << "   ... Loading ... " << std::endl;
        std::chrono::milliseconds(1000);
        score += sum;
        std::cout << "Your account successful refilled! " << sum << std::endl;
        std::cout << " Cash on your account: " << score << "\n" << std::endl;
        mu.unlock();
    }

/**
 * Функция "scoreDown" осуществляет пополнение счета, при этом на время работы
 * функции блокируется доступ к "score".
 *
 * @param sum : сумма, которую необходимо снять со счета.
 * Если на счете не достаточно средств, то операция снятия не выполнится.
 *
 * **/
    void scoreDown(int sum) {
        mu.lock();
        std::cout << "   ... Loading ... " << std::endl;
        std::chrono::milliseconds(1000);
        if (score - sum >= 0) {
            score -= sum;
            std::cout << "You successful withdrew money from your account! " << sum << std::endl;
            std::cout << " Cash on your account: " << score << "\n" << std::endl;

        } else {
            std::cout << "Sorry, too little money on your account!" << std::endl;
            std::cout << " Cash on your account: " << score << "\n" << std::endl;
        }
        mu.unlock();
    }

/**
 * Функция "howMach" выводит информацию о состаянии счета в данный момент.
 *
 * **/
    int howMach() {
        std::cout << " Cash on your account: " << score << std::endl;
        return score;
    }
};

/**
 * Функция "mySrand" осуществляет генерацию псевдослучайного целого числа в диапазоне (100;10000).
 *
 * **/
int mySrand() {
    int numer = 100 * (1 + rand() % 100);
    return numer;
}