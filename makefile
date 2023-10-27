GTEST_DIR=./lib/googletest-1.14.0/googletest
USER_DIR=.
CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread

BUILD = build
TESTS = tests

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
$(GTEST_DIR)/include/gtest/internal/*.h

all: $(BUILD) $(TESTS)

clean :
	rm -f $(BUILD) $(TESTS) runapp app.o gtest.a gtest_main.a *.o

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Builds a sample test.  A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.

account_tests.o : $(USER_DIR)/qa/account_tests.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/qa/account_tests.cpp

tests : account_tests.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
#hello: app.o account_tests.o
#	g++ app.o account_tests.o -o hello

app.o : $(USER_DIR)/app.cpp $(USER_DIR)/internal/methods.h
	$(CXX) $(CXXFLAGS) -c $(USER_DIR)/app.cpp

build : app.o
	$(CXX) $(CXXFLAGS) -lpthread $^ -o $@

#hello: account_tests.o
#	g++ account_tests.o -o hello
#
#app.o: app.cpp internal/methods.h
#	g++ -c app.cpp
#
#account_tests.o: qa/account_tests.cpp internal/methods.h lib/googletest-1.14.0/googletest/include/gtest/gtest.h
#	g++ -c qa/account_tests.cpp
#
#clean:
#	rm -rf *.o hello