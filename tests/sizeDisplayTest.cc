
#include <string>
#include "Asserts.h"
#include "Runner.h"
#include "../SizeFormatter.h"
#include "../SizeFormatterSimple.h"
#include "../SizeFormatterSpaces.h"
#include "../SizeFormatterHr.h"
#include <iostream>
bool checkSizeFormatting(SizeFormatter* formatter, size_t sizeToFormatInBytes, const std::string expectedOut) {

    const std::string formattedSize = formatter->formatSize(sizeToFormatInBytes);
    return Asserts::assertEquals("Size not formated as expected", expectedOut, formattedSize);
}

int main() {
    std::locale::global(std::locale(std::locale("pl_PL.UTF-8"), "C", std::locale::numeric));
    std::setlocale(LC_ALL, "pl_PL.UTF-8");

    std::vector<std::function<bool()>> testsToRun;
    SizeFormatter *sizeFormatterSimple = new SizeFormatterSimple();
    testsToRun.push_back(std::bind(checkSizeFormatting, sizeFormatterSimple, 12345, "12345"));

    SizeFormatter *sizeFormatterSpaces = new SizeFormatterSpaces();
    testsToRun.push_back(std::bind(checkSizeFormatting, sizeFormatterSpaces, 12345, "12 345"));
    testsToRun.push_back(std::bind(checkSizeFormatting, sizeFormatterSpaces, 99999, "99 999"));
    testsToRun.push_back(std::bind(checkSizeFormatting, sizeFormatterSpaces, 99999212, "99 999 212"));
    testsToRun.push_back(std::bind(checkSizeFormatting, sizeFormatterSpaces, 12, "12"));
    testsToRun.push_back(std::bind(checkSizeFormatting, sizeFormatterSpaces, 4096, "4 096"));

    SizeFormatter *sizeFormatterHr = new SizeFormatterHr();
    testsToRun.push_back(std::bind(checkSizeFormatting, sizeFormatterHr, 99, "99 B"));
    testsToRun.push_back(std::bind(checkSizeFormatting, sizeFormatterHr, 12345, "12,06 kB"));
    testsToRun.push_back(std::bind(checkSizeFormatting, sizeFormatterHr, 99999, "97,66 kB"));
    testsToRun.push_back(std::bind(checkSizeFormatting, sizeFormatterHr, 99999212, "95,37 MB"));
    testsToRun.push_back(std::bind(checkSizeFormatting, sizeFormatterHr, 3615376, "3,5 MB"));


    Runner runner;
    for (auto oneTestToRun : testsToRun) {
        runner.run(oneTestToRun);
    }

    runner.showStats();
    std::cout << "The end";
    return 0;
}
