#include "Asserts.h"
#include <iostream>

bool Asserts::assertEquals(const Glib::ustring& msgIfFails, const Glib::ustring& expected, const Glib::ustring& actual) {
    if (expected == actual) {
        std::cout << "ARE EQUAL „" << expected << "” vs ”" << actual << "”." << std::endl;
      return true;
    } else {
      std::cout << "Assertion failed: ";
      std::cout << msgIfFails << ". ";
      std::cout << " Expected \"" << expected << "\", actual \"" << actual << "\"" << std::endl;
      return false;
    }
}
