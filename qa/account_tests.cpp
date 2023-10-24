#include <gtest/gtest.h>
#include "../internal/methods.h"

class TestAccount : public ::testing::Test {
protected:
    void SetUp() {
        acc = new Account;
        acc->score = 5000;
    }

    void SetDown() {
        delete acc;
    }

    Account *acc;
};

TEST_F(TestAccount, test1) {
acc->scoreUp(5000);
EXPECT_EQ(acc->score, 10000);
acc->scoreUp(3000);
EXPECT_EQ(acc->score, 13000);
}

TEST_F(TestAccount, test2) {
acc->scoreUp(3000);
EXPECT_EQ(acc->score, 8000);
}

TEST_F(TestAccount, test3) {
acc->scoreDown(3000);
EXPECT_EQ(acc->score, 2000);
}

TEST_F(TestAccount, test4) {
acc->scoreDown(7000);
EXPECT_EQ(acc->score, 5000);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}