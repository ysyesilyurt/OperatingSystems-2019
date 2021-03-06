#ifndef _OS_2019_MINER_HPP
#define _OS_2019_MINER_HPP

#include "monitor.hpp"

class Miner: public Monitor {
    int oreCount;
    int minerID;
    unsigned int minerPeriod;
    unsigned int capacity;
    unsigned int totalAmount;
    OreType oreType;
    bool quit;

    Condition cv;
    std::vector<Ore> storage;

public:

    Miner(int mID, unsigned int mP, unsigned int cap, OreType oT, unsigned int tA) : cv(this) {
        oreCount = 0;
        minerID = mID;
        minerPeriod = mP;
        capacity = cap;
        oreType = oT;
        totalAmount = tA;
        quit = false;
    }

    void mineOre() {
        __synchronized__;
        Ore ore;
        ore.type = oreType;
        storage.emplace_back(ore);
        oreCount++;
    }

    void removeOre() {
        __synchronized__;
        storage.pop_back();
    }

    void setQuit() {
        __synchronized__;
        quit = true;
    }

    void wait() {
        __synchronized__;
        cv.wait();
    }

    void notify() {
        __synchronized__;
        cv.notify();
    }

    bool isFull() {
        __synchronized__;
        return storage.size() == capacity;
    }

    bool isEmpty() {
        __synchronized__;
        return storage.empty();
    }

    bool checkQuit() {
        __synchronized__;
        return ((oreCount == totalAmount) || quit);
    }

    int getPeriod() {
        __synchronized__;
        return minerPeriod;
    }

    int getMinerId() {
        __synchronized__;
        return minerID;
    }

    int getCapacity() {
        __synchronized__;
        return capacity;
    }

    int getCurrOreCount() {
        __synchronized__;
        return storage.size();
    }

    OreType getOreType() {
        __synchronized__;
        return oreType;
    }
};

#endif /* _OS_2019_MINER_HPP */
