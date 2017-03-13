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
    out << o.getBase() << " with ";
    out << o.getDistance() << endl;
    return out;
}


vector<int> Orlin::randomOrdering(int n) {
    //srand((unsigned int) time(0));
    vector<int> v;
    for (int i = 0; i < n; i++) v.push_back(i);
    random_shuffle(v.begin(), v.end());
    return v;
}



SetFunction *globalSF;

ostream &operator<<(ostream &out, HyperPoint &v) {
    out << "HyperPoint: ";
    out << v.getRepresentation() << endl;
    // out << "Distance - :";
    // out << v.getDistance() << endl;
    out << "Components: <" << v.getOrderings().size() << ">" << endl;
    for (pair<Ordering, double> p : v.getOrderings()) {
        out << p.second << "\t" << p.first << endl;
    }
    return out;
}

Orlin::Orlin(SetFunction *sf)
{
    this->sf = sf;
    int n = sf->getBaseSize();
}


void edmonds(vector<double> &out, vector<int> &o) {
    string set_str(o.size(), '0');
    string zero_str = set_str;
    out = vector<double>(o.size());
    set_str[o[0]] = '1';
    out[o[0]] = globalSF->oracle(set_str) - globalSF->oracle(zero_str);
    double prev = out[o[0]];
    for (int i = 1; i < out.size(); i++) {
        set_str[o[i]] = '1';
        double t = globalSF->oracle(set_str) - globalSF->oracle(zero_str);
        out[o[i]] = t - prev;
        prev = t;
    }
}


string Orlin::runOrlin()
{   
    globalSF = this->sf;
    long long it = 0;
    int n = sf->getBaseSize();

    // Intial W = V
    string set_str(n, '1');
    string res = set_str;
    
    vector<int> d((unsigned long) n);
    auto ordering = randomOrdering(n);
    auto ordering2 = randomOrdering(n);
    
    Ordering orderingObject(ordering);
    Ordering orderingObject2(ordering2);
    
    HyperPoint x;
    x.addOrdering(orderingObject, 1);
    x.addOrdering(orderingObject2, 2);
    
    cout<<x;




    string retval(n, '0');
    for (int i = 0; i < n; i++) if (1) retval[i] = '1';
    return retval;
    
}

vector<int> Orlin::runOrlinVec()
{
    vector<int> retval;
    string ret = this->runOrlin();
    for (int i = 0; i < ret.size(); i++) if (ret[i] == '1') retval.push_back(this->sf->getIndex(i));
    return retval;
}


