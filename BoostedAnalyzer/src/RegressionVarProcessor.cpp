#include "BoostedTTH/BoostedAnalyzer/interface/RegressionVarProcessor.hpp"

using namespace std;

RegressionVarProcessor::RegressionVarProcessor(){}
RegressionVarProcessor::~RegressionVarProcessor(){}


void RegressionVarProcessor::Init(const InputCollections& input,VariableContainer& vars){

  //General Jet varibales
  vars.InitVars( "Jet_chargedMult","N_Jets" );
  vars.InitVars( "Jet_leadTrackPt","N_Jets" );
  vars.InitVars( "Jet_corr","N_Jets" );
  vars.InitVars( "Jet_rawPt","N_Jets" );
  vars.InitVars( "Jet_corr_rawJet","N_Jets" );

  //Vertex variables
  vars.InitVars( "Jet_vtxMass","N_Jets" );
  vars.InitVars( "Jet_vtx3DVal","N_Jets" );
  vars.InitVars( "Jet_vtxNtracks","N_Jets" );
  vars.InitVars( "Jet_vtx3DSig","N_Jets" );
  vars.InitVars( "Jet_vtxPt","N_Jets" );

  //Fraction variables
  vars.InitVars( "Jet_nHEFrac","N_Jets" );
  vars.InitVars( "Jet_cHEFrac","N_Jets" );
  vars.InitVars( "Jet_totHEFrac","N_Jets" );
  vars.InitVars( "Jet_nEmEFrac","N_Jets" );

  //Letpon variables
  vars.InitVars( "Jet_leptonPtRel","N_Jets" );
  vars.InitVars( "Jet_leptonPt","N_Jets" );
  vars.InitVars( "Jet_leptonEta","N_Jets" );
  vars.InitVars( "Jet_leptonDeltaR","N_Jets" );
  vars.InitVars( "Jet_NmatchedsoftLeptons","N_Jets"  );
  vars.InitVars( "Jet_NmatchedsoftElectrons", "N_Jets"  );
  vars.InitVars( "Jet_NmatchedsoftMuons","N_Jets" );
  
  bool stdreginit = false;
  bool addreginit = false;

  for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin() ; itJet != input.selectedJets.end(); ++itJet){
    //int iJet = itJet - input.selectedJets.begin();
    //cout << "cout: " << itJet->userFloatNames() << endl;
    
    for (  auto ituserfloat = (itJet->userFloatNames()).begin() ; ituserfloat != (itJet->userFloatNames()).end() ; ituserfloat++  ) {
      if (  (*ituserfloat).find("bregCorrection") != std::string::npos  ) {
	if(  (*ituserfloat) == "bregCorrection"  ) {

	  vars.InitVars( "Jet_regPt","N_Jets" );
	  vars.InitVars( "Jet_regcorr","N_Jets" );

	  stdreginit = true;
	  
	}
	else {
	  size_t found = (*ituserfloat).find("_");
	  string extention = (*ituserfloat).substr(found);

	  vars.InitVars( "Jet_regPt"+extention,"N_Jets" );
	  vars.InitVars( "Jet_regcorr"+extention,"N_Jets" );

	  extentions.push_back(extention);
	  
	  addreginit = true;
	}
      }//end: bregCorrectio* ? 
    }//end: userfloat loop
    if (  stdreginit || addreginit  ) {  //only loop as long the first regressed jet is found
      break; 
      }
  }//end: loop over jets

}


void RegressionVarProcessor::Process(const InputCollections& input, VariableContainer& vars) {
   
  for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin() ; itJet != input.selectedJets.end(); ++itJet){
    int iJet = itJet - input.selectedJets.begin();
    
    //General Jet varibales
    vars.FillVars( "Jet_chargedMult",iJet, itJet->chargedMultiplicity() );
    vars.FillVars( "Jet_leadTrackPt",iJet,itJet->userFloat("Jet_leadTrackPt") );
    vars.FillVars( "Jet_corr",  iJet, 1.0 / (itJet->jecFactor("Uncorrected") / itJet->jecFactor("L3Absolute")) );
    vars.FillVars( "Jet_rawPt",iJet,itJet->userFloat("Jet_rawPt") );
    vars.FillVars( "Jet_corr_rawJet",iJet,itJet->pt()/itJet->userFloat("Jet_rawPt") );

    //Vertex variables
    vars.FillVars( "Jet_vtxMass",iJet,itJet->userFloat("vtxMass") );
    vars.FillVars( "Jet_vtx3DVal",iJet,itJet->userFloat("vtx3DVal") );
    vars.FillVars( "Jet_vtxNtracks",iJet,itJet->userFloat("vtxNtracks") );
    vars.FillVars( "Jet_vtx3DSig",iJet,itJet->userFloat("vtx3DSig") );
    vars.FillVars( "Jet_vtxPt",iJet,sqrt( itJet->userFloat("vtxPx")*itJet->userFloat("vtxPx") + itJet->userFloat("vtxPy")*itJet->userFloat("vtxPy") ) );

    //Fraction variables
    vars.FillVars( "Jet_nHEFrac",iJet, itJet->neutralHadronEnergyFraction() );
    vars.FillVars( "Jet_cHEFrac",iJet, itJet->chargedHadronEnergyFraction() );
    if (  ( itJet->neutralHadronEnergyFraction() + itJet->neutralEmEnergyFraction() ) >= 1  ){
      vars.FillVars( "Jet_totHEFrac",iJet, 1);
    }
    else {
      vars.FillVars( "Jet_totHEFrac",iJet, itJet->neutralHadronEnergyFraction() + itJet->chargedHadronEnergyFraction() );
    }
    vars.FillVars( "Jet_nEmEFrac",iJet, itJet->neutralEmEnergyFraction() );
    
    //Letpon variables
    vars.FillVars( "Jet_leptonPtRel",iJet,itJet->userFloat("Jet_leptonPtRel") );
    vars.FillVars( "Jet_leptonPt",iJet,itJet->userFloat("Jet_leptonPt") );
    vars.FillVars( "Jet_leptonEta",iJet,itJet->userFloat("Jet_leptonEta") );
    vars.FillVars( "Jet_leptonDeltaR",iJet,itJet->userFloat("Jet_leptonDeltaR") );
    vars.FillVars( "Jet_NmatchedsoftLeptons", iJet, itJet->userFloat("Jet_NmatchsoftLeptons")  );
    vars.FillVars( "Jet_NmatchedsoftElectrons", iJet, itJet->userFloat("Jet_NmatchsoftElectrons")  );
    vars.FillVars( "Jet_NmatchedsoftMuons", iJet, itJet->userFloat("Jet_NmatchsoftMuons")  );


    //Regression Output variables
    if (  itJet->hasUserFloat("bregCorrection")  ) {
      vars.FillVars( "Jet_regPt" , iJet , itJet->userFloat("bregCorrection")*itJet->pt() );
      vars.FillVars( "Jet_regcorr" , iJet , itJet->userFloat("bregCorrection") );
      
      //Loop over remaining regressions (if there are any)
      for(  auto itextentions = extentions.begin() ; itextentions != extentions.end(); itextentions++  ) {
	vars.FillVars(  "Jet_regPt"+(*itextentions) , iJet , itJet->userFloat( "bregCorrection"+(*itextentions) )*itJet->pt()  );
	vars.FillVars(  "Jet_regcorr"+(*itextentions) ,iJet , itJet->userFloat( "bregCorrection"+(*itextentions) )  );
      }
    }
    else {
      vars.FillVars( "Jet_regPt" ,iJet , -10 );
      vars.FillVars( "Jet_regcorr" ,iJet , -10 );

      //Loop over remaining regressions (if there are any)
      for(  auto itextentions = extentions.begin() ; itextentions != extentions.end(); itextentions++  ) {
	vars.FillVars(  "Jet_regPt"+(*itextentions) , iJet , -10  );
	vars.FillVars(  "Jet_regcorr"+(*itextentions) ,iJet , -10  );
      }
    }
  }
}
