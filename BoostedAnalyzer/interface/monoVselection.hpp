#ifndef monoVselection_HPP
#define monoVselection_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"


class monoVselection: public Selection {

public:

	monoVselection(const edm::ParameterSet& iConfig);
	monoVselection(double minpt_, double maxeta_, double minPrunedMass_, double maxPrunedMass_, double maxtau21_chsPrun_, double minSoftDropMass_, double maxSoftDropMass_, double maxtau21_Puppi_);
	~monoVselection();
	void InitCutflow(Cutflow& cutflow);
	bool IsSelected(const InputCollections& input, Cutflow& cutflow);


private:
	double minpt, maxeta, minPrunedMass, maxPrunedMass, maxtau21_chsPrun, minSoftDropMass, maxSoftDropMass, maxtau21_Puppi;
	bool monoVtagged_ChsPrun;
	bool monoVtagged_PuppiSoftDrop;


};

#endif