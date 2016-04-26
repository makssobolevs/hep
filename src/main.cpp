#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <chrono>

#include <signal.h>

#include "m1.h"
#include "m2.h"
#include "m3.h"
#include "m4.h"
#include "m5.h"
#include "m6.h"
#include "m7.h"
#include "m8.h"
#include "m9.h"
#include "definitions.h"

#define POINT_NUMBER 100000

#define MI_NUMBER 9

using namespace std;

string outName = "output.dat";

typedef uniform_real_distribution<> rand_dist;

typedef decltype(chrono::system_clock::now()) TimePoint;
double timeCalculation(TimePoint t1, TimePoint t2);


pair<double,double> s2range(double sqrtS)
{
    return make_pair(mz*mz,(sqrtS-m)*(sqrtS-m));
}


double (*mi[])(double, double, double, double) = {m1, m2, m3, m4, m5, m6, m7, m8, m9};

double matrixEl_terms(int k1, int k2, double s, double s1, double s2, double t1){
    double answer = 0;
    for (int i = k1; i < k2; ++i) {
        answer += (*mi[i])(s, s1, s2, t1);       
    }
    return 8*(ga + gv)*answer;

}

double matrixEl_terms1(double s, double s1, double s2, double t1){
    return matrixEl_terms(0, 5, s, s1, s2, t1);
}

double matrixEl_terms2(double s, double s1, double s2, double t1){
    return matrixEl_terms(5, 9, s, s1, s2, t1);
}

double matrixEl(double s, double s1, double s2, double t1){
    return matrixEl_terms(0, 9, s, s1, s2, t1);
}




int main(){
    double sqrtS = 100;
    double finalSqrtS = 300;
    double d_sqrtS = 10;

    random_device rd;
    mt19937 gen(rd());
    double x = 0;
    ofstream fout(outName);
    int real_point_n = POINT_NUMBER;
    fout.close();


    while (sqrtS < finalSqrtS) {
        TimePoint time1 = chrono::system_clock::now();

        double s = sqrtS*sqrtS;
        long double sum = 0;
        int points_cought = 0;

        double S1_start = 2;//m*m
        double S1_finish = (sqrtS-mz)*(sqrtS-mz);

        double S2_start = s2range(sqrtS).first;
        double S2_finish = s2range(sqrtS).second;

        double T1_start = t1minus(s,S2_start);
        rand_dist disS1(S1_start,S1_finish);
        rand_dist disS2(S2_start, S2_finish);
        rand_dist disT1(T1_start,0);
        long double volume1 = abs(S1_finish - S1_start) * abs(S2_finish - S2_start);
        volume1 *= abs(T1_start);
        //ofstream tout("test.dat");
        for (int i = 0; i < POINT_NUMBER; i++){
            double s2rand = disS2(gen);
            double s1rand = disS1(gen);
            double t1rand = disT1(gen);
            double valueG1 = gg(s,t1rand,s2rand,m*m,0,m*m);
            if (valueG1 < 0 && t1rand < t1plus(s, s2rand) && t1rand > t1minus(s, s2rand)) {
                x = matrixEl(s,s1rand,s2rand,t1rand);
                if (!std::isnan(x)){
                    sum += x;
                    points_cought++;
                }
            }
        }

        ofstream fout(outName,std::ios_base::app);
        fout << sqrtS << ' ' << (sum* volume1 *points_cought)/(POINT_NUMBER*s*s) << '\n';
        fout.close();

        TimePoint time2 = chrono::system_clock::now();
        double workTime = timeCalculation(time1, time2);

        cout << sqrtS << " "  << " " << workTime << endl; 

        sqrtS += d_sqrtS;
    }

    return 0;
}

double  timeCalculation(TimePoint t1, TimePoint t2){
    std::chrono::duration<float> dt = t2 - t1;
    //std::chrono::milliseconds d = std::chrono::duration_cast<std::chrono::milliseconds>(dt);
    //cout << dt.count() << " сек \n";
    //cout << d.count() << " мсек \n";
    return dt.count();
}
//void printSRange(double sqrtS) {
//    cout << m*m <<" < s1 < " << (sqrtS-mz)*(sqrtS-mz) << endl;
//    cout << s2range(sqrtS*sqrtS).first <<" < s2 < " << s2range(sqrtS*sqrtS).second << endl;
//}
//
//    printSRange(s);
//
//    double s1 = 40;
//
//    double s2 = 9000;
//
//    auto s2canBe = s2range(s);
//    if (s2 > s2canBe.second || s2 < s2canBe.first) {
//        cout << "s2 not in range. Exit.";
//        return 0;
//    }
//
//    cout << t1minus(s,s2) <<" < t1 < " << t1plus(s,s2) << endl;
//
//    double t1 = -500;
//
//    cout << matrixEl(s, s1, s2, t1) << endl;
