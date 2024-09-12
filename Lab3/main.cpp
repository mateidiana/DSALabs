#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"
#include "IteratedList.h"
#include "ListIterator.h"
using namespace std;
int main() {

    testAll();
    testAllExtended();

    std::cout << "Finished LP Tests! :D" << std::endl;
    system("pause");
}
