#include "BoostedTTH/BoostedAnalyzer/interface/GenLeptonProcessor.hpp"

using namespace std;

GenLeptonProcessor::GenLeptonProcessor (){}
GenLeptonProcessor::~GenLeptonProcessor (){}

const pat::Electron* GenLeptonProcessor::GetPatElectron(const reco::GenParticle& genelectron,const std::vector<pat::Electron>& patelectrons){
  for(auto patelectron=patelectrons.begin(); patelectron!=patelectrons.end(); patelectron++){
    if(patelectron->pt()>0 && genelectron.pt()>0 && BoostedUtils::DeltaR(patelectron->p4(),genelectron.p4())<0.2){
      return &(*patelectron);
      break;
      }
  }
  return 0;
  }
  
const pat::Muon* GenLeptonProcessor::GetPatMuon(const reco::GenParticle& genmuon,const std::vector<pat::Muon>& patmuons){
  for(auto patmuon=patmuons.begin(); patmuon!=patmuons.end(); patmuon++){
    if(patmuon->pt()>0 && genmuon.pt()>0 && BoostedUtils::DeltaR(patmuon->p4(),genmuon.p4())<0.2){
      return &(*patmuon);
      break;
      }
  }
  return 0;
  }

void GenLeptonProcessor::Init(const InputCollections& input, VariableContainer& vars){
  
  vars.InitVar("N_GenLeptons",-1,"I");
  vars.InitVars( "GenLepton_Pt",-9.,"N_GenLeptons" );
  vars.InitVars( "GenLepton_Eta",-9.,"N_GenLeptons" );
  vars.InitVars( "GenLepton_Phi",-9.,"N_GenLeptons" );
  vars.InitVars( "GenLepton_E",-9.,"N_GenLeptons" );
  
  vars.InitVar("N_GenElectrons",-1,"I");
  vars.InitVars( "GenElectron_Pt",-9.,"N_GenElectrons" );
  vars.InitVars( "GenElectron_Eta",-9.,"N_GenElectrons" );
  vars.InitVars( "GenElectron_Phi",-9.,"N_GenElectrons" );
  vars.InitVars( "GenElectron_E",-9.,"N_GenElectrons" );
  vars.InitVars( "GenElectron_RecoLeptonPt",-9.,"N_GenElectrons" );
  vars.InitVars( "GenElectron_RecoLeptonEta",-9.,"N_GenElectrons" );
  vars.InitVars( "GenElectron_RecoLeptonPhi",-9.,"N_GenElectrons" );
  vars.InitVars( "GenElectron_RecoLeptonE",-9.,"N_GenElectrons" );
        
  vars.InitVar("N_GenMuons",-1,"I");
  vars.InitVars( "GenMuon_Pt",-9.,"N_GenMuons" );
  vars.InitVars( "GenMuon_Eta",-9.,"N_GenMuons" );
  vars.InitVars( "GenMuon_Phi",-9.,"N_GenMuons" );
  vars.InitVars( "GenMuon_E",-9.,"N_GenMuons" );
  vars.InitVars( "GenMuon_RecoLeptonPt",-9.,"N_GenMuons" );
  vars.InitVars( "GenMuon_RecoLeptonEta",-9.,"N_GenMuons" );
  vars.InitVars( "GenMuon_RecoLeptonPhi",-9.,"N_GenMuons" );
  vars.InitVars( "GenMuon_RecoLeptonE",-9.,"N_GenMuons" );
  
  initialized = true;
  
  }

void GenLeptonProcessor::Process(const InputCollections& input,VariableContainer& vars){
  
  if(!initialized) cerr << "tree processor not initialized" << endl;
  
  
  std::vector<reco::GenParticle> electrons = input.customGenElectrons;
  //std::cout << "Size Input collection customGenElectrons: " << electrons.size() << std::endl;
  vars.FillVar( "N_GenElectrons", input.customGenElectrons.size());
  
  if(input.customGenElectrons.size()>0){
    std::vector<const pat::Electron*> electrons_reco;
    for(auto electron = electrons.begin(); electron != electrons.end(); electron++){
      electrons_reco.push_back(GetPatElectron(*electron,input.selectedElectronsLoose));
    }
      
    for(std::vector<reco::GenParticle>::const_iterator itEle = input.customGenElectrons.begin(); itEle < input.customGenElectrons.end(); ++itEle){
      int iEle = itEle - input.customGenElectrons.begin();
      vars.FillVars( "GenElectron_Pt", iEle, itEle->pt());
      vars.FillVars( "GenElectron_Eta", iEle, itEle->eta());
      vars.FillVars( "GenElectron_Phi", iEle, itEle->phi());
      vars.FillVars( "GenElectron_E", iEle, itEle->energy());
      vars.FillVars( "GenElectron_RecoLeptonPt", iEle, electrons_reco[iEle]!=NULL ? electrons_reco[iEle]->pt() : -1);
      vars.FillVars( "GenElectron_RecoLeptonEta", iEle, electrons_reco[iEle]!=NULL ? electrons_reco[iEle]->eta() : -1);
      vars.FillVars( "GenElectron_RecoLeptonPhi", iEle, electrons_reco[iEle]!=NULL ? electrons_reco[iEle]->phi() : -1);
      vars.FillVars( "GenElectron_RecoLeptonE", iEle, electrons_reco[iEle]!=NULL ? electrons_reco[iEle]->energy() : -1);
      }
  }
  
  
  std::vector<reco::GenParticle> muons = input.customGenMuons;
  //std::cout << "Size Input collection customGenMuons: " << muons.size() << std::endl;
  vars.FillVar( "N_GenMuons", input.customGenMuons.size());
  
  if(muons.size()>0){
    std::vector<const pat::Muon*> muons_reco;
    for(auto muon = muons.begin(); muon != muons.end(); muon++){
      muons_reco.push_back(GetPatMuon(*muon,input.selectedMuonsLoose));
    }
    
    for(std::vector<reco::GenParticle>::const_iterator itMuon = input.customGenMuons.begin(); itMuon < input.customGenMuons.end(); ++itMuon){
      int iMu = itMuon - input.customGenMuons.begin();
      vars.FillVars( "GenMuon_Pt", iMu, itMuon->pt());
      vars.FillVars( "GenMuon_Eta", iMu, itMuon->eta());
      vars.FillVars( "GenMuon_Phi", iMu, itMuon->phi());
      vars.FillVars( "GenMuon_E", iMu, itMuon->energy());
      vars.FillVars( "GenMuon_RecoLeptonPt", iMu, muons_reco[iMu]!=NULL ? muons_reco[iMu]->pt() : -1);
      vars.FillVars( "GenMuon_RecoLeptonEta", iMu, muons_reco[iMu]!=NULL ? muons_reco[iMu]->eta() : -1);
      vars.FillVars( "GenMuon_RecoLeptonPhi", iMu, muons_reco[iMu]!=NULL ? muons_reco[iMu]->phi() : -1);
      vars.FillVars( "GenMuon_RecoLeptonE", iMu, muons_reco[iMu]!=NULL ? muons_reco[iMu]->energy() : -1);
      }
  }
  
  
  std::vector<reco::GenParticle> leptons = electrons;
  leptons.insert(leptons.end(), muons.begin(), muons.end());
  
  vars.FillVar( "N_GenLeptons", leptons.size());
  
  if(leptons.size()>0){
    for(std::vector<reco::GenParticle>::const_iterator itLep = leptons.begin(); itLep < leptons.end(); ++itLep){
      int iLep = itLep - leptons.begin();
      vars.FillVars( "GenLepton_Pt", iLep, itLep->pt());
      vars.FillVars( "GenLepton_Eta", iLep, itLep->eta());
      vars.FillVars( "GenLepton_Phi", iLep, itLep->phi());
      vars.FillVars( "GenLepton_E", iLep, itLep->energy());
    }
  }
  
}
