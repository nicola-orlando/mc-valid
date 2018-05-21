#include "MyTruthAnalysis/TruthAna_BaseSelector.h"
#include <TLorentzVector.h>

TruthAna_BaseSelector::TruthAna_BaseSelector(){}


TruthAna_BaseSelector::~TruthAna_BaseSelector(){}


std::vector<TLorentzVector>  TruthAna_BaseSelector::DecayH(const xAOD::TruthParticleContainer *cont, float pt, float eta, DECAY_H decay_h)
{
  std::vector<TLorentzVector> tlv_vec;
  TLorentzVector decdec;
  decdec.SetPtEtaPhiM(10,1,2,1);

  for(auto vcont : *cont){
    float loc_px    =vcont->px(); float loc_py    =vcont->py();
    float loc_pz    =vcont->pz(); float loc_e     =vcont->e() ;
    TLorentzVector tlv; tlv.SetPxPyPzE(loc_px,loc_py,loc_pz,loc_e); 
    
    int apdgid = fabs(vcont->auxdata<int>("pdgId"));

    if( tlv.Pt()<pt )continue;
    if( fabs( tlv.Rapidity() )>eta )continue;

    if     ( decay_h==DECAY_H::TT  && (!(apdgid==top_pid))) continue;
    else if( decay_h==DECAY_H::BB  && (!(apdgid==bottom_pid))) continue;
    else if( decay_h==DECAY_H::TB  && (!(apdgid==top_pid||apdgid==bottom_pid))) continue;
    //take all particles as parent but the Higgs bosons
    else if( decay_h==DECAY_H::ALL && (fabs(apdgid)==35||fabs(apdgid)==36||fabs(apdgid)==37||fabs(apdgid)==25) ) continue;

    //Perhaps that's not needed.. status will change from generator to generator
    //Check that you always have two particles form the H decays

    /*
    //intermediated particle, eg. tt decays from H
    if( decay_h==DECAY_H::TT && ( ! ( vcont->auxdata<int>("status")== 22 ) ) ) continue;
    //final state particle, eg. bb decays from H
    if( decay_h==DECAY_H::BB && ( ! ( vcont->auxdata<int>("status")== 23 ) ) ) continue;
    */

    bool has_a_higgs_parent=false;
    for(unsigned int par_index=0; par_index < vcont->nParents(); par_index++)
      {
        const xAOD::TruthParticle* parent = vcont->parent(par_index);
        if(!parent) continue;
        int parent_pdgId=parent->pdgId();
        if(fabs(parent_pdgId)==35||fabs(parent_pdgId)==36||fabs(parent_pdgId)==37||fabs(parent_pdgId)==25) has_a_higgs_parent=true;
      }
    if(!has_a_higgs_parent) continue;    
    tlv_vec.push_back(tlv);
  }
  if(!(tlv_vec.size()==2))
    {
      std::cout<<"Expected two H decay products, found n="<<tlv_vec.size()<<"), aborting"<<std::endl;
      exit(0);
    }
  else   
    {
      decdec=tlv_vec[0]+tlv_vec[1];
    }

  tlv_vec.push_back(decdec);
  
  return tlv_vec;
}


std::vector<TLorentzVector>  TruthAna_BaseSelector::AssociatedToH(const xAOD::TruthParticleContainer *cont, float pt, float eta, ASSOCIATED_H associated_h)
{
  std::vector<TLorentzVector> tlv_vec;
  TLorentzVector assoc;

  for(auto vcont : *cont){
    float loc_px    =vcont->px(); float loc_py    =vcont->py();
    float loc_pz    =vcont->pz(); float loc_e     =vcont->e() ;
    TLorentzVector tlv; tlv.SetPxPyPzE(loc_px,loc_py,loc_pz,loc_e); 

    int apdgid = fabs(vcont->auxdata<int>("pdgId"));

    if( tlv.Pt()<pt )continue;
    if( fabs( tlv.Rapidity() )>eta )continue;

    if     ( associated_h==ASSOCIATED_H::TT && (!(apdgid==top_pid))) continue;
    else if( associated_h==ASSOCIATED_H::BB && (!(apdgid==bottom_pid))) continue;
    else if( associated_h==ASSOCIATED_H::TB && (!(apdgid==top_pid||apdgid==bottom_pid))) continue;
    else if( associated_h==ASSOCIATED_H::TC && (!(apdgid==top_pid||apdgid==charm_pid))) continue;
    //Debug printouts?
    //else if( associated_h==ASSOCIATED_H::INCLUSIVE ) continue; 

    if( ! ( vcont->auxdata<int>("status")== 22 ) ) continue;

    bool has_a_higgsORtop_parent=false;
    for(unsigned int par_index=0; par_index < vcont->nParents(); par_index++)
      {
        const xAOD::TruthParticle* parent = vcont->parent(par_index);
        if(!parent) continue;
        int parent_pdgId=parent->pdgId();
        if( parent_pdgId==35||parent_pdgId==36||parent_pdgId==37||parent_pdgId==25||parent_pdgId==top_pid)has_a_higgsORtop_parent=true;
      }
    if(has_a_higgsORtop_parent) continue;
    tlv_vec.push_back(tlv);                                                                   
  }
  if(!(tlv_vec.size()==2))
    {
      std::cout<<"Expected two objects in association with H, found ntops="<<tlv_vec.size()<<"), aborting"<<std::endl;
      exit(0);
    }
  assoc=tlv_vec[0]+tlv_vec[1];
  tlv_vec.push_back(assoc);
  
  return tlv_vec;
}


std::vector<int> TruthAna_BaseSelector::GetHiggsDecays(const xAOD::TruthParticleContainer *cont, int H_pdgid)
{
  std::vector<int> PDGID;

  for(auto vcont : *cont){

    int par_pdgid=vcont->auxdata<int>("pdgId");
    
    if(par_pdgid == H_pdgid) continue;

    bool has_a_higgs_parent=false;
    for(unsigned int par_index=0; par_index < vcont->nParents(); par_index++)
      {
        const xAOD::TruthParticle* parent = vcont->parent(par_index);
        if(!parent) continue;
        int parent_pdgId=parent->pdgId();
	//fabs used for H+
        if( fabs(parent_pdgId) == H_pdgid ) has_a_higgs_parent=true;
									      
      }
    if(!has_a_higgs_parent) continue;
    
    //std::cout<<" Higgs doughter "<<par_pdgid<<std::endl;
    PDGID.push_back(par_pdgid);                                                                   
  }
  
  return PDGID;
}

