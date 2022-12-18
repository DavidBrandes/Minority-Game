#include <random>
#include <vector>

#include "function.h"

using namespace std;

int random_uniform_int(int a, int b) {
    
    random_device rd;
    
    mt19937 gen(rd());
    
    double sample;
    uniform_int_distribution<int> d(a, b);
    sample = d(gen);
    return sample;
}

int sgn(int x) {
    if(x == 0) {return 0;}
    else {
        if(x < 0) {return -1;}
        else {return 1;}
    }
}

int randomBit() {
    int x = 2*random_uniform_int(0, 1) - 1;
    return x;
}

double vectorAverage(vector<double> v) {
    double x = 0.0;
    for (int i = 0; i < v.size(); i++) {
        x = x + v[i];
    }
    if (v.size() > 0) {
        return x / v.size();
    }
    else {
        return 0;
    }
}

double vectorSquareAverage(vector<double> v) {
    double x = 0.0;
    for (int i = 0; i < v.size(); i++) {
        x = x + v[i]*v[i];
    }
    if (v.size() > 0) {
        return x / v.size();
    }
    else {
        return 0;
    }    
}

