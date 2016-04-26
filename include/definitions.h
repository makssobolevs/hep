#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include <cmath>

//const double m = 0.510998928e-3;
const double m = 0;

const double mz = 91.1876;

const double ga = -0.5;

const double gv = -0.0206;

double a(double s, double s1); 
double b(double s, double s1, double s2, double t1); 
double c(double s, double s1, double s2, double t1); 
double lambda(double x, double y, double z);
double x1(double s1, double t1);
double x2(double s, double s1);
double t1plus(double s, double s2);
double t1minus(double s, double s2);
double t2plus(double s2, double t1);
double t2minus(double s2, double t1);
double gg(double x, double y, double z, double u, double v, double w);
//double matrixEl(double s, double s1, double s2, double t1);

#endif //DEFINITIONS_H
