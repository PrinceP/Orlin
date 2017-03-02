#include <iostream>
#include "Orlin.h"
#include "SetFunction.h"

double arr[] = {-10.819, -16.1362, -223.9859, 8.0142, -1.9621};

vector<double> y;

using namespace std;

template<class T>
ostream &operator<<(ostream &out, vector<T> v) {
    out << "[";
    for (int i = 0; i < v.size(); i++) {
        out << v[i];
        if (i < v.size() - 1) out << ", ";
    }
    out << "]";
    return out;

}

class MySetFunction: public SetFunction
{
    double oracleFunction(vector<int> s) {
        double sum;
        string st = "";
        for (int i = 0; i < this->getBaseSize(); i++) st += "0";
        for (int i = 0; i < s.size(); i++) st[s[i] - 1] = '1';
        return oracleFunction(st);
    }


    double oracleFunction(string s) {
        int num = 0;
        if (s.length() != this->getBaseSize()) return -1;
        double ans = 0;
        for (int i = 0; i < s.length(); i++)
            if (s[i] == '1') {
                ans += ::y[i];
                num++;
            }
        ans += (num+1) * ((this->getBaseSize()) - num-1);
        return ans;

    }

    public:
        MySetFunction(vector<int> s) {
            this->setBase(s);
        }

};


int main(){
    
    int input = 5;
    vector<int> s;
    
    //cin>>input;
    
    for(int i = 0 ; i < input ;i++) {s.push_back(i+1);y.push_back(arr[i%5]);}
    cout<<y<<endl;
    MySetFunction oracle(s);
    


    double min_t=1e11,t = 1e11;
    for (int i = 0; i < (1 << (s.size())); i++) {
        vector<int> temp;
        for (int j = 0; j < s.size(); j++) {
            if (i & (1 << j)) temp.push_back(s[j]);
        }
        cout<<"Set "<<temp<<" = "<<oracle.oracle(temp)<<endl;
        t=oracle.oracle(temp);
        min_t = min(min_t,t);
    }

    cout<<min_t<<endl;

    Orlin orlin(&oracle);

    //vector<int> *del = oracle.getBase();
    //cout<<"Oracle"<<del;
    vector<int> result = orlin.runOrlinVec();
    cout << "SIZE OF RESULT:  " << result.size() << endl;
    
    for (vector<int>::iterator it = result.begin(); it != result.end(); it++) {
        cout << *it << endl;
    }
    // double min_t2 = oracle.oracle(result);
    // cout<<"Orlin Minimum = "<<min_t2;    

    return 0;

}