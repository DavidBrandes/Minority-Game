#include "game.cpp"
#include <iostream>
#include <iomanip>

using namespace std;

class Games
{
    
private:
    
    //implementation variables
    double alpha;
    double rho;
    double Rnd;
    int G; //Number of different Game Initalisations
    
    //games variables
    int Str; //Number of Strategies
    int X; //Number of Rounds Played
    int p; //History Depth parameter
    int Ns; //Number of Speculator = Number of Agents
    int Np; //Number of Producers
    bool grandCanonical; ////Interchanges between Standart and Grand Canonical Version
    double epsilon; //Epsilon in case of Grand Canonic Version
    double V; //Initial Evaluation Variance
    bool fakeHistory; //Interchanges between true and fake History
    int T; //time delay for evaluation
    double devotionBoundary; //Boundary for when we call an agent devoted
    
    //evaluation variables
    double GainS = 0.0; //Speculators Gain
    double GainP = 0.0; //Producers Gain
    vector<double> Devotion; //devotion to strategies
    double Volume = 0.0; //average Volume
    double Volatility = 0.0; //Volatility
    double Predictability = 0.0; //predictability
    
    vector<double> custom;
    
    //observation
    vector<double> x1;
    vector<double> x2;
    vector<vector<double> > y;
    vector<double> z1;
    vector<double> z2;
    vector<double> z3;
    
    //custom observation
    vector<vector<double> > c;
    
    
public: void initalize(int ns, int pp) {
    alpha = (double)pp / (ns + 15);
    rho = (double)(ns + 15) / ns - 1;
    Rnd = 10000;
    G = 1;
    
    grandCanonical = false;
    fakeHistory = false;
    Ns = ns;
    Np = 0;
    //p = a*(Ns + Np);
    p = pp;
    X = Rnd + 500;
    T = Rnd;
    epsilon = 0.0;
    V = 0;
    devotionBoundary = 1.0 / Rnd;
    Str = 2;

}
    
public: void simulate(){
    
    for (int i=0; i<G; i++) {
        
        Game g;
        g.makeGame(Ns, Np, X, grandCanonical, epsilon, p, V, fakeHistory, T, devotionBoundary, Str);
        
        g.play();
        
        g.observe();
        
        x1.push_back(g.getGainS());
        x2.push_back(g.getGainP());
        
        z1.push_back(g.getVolume());
        z2.push_back(g.getVolatility());
        z3.push_back(g.getPredictability());
        
        c.push_back(g.getCustom());
        
        vector <double> temp;
        for (int j=0; j<Str; j++) {
            temp.push_back(g.getDevotion(j));
        }
        y.push_back(temp);
        
/*
        cout << "Game " << i+1 << " Ns: " << Ns << " Np: " << Np << " alpha: " << alpha << endl;
        cout << "Gain Speculators: " << g.getGainS() << endl;
        cout << "Gain Producers: " << g.getGainP() << endl;
        for (int j=0; j<Str; j++) {
            cout << "Frozen to S" << j + 1 << ": " << g.getDevotion(j) << endl;
        }
        cout << "Volume: " << g.getVolume() << endl;
        cout << "Volatility: " << g.getVolatility() << endl;
        cout << "Predictability: " << g.getPredictability() << endl;
        cout << endl;
*/

        vector<int> OB = g.getOB();
        vector<int> V = g.getV();
        printCustomObservation(OB, V);
  

    }
    
    observe();
    printObservation();
}
    
public: void simulateII(){
    
    int i = 1;
    bool tester = true;
    while (tester == true) {
        cout << "Search " << i;
        i++;
        Game g;
        g.makeGame(Ns, Np, X, grandCanonical, epsilon, p, V, fakeHistory, T, devotionBoundary, Str);
        
        g.play();
        
        g.observe();
        
        double v = g.getVolatility();
        cout << " Volatility " << v << endl;
        if ( v > 0 && v < 1 ) {
            tester = false;
            
            x1.push_back(g.getGainS());
            x2.push_back(g.getGainP());
        
            z1.push_back(g.getVolume());
            z2.push_back(g.getVolatility());
            z3.push_back(g.getPredictability());
        
            c.push_back(g.getCustom());
        
            vector <double> temp;
            for (int j=0; j<Str; j++) {
                temp.push_back(g.getDevotion(j));
            }
            y.push_back(temp);
        
        vector<int> OB = g.getOB();
        vector<int> V = g.getV();
        printCustomObservation(OB, V);
        }
        
    }
    observe();
    printObservation();
}
    
private: void printCustomObservation(vector<int> OB, vector<int> V) {
    int L = OB.size();
    for (int i=0; i<L;i++) {
        cout << setw(5) << i << " " << setw(4) << OB[i] << " " << setw(4) << V[i] << endl;
    }
}
    
private: void observe() {
    
    GainS = vectorAverage(x1);
    GainP = vectorAverage(x2);
    
    Volume = vectorAverage(z1);
    Volatility = vectorAverage(z2);
    Predictability = vectorAverage(z3);
        
    
    for (int i=0; i<Str; i++) {
        vector<double> x;
        for (int j=0; j<G; j++) {
            x.push_back(y[j][i]);
        }
        Devotion.push_back(vectorAverage(x));
    }
    
    int x = c[0][0];
    int y = c[0][1];
    for (int j=1; j<G; j++) {
        if (c[j][0] > x) {
            x = c[j][0];
        }
        if (c[j][1] > y) {
            y = c[j][1];
        }
    }
    custom.push_back(x);
    custom.push_back(y);
}
    
private: void printObservation() {
    cout << endl << "Average Observation" << endl;
    cout << "Ns: " << Ns << " Np: " << Np << " p: " << p << " epsilon: " << epsilon << endl;
    cout << "Gain Speculators: " << GainS << endl;
    cout << "Gain Producers: " << GainP << endl;
    for (int i=0; i<Str; i++) {
        cout << "Frozen to S" << i + 1 << ": " << Devotion[i] << endl;
    }
    cout << "Volume: " << Volume << endl;
    cout << "Volatility: " << Volatility << endl;
    cout << "Predictability: " << Predictability << endl;
    
    cout << "SpreadV: " << custom[0] << " SpreadOB: " << custom[1] << endl;
    
    cout << endl;
}
    
};
