#include <vector>
#include <math.h>
#include "function.h"
#include <iostream>

using namespace std;

double absolute(double x) {
    if (x >= 0) {
        return x;
    }
    else {
        return -x;
    }
}

vector<double> getPos(vector<double> a) {
    vector<double> y;
    for (int i=0; i<a.size(); i++) {
        if (a[i] > 0) {
            y.push_back(a[i]);
        }
    }
    return y;
}

vector<double> getNeg(vector<double> a) {
    vector<double> y;
    for (int i=0; i<a.size(); i++) {
        if (a[i] < 0) {
            y.push_back(a[i]);
        }
    }
    return y;
}

int findMin(vector<double> a, int delay) {
    int min = delay;
    for (int i=delay+1; i<a.size(); i++) {
        if (a[i] < a[min]) {
            min = i;
        }
    }
    return min;
}

vector<double> sort(vector<double> a) {
    vector<double> b = a;
    for (int i=0; i<b.size(); i++) {
        int min = findMin(b, i);
        double temp = b[i];
        b[i] = b[min];
        b[min] = temp;
    }
    return b;
}

vector<vector<double> > returnDistributionPos(vector<double> a) {
    a = getPos(a);
    a = sort(a);
    
    vector<vector<double> > y;
    for (int i=0; i<a.size(); i++) {
        if (a[i] == a[i+1]) {
            
        }
        else {
            vector<double> temp;
            temp.push_back(a[i]);
            double prob = (double)(a.size() - i - 1) / a.size();
            temp.push_back(prob);
            y.push_back(temp);
        }
    }
    return y;
}

vector<vector<double> > returnDistributionNeg(vector<double> a) {
    a = getNeg(a);
    a = sort(a);
    
    vector<vector<double> > y;
    for (int i=0; i<a.size(); i++) {
        if (a[a.size() - i - 1] == a[a.size() - i - 2]) {
            
        }
        else {
            vector<double> temp;
            temp.push_back(a[a.size() - i - 1]);
            double prob = (double)(a.size() - i - 1) / a.size();
            temp.push_back(prob);
            y.push_back(temp);
        }
    }
    return y;
}

vector<vector<double> > returnDistributionNegInver(vector<double> a) {
    a = getNeg(a);
    a = sort(a);
    
    vector<vector<double> > y;
    for (int i=0; i<a.size(); i++) {
        if (a[a.size() - i - 1] == a[a.size() - i - 2]) {
            
        }
        else {
            vector<double> temp;
            temp.push_back(absolute(a[a.size() - i - 1]));
            double prob = (double)(a.size() - i - 1) / a.size();
            temp.push_back(prob);
            y.push_back(temp);
        }
    }
    return y;
}

//ignores 0
vector<double> makePos(vector<double> a) {
    vector<double> y;
    for (int i=0; i<a.size(); i++) {
        if (a[i] <= 0) {
            if (a[i] < 0) {
                y.push_back(absolute(a[i]));
            }
        }
        else {
            y.push_back(a[i]);
        }
    }
    return y;
}

//includes 0
vector<double> makePosII(vector<double> a) {
    vector<double> y;
    for (int i=0; i<a.size(); i++) {
        if (a[i] < 0) {
            y.push_back(absolute(a[i]));
        }
        else {
            y.push_back(a[i]);
        }
    }
    return y;
}

vector<vector<double> > returnDistributionAbs(vector<double> a) {
    a = makePos(a);
    a = sort(a);
    
    vector<vector<double> > y;
    for (int i=0; i<a.size(); i++) {
        if (a[i] == a[i+1]) {
            
        }
        else {
            vector<double> temp;
            temp.push_back(a[i]);
            double prob = (double)(a.size() - i - 1) / a.size();
            temp.push_back(prob);
            y.push_back(temp);
        }
    }
    return y;
}

vector<double> returns(vector<double> a) {
    vector<double> y;
    y.push_back(0.0);
    for (int i=1; i<a.size(); i++) {
        double r = log(a[i]/a[i-1]);
        y.push_back(r);
    }
    return y;
}

vector<double> multiplyVector(vector<double> a, double x) {
    for (int i=0; i<a.size(); i++) {
        a[i] = (double)a[i] * x;
    }
    return a;
}

double doubleMean(vector<double> a, int end, int delay, bool abs) {
    double y = 0.0;
    for (int i=0; i<=end-1; i++) {
        if (abs == true) {
            y = y + absolute(a[i])*absolute(a[i+delay]);
        }
        else {
            y = y + a[i]*a[i+delay];
        }
    }
    y = y / end;
    return y;
}

double mean(vector<double> a,int start, int end, int delay, bool abs) {
    double y = 0.0;
    for (int i=start-1; i<end; i++) {
        if (abs == true) {
            y = y + absolute(a[i+delay]);
        }
        else {
            y = y + a[i+delay];
        }
    }
    y = y / (end - start + 1);
    return y;
}

vector<vector<double> > clusteringApprox(vector<double> a, bool abs) {
    vector<vector<double> > y;
    for (int i=0; i<a.size(); i++) {
        vector<double> temp;
        temp.push_back(i);
        double x = doubleMean(a, a.size()-i, i, abs) / doubleMean(a, a.size()-1, 0, abs);
        temp.push_back(x);
        y.push_back(temp);
    }
    return y;
}

vector<vector<double> > clustering(vector<double> a, bool abs) {
    vector<vector<double> > y;
    for (int i=0; i<a.size()-1; i++) {
        vector<double> temp;
        temp.push_back(i);
        double x1 = doubleMean(a, a.size()-i, i, abs) - mean(a, 1, a.size()-i, 0, abs)*mean(a, 1, a.size()-i, i, abs);
        double x2 = doubleMean(a, a.size()-i, 0, abs) - mean(a, 1, a.size()-i, 0, abs)*mean(a, 1, a.size()-i, 0, abs);
        temp.push_back(x1/x2);
        y.push_back(temp);
    }
    return y;
}

vector<vector<double> > clusteringInv(vector<double> a, bool abs) {
    vector<vector<double> > y;
    for (int i=0; i<a.size()-1; i++) {
        vector<double> temp;
        temp.push_back(i);
        double x1 = doubleMean(a, a.size()-i, i, abs) - mean(a, 1, a.size()-i, 0, abs)*mean(a, 1, a.size()-i, i, abs);
        double x2 = doubleMean(a, a.size()-i, 0, abs) - mean(a, 1, a.size()-i, 0, abs)*mean(a, 1, a.size()-i, 0, abs);
        temp.push_back(x1/x2);
        y.push_back(makePosII(temp));
    }
    return y;
}

void printMatrix(vector<vector<double> > a) {
    for (int i=0; i<a.size(); i++) {
        for (int j=0; j<a[i].size(); j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

void printVector(vector<double> a) {
    for (int i=0; i<a.size(); i++) {
        cout << i << " " << a[i] << endl;
    }
}

void printValue(double a) {
        cout << a << endl;
}

vector<vector<double> > volatility(vector<double> a,int w, bool prop, double lambda, bool exp) {
    vector<vector<double> > y;
    for (int i=w-1; i<a.size(); i++) {
        double mu = 0.0;
        if (prop == true) {
            mu = mean(a, i-w+2, i+1, 0, false);
        }
        double sigma = 0.0;
        for (int j=i-w+1; j<i+1; j++) {
            if (exp == true) {
                sigma = sigma + pow(lambda,i-j)*(a[j]-mu)*(a[j]-mu);
            }
            else {
                sigma = sigma + (a[j]-mu)*(a[j]-mu);
            }
        }
        if (exp == true) {
            sigma = (1 - lambda)*sigma;
        }
        else {
            sigma = sigma / w;
        }
        vector<double> temp;
        temp.push_back(i);
        temp.push_back(sigma);
        y.push_back(temp);
    }
    return y;
}

vector<double> getPart(vector<double> a, int begin, int end) {
    vector<double> y;
    for (int i=begin; i<=end; i++) {
        y.push_back(a[i]);
    }
    return y;
}
