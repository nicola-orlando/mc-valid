#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <MyTruthAnalysis/MyxAODTruthAnalysis.h>

// Infrastructure include(s):
#include "xAODRootAccess/Init.h"
#include "xAODRootAccess/TEvent.h"
#include "xAODRootAccess/tools/Message.h"

// EDM includes:
#include "xAODEventInfo/EventInfo.h"

#include <TFile.h>

// this is needed to distribute the algorithm to the workers
ClassImp(MyxAODTruthAnalysis)

/// Helper macro for checking xAOD::TReturnCode return values
#define EL_RETURN_CHECK( CONTEXT, EXP )                     \
  do {							    \
    if( ! EXP.isSuccess() ) {				    \
      Error( CONTEXT,					    \
	     XAOD_MESSAGE( "Failed to execute: %s" ),	    \
	     #EXP );					    \
      return EL::StatusCode::FAILURE;			    \
    }							    \
  } while( false )



MyxAODTruthAnalysis :: MyxAODTruthAnalysis()
{
  proc =PROCESS::LOWMASSHPLUS;
  deriv=DERIVATION::TRUTH1;

  m_OptionParser         = new TruthAna_OptionParser;  
  m_NtupleManager        = new TruthAna_NtupleManager; 
  m_GenericSelector      = new TruthAna_GenericSelector; 
  m_ttHttSelector        = new TruthAna_ttHttSelector; 
  m_bbHttSelector        = new TruthAna_bbHttSelector; 
  m_tcHbbSelector        = new TruthAna_tcHbbSelector; 
  m_LowMassHplusSelector = new TruthAna_LowMassHplusSelector; 
  m_ZbSelector           = new TruthAna_ZbSelector; 
  m_CutFlowTools         = new TruthAna_CutFlowTools; 

  v_leptons_pdgid  .push_back(11); 
  v_leptons_pdgid  .push_back(13); 
  v_leptons_pdgid  .push_back(15); 
  v_neutrinos_pdgid.push_back(-12);  
  v_neutrinos_pdgid.push_back(-14);  
  v_neutrinos_pdgid.push_back(-16);  

  m_CutFlowTools->addCutFlow("Cut-Flow","All|OneMu|OneEl|OneTau|OneNu|Lep+Nu|FourJets|FiveJets|>=SixJets");
  m_CutFlowTools->addCutFlow("Cut-Flow weighted","All|OneMu|OneEl|OneTau|OneNu|Lep+Nu|FourJets|FiveJets|>=SixJets");
  
}



EL::StatusCode MyxAODTruthAnalysis :: setupJob (EL::Job& job)
{
  job.useXAOD ();
  EL_RETURN_CHECK( "setupJob()", xAOD::Init() ); // call before opening first file

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODTruthAnalysis :: histInitialize ()
{
  TFile *outputFile = wk()->getOutputFile (outputName);
  tree = new TTree ("tree", "tree");
  tree->SetDirectory (outputFile);
  
  m_NtupleManager->SetNtupleVars(m_OptionParser,tree);

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODTruthAnalysis :: fileExecute ()
{
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODTruthAnalysis :: changeInput (bool firstFile)
{
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODTruthAnalysis :: initialize ()
{
  //Just print infos
  xAOD::TEvent* event = wk()->xaodEvent(); 
  Info("initialize()", "Number of events = %lli", event->getEntries() ); // print long long int
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODTruthAnalysis :: execute ()
{
  
  //Info("initialize()", "Number of events = %lli", event->getEntries() ); // print long long int
  
  //Clear vectors to be saved in the tree
  m_NtupleManager->ClearCollections();
  //Load xAOD containers
  LoadContainers();
  //Fill TLorentzVectors of all particles
  ParticleFiller();
  //Fill ntuple
  NtupleFiller();
  //Checking some basic cuts, may use it to enable the tree filling
  CutFlow();
  //Clear vectors to be saved in the tree
  ClearParticles();
  
  tree->Fill();

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODTruthAnalysis :: postExecute ()
{
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODTruthAnalysis :: finalize ()
{
  m_CutFlowTools->printAllCutFlow();
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODTruthAnalysis :: histFinalize ()
{
  return EL::StatusCode::SUCCESS;
}


EL::StatusCode MyxAODTruthAnalysis :: LoadContainers()
{
  xAOD::TEvent* event = wk()->xaodEvent(); // you should have already added this as described before
  m_eventInfoCont           =0; EL_RETURN_CHECK("execute()",event->retrieve(m_eventInfoCont     , "EventInfo"));
  m_TruthParticles          =0; EL_RETURN_CHECK("execute()",event->retrieve(m_TruthParticles    , "TruthParticles"));

  mc_event_weight=m_eventInfoCont->mcEventWeight();

  if(deriv==DERIVATION::TRUTH1)
    {
      m_TruthNeutrinos      =0; EL_RETURN_CHECK("execute()",event->retrieve(m_TruthNeutrinos    ,"TruthNeutrinos"));
      m_TruthMuons          =0; EL_RETURN_CHECK("execute()",event->retrieve(m_TruthMuons        ,"TruthMuons"));       
      m_TruthElectrons      =0; EL_RETURN_CHECK("execute()",event->retrieve(m_TruthElectrons    ,"TruthElectrons"));   
      m_TruthTaus           =0; EL_RETURN_CHECK("execute()",event->retrieve(m_TruthTaus         ,"TruthTaus"));         
      m_AntiKt4TruthWZJets  =0; EL_RETURN_CHECK("execute()",event->retrieve(m_AntiKt4TruthWZJets,"AntiKt4TruthWZJets"));
    }

  return EL::StatusCode::SUCCESS;
}


EL::StatusCode MyxAODTruthAnalysis :: ParticleFiller ()
{
  
  //Fills with the GenericSelector
  //TRUTH1 ONLY
  if(deriv==DERIVATION::TRUTH1)
    {
      v_neutrinos = m_GenericSelector->GenericParticle(m_TruthNeutrinos,(float)25000.,(float)10.,
						       m_GenericSelector->CUT_PDG::NO,-1,m_GenericSelector->CUT_STATUS::NO,-1);
      v_muons     = m_GenericSelector->GenericParticle(m_TruthMuons,(float)25000.,(float)2.5,
						       m_GenericSelector->CUT_PDG::NO,-1,m_GenericSelector->CUT_STATUS::NO,-1);
      v_electrons = m_GenericSelector->GenericParticle(m_TruthElectrons,(float)25000.,(float)2.5,
						       m_GenericSelector->CUT_PDG::NO,-1,m_GenericSelector->CUT_STATUS::NO,-1);
      v_taus      = m_GenericSelector->GenericParticle(m_TruthTaus,(float)25000.,(float)2.5,
						       m_GenericSelector->CUT_PDG::NO,-1,m_GenericSelector->CUT_STATUS::NO,-1);
      
      v_AntiKt4TruthWZJets = m_GenericSelector->GenericJet(m_AntiKt4TruthWZJets,(float)25000.,(float)2.5);

      v_HT =  m_GenericSelector->CalculateHT(v_AntiKt4TruthWZJets, v_electrons, v_muons, v_taus, v_neutrinos);

      //If run on Truth1 you won't need to go any further
      return EL::StatusCode::SUCCESS;
    }

  //If run on Truth0 derivations keep going as you will need to access more information and store additional variables

  //Final state matrix-element particles
  std::vector< std::pair< TLorentzVector,int > > AllStablePartons = m_GenericSelector->GetAllPartons(m_TruthParticles, m_GenericSelector->CUT_STATUS::YES, 23);
  v_parton_u    = m_GenericSelector->RetrieveParton(AllStablePartons, m_GenericSelector->CUT_PDG::YES,  2);
  v_parton_au   = m_GenericSelector->RetrieveParton(AllStablePartons, m_GenericSelector->CUT_PDG::YES, -2);
  v_parton_d    = m_GenericSelector->RetrieveParton(AllStablePartons, m_GenericSelector->CUT_PDG::YES,  1);
  v_parton_ad   = m_GenericSelector->RetrieveParton(AllStablePartons, m_GenericSelector->CUT_PDG::YES, -1);
  v_parton_c    = m_GenericSelector->RetrieveParton(AllStablePartons, m_GenericSelector->CUT_PDG::YES,  4);
  v_parton_ac   = m_GenericSelector->RetrieveParton(AllStablePartons, m_GenericSelector->CUT_PDG::YES, -4);
  v_parton_s    = m_GenericSelector->RetrieveParton(AllStablePartons, m_GenericSelector->CUT_PDG::YES,  3);
  v_parton_as   = m_GenericSelector->RetrieveParton(AllStablePartons, m_GenericSelector->CUT_PDG::YES, -3);
  v_parton_b    = m_GenericSelector->RetrieveParton(AllStablePartons, m_GenericSelector->CUT_PDG::YES,  5);
  v_parton_ab   = m_GenericSelector->RetrieveParton(AllStablePartons, m_GenericSelector->CUT_PDG::YES, -5);

  //Intermediate particles
  std::vector< std::pair< TLorentzVector,int > > AllIntermediatePartons = m_GenericSelector->GetAllPartons(m_TruthParticles, m_GenericSelector->CUT_STATUS::YES, 22);
  v_parton_top   = m_GenericSelector->RetrieveParton(AllIntermediatePartons, m_GenericSelector->CUT_PDG::YES,  6 );
  v_parton_atop  = m_GenericSelector->RetrieveParton(AllIntermediatePartons, m_GenericSelector->CUT_PDG::YES, -6 );
  v_parton_wplus = m_GenericSelector->RetrieveParton(AllIntermediatePartons, m_GenericSelector->CUT_PDG::YES,  24);
  v_parton_wminus= m_GenericSelector->RetrieveParton(AllIntermediatePartons, m_GenericSelector->CUT_PDG::YES, -24);
  
  if(proc==PROCESS::TT_H_TT ||  proc==PROCESS::BB_H_TT)v_parton_higgs = m_GenericSelector->RetrieveParton(AllIntermediatePartons, m_GenericSelector->CUT_PDG::ABS,  35);
  else if(proc==PROCESS::TC_H_BB)                      v_parton_higgs = m_GenericSelector->RetrieveParton(AllIntermediatePartons, m_GenericSelector->CUT_PDG::ABS,  25);
  else if(proc==PROCESS::LOWMASSHPLUS)                 v_parton_higgs = m_GenericSelector->RetrieveParton(AllIntermediatePartons, m_GenericSelector->CUT_PDG::ABS,  37);

  //Process specific fills 
  if(proc==PROCESS::TT_H_TT)
    {
      v_parton_ttfromH    = m_ttHttSelector->DecayH(m_TruthParticles,(float)0.,(float)10.,m_ttHttSelector->DECAY_H::ALL);
      v_parton_ttnotfromH = m_ttHttSelector->AssociatedToH(m_TruthParticles,(float)0.,(float)10.,m_ttHttSelector->ASSOCIATED_H::TT);
    }

  else if(proc==PROCESS::BB_H_TT)
    {
      v_parton_ttfromH    = m_bbHttSelector->DecayH(m_TruthParticles,(float)0.,(float)10.,m_bbHttSelector->DECAY_H::ALL);
      v_H_decay_pdgid     = m_bbHttSelector->GetHiggsDecays(m_TruthParticles,35);
      //to be added
      //Implemetation has to make sure that there are no b-quarks from the chains H->b->gb->ggb..
      //v_parton_bbnotfromH = m_bbHttSelector->AssociatedToH(m_TruthParticles,(float)0.,(float)10.,m_bbHttSelector->ASSOCIATED_H::BB);
    }

  else if(proc==PROCESS::TC_H_BB)
    {
      //W boson particle level 
      if(deriv==DERIVATION::TRUTH1 && v_electrons.size()!=0 && v_neutrinos.size()!=0 )
	v_particle_wboson= m_tcHbbSelector->GetParticleW(v_electrons,v_neutrinos);
      
      v_parton_bbfromH    = m_tcHbbSelector->DecayH(m_TruthParticles,(float)0.,(float)10.,m_tcHbbSelector->DECAY_H::ALL);
      v_parton_tcnotfromH = m_tcHbbSelector->AssociatedToH(m_TruthParticles,(float)0.,(float)10.,m_tcHbbSelector->ASSOCIATED_H::TC);
      v_H_decay_pdgid     = m_tcHbbSelector->GetHiggsDecays(m_TruthParticles,25);
    }

  else if(proc==PROCESS::LOWMASSHPLUS)
    {
      v_parton_Hplus_decays  = m_LowMassHplusSelector->DecayH(m_TruthParticles,(float)0.,(float)10., m_LowMassHplusSelector->DECAY_H::ALL);
      v_H_decay_pdgid        = m_LowMassHplusSelector->GetHiggsDecays(m_TruthParticles,37);
      
      //for spin correlation observables

      v_TopDecayChain                 = m_LowMassHplusSelector->GetTopDecayChain(m_TruthParticles);
      v_parton_topdecaychain_lepton   = m_LowMassHplusSelector->GetParticleInTopDecays(v_TopDecayChain, v_leptons_pdgid  );
      v_parton_topdecaychain_neutrino = m_LowMassHplusSelector->GetParticleInTopDecays(v_TopDecayChain, v_neutrinos_pdgid);

      v_angana_lep_top_dphi	  =m_LowMassHplusSelector->CalculateAngle(v_TopDecayChain, m_LowMassHplusSelector->ANGLE::LEP_TOP_DPHI);      
      v_angana_lep_top_dr	  =m_LowMassHplusSelector->CalculateAngle(v_TopDecayChain, m_LowMassHplusSelector->ANGLE::LEP_TOP_DR);        
      v_angana_nu_top_dphi	  =m_LowMassHplusSelector->CalculateAngle(v_TopDecayChain, m_LowMassHplusSelector->ANGLE::NU_TOP_DPHI);       
      v_angana_nu_top_dr	  =m_LowMassHplusSelector->CalculateAngle(v_TopDecayChain, m_LowMassHplusSelector->ANGLE::NU_TOP_DR);         
      v_angana_lep_top_dphi_topcm =m_LowMassHplusSelector->CalculateAngle(v_TopDecayChain, m_LowMassHplusSelector->ANGLE::LEP_TOP_DPHI_TOPCM);
      v_angana_nu_top_dphi_topcm  =m_LowMassHplusSelector->CalculateAngle(v_TopDecayChain, m_LowMassHplusSelector->ANGLE::NU_TOP_DPHI_TOPCM); 
    }

  else if(proc==PROCESS::ZB)
    {
      if     (v_muons.size()==2)      v_Zb_Z = m_ZbSelector->GetZboson(v_muons);
      else if(v_electrons.size()==2)  v_Zb_Z = m_ZbSelector->GetZboson(v_electrons);
      //cut on abs pdgid
      std::vector<TLorentzVector> v_b = m_GenericSelector->GenericParticle(m_TruthParticles,(float)0.,(float)10.,
									   m_GenericSelector->CUT_PDG::ABS,5,
									   m_GenericSelector->CUT_STATUS::YES,23);
      
      if(v_b.size()!=0)v_Zb_wzjets=m_ZbSelector->GetBJets(v_b,v_AntiKt4TruthWZJets);
    }

  return EL::StatusCode::SUCCESS;

}


EL::StatusCode MyxAODTruthAnalysis :: NtupleFiller ()
{
  if(v_neutrinos         .size()!=0)m_NtupleManager->FillParticleCollection(v_neutrinos,         "Neutrinos"         );
  if(v_electrons         .size()!=0)m_NtupleManager->FillParticleCollection(v_electrons,         "Electrons"         );
  if(v_muons             .size()!=0)m_NtupleManager->FillParticleCollection(v_muons,             "Muons"             );
  if(v_taus              .size()!=0)m_NtupleManager->FillParticleCollection(v_taus,              "Taus"              );
  if(v_AntiKt4TruthWZJets.size()!=0)m_NtupleManager->FillParticleCollection(v_AntiKt4TruthWZJets,"AntiKt4TruthWZJets");
  if(v_particle_wboson   .size()!=0)m_NtupleManager->FillParticleCollection(v_particle_wboson,   "ParticleWBoson"    );

  if(v_parton_u          .size()!=0)m_NtupleManager->FillParticleCollection(v_parton_u,          "UpQuarks"          );
  if(v_parton_au         .size()!=0)m_NtupleManager->FillParticleCollection(v_parton_au,         "Anti-UpQuarks"     );
  if(v_parton_d          .size()!=0)m_NtupleManager->FillParticleCollection(v_parton_d,          "DownQuarks"        );
  if(v_parton_ad         .size()!=0)m_NtupleManager->FillParticleCollection(v_parton_ad,         "Anti-DownQuarks"   );
  if(v_parton_c          .size()!=0)m_NtupleManager->FillParticleCollection(v_parton_c,          "CharmQuarks"       );
  if(v_parton_ac         .size()!=0)m_NtupleManager->FillParticleCollection(v_parton_ac,         "Anti-CharmQuarks"  );
  if(v_parton_s          .size()!=0)m_NtupleManager->FillParticleCollection(v_parton_s,          "StrangeQuarks"     );
  if(v_parton_as         .size()!=0)m_NtupleManager->FillParticleCollection(v_parton_as,         "Anti-StrangeQuarks");
  if(v_parton_top        .size()!=0)m_NtupleManager->FillParticleCollection(v_parton_top,        "TopQuarks"         );
  if(v_parton_atop       .size()!=0)m_NtupleManager->FillParticleCollection(v_parton_atop,       "Anti-TopQuarks"    );
  if(v_parton_b          .size()!=0)m_NtupleManager->FillParticleCollection(v_parton_b,          "BottomQuarks"      );
  if(v_parton_ab         .size()!=0)m_NtupleManager->FillParticleCollection(v_parton_ab,         "Anti-BottomQuarks" );
  if(v_parton_wplus      .size()!=0)m_NtupleManager->FillParticleCollection(v_parton_wplus,      "WPlus"             );
  if(v_parton_wminus     .size()!=0)m_NtupleManager->FillParticleCollection(v_parton_wminus,     "WMinus"            );
  if(v_parton_higgs      .size()!=0)m_NtupleManager->FillParticleCollection(v_parton_higgs,      "Higgs"             );

  //tttt/bbtt specific
  if(v_parton_ttfromH     .size()!=0)m_NtupleManager->FillHCollection(v_parton_ttfromH,           "FromH"            );
  if(v_parton_ttnotfromH  .size()!=0)m_NtupleManager->FillHCollection(v_parton_ttnotfromH,        "TTNotFromH"       );
  //tcbb specific
  if(v_parton_bbfromH     .size()!=0)m_NtupleManager->FillHCollection(v_parton_bbfromH,           "FromH"            );
  if(v_parton_tcnotfromH  .size()!=0)m_NtupleManager->FillHCollection(v_parton_tcnotfromH,        "TCNotFromH"       );
  //Hplus
  if(v_parton_Hplus_decays.size()!=0)m_NtupleManager->FillHCollection(v_parton_Hplus_decays,      "FromH"            );

  if(v_parton_topdecaychain_lepton  .size()!=0)m_NtupleManager->FillParticleCollection(v_parton_topdecaychain_lepton  , "Topdecaychain_lepton"   );
  if(v_parton_topdecaychain_neutrino.size()!=0)m_NtupleManager->FillParticleCollection(v_parton_topdecaychain_neutrino, "Topdecaychain_neutrino" );
 
  if(v_HT !=0)m_NtupleManager->FillScalarCollection(v_HT, "HT" );

  if(v_angana_lep_top_dphi	  !=0)m_NtupleManager->FillScalarCollection(v_angana_lep_top_dphi,       "Angana_lep_top_dphi"         );
  if(v_angana_lep_top_dr	  !=0)m_NtupleManager->FillScalarCollection(v_angana_lep_top_dr,         "Angana_lep_top_dr"           );
  if(v_angana_nu_top_dphi	  !=0)m_NtupleManager->FillScalarCollection(v_angana_nu_top_dphi,        "Angana_nu_top_dphi"          );
  if(v_angana_nu_top_dr	          !=0)m_NtupleManager->FillScalarCollection(v_angana_nu_top_dr,          "Angana_nu_top_dr"            );
  if(v_angana_lep_top_dphi_topcm  !=0)m_NtupleManager->FillScalarCollection(v_angana_lep_top_dphi_topcm, "Angana_lep_top_dphi_topcm"   );
  if(v_angana_nu_top_dphi_topcm   !=0)m_NtupleManager->FillScalarCollection(v_angana_nu_top_dphi_topcm,  "Angana_nu_top_dphi_topcm"    );

  if(v_parton_bbfromH.size()!=0 && v_parton_Hplus_decays.size()!=0){
    std::cout<<"Got both a neutral and a charged Higgs, exit now ! "<<std::endl;
    exit(0);
  }

  //Zb specific
  if(v_Zb_Z              .size()!=0){
    std::cout<<"mhm 1"<<std::endl;
    m_NtupleManager->FillParticleCollection(v_Zb_Z,              "Zb_Z"              );
  }
  
  if(v_Zb_wzjets         .size()!=0){
    std::cout<<"mhm 2"<<std::endl;    
    m_NtupleManager->FillParticleCollection(v_Zb_wzjets,         "Zb_wzjets"         );
  }
  //to be added
  //m_NtupleManager->FillHCollection(v_parton_bbnotfromH,        "BBNotFromH"        );

  //temporary implementation
  m_NtupleManager->FillEventCollection(mc_event_weight);
  m_NtupleManager->FillEventCollectionHack(v_H_decay_pdgid);

  return EL::StatusCode::SUCCESS;
}


EL::StatusCode MyxAODTruthAnalysis :: ClearParticles ()
{
  //particle level 
  v_neutrinos.clear(); 
  v_muons.clear(); 
  v_electrons.clear();
  v_taus.clear(); 
  v_AntiKt4TruthWZJets.clear();
  v_particle_wboson.clear();
  //parton level
  v_parton_u.clear(); 
  v_parton_au.clear(); 
  v_parton_d.clear(); 
  v_parton_ad.clear(); 
  v_parton_c.clear(); 
  v_parton_ac.clear(); 
  v_parton_s.clear(); 
  v_parton_as.clear(); 
  v_parton_top.clear(); 
  v_parton_atop.clear(); 
  v_parton_b.clear(); 
  v_parton_ab.clear(); 
  v_parton_wplus.clear();  
  v_parton_wminus.clear();  
  v_parton_higgs.clear(); 
  //process specific
  v_parton_ttfromH.clear(); 
  v_parton_ttnotfromH.clear();
  v_parton_bbfromH.clear(); 
  v_parton_tcnotfromH.clear(); 
  v_parton_Hplus_decays.clear(); 
  v_parton_fromH.clear(); 
  v_Zb_Z.clear();
  v_Zb_wzjets.clear();
  v_H_decay_pdgid.clear();
  v_parton_topdecaychain_lepton.clear();
  v_parton_topdecaychain_neutrino.clear();
  
  v_TopDecayChain.clear();

  mc_event_weight=0;
  v_HT=0.;
  v_angana_lep_top_dphi=0.;
  v_angana_lep_top_dr=0.;
  v_angana_nu_top_dphi=0.;
  v_angana_nu_top_dr=0.;
  v_angana_lep_top_dphi_topcm=0.;
  v_angana_nu_top_dphi_topcm=0.;

  return EL::StatusCode::SUCCESS;

}


bool MyxAODTruthAnalysis :: CutFlow ()
{
  float w = mc_event_weight;

  m_CutFlowTools->cutFlow("Cut-Flow","All" ,1.);
  m_CutFlowTools->cutFlow("Cut-Flow weighted","All" ,w);

  if(deriv==DERIVATION::TRUTH1)
    {

      if(v_muons    .size()>=1)
	{
	  m_CutFlowTools->cutFlow("Cut-Flow","OneMu" ,1.);
	  m_CutFlowTools->cutFlow("Cut-Flow weighted","OneMu" ,w);
	}
  
      if(v_electrons.size()>=1)
	{
	  m_CutFlowTools->cutFlow("Cut-Flow","OneEl" ,1.);
	  m_CutFlowTools->cutFlow("Cut-Flow weighted","OneEl" ,w );
	}
  
      if(v_taus     .size()>=1)
	{
	  m_CutFlowTools->cutFlow("Cut-Flow","OneTau",1.);
	  m_CutFlowTools->cutFlow("Cut-Flow weighted","OneTau",w );
	}

      if(v_neutrinos.size()>=1)
	{
	  m_CutFlowTools->cutFlow("Cut-Flow","OneNu" ,1.);
	  m_CutFlowTools->cutFlow("Cut-Flow weighted","OneNu" ,w );
	}
  
      if(! (v_muons.size()>=1 || v_electrons.size()>=1 || v_taus.size()>=1) ) return false;
      if(! (v_neutrinos.size()>=1) ) return false;
  
      m_CutFlowTools->cutFlow("Cut-Flow","Lep+Nu",1.);
      m_CutFlowTools->cutFlow("Cut-Flow weighted","Lep+Nu",w );
 
      if(v_AntiKt4TruthWZJets.size()==4)
	{
	  m_CutFlowTools->cutFlow("Cut-Flow","FourJets" ,1.);
	  m_CutFlowTools->cutFlow("Cut-Flow weighted","FourJets" ,w );
	}
  
      if(v_AntiKt4TruthWZJets.size()==5)
	{
	  m_CutFlowTools->cutFlow("Cut-Flow","FiveJets" ,1.);
	  m_CutFlowTools->cutFlow("Cut-Flow weighted","FiveJets" ,w );
	}

      if(v_AntiKt4TruthWZJets.size()>=6)
	{
	  m_CutFlowTools->cutFlow("Cut-Flow",">=SixJets",1.);
	  m_CutFlowTools->cutFlow("Cut-Flow weighted",">=SixJets",w );
	}

      if(v_AntiKt4TruthWZJets.size()>=4) return true;
      else return false;

    }
 
  return true;
}
