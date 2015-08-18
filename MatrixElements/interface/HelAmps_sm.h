//==========================================================================
// This file has been automatically generated for C++ Standalone
// MadGraph5_aMC@NLO v. 2.2.3, 2015-02-10
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#ifndef HelAmps_sm_H
#define HelAmps_sm_H

#include <cmath> 
#include <complex> 

using namespace std; 

namespace MG5_sm 
{
double Sgn(double e, double f); 

void ixxxxx(double p[4], double fmass, int nhel, int nsf, std::complex<double>
    fi[6]);

void oxxxxx(double p[4], double fmass, int nhel, int nsf, std::complex<double>
    fo[6]);

void sxxxxx(double p[4], int nss, std::complex<double> sc[3]); 

void txxxxx(double p[4], double tmass, int nhel, int nst, std::complex<double>
    fi[18]);

void vxxxxx(double p[4], double vmass, int nhel, int nsv, std::complex<double>
    v[6]);

void FFV1_0(complex<double> F1[], complex<double> F2[], complex<double> V3[],
    complex<double> COUP, complex<double> & vertex);

void VVVV4_0(complex<double> V1[], complex<double> V2[], complex<double> V3[],
    complex<double> V4[], complex<double> COUP, complex<double> & vertex);

void FFV1P0_3(complex<double> F1[], complex<double> F2[], complex<double> COUP,
    double M3, double W3, complex<double> V3[]);

void VVVV1_0(complex<double> V1[], complex<double> V2[], complex<double> V3[],
    complex<double> V4[], complex<double> COUP, complex<double> & vertex);

void FFV1_2(complex<double> F1[], complex<double> V3[], complex<double> COUP,
    double M2, double W2, complex<double> F2[]);

void VVV1_0(complex<double> V1[], complex<double> V2[], complex<double> V3[],
    complex<double> COUP, complex<double> & vertex);

void FFV1_1(complex<double> F2[], complex<double> V3[], complex<double> COUP,
    double M1, double W1, complex<double> F1[]);

void VVVV3_0(complex<double> V1[], complex<double> V2[], complex<double> V3[],
    complex<double> V4[], complex<double> COUP, complex<double> & vertex);

void VVV1P0_1(complex<double> V2[], complex<double> V3[], complex<double> COUP,
    double M1, double W1, complex<double> V1[]);

void FFS4_0(complex<double> F1[], complex<double> F2[], complex<double> S3[],
    complex<double> COUP, complex<double> & vertex);

void FFS4_1(complex<double> F2[], complex<double> S3[], complex<double> COUP,
    double M1, double W1, complex<double> F1[]);

void FFS4_2(complex<double> F1[], complex<double> S3[], complex<double> COUP,
    double M2, double W2, complex<double> F2[]);

void FFS4_3(complex<double> F1[], complex<double> F2[], complex<double> COUP,
    double M3, double W3, complex<double> S3[]);


}  // end namespace MG5_sm

#endif  // HelAmps_sm_H
