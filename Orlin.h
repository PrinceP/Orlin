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
    Class: Ordering -> object for keeping the integer ordering and the extreme base corresponding to that ordering with the current oracle function with distance label.
    @members: ordering-> vector of int, ExtremeBase -> vector of double
*/
class Ordering {
    vector<int> ordering;
    vector<double> ExtremeBase;
    vector<int> distance;

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
        this->distance = vector<int>();
    }

    /*
        Function: Parametric Constructor to Ordering
        @params: o -> an ordering in vector of int
        @return: None.
    */
    Ordering(const vector<int> &o) {
        this->ordering = vector<int>(o);
        this->distance = vector<int>(o.size(),0);
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
        this->distance = vector<int>(o.getDistance());
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
            this->distance = other.distance;
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
        Function: Getter for member distance
        @params: None
        @return: vector of int
    */
    vector<int> getDistance() const { return this->distance; }



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
        this->distance.clear();
    }
};

/*
    Class: HyperPoint -> object for keeping a hyperPoint in the base polyhedron of the current oracle function. Also stores the representation of the hyperpoint in terms of extreme bases
    @members: representation->vector of double, orderings->vector of Orderings and their corresponding coefficients in the convex combination.
    n: dimension of the hyperpoint
*/
class HyperPoint {

    vector<double> representation;
    vector<pair<Ordering, double>> orderings;
    int n;
public:
    /*
        Function: Operator Overload (<<)
        @params: out-> ostream to print, o-> HyperPoint to Print to ostream
        @return: ostream with printed hyperpoint
    */
    friend ostream &operator<<(ostream &out, HyperPoint &h);

    /*
        Function: Default Constructor to HyperPoint
        @params: None.
        @return: None.
    */
    HyperPoint() {
        this->n = 0;
        this->orderings = vector<pair<Ordering, double>>();
        this->representation = vector<double>();
    }

    /*
        Function: Parametric Constructor to HyperPoint. Initilize via the point x = 1.0*o.ExtremeBase
        @params: o -> ordering
        @return: None.
    */
    HyperPoint(Ordering &o)
    {
        this->n = o.getOrdering().size();
        Ordering temp(o.getOrdering());
        this->orderings.push_back(make_pair(temp, 1));
        this->calculateRepresentation();
    }

    /*
        Function: Copy Constructor to HyperPoint.
        @params: hp -> HyperPoint object to copy
        @return: None.
    */
    HyperPoint(const HyperPoint &hp) {
        assert(this != nullptr);
        this->orderings = vector<pair<Ordering, double>>(hp.orderings);
        this->n = hp.n;
        this->calculateRepresentation();
    }

    /*
        Function: Getter for the member n = dimension of the HyyperPoint
        @params: None.
        @return: int
    */
    int getDimension() { return this->n; }

    /*
        Function:  Calculates the coordinates of the point using the current combination of bases in the member and stores in representation
        @params: None.
        @return: None.
    */
    void calculateRepresentation() {
        this->representation = vector<double>(this->n, 0);
        for (pair<Ordering, double> p : this->orderings) {
            vector<double> e = p.first.getBase();
            double multiplier = p.second;
            this->representation = this->representation + multiplier * e;
        }
        for (int i = 0; i < this->representation.size(); i++)
            if (abs(this->representation[i]) < 1e-7)
                this->representation[i] = 0;
    }

    /*
        Function: Adds an ordering to the extremebases combination with the given coefficient. keepDirty controls whether to recalculate representation or not.
        @params: Ordering b-> ordering object, Double coeff-> Coefficient to keep in the representation, Bool keepDirty.
        @return: None.
    */
    void addOrdering(const Ordering &b, double coeff, bool keepDirty = false) {
        this->n = b.getOrdering().size();
        bool flag = false;
        for (int i = 0; i < this->orderings.size(); i++) {
            auto l = this->orderings[i].first.getOrdering();
            if (l == b.getOrdering()) {
                flag = true;
                this->orderings[i].second += coeff;
            }
        }
        if (!flag) {
            Ordering temp(b.getOrdering());
            this->orderings.push_back(make_pair(temp, coeff));
        }
        if(!keepDirty) this->calculateRepresentation();
    }

    /*
        Function: Operator overload(=): Copy Assignment
        @params: other-> HyperPoint to copy
        @return: New HyperPoint object
    */
    HyperPoint &operator=(const HyperPoint &other) // copy assignment
    {
        if (this != &other) { // self-assignment check expected
            this->orderings = vector<pair<Ordering, double>>(other.orderings);
            //copy(other.orderings.begin(),other.orderings.end(),this->orderings.begin());
            this->n = other.n;
            this->calculateRepresentation();
        }
        return *this;
    }
    
    /*
        Function: Operator overload(=): Move Assignment
        @params: other-> HyperPoint to move. The data in the other HyperPoint may not remain the same.
        @return: New HyperPoint object with the data as it were in other.
    */
    HyperPoint &operator=(HyperPoint &&other) // move assignment
    {
        assert(this != &other); // self-assignment check not required
        this->orderings = move(other.orderings);
        this->n = other.n;
        this->calculateRepresentation();
        return *this;
    }

    /*
        Function: Operator overload(=): Move Assignment
        @params: other-> ordering to move. The data in the other ordering may not remain the same.
        @return: New Ordering object with the data as it were in other.
    */
    friend HyperPoint operator+(HyperPoint n, const Ordering &b) {
        n.addOrdering(b, 1);
        return n;
    }

    /*
        Function: Operator overload(+=), Adds HyperPoints Combination component wise.
        @params: HyperPoint a
        @return: this += a
    */
    HyperPoint &operator+=(const HyperPoint &a) {
        for (pair<Ordering, double> p : a.getOrderings()) {
            this->addOrdering(p.first, p.second,true);
        }
        this->calculateRepresentation();
        return *this;
    }

    /*
        Function: Operator overload(+)
        @params: HyperPoints n,a 
        @return: HyperPoint n+a
    */
    friend HyperPoint operator+(HyperPoint n, const HyperPoint &a) {
        n += a;
        return n;
    }

    /*
        Function: Operator overload(*=)
        @params: k -> double
        @return: this *= k; Scalar Multiplication
    */
    HyperPoint &operator*=(const double &k) {
        for (int i = 0; i < this->orderings.size(); i++) {
            this->orderings[i].second *= k;
        }
        this->calculateRepresentation();
        return *this;
    }

    /*
        Function: Operator overload(*)
        @params: HyperPoint n, double k
        @return: HyperPoint n*k
    */
    friend HyperPoint operator*(HyperPoint n, const double &k) {
        n *= k;
        return n;
    }

    /*
        Function: Getter for member representation
        @params: None.
        @return: vector of double
    */
    vector<double> getRepresentation() const {
        return this->representation;
    }


    /*
        Function: Getter for member distance
        @params: None.
        @return: vector of int
    */
    // vector<int> getDistance() const {
    //     return this->distance;
    // }

    /*
        Function: Getter for member orderings
        @params: None.
        @return: vector of pairs of double and Ordering
    */
    vector<pair<Ordering, double>> getOrderings() const {
        return this->orderings;
    }

    /*
        Function: Getter for member representation
        @params: None.
        @return: vector of double
    */
    double operator[](int i) const {
        return this->representation[i];
    }

    /*
        Function: Remove bases with coefficient 0 in the current combination
        @params: None.
        @return: None.
    */
    void removeExtraBases() {
        vector<pair<Ordering, double>> new_orderings;
        for (int i = 0; i < this->orderings.size(); i++) {
            if (abs(this->orderings[i].second) < EPSILON) continue;
            new_orderings.push_back(orderings[i]);
        }
        if (new_orderings.size() != this->orderings.size())
            this->orderings.assign(new_orderings.begin(), new_orderings.end());
        this->calculateRepresentation();
    }

    /*
        Function: Reduce bases by using Caratheodory's theorem
        @params: None.
        @return: None.
    */
    void affineReduceBases();

    /*
        Function: Default Destructor for HyperPoint
        @params: None.
        @return: None.
    */
    ~HyperPoint() {
        this->representation.clear();
        this->orderings.clear();
    }
};



class Orlin{
    private:
           
    public:    
         vector<int> randomOrdering(int n);
       
        SetFunction *sf;
    Orlin(){
        sf = NULL;
    };

    Orlin(SetFunction *sf);
    
    vector<int> runOrlinVec();
    
    string runOrlin();

    ~Orlin(){

    }
};

#endif