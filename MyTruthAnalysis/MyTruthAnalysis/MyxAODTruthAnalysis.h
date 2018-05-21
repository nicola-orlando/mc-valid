#ifndef MyTruthAnalysis_MyxAODTruthAnalysis_H
#define MyTruthAnalysis_MyxAODTruthAnalysis_H

#include <EventLoop/Algorithm.h>

#include "xAODTruth/TruthParticleContainer.h"
#include "xAODJet/JetContainer.h"
#include "xAODEventInfo/EventInfo.h"

#include <TTree.h>

#include "MyTruthAnalysis/TruthAna_OptionParser.h"
#include "MyTruthAnalysis/TruthAna_NtupleManager.h"
#include "MyTruthAnalysis/TruthAna_GenericSelector.h"
#include "MyTruthAnalysis/TruthAna_ttHttSelector.h"
#include "MyTruthAnalysis/TruthAna_bbHttSelector.h"
#include "MyTruthAnalysis/TruthAna_tcHbbSelector.h"
#include "MyTruthAnalysis/TruthAna_LowMassHplusSelector.h"
#include "MyTruthAnalysis/TruthAna_ZbSelector.h"
#include "MyTruthAnalysis/TruthAna_CutFlowTools.h"

class TruthAna_OptionParser;
class TruthAna_NtupleManager;
class TruthAna_GenericSelector;
class TruthAna_ttHttSelector;
class TruthAna_bbHttSelector;
class TruthAna_tcHbbSelector;
class TruthAna_LowMassHplusSelector;
class TruthAna_ZbSelector;
class TruthAna_CutFlowTools;

class MyxAODTruthAnalysis : public EL::Algorithm
{

public:

  MyxAODTruthAnalysis ();

  enum class PROCESS{TT_H_TT,BB_H_TT,TC_H_BB,ZB,TT,LOWMASSHPLUS,GENERIC};
  enum class DERIVATION{TRUTH0,TRUTH1};

  PROCESS proc;
  DERIVATION deriv;

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode fileExecute ();
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();

  std::string outputName;

  EL::StatusCode LoadContainers();
  EL::StatusCode ParticleFiller();
  EL::StatusCode NtupleFiller();
  EL::StatusCode ClearParticles();
  bool CutFlow();
  
  TTree *tree; //!
  const xAOD::EventInfo              *m_eventInfoCont; //!                                                         
  const xAOD::TruthParticleContainer *m_TruthParticles; //!                                                      
  const xAOD::TruthParticleContainer *m_TruthNeutrinos; //!                                                      
  const xAOD::TruthParticleContainer *m_TruthMuons; //!                                                          
  const xAOD::TruthParticleContainer *m_TruthElectrons; //!                                                      
  const xAOD::TruthParticleContainer *m_TruthTaus; //!                                                           
  const xAOD::JetContainer           *m_AntiKt4TruthWZJets; //!                                                            

  TruthAna_OptionParser* m_OptionParser; //! 
  TruthAna_NtupleManager* m_NtupleManager; //!
  TruthAna_GenericSelector* m_GenericSelector; //!
  TruthAna_ttHttSelector* m_ttHttSelector; //!
  TruthAna_bbHttSelector* m_bbHttSelector; //!
  TruthAna_tcHbbSelector* m_tcHbbSelector; //!
  TruthAna_LowMassHplusSelector* m_LowMassHplusSelector; //!
  TruthAna_ZbSelector* m_ZbSelector; //!
  TruthAna_CutFlowTools* m_CutFlowTools; //!

  std::vector<int> v_leptons_pdgid; //!
  std::vector<int> v_neutrinos_pdgid; //!

  std::vector<TLorentzVector> v_neutrinos; //! 
  std::vector<TLorentzVector> v_muons; //! 
  std::vector<TLorentzVector> v_electrons; //!
  std::vector<TLorentzVector> v_taus; //! 
  std::vector<TLorentzVector> v_AntiKt4TruthWZJets; //!  
  std::vector<TLorentzVector> v_particle_wboson; //! 
  std::vector<TLorentzVector> v_parton_u; //!  
  std::vector<TLorentzVector> v_parton_au; //!  
  std::vector<TLorentzVector> v_parton_d; //!  
  std::vector<TLorentzVector> v_parton_ad; //!  
  std::vector<TLorentzVector> v_parton_c; //!  
  std::vector<TLorentzVector> v_parton_ac; //!  
  std::vector<TLorentzVector> v_parton_s; //!  
  std::vector<TLorentzVector> v_parton_as; //!  
  std::vector<TLorentzVector> v_parton_top; //!  
  std::vector<TLorentzVector> v_parton_atop; //!  
  std::vector<TLorentzVector> v_parton_b; //!  
  std::vector<TLorentzVector> v_parton_ab; //!  
  std::vector<TLorentzVector> v_parton_wplus; //!  
  std::vector<TLorentzVector> v_parton_wminus; //!  
  std::vector<TLorentzVector> v_parton_higgs; //!  
  std::vector<TLorentzVector> v_parton_ttfromH; //!  
  std::vector<TLorentzVector> v_parton_ttnotfromH; //!  
  std::vector<TLorentzVector> v_parton_bbfromH; //!  
  std::vector<TLorentzVector> v_parton_tcnotfromH; //!  
  std::vector<TLorentzVector> v_parton_Hplus_decays; //!    
  std::vector<TLorentzVector> v_Zb_Z; //!  
  std::vector<TLorentzVector> v_Zb_wzjets; //!  
  std::vector<TLorentzVector> v_parton_fromH; //!  
  std::vector<int> v_H_decay_pdgid; //!  
  std::vector<TLorentzVector> v_parton_topdecaychain_lepton; //!    
  std::vector<TLorentzVector> v_parton_topdecaychain_neutrino; //!    

  std::vector< std::pair< TLorentzVector,int > > v_TopDecayChain; //!    

  float mc_event_weight; //!
  float v_HT; //!
  //H+ angular analysis 
  float v_angana_lep_top_dphi; //!
  float v_angana_lep_top_dr; //!
  float v_angana_nu_top_dphi; //!
  float v_angana_nu_top_dr; //!
  float v_angana_lep_top_dphi_topcm; //!
  float v_angana_nu_top_dphi_topcm; //!

  // this is needed to distribute the algorithm to the workers
  ClassDef(MyxAODTruthAnalysis, 1);

};

#endif
