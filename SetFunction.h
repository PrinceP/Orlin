#ifndef SETFUNCTION_H
#define SETFUNCTION_H

#include <vector>
#include <iostream>

// f: P(S) -> R
class SetFunction {
private:
    std::vector<int> base;
protected:
    virtual double oracleFunction(std::vector<int> a) = 0;

    virtual double oracleFunction(std::string a) = 0;

    void setBase(std::vector<int> base);

public:
    double oracle(std::vector<int> a);

    double oracle(std::string a);

    std::vector<int> *getBase();

    int getBaseSize();

    int getIndex(int i);

    ~SetFunction() {
        this->base.clear();
    }
};

#endif