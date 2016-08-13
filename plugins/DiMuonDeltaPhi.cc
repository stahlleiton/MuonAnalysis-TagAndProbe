// system include files
#include <memory>
#include <cmath>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"

#include "TVector2.h"

//
// class declaration
//

class DiMuonDeltaPhi : public edm::EDProducer {
public:
  explicit DiMuonDeltaPhi(const edm::ParameterSet&);
  ~DiMuonDeltaPhi();

private:
  virtual void beginJob() ;
  virtual void produce(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  // ----------member data ---------------------------
  const edm::EDGetTokenT<reco::CandidateView> tagProbePairs_;
};

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
DiMuonDeltaPhi::DiMuonDeltaPhi(const edm::ParameterSet& iConfig):
tagProbePairs_(consumes<edm::View<reco::Candidate>>(iConfig.getParameter<edm::InputTag>("tagProbePairs")))
{
  produces<edm::ValueMap<float> >("deltaPhi");
}


DiMuonDeltaPhi::~DiMuonDeltaPhi()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
DiMuonDeltaPhi::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;

  // read input
  Handle< edm::View<reco::Candidate> > tagProbePairs;
  iEvent.getByToken(tagProbePairs_,  tagProbePairs);

  // prepare vector for output    
  std::vector<double> pair_deltaPhi;

  // fill
  edm::View<reco::Candidate>::const_iterator tagProbePair, endTagProbePair = tagProbePairs->end();

  // loop on PAIRS
  for (tagProbePair = tagProbePairs->begin(); tagProbePair != endTagProbePair; ++tagProbePair) {

    if(tagProbePair->daughter(0)->charge() > tagProbePair->daughter(1)->charge()){
      pair_deltaPhi.push_back(TVector2::Phi_mpi_pi(tagProbePair->daughter(0)->phi() - tagProbePair->daughter(1)->phi()));
    }else{
      pair_deltaPhi.push_back(TVector2::Phi_mpi_pi(tagProbePair->daughter(1)->phi() - tagProbePair->daughter(0)->phi()));
    }

  }// end loop on probes

  // convert into ValueMap and store
  std::auto_ptr<ValueMap<float> > deltaPhi(new ValueMap<float>());
  ValueMap<float>::Filler filler0(*deltaPhi);
  filler0.insert(tagProbePairs, pair_deltaPhi.begin(), pair_deltaPhi.end());
  filler0.fill();

  iEvent.put(deltaPhi, "deltaPhi");

}

// ------------ method called once each job just before starting event loop  ------------
void 
DiMuonDeltaPhi::beginJob()
{


}

// ------------ method called once each job just after ending the event loop  ------------
void 
DiMuonDeltaPhi::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(DiMuonDeltaPhi);
