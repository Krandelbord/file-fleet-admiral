#ifndef RUNNER_H
#define RUNNER_H

#include <functional>

/**
 * Test runner.
 */
class Runner {
public :
    void run(std::function<bool()> oneTestFunction);

    void showStats();

private :
    unsigned int totalCount = 0;
    unsigned int successCount = 0;

    void doRun(bool runResultWasSuccess);
};


#endif //RUNNER_H
