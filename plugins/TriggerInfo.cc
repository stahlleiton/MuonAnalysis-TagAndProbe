// -*- C++ -*-
//
// Package:    MuonAnalysis/TagAndProbe
// Class:      TriggerInfo
// 
/**\class TriggerInfo TriggerInfo.cc MuonAnalysis/TagAndProbe/plugins/TriggerInfo.cc

 Description: Add trigger information on the tag muons
*/
//
// Original Author:  Andre Stahl
//         Created:  Mon, 01 Feb 2020 14:45:12 GMT
//
//

#include <memory>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "TRegexp.h"

class TriggerInfo : public edm::stream::EDProducer<> {
   public:
      explicit TriggerInfo(const edm::ParameterSet&);
      ~TriggerInfo();

   private:
      virtual void produce(edm::Event&, const edm::EventSetup&) override;

      edm::EDGetTokenT<edm::View<reco::Candidate> > src_;
      edm::EDGetTokenT<edm::TriggerResults> triggerTag_;
      std::vector<std::string> triggerNames_;
      std::map<std::string, std::string> nameMap_;

      void writeValueMap(edm::Event &iEvent,
                const edm::Handle<edm::View<reco::Candidate> > & handle,
                const std::vector<float> & values,
                const std::string & label) const ;
};

TriggerInfo::TriggerInfo(const edm::ParameterSet& iConfig) :
   src_(consumes<edm::View<reco::Candidate> >(iConfig.getParameter<edm::InputTag>("src"))),
   triggerTag_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerTag"))),
   triggerNames_(iConfig.getParameter<std::vector<std::string> >("triggerNames"))
{
   for (const auto& trg : triggerNames_) {
     auto n = trg;
     n.erase(std::remove(n.begin(), n.end(), '*'), n.end());
     n.erase(std::remove(n.begin(), n.end(), '_'), n.end());
     nameMap_[trg] = n;
     produces<edm::ValueMap<float> >(n);
   }
}


TriggerInfo::~TriggerInfo()
{
}

void
TriggerInfo::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;

   Handle<View<reco::Candidate> > src;
   iEvent.getByToken(src_, src);

   Handle<edm::TriggerResults> triggers;
   iEvent.getByToken(triggerTag_, triggers);
   const auto& trgN = iEvent.triggerNames(*triggers);

   std::map<std::string, std::vector<float> > result;

   for (const auto& path : triggerNames_) {
     float trgFire = 0;
     for (size_t i = 0; i < triggers->size(); i++) {
       if (triggers->accept(i) && TString(trgN.triggerName(i)).Contains(TRegexp(path))) {
         trgFire = 1.;
         break;
       }
     }
     result.insert({nameMap_.at(path), vector<float>(src->size(), trgFire)});
   }
     
   for (const auto& res : result) {
     writeValueMap(iEvent, src, res.second,	res.first);
   }
}

void
TriggerInfo::writeValueMap(edm::Event &iEvent,
        const edm::Handle<edm::View<reco::Candidate> > & handle,
        const std::vector<float> & values,
        const std::string & label) const 
{
    using namespace edm; 
    using namespace std;
    unique_ptr<ValueMap<float> > valMap(new ValueMap<float>());
    edm::ValueMap<float>::Filler filler(*valMap);
    filler.insert(handle, values.begin(), values.end());
    filler.fill();
    iEvent.put(std::move(valMap), label);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TriggerInfo);
