#include "games.cpp"
#include <math.h>


using namespace std;

void simulate(int Ns, int p) {
    Games g;
    g.initalize(Ns, p);
    g.simulate();
}

void iterate() {
    vector<double> eps = {-0.01};
    vector<int> p = {8};
    vector<int> Ns = {50};
    
    for (int a=0; a<eps.size(); a++) {
        for (int b=0; b<Ns.size(); b++) {
            for (int c=0; c<p.size(); c++) {
               // simulate(Ns[b],p[c],eps[a]);
            }
        }
    }
}

int main() {

    simulate(257, 128);
    
    return 0;
}
