//==========================================================================
// This file has been automatically generated for C++ Standalone by
// MadGraph5_aMC@NLO v. 2.2.3, 2015-02-10
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#ifndef MG5_Sigma_sm_gg_ttxh_H
#define MG5_Sigma_sm_gg_ttxh_H

#include <complex> 
#include <vector> 

#include "BoostedTTH/MatrixElements/interface/Parameters_sm.h"
#include "BoostedTTH/MatrixElements/interface/HelAmps_sm.h"

//==========================================================================
// A class for calculating the matrix elements for
// Process: g g > t t~ h WEIGHTED=4
//--------------------------------------------------------------------------

class tthProcess
{
  public:

    // Constructor.
    tthProcess() {}

    // Initialize process.
    virtual void initProc(std::string param_card_name); 

    // Calculate flavour-independent parts of cross section.
    virtual void sigmaKin(); 

    // Evaluate sigmaHat(sHat).
    virtual double sigmaHat(); 

    // Info on the subprocess.
    virtual std::string name() const {return "g g > t t~ h (sm)";}

    virtual int code() const {return 0;}

    const std::vector<double> & getMasses() const {return mME;}

    // Get and set momenta for matrix element evaluation
    std::vector < double * > getMomenta(){return p;}
    void setMomenta(std::vector < double * > & momenta){p = momenta;}
    void setInitial(int inid1, int inid2){id1 = inid1; id2 = inid2;}

    // Get matrix element vector
    const double * getMatrixElements() const {return matrix_element;}

    // Constants for array limits
    static const int ninitial = 2; 
    static const int nexternal = 5; 
    static const int nprocesses = 1; 

  private:

    // Private functions to calculate the matrix element for all subprocesses
    // Calculate wavefunctions
    void calculate_wavefunctions(const int perm[], const int hel[]); 
    static const int nwavefuncs = 12; 
    std::complex<double> w[nwavefuncs][18]; 
    static const int namplitudes = 8; 
    std::complex<double> amp[namplitudes]; 
    double matrix_gg_ttxh(); 

    // Store the matrix element value from sigmaKin
    double matrix_element[nprocesses]; 

    // Color flows, used when selecting color
    double * jamp2[nprocesses]; 

    // Pointer to the model parameters
    Parameters_sm * pars; 

    // vector with external particle masses
    std::vector<double> mME; 

    // vector with momenta (to be changed each event)
    std::vector < double * > p; 
    // Initial particle ids
    int id1, id2; 

}; 


#endif  // MG5_Sigma_sm_gg_ttxh_H
