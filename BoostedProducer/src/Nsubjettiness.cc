#include "BoostedTTH/BoostedProducer/interface/Nsubjettiness.h"

FASTJET_BEGIN_NAMESPACE

Nsubjettiness::Nsubjettiness(int N, Njettiness::AxesMode mode, double beta, double R0, double Rcutoff)
  : _N(N), _njettinessFinder(mode, NsubParameters(beta, R0, Rcutoff))
{}


Double32_t Nsubjettiness::result(const PseudoJet& jet) const
{
   std::vector<fastjet::PseudoJet> particles = jet.constituents();
   return _njettinessFinder.getTau(_N, particles);
}

FASTJET_END_NAMESPACE
