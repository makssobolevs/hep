#include "definitions.h"

double a(double s, double s2) 
{
	return (pow(m,4) - 2*m*m*s + s*s - 2*m*m*s2 - 2*s*s2 + s2*s2)/16;
}

double b(double s, double s1, double s2, double t1) 
{
	return (2*pow(m,4)*s2 + 4*m*m*mz*mz*s2 - 2*m*m*s*s2 - 2*m*m*s1*s2
	+ 2*s*s1*s2 - 2*m*m*s2*s2 - 2*s1*s2*s2 +
	2*m*m*mz*mz*t1 + 2*m*m*s*t1 + 2*mz*mz*s*t1 -
	2*s*s*t1 - 2*m*m*s1*t1 + 2*s*s1*t1 - 2*mz*mz*s2*t1
	+ 2*s*s2*t1 + 2*s1*s2*t1)/16;
}

double c(double s, double s1, double s2, double t1) 
{
	return (pow(m,4)*s2*s2)/16 - (m*m*s1*s2*s2)/8 + (s1*s1*s2*s2)/16 -
	(pow(m,4)*mz*mz*t1)/4 - (m*m*pow(mz,4)*t1)/4 +
	(m*m*mz*mz*s*t1)/4 + (m*m*mz*mz*s1*t1)/4 -
	(mz*mz*s*s1*t1)/4 + (m*m*mz*mz*s2*t1)/8 -
	(m*m*s*s2*t1)/8 + (m*m*s1*s2*t1)/8 +
	(mz*mz*s1*s2*t1)/8 + (s*s1*s2*t1)/8 -
	(s1*s1*s2*t1)/8 + (pow(mz,4)*t1*t1)/16 -
	(mz*mz*s*t1*t1)/8 + (s*s*t1*t1)/16 -
	(mz*mz*s1*t1*t1)/8 - (s*s1*t1*t1)/8 +
	(s1*s1*t1*t1)/16;
}



double lambda(double x, double y, double z)
{
    return sqrt((x-y-z)*(x-y-z)-4*y*z);
}

double x1(double s1, double t1)
{
    return m*m - s1 - t1;
}

double x2(double s, double s1)
{
    return mz*mz-s+s1;
}


double t1plus(double s, double s2){
    return 2*m*m - ((m*m+s)*(m*m+s-s2)-lambda(s,m*m,0)*lambda(s,s2,m*m))/(2*s);
}

double t1minus(double s, double s2){
    return 2*m*m - ((m*m+s)*(m*m+s-s2)+lambda(s,m*m,0)*lambda(s,s2,m*m))/(2*s);
}

double t2plus(double s2, double t1) {
    return mz*mz + (lambda(s2,mz*mz,0)*lambda(s2,0,t1))/(2*s2) - ((mz*mz+s2)*(s2-t1))/(2*s2); 
}

double t2minus(double s2, double t1) {
    return mz*mz - (lambda(s2,mz*mz,0)*lambda(s2,0,t1))/(2*s2) - ((mz*mz+s2)*(s2-t1))/(2*s2); 
}

double gg(double x, double y, double z, double u, double v, double w){
    return x*x*y + x*y*y + z*z*u + z*u*u + v*v*w + v*w*w + x*z*w +
  x*u*v  +  y*z*w  +   y*u*w  -  x*y*(z + u + v + w) -
  z*u*(x + y + v + w) -  v*w*(x + y + z + u);

}
