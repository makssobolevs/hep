#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <future>
//#include <prng.h>

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

typedef uniform_real_distribution<double> rand_dist;

typedef decltype(chrono::system_clock::now()) TimePoint;
double timeCalculation(TimePoint t1, TimePoint t2);


pair<double,double> s2range(double sqrtS)
{
    return make_pair(mz*mz,(sqrtS-m)*(sqrtS-m));
}


double (*mi[])(double, double, double, double) = {m6, m2, m3, m4, m5, m1, m7, m8, m9};


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


random_device rd;
 
void f_thread(double s, double (*func)(double, double, double, double),
        rand_dist disS1, rand_dist disS2, rand_dist disT1,
        mt19937::result_type seed, promise<pair<double, int>> pr){
    double sum = 0;
    int points_cought = 0;
    mt19937 gen(rd());
    gen.seed(seed);
    for (int i = 0; i < POINT_NUMBER; i++){
        double s2rand = disS2(gen);
        double s1rand = disS1(gen);
        double t1rand = disT1(gen);
        double valueG1 = gg(s,t1rand,s2rand,m*m,0,m*m);
        //valueG1++;
        //ofstream st("thread2.txt", std::ios_base::app);
        //st << i << " " << s1rand << " " << s2rand << "\n";
        //st.close();
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        if (valueG1 < 0 && t1rand < t1plus(s, s2rand) && t1rand > t1minus(s, s2rand)) {
            double x = (*func)(s,s1rand,s2rand,t1rand);
            if (!std::isnan(x)){
                sum += x;
                points_cought++;
            }
            //else {
            //}
        }
    }
    pr.set_value(make_pair(sum, points_cought));
}

void  f_thread_1(double s, rand_dist disS1, rand_dist disS2, rand_dist disT1,
        mt19937::result_type seed, promise<pair<double, int>> p){
    f_thread(s, matrixEl_terms1, disS1, disS2, disT1, seed, std::move(p));
    cout << "thread 1 finished" << endl;
}

void f_thread_2(double s, rand_dist disS1, rand_dist disS2, rand_dist disT1,
        mt19937::result_type seed, promise<pair<double, int>> p){
    f_thread(s, matrixEl_terms2, disS1, disS2, disT1, seed, std::move(p));
    cout << "thread 2 finished" << endl;
}


int main(){
    double sqrtS = 100;
    double finalSqrtS = 300;
    double d_sqrtS = 10;

    ofstream fout(outName);
    fout.close();

    while (sqrtS < finalSqrtS) {
        TimePoint time1 = chrono::system_clock::now();

        double s = sqrtS*sqrtS;

        double S1_start = 2;//m*m;
        double S1_finish = (sqrtS-mz)*(sqrtS-mz);

        double S2_start = s2range(sqrtS).first;
        double S2_finish = s2range(sqrtS).second;

        double T1_start = t1minus(s,S2_start);
        rand_dist disS1(S1_start,S1_finish);
        rand_dist disS2(S2_start, S2_finish);
        rand_dist disT1(T1_start,0);
        long double volume1 = abs(S1_finish - S1_start) * abs(S2_finish - S2_start);
        volume1 *= abs(T1_start);
        mt19937::result_type seed = chrono::high_resolution_clock::now().time_since_epoch().count();

        std::promise<pair<double, int>> sum1;
        std::promise<pair<double, int>> sum2;
        std::future<pair<double, int>> fsum1 = sum1.get_future();
        std::future<pair<double, int>> fsum2 = sum2.get_future();

        thread thread1(f_thread_1, s,disS1, disS2, disT1, seed, std::move(sum1));
        thread thread2(f_thread_2, s,disS1, disS2, disT1, seed, std::move(sum2));
        fsum1.wait();
        fsum2.wait();
        auto result1 = fsum1.get();
        auto result2 = fsum2.get();
        thread1.join();
        thread2.join();

        double sum = result1.first + result2.first;
        int points_cought = result1.second + result2.second;

        ofstream fout(outName,std::ios_base::app);
        fout << sqrtS << ' ' << (sum* volume1*points_cought)/(POINT_NUMBER*s*s) << '\n';
        fout.close();

        TimePoint time2 = chrono::system_clock::now();
        double workTime = timeCalculation(time1, time2);

        cout << sqrtS << " " << points_cought << " " << workTime << endl; 

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
