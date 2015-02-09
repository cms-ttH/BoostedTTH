//  Njettiness Package
//  Version 0.5.1 (September 19, 2012)
//  Questions/Comments?  jthaler@jthaler.net

// Copyright (c) 2011-12, Jesse Thaler, Ken Van Tilburg, and Christopher K.
// Vermilion
//
//----------------------------------------------------------------------
// This file is part of the N-jettiness package ("N-jettiness").
//
//  N-jettiness is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 3 of the License, or
//  (at your option) any later version.
//
//  SpartyJet is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with SpartyJet; if not, write to the Free Software
//  Foundation, Inc.:
//      59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//----------------------------------------------------------------------


#ifndef __NJETTINESS_HH__
#define __NJETTINESS_HH__


#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
#include <cmath>
#include <vector>
#include <list>

FASTJET_BEGIN_NAMESPACE      // defined in fastjet/internal/base.hh
///////
//
// Parameter classes
//
///////


inline double sq(double x) {return x*x;}

// Parameters that define Njettiness
class NsubParameters {
private:
   double _beta;  // angular weighting exponent
   double _R0;    // characteristic jet radius (for normalization)
   double _Rcutoff;  // Cutoff scale for cone jet finding (default is large number such that no boundaries are used)

public:
   NsubParameters(const double mybeta, const double myR0, const double myRcutoff=10000.0) :
   _beta(mybeta), _R0(myR0), _Rcutoff(myRcutoff) {}
   double beta() const {return _beta;}
   double R0() const {return _R0;}
   double Rcutoff() const {return _Rcutoff;}
};

// Parameters that define GeometricMeasure
class NsubGeometricParameters {
private:
   double _Rcutoff;  // Cutoff scale for cone jet finding (default is large number such that no boundaries are used)

public:
   NsubGeometricParameters(const double myRcutoff=10000.0) : _Rcutoff(myRcutoff) {}
   double Rcutoff() const {return _Rcutoff;}
};




// Parameters that change minimization procedure.
// Set automatically when you choose NsubAxesMode, but can be adjusted manually as well
class KmeansParameters {
private:
   int _n_iterations;  // Number of iterations to run  (0 for no minimization, 1 for one-pass, >>1 for global minimum)
   double _precision;  // Desired precision in axes alignment
   int _halt;          // maximum number of steps per iteration
   double _noise_range;// noise range for random initialization

public:
   KmeansParameters() : _n_iterations(0), _precision(0.0), _halt(0), _noise_range(0.0) {}
   KmeansParameters(const int my_n_iterations, double my_precision, int my_halt, double my_noise_range) :
   _n_iterations(my_n_iterations),  _precision(my_precision), _halt(my_halt), _noise_range(my_noise_range) {}
   int n_iterations() const { return _n_iterations;}
   double precision() const {return _precision;}
   int halt() const {return _halt;}
   double noise_range() const {return _noise_range;}
};


///////
//
// Measure Functor
//
///////


class MeasureFunctor {

   protected:
      MeasureFunctor() {}

   public:
      virtual ~MeasureFunctor() {}
      virtual bool doCluster(const fastjet::PseudoJet& particle, const fastjet::PseudoJet& axis) = 0;
      virtual double distance(const fastjet::PseudoJet& particle, const fastjet::PseudoJet& axis) = 0;
      virtual double numerator(const fastjet::PseudoJet& particle, const fastjet::PseudoJet& axis) = 0;
      virtual double denominator(const fastjet::PseudoJet& particle) = 0;

      std::vector<double> subTaus(const std::vector <fastjet::PseudoJet> & particles, const std::vector<fastjet::PseudoJet>& axes);
      double tau(const std::vector <fastjet::PseudoJet>& particles, const std::vector<fastjet::PseudoJet>& axes);

};

///Default Measure (includes normalization)
class DefaultMeasure : public MeasureFunctor {

   private:
      NsubParameters _paraNsub;

   public:
      DefaultMeasure(NsubParameters paraNsub): _paraNsub(paraNsub) {}

      virtual bool doCluster(const fastjet::PseudoJet& particle, const fastjet::PseudoJet& axis) {
         return (distance(particle,axis) <= _paraNsub.Rcutoff());
      }

      virtual double distance(const fastjet::PseudoJet& particle, const fastjet::PseudoJet& axis) {
         return std::sqrt(particle.squared_distance(axis));
      }

      virtual double numerator(const fastjet::PseudoJet& particle, const fastjet::PseudoJet& axis) {
         double deltaR = std::sqrt(particle.squared_distance(axis));
         if (deltaR > _paraNsub.Rcutoff()) deltaR = _paraNsub.Rcutoff();
         return particle.perp() * std::pow(deltaR,_paraNsub.beta());
      }

      virtual double denominator(const fastjet::PseudoJet& particle) {
         return particle.perp() * std::pow(_paraNsub.R0(),_paraNsub.beta());
      }

};

///Geometric Measure (includes normalization)
class GeometricMeasure : public MeasureFunctor {

   private:
      double _Rcutoff;

      // create light-like axis
      fastjet::PseudoJet lightFrom(const fastjet::PseudoJet& input) const {
         double length = sqrt(pow(input.px(),2) + pow(input.py(),2) + pow(input.pz(),2));
         return fastjet::PseudoJet(input.px()/length,input.py()/length,input.pz()/length,1.0);
      }

      // get Q value
      double qValueOf(const fastjet::PseudoJet& input) const {
         return lightFrom(input).pt();
      }

   public:
      GeometricMeasure(double Rcutoff) : _Rcutoff(Rcutoff) {}

      virtual bool doCluster(const fastjet::PseudoJet& particle, const fastjet::PseudoJet& axis) {
         return (distance(particle,axis) <= _Rcutoff);
      }

      virtual double distance(const fastjet::PseudoJet& particle, const fastjet::PseudoJet& axis) {
         double axisValue = 2.0*dot_product(lightFrom(axis),particle)/qValueOf(axis);
         double beamValue = particle.pt();
         double pseudoR = std::sqrt(axisValue/beamValue);
         return pseudoR;
      }

      virtual double numerator(const fastjet::PseudoJet& particle, const fastjet::PseudoJet& axis) {
         double pseudoR = distance(particle,axis);

         if (pseudoR > _Rcutoff) {
            pseudoR = _Rcutoff;
         }
         return particle.pt()*sq(pseudoR);
      }

      virtual double denominator(const fastjet::PseudoJet& particle) {
         return 1.0;
      }
};



///////
//
// Axes Finder Options
//
///////

class AxesFinder {

   protected:
      AxesFinder() {}

   public:
      virtual ~AxesFinder() {}
      virtual std::vector<fastjet::PseudoJet> getAxes(int n_jets, const std::vector<fastjet::PseudoJet> & inputs, const std::vector<fastjet::PseudoJet>& currentAxes) = 0;

};

/// Axes From Exclusive Jets

class AxesFinderFromExclusiveJetDefinition : public AxesFinder {

   private:
      fastjet::JetDefinition _def;

   public:
      AxesFinderFromExclusiveJetDefinition(fastjet::JetDefinition def) : _def(def) {}

      virtual std::vector<fastjet::PseudoJet> getAxes(int n_jets, const std::vector <fastjet::PseudoJet> & inputs, const std::vector<fastjet::PseudoJet>& currentAxes) {
         fastjet::ClusterSequence jet_clust_seq(inputs, _def);
         return jet_clust_seq.exclusive_jets(n_jets);
      }
};

class AxesFinderFromKT : public AxesFinderFromExclusiveJetDefinition {
   public:
      AxesFinderFromKT() : AxesFinderFromExclusiveJetDefinition(fastjet::JetDefinition(fastjet::kt_algorithm,M_PI/2.0,fastjet::E_scheme,fastjet::Best)) {}
};

class AxesFinderFromCA : public AxesFinderFromExclusiveJetDefinition {
   public:
      AxesFinderFromCA() : AxesFinderFromExclusiveJetDefinition(fastjet::JetDefinition(fastjet::cambridge_algorithm,M_PI/2.0,fastjet::E_scheme,fastjet::Best)) {}
};


/// Axes From Hardest Jets

class AxesFinderFromHardestJetDefinition : public AxesFinder {

   private:
      fastjet::JetDefinition _def;

   public:
      AxesFinderFromHardestJetDefinition(fastjet::JetDefinition def) : _def(def) {}

      virtual std::vector<fastjet::PseudoJet> getAxes(int n_jets, const std::vector <fastjet::PseudoJet> & inputs, const std::vector<fastjet::PseudoJet>& currentAxes) {
         fastjet::ClusterSequence jet_clust_seq(inputs, _def);
         std::vector<fastjet::PseudoJet> myJets = sorted_by_pt(jet_clust_seq.inclusive_jets());
         myJets.resize(n_jets);  // only keep n hardest
         return myJets;
      }
};


class AxesFinderFromAntiKT : public AxesFinderFromHardestJetDefinition {
   public:
      AxesFinderFromAntiKT(double R0) : AxesFinderFromHardestJetDefinition(fastjet::JetDefinition(fastjet::antikt_algorithm,R0,fastjet::E_scheme,fastjet::Best)) {}
};


/// Manual Axes

class AxesFinderFromUserInput : public AxesFinder {

   public:
      AxesFinderFromUserInput() {}

      virtual std::vector<fastjet::PseudoJet> getAxes(int n_jets, const std::vector <fastjet::PseudoJet> & inputs, const std::vector<fastjet::PseudoJet>& currentAxes) {
         assert(currentAxes.size() == (unsigned)n_jets);
         return currentAxes;
      }
};

/// Minimum Axes

std::vector<fastjet::PseudoJet> GetMinimumAxes(const std::vector <fastjet::PseudoJet> & seedAxes, const std::vector <fastjet::PseudoJet> & inputJets, KmeansParameters para,
                                          NsubParameters paraNsub, MeasureFunctor* functor);
class AxesFinderFromKmeansMinimization : public AxesFinder {

   private:
      AxesFinder* _startingFinder;
      KmeansParameters _paraKmeans;
      NsubParameters _paraNsub;

      MeasureFunctor* _functor;

   public:
      AxesFinderFromKmeansMinimization(AxesFinder* startingFinder, KmeansParameters paraKmeans, NsubParameters paraNsub)
         : _startingFinder(startingFinder), _paraKmeans(paraKmeans), _paraNsub(paraNsub) {
         _functor = new DefaultMeasure(paraNsub);
      }

      ~AxesFinderFromKmeansMinimization() { delete _functor;}

      virtual std::vector<fastjet::PseudoJet> getAxes(int n_jets, const std::vector <fastjet::PseudoJet> & inputs, const std::vector<fastjet::PseudoJet>& currentAxes) {
         std::vector<fastjet::PseudoJet> seedAxes = _startingFinder->getAxes(n_jets, inputs, currentAxes);
         return GetMinimumAxes(seedAxes, inputs, _paraKmeans, _paraNsub,_functor);
      }
};


class AxesFinderFromGeometricMinimization : public AxesFinder {

   private:
      AxesFinder* _startingFinder;
      MeasureFunctor* _functor;
      double _Rcutoff;
      double _nAttempts;
      double _accuracy;


   public:
      AxesFinderFromGeometricMinimization(AxesFinder* startingFinder, double Rcutoff) : _startingFinder(startingFinder), _Rcutoff(Rcutoff) {
         _nAttempts = 100;
         _accuracy = 0.000000001;
         _functor = new GeometricMeasure(_Rcutoff);
      }

      ~AxesFinderFromGeometricMinimization() { delete _functor;}

      virtual std::vector<fastjet::PseudoJet> getAxes(int n_jets, const std::vector <fastjet::PseudoJet> & particles, const std::vector<fastjet::PseudoJet>& currentAxes) {

         std::vector<fastjet::PseudoJet> seedAxes = _startingFinder->getAxes(n_jets, particles, currentAxes);
         double seedTau = _functor->tau(particles,seedAxes);

         for (int i = 0; i < _nAttempts; i++) {

            std::vector<fastjet::PseudoJet> newAxes(seedAxes.size(),fastjet::PseudoJet(0,0,0,0));

            for (unsigned int i = 0; i < particles.size(); i++) {
               double minDist = 100000000.0; //large number
               int minJ = -1; //bad ref
               for (unsigned int j = 0; j < seedAxes.size(); j++) {
                  double tempDist = _functor->distance(particles[i],seedAxes[j]);
                  if (tempDist < minDist) {
                     minDist = tempDist;
                     minJ = j;
                  }
               }

               if (_functor->doCluster(particles[i],seedAxes[minJ])) {
                  newAxes[minJ] += particles[i];
               }
            }

            seedAxes = newAxes;


            double tempTau = _functor->tau(particles,newAxes);

//            std::cout << seedTau << " " << tempTau << " " << fabs(tempTau - seedTau) << " " << _accuracy << " " << (fabs(tempTau - seedTau) < _accuracy) << true << std::endl;

            if (fabs(tempTau - seedTau) < _accuracy) break;
            seedTau = tempTau;
         }

         return seedAxes;
      }
};


// Helper class for minimization
class LightLikeAxis {
private:
   double _rap, _phi, _weight, _mom;

   double DistanceSq(double rap2, double phi2) const {
      double rap1 = _rap;
      double phi1 = _phi;

      double distRap = rap1-rap2;
      double distPhi = std::fabs(phi1-phi2);
      if (distPhi > M_PI) {distPhi = 2.0*M_PI - distPhi;}
      return sq(distRap) + sq(distPhi);
   }

   double Distance(double rap2, double phi2) const {
      return std::sqrt(DistanceSq(rap2,phi2));
   }


public:
   LightLikeAxis() : _rap(0.0), _phi(0.0), _weight(0.0), _mom(0.0) {}
   LightLikeAxis(double my_rap, double my_phi, double my_weight, double my_mom) :
   _rap(my_rap), _phi(my_phi), _weight(my_weight), _mom(my_mom) {}
   double rap() const {return _rap;}
   double phi() const {return _phi;}
   double weight() const {return _weight;}
   double mom() const {return _mom;}
   void set_rap(double my_set_rap) {_rap = my_set_rap;}
   void set_phi(double my_set_phi) {_phi = my_set_phi;}
   void set_weight(double my_set_weight) {_weight = my_set_weight;}
   void set_mom(double my_set_mom) {_mom = my_set_mom;}
   void reset(double my_rap, double my_phi, double my_weight, double my_mom) {_rap=my_rap; _phi=my_phi; _weight=my_weight; _mom=my_mom;}



   double DistanceSq(const fastjet::PseudoJet& input) const {
      return DistanceSq(input.rap(),input.phi());
   }

   double Distance(const fastjet::PseudoJet& input) const {
      return std::sqrt(DistanceSq(input));
   }

   double DistanceSq(const LightLikeAxis& input) const {
      return DistanceSq(input.rap(),input.phi());
   }

   double Distance(const LightLikeAxis& input) const {
      return std::sqrt(DistanceSq(input));
   }

};

///////
//
// Functions for minimization.
// TODO:  Wrap these in N-subjettiness class
//
///////


// Given starting axes, update to find better axes
template <int N>
std::vector<LightLikeAxis> UpdateAxesFast(const std::vector <LightLikeAxis> & old_axes,
                                  const std::vector <fastjet::PseudoJet> & inputJets,
					  NsubParameters paraNsub, double precision);

// Given starting axes, update to find better axes
// (This is just a wrapper for the templated version above.)
std::vector<LightLikeAxis> UpdateAxes(const std::vector <LightLikeAxis> & old_axes,
                                      const std::vector <fastjet::PseudoJet> & inputJets, NsubParameters paraNsub, double precision);

// Go from internal LightLikeAxis to PseudoJet
// TODO:  Make part of LightLikeAxis class.
std::vector<fastjet::PseudoJet> ConvertToPseudoJet(const std::vector <LightLikeAxis>& axes);

// Get minimization axes
std::vector<fastjet::PseudoJet> GetMinimumAxes(const std::vector <fastjet::PseudoJet> & seedAxes, const std::vector <fastjet::PseudoJet> & inputJets, KmeansParameters para,
					       NsubParameters paraNsub,MeasureFunctor* functor);
///////
//
// Main Njettiness Class
//
///////

class Njettiness {
public:
   enum AxesMode {
      kt_axes,  // exclusive kt axes
      ca_axes,  // exclusive ca axes
      antikt_0p2_axes,  // inclusive hardest axes with antikt-0.2
      min_axes, // axes that minimize N-subjettiness (100 passes by default)
      manual_axes, // set your own axes with setAxes()
      onepass_kt_axes, // one-pass minimization from kt starting point
      onepass_ca_axes, // one-pass minimization from ca starting point
      onepass_antikt_0p2_axes,  // one-pass minimization from antikt-0.2 starting point
      onepass_manual_axes  // one-pass minimization from manual starting point
   };

private:
   MeasureFunctor* _functor;
   AxesFinder* _axesFinder;

   std::vector<fastjet::PseudoJet> _currentAxes;
   std::vector<double> _currentTaus;
   double _currentTau;

   void establishAxes(unsigned n_jets, const std::vector <fastjet::PseudoJet> & inputs);
   void establishTaus(const std::vector <fastjet::PseudoJet> & inputs);

public:
   Njettiness(MeasureFunctor* functor, AxesFinder* axesFinder) : _functor(functor), _axesFinder(axesFinder) {}

   Njettiness(AxesMode axes, NsubParameters paraNsub);
   Njettiness(NsubGeometricParameters paraGeo);

   ~Njettiness();

   void setMeasureFunctor(MeasureFunctor* newFunctor) {_functor = newFunctor;}
   void setAxesFinder(AxesFinder* newAxesFinder) {_axesFinder = newAxesFinder;}

   // setAxes for Manual mode
   void setAxes(std::vector<fastjet::PseudoJet> myAxes) {
//      assert((_axes == manual_axes) || (_axes == onepass_manual_axes));
      _currentAxes = myAxes;
   }

   // The value of N-subjettiness
   double getTau(unsigned n_jets, const std::vector<fastjet::PseudoJet> & inputJets) {
      if (inputJets.size() <= n_jets) {
         _currentAxes = inputJets;
         _currentAxes.resize(n_jets,fastjet::PseudoJet(0.0,0.0,0.0,0.0));
         return 0.0;
      }
      establishAxes(n_jets, inputJets);  // sets current Axes
      establishTaus(inputJets); // sets current Tau Values

      return _currentTau;
   }

   // get axes used by getTau.
   std::vector<fastjet::PseudoJet> currentAxes() {
      return _currentAxes;
   }

   // get subTau values calculated in getTau.
   std::vector<double> currentTaus() {
      return _currentTaus;
   }

   // get total Tau value calculated in getTau.
   double currentTau() {
      return _currentTau;
   }

   // partition inputs by Voronoi (each vector stores indices corresponding to inputJets)
   std::vector<std::list<int> > getPartition(const std::vector<fastjet::PseudoJet> & inputJets);

   // partition inputs by Voronoi
   std::vector<fastjet::PseudoJet> getJets(const std::vector<fastjet::PseudoJet> & inputJets);

};
FASTJET_END_NAMESPACE      // defined in fastjet/internal/base.hh
#endif

