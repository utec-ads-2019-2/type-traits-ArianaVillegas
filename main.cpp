#include <iostream>
#include <algorithm>

#include "test/tester.h"

using namespace std;

int main(int argc, char const *argv[]) {
    Tester::execute();
    SelfList<int> list(SelfList<int>::Move);
    return EXIT_SUCCESS;
}
