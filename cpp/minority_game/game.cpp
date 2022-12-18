#include "agent.cpp"
#include "producer.cpp"

using namespace std;

class Game
{
    
private:
    
    //class variables
    vector<Agent> agent;
    vector<Producer> producer;
    
    //game variables
    int Ns;
    int Np;
    int X;
    int p;
    bool fakeHistory;
    double devotionBoundary;
    int T;
    int Str;
    
    //process variables
    int H = 0; //History
    double Volat = 0.0; //Overall Bid
    double Volu = 0.0; //Volume
    vector<double> Pred;
    vector<int> PredII;
    
    //evaluation variables
    double GainS = 0.0; //Speculators Gain
    double GainP = 0.0; //Producers Gain
    vector<double> Devotion; //devotion to strategies
    double Volume = 0.0; //average Volume
    double Volatility = 0.0; //Volatility
    double Predictability = 0.0; //predictability
    
    //print variables
    vector<int> OB;
    vector<int> V;
    
    //custom observation
    vector<double> custom;
    
    
public: void makeGame(int Nsx, int Npx, int Xx, bool grandCanonical, double epsilon, int px, double V, bool fakeHistoryx, int Tx, double devotionBoundaryx, int StrX) {
    Ns = Nsx;
    Np = Npx;
    X = Xx;
    p = px;
    fakeHistory = fakeHistoryx;
    devotionBoundary = devotionBoundaryx;
    T = Tx;
    Str = StrX;
    
    Pred = vector<double> (p, 0.0);
    PredII = vector<int> (p, 0);
    Devotion = vector<double> (Str, 0.0);

    for (int i=0; i<Ns; i++) {
        Agent a;
        a.makeAgent(epsilon, p, grandCanonical, V, Str, devotionBoundary);
        agent.push_back(a);
    }
    
    for (int i=0; i<Np; i++) {
        Producer pr;
        pr.makeProducer(p);
        producer.push_back(pr);
    }
    
    H = random_uniform_int(0, p-1);
}
    
private: void updateHistory(int A) {
    if (fakeHistory == true) {
        H = random_uniform_int(0, p-1);
    }
    else {
        if (sgn(A) == -1) {
            H = (int)(p*0.5) + (int)(0.5*H);
        }
        else {
            H = (int)(0.5*H);
        }
    }
}
    
public: void play(){
    for (int i=0; i<X; i++) {
        playRound(i + 1);
    }
}
    
private: void playRound(int r) {
    
    int As = 0;
    int Vols = 0;
    for (int i=0; i<Ns; i++) {
        agent[i].evaluate();
        int x = agent[i].bid(H);
        As = As + x;
        Vols = Vols + sgn(x)*x;
    }
    
    int Ap = 0;
    for (int i=0; i<Np; i++) {
        Ap = Ap + producer[i].bid(H);
    }
    
    int A = As + Ap;
    if (A == 0) {
        A = randomBit();
    }
    
    if (r > T) {
        Volat = Volat + A*A;
        //Volu = Volu + Vols + Np;
        Volu = Volu + Vols;
        Pred[H] = Pred[H] + A;
        PredII[H] = PredII[H] + 1;
        OB.push_back(A);
        V.push_back(Vols);
    }
    
    for (int i=0; i<Ns; i++) {
        agent[i].updateI(H, A);
    }
    
    if (r > T) {
        for (int i=0; i<Ns; i++) {
            agent[i].updateII(H, A);
        }
        
        for (int i=0; i<Np; i++) {
            producer[i].update(H, A);
        }
    }
    
    updateHistory(A);

}
    
public: void observe() {
    for (int i=0; i<Ns; i++) {
        agent[i].observe(X - T);
    }

    for (int i=0; i<Np; i++) {
        producer[i].observe(X - T);
    }
    
    gain();
    devotion();
    average();
    observeCustom();
}
    
private: void observeCustom() {
    int minV = V[0];
    int maxV = V[0];
    for (int i=1; i<V.size(); i++) {
        if (V[i] > maxV) {
            maxV = V[i];
        }
        if (V[i] < minV) {
            minV = V[i];
        }
    }
    
    int minOB = OB[0];
    int maxOB = OB[0];
    for (int i=1; i<OB.size(); i++) {
        if (OB[i] > maxOB) {
            maxOB = OB[i];
        }
        if (OB[i] < minOB) {
            minOB = OB[i];
        }
    }
    custom.push_back(maxV - minV);
    custom.push_back(maxOB - minOB);
}
    
private: void gain() {
    vector<double> x;
    for (int i=0; i<Ns; i++) {
        x.push_back(agent[i].getGain());
    }
    GainS = vectorAverage(x);
    
    vector<double> y;
    for (int i=0; i<Np; i++) {
        y.push_back(producer[i].getGain());
    }
    GainP = vectorAverage(y);
}
    
private: void devotion() {
    for (int i=0; i<Ns; i++) {
        int k = agent[i].getDevotion();
        if (k > -1) {
            Devotion[k] = Devotion[k] + 1.0;
        }
    }
    
    for (int i=0; i<Str; i++) {
        Devotion[i] = Devotion[i] / Ns;
    }
}
    
private: void average() {
    int N = Ns + Np;
    
    Volume = (Volu / (X - T)) / N;
    Volatility = (Volat / (X - T)) / N;
    
    for (int i=0; i<p; i++) {
        if (PredII[i] > 0) {
            Pred[i] = Pred[i] / PredII[i];
        }
    }
    Predictability = vectorSquareAverage(Pred) / N;
}
    
public: double getGainS() {
    return GainS;
}
    
public: double getGainP() {
    return GainP;
}
    
public: double getDevotion(int k) {
    return Devotion[k];
}
    
public: double getVolume() {
    return Volume;
}
    
public: double getVolatility() {
    return Volatility;
}
    
public: double getPredictability() {
    return Predictability;
}
    
public: vector<int> getOB() {
    return OB;
}
    
public: vector<int> getV() {
    return V;
}
    
public: vector<double> getCustom() {
    return custom;
}
};
