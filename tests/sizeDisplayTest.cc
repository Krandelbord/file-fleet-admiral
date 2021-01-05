
#include <string>
#include "Asserts.h"
#include "Runner.h"
#include "../src/gui/SizeFormatter.h"
#include "../src/gui/SizeFormatterSimple.h"
#include "../src/gui/SizeFormatterSpaces.h"
#include "../src/gui/SizeFormatterHr.h"
#include <iostream>
bool checkSizeFormatting(SizeFormatter* formatter, size_t sizeToFormatInBytes, const std::string expectedOut) {

    const std::string formattedSize = formatter->formatSize(sizeToFormatInBytes);
    return Asserts::assertEquals("Size not formatted as expected", expectedOut, formattedSize);
}

int main() {
    std::locale::global(std::locale(std::locale("pl_PL.UTF-8"), "C", std::locale::numeric));
    std::setlocale(LC_ALL, "pl_PL.UTF-8");

    std::vector<std::function<bool()>> testsToRun;
    SizeFormatter *sizeFormatterSimple = new SizeFormatterSimple();
    testsToRun.emplace_back(std::bind(checkSizeFormatting, sizeFormatterSimple, 12345, "12345"));

    SizeFormatter *sizeFormatterSpaces = new SizeFormatterSpaces();
    testsToRun.emplace_back(std::bind(checkSizeFormatting, sizeFormatterSpaces, 12345, "12 345"));
    testsToRun.emplace_back(std::bind(checkSizeFormatting, sizeFormatterSpaces, 99999, "99 999"));
    testsToRun.emplace_back(std::bind(checkSizeFormatting, sizeFormatterSpaces, 99999212, "99 999 212"));
    testsToRun.emplace_back(std::bind(checkSizeFormatting, sizeFormatterSpaces, 12, "12"));
    testsToRun.emplace_back(std::bind(checkSizeFormatting, sizeFormatterSpaces, 4096, "4 096"));

    SizeFormatter *sizeFormatterHr = new SizeFormatterHr();
    testsToRun.emplace_back(std::bind(checkSizeFormatting, sizeFormatterHr, 99, "99 B"));
    testsToRun.emplace_back(std::bind(checkSizeFormatting, sizeFormatterHr, 12345, "12,06 kB"));
    testsToRun.emplace_back(std::bind(checkSizeFormatting, sizeFormatterHr, 99999, "97,66 kB"));
    testsToRun.emplace_back(std::bind(checkSizeFormatting, sizeFormatterHr, 99999212, "95,37 MB"));
    testsToRun.emplace_back(std::bind(checkSizeFormatting, sizeFormatterHr, 3615376, "3,45 MB"));


    Runner runner;
    for (const auto& oneTestToRun : testsToRun) {
        runner.run(oneTestToRun);
    }

    runner.showStats();
    std::cout << "The end";
    return 0;
}
