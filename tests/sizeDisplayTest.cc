#include <cstddef>
#include <string>
#include "Asserts.h"
#include "Runner.h"
#include "../SizeFormatter.h"
#include "../SizeFormatterSimple.h"
#include <iostream>
bool checkSizeFormatting(SizeFormatter* formatter, size_t sizeToFormatInBytes, const std::string expectedOut) {

    const std::string formattedSize = formatter->formatSize(sizeToFormatInBytes);
    return Asserts::assertEquals("Size not formated as expected", expectedOut, formattedSize);
}

int main() {
    std::vector<std::function<bool()>> testsToRun;
    SizeFormatter *sizeFormatterSimple = new SizeFormatterSimple();
    testsToRun.push_back(std::bind(checkSizeFormatting, sizeFormatterSimple, 12345, "12 345"));
    Runner runner;
    for (auto oneTestToRun : testsToRun) {
        runner.run(oneTestToRun);
    }

    runner.showStats();
    std::cout << "The end";
}