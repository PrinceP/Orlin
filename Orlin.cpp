#include "Orlin.h"
#include <set>
#include <math.h>
#include <cfloat>

template<class T>
ostream &operator<<(ostream &out, vector<T> v) 
{
    out << "[";
    for (int i = 0; i < v.size(); i++) {
        out << v[i];
        if (i < v.size() - 1) out << ", ";
    }
    out << "]";
    return out;
}

ostream &operator<<(ostream &out, const Ordering &o) 
{
    out << "Ordering ";
    out << o.getOrdering() << " at ";
    out << o.getBase() << endl;
    return out;
}


SetFunction *globalSF;

Orlin::Orlin(SetFunction *sf)
{
    this->sf = sf;
    int n = sf->getBaseSize();
    for (int i = 0; i < n + 1; ++i) {
        vector<bool> v((unsigned long) n + 1, false);
    }
}
