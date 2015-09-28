//
// Created by enowak on 28.09.15.
//

#ifndef RUNNER_H
#define RUNNER_H

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
