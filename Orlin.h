#ifndef Orlin_H
#define Orlin_H

#include "SetFunction.h"
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#define EPSILON 1e-7

using namespace std;

/*
    Function: Finds the extreme base corresponding to the ordering
    @params: o -> Ordering as vector<int>
    @return: out-> The extreme base corresponding to the ordering o 
*/
void edmonds(vector<double> &out, vector<int> &o);

/*
    Function: Operator Overload (<<)
    @params: out-> ostream to print, v-> Vector to Print to ostream
    @return: ostream with printed v
*/
template<class T>
ostream &operator<<(ostream &out, vector<T> v);

/*
    Function: Operator Overload (*)
    @params: k-> double, base-> vector
    @return: scalar multiplication k*v
*/
template<class T>
vector<T> operator*(const double &k, const vector<T> &base) {
    vector<T> v(base);
    int i = 0;
    while (i < v.size()) {
        v[i] = v[i] * k;
        i++;
    }
    return v;
}

/*
    Function: Operator Overload (*)
    @params: k-> double, base-> vector
    @return: scalar multiplication v*k
*/
template<class T>
vector<T> operator*(const vector<T> &base, const double &k) {
    return k * base;
}

/*
    Function: Operator Overload (*=)
    @params: k-> double, base-> vector
    @return: base = base*k 
*/
template<class T>
void operator*=(vector<T> &base, const double &k) {
    for (int i = 0; i < base.size(); i++) {
        base[i] *= k;
    }
}

/*
    Function: Operator Overload (+)
    @params: a -> vector, b-> vector
    @return: component wise addition a+b
*/
template<class T>
vector<T> operator+(vector<T> &a, const vector<T> &b) {
    vector<T> v(a.size(), 0);
    int i = 0;
    while (i < v.size()) {
        v[i] = a[i] + b[i];
        i++;
    }
    return v;
}

/*
    Function: Operator Overload (+=)
    @params: a -> vector, b-> vector
    @return: a = a+b
*/
template<class T>
void operator+=(vector<T> &a, const vector<T> &b) {
    int i = 0;
    while (i < a.size()) {
        a[i] += b[i];
        i++;
    }
}

/*
    Function: Operator Overload (-)
    @params: a -> vector, b-> vector
    @return: component wise addition a-b
*/
template<class T>
vector<T> operator-(vector<T> &a, const vector<T> &b) {
    vector<T> v(a.size(), 0);
    int i = 0;
    while (i < v.size()) {
        v[i] = a[i] - b[i];
        i++;
    }
    return v;
}

/*
    Function: Operator Overload (-=)
    @params: a -> vector, b-> vector
    @return: a = a-b
*/
template<class T>
void operator-=(vector<T> &a, const vector<T> &b) {
    int i = 0;
    while (i < a.size()) {
        a[i] -= b[i];
        i++;
    }
}

/*
    Function: Operator Overload (*)
    @params: a -> vector, b-> vector
    @return: component wise multiplication a*b
*/
template<class T>
T operator*(vector<T> &a, const vector<T> &b) {
    T ret;
    int i = 0;
    while (i < a.size()) {
        ret += (a[i] * b[i]);
        i++;
    }
    return ret;
}

/*
    Function: Operator Overload (==)
    @params: a -> vector, b-> vector
    @return: bool -> component wise equality
*/
bool operator==(const vector<double> &a, const vector<double> &b);


/*
    Class: Ordering -> object for keeping the integer ordering and the extreme base corresponding to that ordering with the current oracle function.
    @members: ordering-> vector of int, ExtremeBase -> vector of double
*/
class Ordering {
    vector<int> ordering;
    vector<double> ExtremeBase;
public:
    
    /*
        Function: Operator Overload (<<)
        @params: out-> ostream to print, o-> Ordering to Print to ostream
        @return: ostream with printed ordering
    */
    friend ostream &operator<<(ostream &out, const Ordering &o);

    /*
        Function: Default Constructor to Ordering
        @params: None.
        @return: None.
    */
    Ordering() {
        this->ordering = vector<int>();
        this->ExtremeBase = vector<double>();
    }

    /*
        Function: Parametric Constructor to Ordering
        @params: o -> an ordering in vector of int
        @return: None.
    */
    Ordering(const vector<int> &o) {
        this->ordering = vector<int>(o);
        fill(this->ExtremeBase.begin(), this->ExtremeBase.end(), 0.0);
        edmonds(this->ExtremeBase, this->ordering);
    }

    /*
        Function: Copy Constructor to Ordering
        @params: o-> Ordering to copy
        @return: None.
    */
    Ordering(const Ordering &o) {
        this->ordering = vector<int>(o.getOrdering());
        fill(this->ExtremeBase.begin(), this->ExtremeBase.end(), 0.0);
        edmonds(this->ExtremeBase, this->ordering);
    }

    /*
        Function: Operator overload(=): Copy Assignment
        @params: other-> ordering to copy
        @return: New Ordering object
    */
    Ordering &operator=(const Ordering &other) // copy assignment
    {
        assert(this != NULL);
        if (this != &other) { // self-assignment check expected
            this->ordering = vector<int>();
            this->ordering.reserve(other.ordering.size());
            copy(other.ordering.begin(), other.ordering.end(), back_inserter(this->ordering));
            //this->ordering other.ordering;
            this->ExtremeBase = other.ExtremeBase;
        }
        return *this;
    }

    
    /*
        Function: Getter for member ordering
        @params: None
        @return: vector of int
    */
    vector<int> getOrdering() const { return this->ordering; }

    /*
        Function: Getter for member ExtremeBase
        @params: None
        @return: vector of double
    */
    vector<double> getBase() const { return this->ExtremeBase; }

    /*
        Function: Getter for the size of the ordering/ExtremeBase
        @params: None
        @return: size_t
    */
    size_t getDimension() const {return this->ExtremeBase.size();}
    
    /*
        Function: Getter for an element in ExtremeBase by index
        @params: The Index i : int
        @return: ExtremeBase[i] -> double
    */
    double getBaseElement(int i) const {return this->ExtremeBase[i];}
    
    /*
        Function: Getter for an element in ordering by index
        @params: The Index i : int
        @return: ordering[i] -> int
    */
    int getOrderingElement(int i) const {return this->ordering[i];}
    
    /*
        Function: Default Destructor
        @params: None
        @return: None
    */
    ~Ordering() {
        this->ordering.clear();
        this->ExtremeBase.clear();
    }
};

class Orlin{

    private:
        SetFunction *sf;

    Orlin(){
        
        sf = NULL;
    
    };

    Orlin(SetFunction *sf);
    std::vector<int> runOrlinVec();
    std::string runOrlin();

    ~Orlin(){

    }
};

#endif