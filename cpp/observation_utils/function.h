#ifndef function_h
#define function_h

using namespace std;

vector<vector<double> > returnDistributionPos(vector<double> a);
vector<vector<double> > returnDistributionNeg(vector<double> a);
vector<vector<double> > returnDistributionAbs(vector<double> a);
vector<vector<double> > returnDistributionNegInver(vector<double> a);
vector<vector<double> > volatility(vector<double> a,int w, bool prop, double lambda, bool exp);
vector<double> returns(vector<double> a);
vector<double> multiplyVector(vector<double> a, double x);
vector<double> getPart(vector<double> a, int begin, int end);
vector<vector<double> > clustering(vector<double> a, bool abs);
vector<vector<double> > clusteringInv(vector<double> a, bool abs);
vector<vector<double> > clusteringApprox(vector<double> a, bool abs);
void printMatrix(vector<vector<double> > a);
void printVector(vector<double> a);
void printValue(double a);
double mean(vector<double> a,int start, int end, int delay, bool abs);


#endif
