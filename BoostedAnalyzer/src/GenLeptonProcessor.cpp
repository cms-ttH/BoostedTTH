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
  
  vars.InitVar("N_GenElectrons",-1,"I");
  vars.InitVars( "GenElectron_Pt",-9.,"N_GenElectrons" );
  vars.InitVars( "GenElectron_Eta",-9.,"N_GenElectrons" );
  vars.InitVars( "GenElectron_Phi",-9.,"N_GenElectrons" );
  vars.InitVars( "GenElectron_E",-9.,"N_GenElectrons" );
  vars.InitVars( "GenElectron_RecoLeptonPt",-9.,"N_GenElectrons" );
  vars.InitVars( "GenElectron_RecoLeptonEta",-9.,"N_GenElectrons" );
  vars.InitVars( "GenElectron_RecoLeptonPhi",-9.,"N_GenElectrons" );
  vars.InitVars( "GenElectron_RecoLeptonE",-9.,"N_GenElectrons" );
  vars.InitVars( "GenElectron_NHadrons",-9.,"N_GenElectrons" );
        
  vars.InitVar("N_GenMuons",-1,"I");
  vars.InitVars( "GenMuon_Pt",-9.,"N_GenMuons" );
  vars.InitVars( "GenMuon_Eta",-9.,"N_GenMuons" );
  vars.InitVars( "GenMuon_Phi",-9.,"N_GenMuons" );
  vars.InitVars( "GenMuon_E",-9.,"N_GenMuons" );
  vars.InitVars( "GenMuon_RecoLeptonPt",-9.,"N_GenMuons" );
  vars.InitVars( "GenMuon_RecoLeptonEta",-9.,"N_GenMuons" );
  vars.InitVars( "GenMuon_RecoLeptonPhi",-9.,"N_GenMuons" );
  vars.InitVars( "GenMuon_RecoLeptonE",-9.,"N_GenMuons" );
  vars.InitVars( "GenMuon_NHadrons",-9.,"N_GenMuons" );
  
  initialized = true;
  
  }

void GenLeptonProcessor::Process(const InputCollections& input,VariableContainer& vars){
  
  if(!initialized) cerr << "tree processor not initialized" << endl;
  
  
  std::vector<reco::GenParticle> electrons = input.customGenElectrons;
  //std::cout << "Size Input collection customGenElectrons: " << electrons.size() << std::endl;
  
  if(electrons.size()>0){
    std::vector<const pat::Electron*> electrons_reco;
    for(auto electron = electrons.begin(); electron != electrons.end(); electron++){
      electrons_reco.push_back(GetPatElectron(*electron,input.selectedElectronsLoose));
    }
        
    vars.FillVar( "N_GenElectrons", electrons.size());
      
    reco::GenParticle leadingelectron = electrons.at(0);  
    for(uint i=0; i<electrons.size(); i++){
      if(electrons[i].pt() > leadingelectron.pt()){
        leadingelectron = electrons[i];
        }
      vars.FillVars( "GenElectron_Pt", i, electrons[i].pt());
      vars.FillVars( "GenElectron_Eta", i, electrons[i].eta());
      vars.FillVars( "GenElectron_Phi", i, electrons[i].phi());
      vars.FillVars( "GenElectron_E", i, electrons[i].energy());
      vars.FillVars( "GenElectron_RecoLeptonPt", i, electrons_reco[i]!=0 ? electrons_reco[i]->pt() : -1);
      vars.FillVars( "GenElectron_RecoLeptonEta", i, electrons_reco[i]!=0 ? electrons_reco[i]->eta() : -1);
      vars.FillVars( "GenElectron_RecoLeptonPhi", i, electrons_reco[i]!=0 ? electrons_reco[i]->phi() : -1);
      vars.FillVars( "GenElectron_RecoLeptonE", i, electrons_reco[i]!=0 ? electrons_reco[i]->energy() : -1);
      }
  }
  
  
  std::vector<reco::GenParticle> muons = input.customGenMuons;
  //std::cout << "Size Input collection customGenMuons: " << muons.size() << std::endl;
  
  if(muons.size()>0){
    std::vector<const pat::Muon*> muons_reco;
    for(auto muon = muons.begin(); muon != muons.end(); muon++){
    muons_reco.push_back(GetPatMuon(*muon,input.selectedMuonsLoose));
    }
    
    vars.FillVar( "N_GenMuons", muons.size());
    
    reco::GenParticle leadingmuon = muons.at(0);
    for(uint i=0; i<muons.size(); i++){
      if(muons[i].pt() > leadingmuon.pt()){
        leadingmuon = muons[i];
        }
      vars.FillVars( "GenMuon_Pt", i, muons[i].pt());
      vars.FillVars( "GenMuon_Eta", i, muons[i].eta());
      vars.FillVars( "GenMuon_Phi", i, muons[i].phi());
      vars.FillVars( "GenMuon_E", i, muons[i].energy());
      vars.FillVars( "GenMuon_RecoLeptonPt", i, muons_reco[i]!=0 ? muons_reco[i]->pt() : -1);
      vars.FillVars( "GenMuon_RecoLeptonEta", i, muons_reco[i]!=0 ? muons_reco[i]->eta() : -1);
      vars.FillVars( "GenMuon_RecoLeptonPhi", i, muons_reco[i]!=0 ? muons_reco[i]->phi() : -1);
      vars.FillVars( "GenMuon_RecoLeptonE", i, muons_reco[i]!=0 ? muons_reco[i]->energy() : -1);
      }
  }
  
  }
