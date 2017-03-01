#include "SetFunction.h"

void SetFunction::setBase(std::vector<int> s) {
    this->base = s;
}

double SetFunction::oracle(std::vector<int> s) {
    return this->oracleFunction(s);
};

double SetFunction::oracle(std::string s) {
    return this->oracleFunction(s);
};

int SetFunction::getIndex(int i) {
    return (this->base)[i];
}

int SetFunction::getBaseSize() {
    return (int) (this->base).size();
}