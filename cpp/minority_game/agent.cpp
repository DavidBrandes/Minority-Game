#include "function.h"

using namespace std;

class Agent
{
    
private:
    
    //agent variables
    double epsilon; //epsilon value
    vector<vector<int> > S; //Strategy Matrix
    int Str;
    double devotionBoundary;
    
    //process variables
    vector<double> R; //Strategy Rating
    vector<int> pS; //Times Strategy is played
    int W = 0; //Win or Loss
    int cs = 0; //momentarily used strategy, changes every round
    
    //evaluation variables
    double Gain = 0.0; //total Gain
    int Devotion = -1; //Strategy Devotion
    
public: void makeAgent(double epsilonx, int p, bool grandCanonical, double V, int StrX, double devotionBoundaryX) {
    epsilon = epsilonx;
    Str = StrX;
    devotionBoundary = devotionBoundaryX;
    
    R = vector<double> (Str, 0.0);
    pS = vector<int> (Str, 0);
    
    for (int i=0; i<Str; i++) {
        vector<int> x;
        for (int j=0; j<p; j++) {
            if (i == Str - 1 && grandCanonical == true) {
                x.push_back(0);
            }
            else {
                x.push_back(randomBit());
            }
        }
        S.push_back(x);
    }
    
    int k = random_uniform_int(0, Str - 2);
    R[k] = randomBit()*V;
}
    
public: void evaluate() {
    double x = R[0];
    cs = 0;
    for (int i=1; i<Str; i++) {
        if (R[i] > x) {
            x = R[i];
            cs = i;
        }
        else {
            if (R[i] == x) {
                int r = randomBit();
                if (r == 1) {
                    cs = i;
                }
            }
        }
    }
}
    
public: void updateII(int mu, int A){
    W = W - A*S[cs][mu];
    pS[cs] = pS[cs] + 1;
}
    
public: int bid(int mu) {    
    return S[cs][mu];
}
    
public: void updateI(int mu, int A) {
    for (int i=0; i<Str; i++) {
        if (i == Str - 1) {
            R[i] = R[i] - A*S[i][mu];
        }
        else {
            R[i] = R[i] - A*S[i][mu] - epsilon;
        }
    }
}
    
private: void gain(int m) {
    Gain = (double)W / m;
}
    
private: void devotion(int m) {
    for (int i=0; i<Str; i++) {
        double x = pS[i] / m;
        if (x > 1 - devotionBoundary) {
            Devotion = i;
        }
    }
}
    
public: void observe(int m) {
    gain(m);
    devotion(m);
}
    
public: double getGain() {
    return Gain;
}
    
public: int getDevotion() {
    return Devotion;
}
        
};

