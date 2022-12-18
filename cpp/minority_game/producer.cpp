#include "function.h"

using namespace std;

class Producer
{
    
private:
    
    //producer variables
    vector<int> S; //Strategy
    
    //process variables
    int W = 0; //Win or Loss
    
    //evaluation variables
    double Gain = 0.0; //total Gain
    
public: void makeProducer(int p) {
    
    int x = 0;
    for (int i=0; i<p; i++) {
        x = randomBit();
        S.push_back(x);
    }
}
    
public: int bid(int mu) {
    return S[mu];
}
    
public: void update(int mu, int A){
    W = W - A*S[mu];
}
    
private: void gain(int m) {
    Gain = (double)W / m;
}
    
public: void observe(int m) {
    gain(m);
}
    
public: double getGain() {
    return Gain;
}
    
};
