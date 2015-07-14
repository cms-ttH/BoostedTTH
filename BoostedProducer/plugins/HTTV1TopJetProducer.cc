#include "BoostedTTH/BoostedProducer/plugins/HTTV1TopJetProducer.h"

#include "RecoJets/JetProducers/interface/JetSpecific.h"
#include "FWCore/Framework/interface/MakerMacros.h"


using namespace std;


////////////////////////////////////////////////////////////////////////////////
// construction / destruction
////////////////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
HTTV1TopJetProducer::HTTV1TopJetProducer(edm::ParameterSet const& iConfig):
		VirtualJetProducer(iConfig),
		alg_(
			iConfig.getParameter<string>	("@module_label"),
			iConfig.getParameter<bool>		("verbose"),
			iConfig.getParameter<bool>		("doAreaFastjet"),
			iConfig.getParameter<unsigned>	("nFatMax"),
			iConfig.getParameter<double>	("jetPtMin"),             // min jet pt
			iConfig.getParameter<double>	("centralEtaCut"),        // eta for defining "central" jets
			iConfig.getParameter<double>	("massDropCut"),          // mass drop threshold for declustering
			iConfig.getParameter<double>	("subjetMassCut"),        // maximal subjet mass
			iConfig.getParameter<bool>		("requireTopTag")        // use subjet mass cuts?
		),
		nSubJetAlgo1_(
			  1, // N
			  fastjet::Njettiness::AxesMode::kt_axes,
			  1., //beta
			  iConfig.getParameter<double>	("rParam") // cone size R0
			  ),
		nSubJetAlgo2_(
			  2, // N
			  fastjet::Njettiness::AxesMode::kt_axes,
			  1., //beta
			  iConfig.getParameter<double>	("rParam") // cone size R0
			  ),

		nSubJetAlgo3_(
			  3, // N
			  fastjet::Njettiness::AxesMode::kt_axes,
			  1., //beta
			  iConfig.getParameter<double>	("rParam") // cone size R0
			  ),

		nSubJetAlgo4_(
			  4, // N
			  fastjet::Njettiness::AxesMode::kt_axes,
			  1., //beta
			  iConfig.getParameter<double>	("rParam") // cone size R0
			  )

{
	produces<reco::BasicJetCollection>("fatjet");
	makeProduces(moduleLabel_,"subjets");
	
	produces<std::vector<bool> >("toptag");
	for(size_t N=1;N<=4;N++){
		char tau_char[50];
		sprintf (tau_char, "tau%i", (int) N);
		std::string tau_string = tau_char;
		
  		produces<std::vector<double> >(tau_string);
	}
}


//______________________________________________________________________________
HTTV1TopJetProducer::~HTTV1TopJetProducer()
{

}


////////////////////////////////////////////////////////////////////////////////
// implementation of member functions
////////////////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
void HTTV1TopJetProducer::produce(  edm::Event & e, const edm::EventSetup & c ) 
{
  VirtualJetProducer::produce(e, c);
}


//______________________________________________________________________________
void HTTV1TopJetProducer::endJob()
{
  cout<<alg_.summary()<<endl;
}


//______________________________________________________________________________
void HTTV1TopJetProducer::runAlgorithm( edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  if ( !doAreaFastjet_ && !doRhoFastjet_) {
    fjClusterSeq_ = ClusterSequencePtr( new fastjet::ClusterSequence( fjInputs_, *fjJetDefinition_ ) );
  } else if (voronoiRfact_ <= 0) {
    fjClusterSeq_ = ClusterSequencePtr( new fastjet::ClusterSequenceArea( fjInputs_, *fjJetDefinition_ , *fjAreaDefinition_ ) );
  } else {
    fjClusterSeq_ = ClusterSequencePtr( new fastjet::ClusterSequenceVoronoiArea( fjInputs_, *fjJetDefinition_ , fastjet::VoronoiAreaSpec(voronoiRfact_) ) );
  }
  
  alg_.run(fjInputs_,fjCompoundJets_,topTags_,fjClusterSeq_);
  for(uint i=0; i<fjCompoundJets_.size();i++){
    // run nsubjettiness algorithms on fat jet
    double n1= nSubJetAlgo1_(fjCompoundJets_[i].hardJet());
    double n2= nSubJetAlgo2_(fjCompoundJets_[i].hardJet());
    double n3= nSubJetAlgo3_(fjCompoundJets_[i].hardJet());
    double n4= nSubJetAlgo4_(fjCompoundJets_[i].hardJet());
    nSjn1_.push_back(n1);
    nSjn2_.push_back(n2);
    nSjn3_.push_back(n3);
    nSjn4_.push_back(n4);
  }
}


//______________________________________________________________________________
void HTTV1TopJetProducer::inputTowers()
{
  fjCompoundJets_.clear();
  topTags_.clear();
  nSjn1_.clear();
  nSjn2_.clear();
  nSjn3_.clear();
  nSjn4_.clear();
  VirtualJetProducer::inputTowers();
}


//______________________________________________________________________________
void HTTV1TopJetProducer::output(edm::Event& iEvent,
				     edm::EventSetup const& iSetup)
{
  // Write jets and constitutents. Will use fjCompoundJets_. 
  switch( jetTypeE ) {
  case JetType::CaloJet :
    writeCompoundJets<reco::CaloJet>( iEvent, iSetup );
    break;
  case JetType::PFJet :
    writeCompoundJets<reco::PFJet>( iEvent, iSetup );
    break;
  case JetType::GenJet :
    writeCompoundJets<reco::GenJet>( iEvent, iSetup );
    break;
  case JetType::BasicJet :
    writeCompoundJets<reco::BasicJet>( iEvent, iSetup );
    break;
  default:
    edm::LogError("InvalidInput")<<" invalid jet type in SubjetFilterJetProducer\n";
    break;
  };
  
}


//______________________________________________________________________________
template< class T>
void HTTV1TopJetProducer::writeCompoundJets(edm::Event& iEvent,const edm::EventSetup& iSetup)
{
	auto_ptr<reco::BasicJetCollection> fatJets( new reco::BasicJetCollection() );
	auto_ptr< vector<T> >	subJets( new vector<T>() );
	auto_ptr< vector<bool> > topTags( new vector<bool>() );

	edm::OrphanHandle< vector<bool> > topTagsAfterPut;
	edm::OrphanHandle< vector<T> > subJetsAfterPut;

	vector< vector<int> > subIndices(fjCompoundJets_.size());

	vector<math::XYZTLorentzVector> p4FatJets;

	vector<double> areaFatJets;

	vector<CompoundPseudoJet>::const_iterator itBegin(fjCompoundJets_.begin());
	vector<CompoundPseudoJet>::const_iterator itEnd(fjCompoundJets_.end());
	vector<CompoundPseudoJet>::const_iterator it(itBegin);
	
	for (;it!=itEnd;++it) {

		int jetIndex = it-itBegin;

		fastjet::PseudoJet fatJet = it->hardJet();
		p4FatJets.push_back(math::XYZTLorentzVector(fatJet.px(),fatJet.py(),
		fatJet.pz(),fatJet.e()));
		areaFatJets.push_back(it->hardJetArea());
		
		vector<CompoundPseudoSubJet>::const_iterator itSubBegin(it->subjets().begin());
		vector<CompoundPseudoSubJet>::const_iterator itSubEnd(it->subjets().end());
		vector<CompoundPseudoSubJet>::const_iterator itSub(itSubBegin);

		for (; itSub!=itSubEnd;++itSub) {
			
			fastjet::PseudoJet fjSubJet = itSub->subjet();
			math::XYZTLorentzVector p4SubJet(fjSubJet.px(),fjSubJet.py(),
			fjSubJet.pz(),fjSubJet.e());
			reco::Particle::Point point(0,0,0);

			vector<reco::CandidatePtr> subJetConstituents;
			const vector<int>& subJetConstituentIndices = itSub->constituents();
			vector<int>::const_iterator itIndexBegin(subJetConstituentIndices.begin());
			vector<int>::const_iterator itIndexEnd(subJetConstituentIndices.end());
			vector<int>::const_iterator itIndex(itIndexBegin);

			for (;itIndex!=itIndexEnd;++itIndex)
				if ((*itIndex) < static_cast<int>(inputs_.size())) 
					subJetConstituents.push_back(inputs_[*itIndex]);
			
			T subJet;
			reco::writeSpecific(subJet,p4SubJet,point,subJetConstituents,iSetup);
			subJet.setJetArea(itSub->subjetArea());

			subIndices[jetIndex].push_back(subJets->size());
			subJets->push_back(subJet);
		}
	}

	subJetsAfterPut = iEvent.put(subJets,"subjets");
	
	topTags = auto_ptr< vector<bool> >(new vector<bool>(topTags_));
	
	topTagsAfterPut = iEvent.put(topTags,"toptag");
	
	vector<math::XYZTLorentzVector>::const_iterator itP4Begin(p4FatJets.begin());
	vector<math::XYZTLorentzVector>::const_iterator itP4End(p4FatJets.end());
	vector<math::XYZTLorentzVector>::const_iterator itP4(itP4Begin);
   
	for (;itP4!=itP4End;++itP4) {
		int fatIndex = itP4-itP4Begin;

		vector<int>& fatToSub			= subIndices[fatIndex];

		vector<reco::CandidatePtr> i_fatJetConstituents;

		vector<int>::const_iterator itSubBegin(fatToSub.begin());
		vector<int>::const_iterator itSubEnd(fatToSub.end());
		vector<int>::const_iterator itSub(itSubBegin);

		for(;itSub!=itSubEnd;++itSub) {
			reco::CandidatePtr candPtr(subJetsAfterPut,(*itSub),false);
			i_fatJetConstituents.push_back(candPtr);
		}

		reco::Particle::Point point(0,0,0);

		fatJets->push_back(reco::BasicJet((*itP4),point,i_fatJetConstituents));
		fatJets->back().setJetArea(areaFatJets[fatIndex]);
	}

	iEvent.put(fatJets,"fatjet");
	
	for(size_t N=1;N<=4;N++){
	  auto_ptr< vector<double> > NSubjettiness(new vector<double>());
	  if(N==1)*NSubjettiness = nSjn1_;
	  if(N==2)*NSubjettiness = nSjn2_;
	  if(N==3)*NSubjettiness = nSjn3_;
	  if(N==4)*NSubjettiness = nSjn4_;
	  
	  char tau_char[50];
	  sprintf (tau_char, "tau%i", (int) N);
	  std::string tau_string = tau_char;
		
	  iEvent.put(NSubjettiness, tau_string);
	}
}

//define this as a plug-in
DEFINE_FWK_MODULE(HTTV1TopJetProducer);
