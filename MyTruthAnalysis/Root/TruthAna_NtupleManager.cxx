#include "MyTruthAnalysis/TruthAna_OptionParser.h"
#include "MyTruthAnalysis/TruthAna_NtupleManager.h"

TruthAna_NtupleManager::TruthAna_NtupleManager()
{
}

TruthAna_NtupleManager::TruthAna_NtupleManager(TruthAna_OptionParser *opt, TTree *tree)
{
}


TruthAna_NtupleManager::~TruthAna_NtupleManager()
{
}


void TruthAna_NtupleManager::SetNtupleVars(TruthAna_OptionParser *opt, TTree *tree)
{

  tree->Branch("n_mc_event_weight",&n_mc_event_weight);

  //TRUTH1 collections
  tree->Branch("n_neutrinos_pt" , &n_neutrinos_pt      );
  tree->Branch("n_neutrinos_eta", &n_neutrinos_eta     );
  tree->Branch("n_neutrinos_phi", &n_neutrinos_phi     );
  tree->Branch("n_neutrinos_m"  , &n_neutrinos_m       );
  tree->Branch("n_neutrinos_n"  , &n_neutrinos_n       );
  tree->Branch("n_muons_pt"     , &n_muons_pt          );
  tree->Branch("n_muons_eta"    , &n_muons_eta         );
  tree->Branch("n_muons_phi"    , &n_muons_phi         );
  tree->Branch("n_muons_m"      , &n_muons_m           );
  tree->Branch("n_muons_n"      , &n_muons_n           );
  tree->Branch("n_electrons_pt" , &n_electrons_pt      );
  tree->Branch("n_electrons_eta", &n_electrons_eta     );
  tree->Branch("n_electrons_phi", &n_electrons_phi     );
  tree->Branch("n_electrons_m"  , &n_electrons_m       );
  tree->Branch("n_electrons_n"  , &n_electrons_n       );
  tree->Branch("n_taus_pt"      , &n_taus_pt           );                                                       
  tree->Branch("n_taus_eta"     , &n_taus_eta          );                                                       
  tree->Branch("n_taus_phi"     , &n_taus_phi          );                                                       
  tree->Branch("n_taus_m"       , &n_taus_m            );                                                       
  tree->Branch("n_taus_n"       , &n_taus_n            );                                                       
  tree->Branch("n_wzjets_pt"    , &n_wzjets_pt         );
  tree->Branch("n_wzjets_eta"   , &n_wzjets_eta        );
  tree->Branch("n_wzjets_phi"   , &n_wzjets_phi        );
  tree->Branch("n_wzjets_m"     , &n_wzjets_m          );
  tree->Branch("n_wzjets_n"     , &n_wzjets_n          );

  tree->Branch("n_particle_wboson_pt"    , &n_particle_wboson_pt           );
  tree->Branch("n_particle_wboson_eta"   , &n_particle_wboson_eta          );
  tree->Branch("n_particle_wboson_phi"   , &n_particle_wboson_phi          );
  tree->Branch("n_particle_wboson_m"     , &n_particle_wboson_m            );
  tree->Branch("n_particle_wboson_n"     , &n_particle_wboson_n            );

  tree->Branch("n_parton_decay"     , &n_parton_decay              );
  tree->Branch("n_parton_higgs_pt"  , &n_parton_higgs_pt           );
  tree->Branch("n_parton_higgs_eta" , &n_parton_higgs_eta          );
  tree->Branch("n_parton_higgs_phi" , &n_parton_higgs_phi          );
  tree->Branch("n_parton_higgs_m"   , &n_parton_higgs_m            );
  tree->Branch("n_parton_higgs_n"   , &n_parton_higgs_n            );

  tree->Branch("n_parton_u_pt"      , &n_parton_u_pt               );
  tree->Branch("n_parton_u_eta"     , &n_parton_u_eta              );
  tree->Branch("n_parton_u_phi"     , &n_parton_u_phi              );
  tree->Branch("n_parton_u_m"       , &n_parton_u_m                );
  tree->Branch("n_parton_u_n"       , &n_parton_u_n                );
  tree->Branch("n_parton_au_pt"     , &n_parton_au_pt              );
  tree->Branch("n_parton_au_eta"    , &n_parton_au_eta             );
  tree->Branch("n_parton_au_phi"    , &n_parton_au_phi             );
  tree->Branch("n_parton_au_m"      , &n_parton_au_m               );
  tree->Branch("n_parton_au_n"      , &n_parton_au_n               );

  tree->Branch("n_parton_d_pt"      , &n_parton_d_pt               );
  tree->Branch("n_parton_d_eta"     , &n_parton_d_eta              );
  tree->Branch("n_parton_d_phi"     , &n_parton_d_phi              );
  tree->Branch("n_parton_d_m"       , &n_parton_d_m                );
  tree->Branch("n_parton_d_n"       , &n_parton_d_n                );
  tree->Branch("n_parton_ad_pt"     , &n_parton_ad_pt              );
  tree->Branch("n_parton_ad_eta"    , &n_parton_ad_eta             );
  tree->Branch("n_parton_ad_phi"    , &n_parton_ad_phi             );
  tree->Branch("n_parton_ad_m"      , &n_parton_ad_m               );
  tree->Branch("n_parton_ad_n"      , &n_parton_ad_n               );

  tree->Branch("n_parton_c_pt"      , &n_parton_c_pt               );
  tree->Branch("n_parton_c_eta"     , &n_parton_c_eta              );
  tree->Branch("n_parton_c_phi"     , &n_parton_c_phi              );
  tree->Branch("n_parton_c_m"       , &n_parton_c_m                );
  tree->Branch("n_parton_c_n"       , &n_parton_c_n                );
  tree->Branch("n_parton_ac_pt"     , &n_parton_ac_pt              );
  tree->Branch("n_parton_ac_eta"    , &n_parton_ac_eta             );
  tree->Branch("n_parton_ac_phi"    , &n_parton_ac_phi             );
  tree->Branch("n_parton_ac_m"      , &n_parton_ac_m               );
  tree->Branch("n_parton_ac_n"      , &n_parton_ac_n               );

  tree->Branch("n_parton_s_pt"      , &n_parton_s_pt               );
  tree->Branch("n_parton_s_eta"     , &n_parton_s_eta              );
  tree->Branch("n_parton_s_phi"     , &n_parton_s_phi              );
  tree->Branch("n_parton_s_m"       , &n_parton_s_m                );
  tree->Branch("n_parton_s_n"       , &n_parton_s_n                );
  tree->Branch("n_parton_as_pt"     , &n_parton_as_pt              );
  tree->Branch("n_parton_as_eta"    , &n_parton_as_eta             );
  tree->Branch("n_parton_as_phi"    , &n_parton_as_phi             );
  tree->Branch("n_parton_as_m"      , &n_parton_as_m               );
  tree->Branch("n_parton_as_n"      , &n_parton_as_n               );

  tree->Branch("n_parton_top_pt"    , &n_parton_top_pt             );
  tree->Branch("n_parton_top_eta"   , &n_parton_top_eta            );
  tree->Branch("n_parton_top_phi"   , &n_parton_top_phi            );
  tree->Branch("n_parton_top_m"     , &n_parton_top_m              );
  tree->Branch("n_parton_top_n"     , &n_parton_top_n              );
  tree->Branch("n_parton_atop_pt"   , &n_parton_atop_pt            );
  tree->Branch("n_parton_atop_eta"  , &n_parton_atop_eta           );
  tree->Branch("n_parton_atop_phi"  , &n_parton_atop_phi           );
  tree->Branch("n_parton_atop_m"    , &n_parton_atop_m             );
  tree->Branch("n_parton_atop_n"    , &n_parton_atop_n             );

  tree->Branch("n_parton_b_pt"      , &n_parton_b_pt               );
  tree->Branch("n_parton_b_eta"     , &n_parton_b_eta              );
  tree->Branch("n_parton_b_phi"     , &n_parton_b_phi              );
  tree->Branch("n_parton_b_m"       , &n_parton_b_m                );
  tree->Branch("n_parton_b_n"       , &n_parton_b_n                );
  tree->Branch("n_parton_ab_pt"     , &n_parton_ab_pt              );
  tree->Branch("n_parton_ab_eta"    , &n_parton_ab_eta             );
  tree->Branch("n_parton_ab_phi"    , &n_parton_ab_phi             );
  tree->Branch("n_parton_ab_m"      , &n_parton_ab_m               );
  tree->Branch("n_parton_ab_n"      , &n_parton_ab_n               );

  tree->Branch("n_parton_wplus_pt"  , &n_parton_wplus_pt           );
  tree->Branch("n_parton_wplus_eta" , &n_parton_wplus_eta          );
  tree->Branch("n_parton_wplus_phi" , &n_parton_wplus_phi          );
  tree->Branch("n_parton_wplus_m"   , &n_parton_wplus_m            );
  tree->Branch("n_parton_wplus_n"   , &n_parton_wplus_n            );
  tree->Branch("n_parton_wminus_pt" , &n_parton_wminus_pt          );
  tree->Branch("n_parton_wminus_eta", &n_parton_wminus_eta         );
  tree->Branch("n_parton_wminus_phi", &n_parton_wminus_phi         );
  tree->Branch("n_parton_wminus_m"  , &n_parton_wminus_m           );
  tree->Branch("n_parton_wminus_n"  , &n_parton_wminus_n           );

  //bbHtt and ttHtt collections
  tree->Branch("n_parton_ttfromH_pt"       , &n_parton_ttfromH_pt 	              );
  tree->Branch("n_parton_ttfromH_eta"      , &n_parton_ttfromH_eta	              );
  tree->Branch("n_parton_ttfromH_phi"      , &n_parton_ttfromH_phi	              );
  tree->Branch("n_parton_ttfromH_m"        , &n_parton_ttfromH_m  	              );
  tree->Branch("n_parton_ttfromH_n"        , &n_parton_ttfromH_n  	              );
  tree->Branch("n_parton_ttfromH_poscosphi", &n_parton_ttfromH_poscosphi              );
  tree->Branch("n_parton_ttfromH_deltaeta" , &n_parton_ttfromH_deltaeta          );
  tree->Branch("n_parton_ttfromH_deltaphi" , &n_parton_ttfromH_deltaphi          );
  tree->Branch("n_parton_ttfromH_deltar"   , &n_parton_ttfromH_deltar            );

  //ttHtt specific
  tree->Branch("n_parton_ttnotfromH_pt"      , &n_parton_ttnotfromH_pt                );
  tree->Branch("n_parton_ttnotfromH_eta"     , &n_parton_ttnotfromH_eta               );
  tree->Branch("n_parton_ttnotfromH_phi"     , &n_parton_ttnotfromH_phi               );
  tree->Branch("n_parton_ttnotfromH_m"       , &n_parton_ttnotfromH_m                 );
  tree->Branch("n_parton_ttnotfromH_n"       , &n_parton_ttnotfromH_n                 );
  tree->Branch("n_parton_ttnotfromH_deltaeta", &n_parton_ttnotfromH_deltaeta          );
  tree->Branch("n_parton_ttnotfromH_deltaphi", &n_parton_ttnotfromH_deltaphi          );
  tree->Branch("n_parton_ttnotfromH_deltar"  , &n_parton_ttnotfromH_deltar            );

  //bbHtt specific
  tree->Branch("n_parton_bbnotfromH_pt"      , &n_parton_bbnotfromH_pt                );
  tree->Branch("n_parton_bbnotfromH_eta"     , &n_parton_bbnotfromH_eta               );
  tree->Branch("n_parton_bbnotfromH_phi"     , &n_parton_bbnotfromH_phi               );
  tree->Branch("n_parton_bbnotfromH_m"       , &n_parton_bbnotfromH_m                 );
  tree->Branch("n_parton_bbnotfromH_n"       , &n_parton_bbnotfromH_n                 );
  tree->Branch("n_parton_bbnotfromH_deltaeta", &n_parton_bbnotfromH_deltaeta          );
  tree->Branch("n_parton_bbnotfromH_deltaphi", &n_parton_bbnotfromH_deltaphi          );
  tree->Branch("n_parton_bbnotfromH_deltar"  , &n_parton_bbnotfromH_deltar            );

  //Generic collection
  tree->Branch("n_parton_fromH_pt"       , &n_parton_fromH_pt 	              );
  tree->Branch("n_parton_fromH_eta"      , &n_parton_fromH_eta	              );
  tree->Branch("n_parton_fromH_phi"      , &n_parton_fromH_phi	              );
  tree->Branch("n_parton_fromH_m"        , &n_parton_fromH_m  	              );
  tree->Branch("n_parton_fromH_n"        , &n_parton_fromH_n  	              );
  tree->Branch("n_parton_fromH_deltaeta" , &n_parton_fromH_deltaeta           );
  tree->Branch("n_parton_fromH_deltaphi" , &n_parton_fromH_deltaphi           );
  tree->Branch("n_parton_fromH_deltar"   , &n_parton_fromH_deltar             );
  tree->Branch("n_parton_H_decays"       , &n_parton_H_decays                 );

  //Zb collection 
  tree->Branch("n_Zb_Z_pt"       , &n_Zb_Z_pt 	              );
  tree->Branch("n_Zb_Z_eta"      , &n_Zb_Z_eta	              );
  tree->Branch("n_Zb_Z_phi"      , &n_Zb_Z_phi	              );
  tree->Branch("n_Zb_Z_m"        , &n_Zb_Z_m  	              );
  tree->Branch("n_Zb_wzjets_pt"  , &n_Zb_wzjets_pt            );
  tree->Branch("n_Zb_wzjets_eta" , &n_Zb_wzjets_eta           );
  tree->Branch("n_Zb_wzjets_phi" , &n_Zb_wzjets_phi           );
  tree->Branch("n_Zb_wzjets_m"   , &n_Zb_wzjets_m             );
  tree->Branch("n_Zb_wzjets_n"   , &n_Zb_wzjets_n             );

  //H+ angular variables
  tree->Branch("n_parton_topdecaychain_lepton_pt"    , &n_parton_topdecaychain_lepton_pt      );
  tree->Branch("n_parton_topdecaychain_lepton_eta"   , &n_parton_topdecaychain_lepton_eta     );
  tree->Branch("n_parton_topdecaychain_lepton_phi"   , &n_parton_topdecaychain_lepton_phi     );
  tree->Branch("n_parton_topdecaychain_lepton_m"     , &n_parton_topdecaychain_lepton_m       );
  tree->Branch("n_parton_topdecaychain_neutrino_pt"  , &n_parton_topdecaychain_neutrino_pt    );
  tree->Branch("n_parton_topdecaychain_neutrino_eta" , &n_parton_topdecaychain_neutrino_eta   );
  tree->Branch("n_parton_topdecaychain_neutrino_phi" , &n_parton_topdecaychain_neutrino_phi   );
  tree->Branch("n_parton_topdecaychain_neutrino_m"   , &n_parton_topdecaychain_neutrino_m     );

  tree->Branch("n_HT", &n_HT );

  tree->Branch("n_angana_lep_top_dphi"           , &n_angana_lep_top_dphi	     );
  tree->Branch("n_angana_lep_top_dr"             , &n_angana_lep_top_dr		     );
  tree->Branch("n_angana_nu_top_dphi"            , &n_angana_nu_top_dphi      	     );
  tree->Branch("n_angana_nu_top_dr"              , &n_angana_nu_top_dr		     );
  tree->Branch("n_angana_lep_top_dphi_topcm"     , &n_angana_lep_top_dphi_topcm	     );
  tree->Branch("n_angana_nu_top_dphi_topcm"      , &n_angana_nu_top_dphi_topcm	     );

  return;
}


void TruthAna_NtupleManager::FillParticleCollection(std::vector<TLorentzVector> vtlv, std::string coll_name)
{
  int size=vtlv.size();
  
  for(int i=0; i<size; i++)
    {
      float pt =vtlv[i].Pt();
      float eta=vtlv[i].Rapidity();
      float phi=vtlv[i].Phi();
      float m  =vtlv[i].M();


      if(coll_name=="Topdecaychain_lepton")
	{
	  n_parton_topdecaychain_lepton_pt .push_back( pt  );
	  n_parton_topdecaychain_lepton_eta.push_back( eta );
	  n_parton_topdecaychain_lepton_phi.push_back( phi );
	  n_parton_topdecaychain_lepton_m  .push_back( m   );
	}
      else if(coll_name=="Topdecaychain_neutrino")
	{
	  n_parton_topdecaychain_neutrino_pt .push_back( pt  );
	  n_parton_topdecaychain_neutrino_eta.push_back( eta );
	  n_parton_topdecaychain_neutrino_phi.push_back( phi );
	  n_parton_topdecaychain_neutrino_m  .push_back( m   );
	}
      else if(coll_name=="Neutrinos")
	{
	  n_neutrinos_pt  .push_back( pt  );
	  n_neutrinos_eta .push_back( eta );
	  n_neutrinos_phi .push_back( phi );
	  n_neutrinos_m   .push_back( m   ); 
	  n_neutrinos_n   =size;
	}

      else if(coll_name=="Electrons")
	{
	  n_electrons_pt  .push_back( pt  );
	  n_electrons_eta .push_back( eta );
	  n_electrons_phi .push_back( phi );
	  n_electrons_m   .push_back( m   ); 
	  n_electrons_n   =size;
	}

      else if(coll_name=="Muons")
	{
	  n_muons_pt  .push_back( pt  );
	  n_muons_eta .push_back( eta );
	  n_muons_phi .push_back( phi );
	  n_muons_m   .push_back( m   ); 
	  n_muons_n   =size;
	}

      else if(coll_name=="Taus")
	{
	  n_taus_pt  .push_back( pt  );
	  n_taus_eta .push_back( eta );
	  n_taus_phi .push_back( phi );
	  n_taus_m   .push_back( m   ); 
	  n_taus_n   =size;
	}

      else if(coll_name=="AntiKt4TruthWZJets")
	{
	  n_wzjets_pt  .push_back( pt  );
	  n_wzjets_eta .push_back( eta );
	  n_wzjets_phi .push_back( phi );
	  n_wzjets_m   .push_back( m   ); 
	  n_wzjets_n   =size;
	}

      else if(coll_name=="ParticleWBoson")
	{
	  n_particle_wboson_pt  .push_back( pt  );
	  n_particle_wboson_eta .push_back( eta );
	  n_particle_wboson_phi .push_back( phi );
	  n_particle_wboson_m   .push_back( m   ); 
	  n_particle_wboson_n   =size;
	}

      else if(coll_name=="UpQuarks")
      	{
	  n_parton_u_pt  .push_back( pt  );
	  n_parton_u_eta .push_back( eta );
	  n_parton_u_phi .push_back( phi );
	  n_parton_u_m   .push_back( m   ); 
	  n_parton_u_n   =size;
	}
      
      else if(coll_name=="Anti-UpQuarks")
      	{
	  n_parton_au_pt  .push_back( pt  );
	  n_parton_au_eta .push_back( eta );
	  n_parton_au_phi .push_back( phi );
	  n_parton_au_m   .push_back( m   ); 
	  n_parton_au_n   =size;
	}
      
      else if(coll_name=="DownQuarks")
      	{
	  n_parton_d_pt  .push_back( pt  );
	  n_parton_d_eta .push_back( eta );
	  n_parton_d_phi .push_back( phi );
	  n_parton_d_m   .push_back( m   ); 
	  n_parton_d_n   =size;
	}
      
      else if(coll_name=="Anti-DownQuarks")
      	{
	  n_parton_ad_pt  .push_back( pt  );
	  n_parton_ad_eta .push_back( eta );
	  n_parton_ad_phi .push_back( phi );
	  n_parton_ad_m   .push_back( m   ); 
	  n_parton_ad_n   =size;
	}

      else if(coll_name=="CharmQuarks")
      	{
	  n_parton_c_pt  .push_back( pt  );
	  n_parton_c_eta .push_back( eta );
	  n_parton_c_phi .push_back( phi );
	  n_parton_c_m   .push_back( m   ); 
	  n_parton_c_n   =size;
	}
      
      else if(coll_name=="Anti-CharmQuarks")
      	{
	  n_parton_ac_pt  .push_back( pt  );
	  n_parton_ac_eta .push_back( eta );
	  n_parton_ac_phi .push_back( phi );
	  n_parton_ac_m   .push_back( m   ); 
	  n_parton_ac_n   =size;
	}

      else if(coll_name=="StrangeQuarks")
      	{
	  n_parton_s_pt  .push_back( pt  );
	  n_parton_s_eta .push_back( eta );
	  n_parton_s_phi .push_back( phi );
	  n_parton_s_m   .push_back( m   ); 
	  n_parton_s_n   =size;
	}
      
      else if(coll_name=="Anti-StrangeQuarks")
      	{
	  n_parton_as_pt  .push_back( pt  );
	  n_parton_as_eta .push_back( eta );
	  n_parton_as_phi .push_back( phi );
	  n_parton_as_m   .push_back( m   ); 
	  n_parton_as_n   =size;
	}

      else if(coll_name=="TopQuarks")
      	{
	  n_parton_top_pt  .push_back( pt  );
	  n_parton_top_eta .push_back( eta );
	  n_parton_top_phi .push_back( phi );
	  n_parton_top_m   .push_back( m   ); 
	  n_parton_top_n   =size;
	}
      
      else if(coll_name=="Anti-TopQuarks")
      	{
	  n_parton_atop_pt  .push_back( pt  );
	  n_parton_atop_eta .push_back( eta );
	  n_parton_atop_phi .push_back( phi );
	  n_parton_atop_m   .push_back( m   ); 
	  n_parton_atop_n   =size;
	}

      else if(coll_name=="BottomQuarks")
      	{
	  n_parton_b_pt  .push_back( pt  );
	  n_parton_b_eta .push_back( eta );
	  n_parton_b_phi .push_back( phi );
	  n_parton_b_m   .push_back( m   ); 
	  n_parton_b_n   =size;
	}
      
      else if(coll_name=="Anti-BottomQuarks")
      	{
	  n_parton_ab_pt  .push_back( pt  );
	  n_parton_ab_eta .push_back( eta );
	  n_parton_ab_phi .push_back( phi );
	  n_parton_ab_m   .push_back( m   ); 
	  n_parton_ab_n   =size;
	}

      else if(coll_name=="WPlus")
      	{
	  n_parton_wplus_pt .push_back( pt  );
	  n_parton_wplus_eta.push_back( eta );
	  n_parton_wplus_phi.push_back( phi );
	  n_parton_wplus_m  .push_back( m   ); 
	  n_parton_wplus_n  =size;
	}
      
      else if(coll_name=="WMinus")
      	{
	  n_parton_wminus_pt .push_back( pt  );
	  n_parton_wminus_eta.push_back( eta );
	  n_parton_wminus_phi.push_back( phi );
	  n_parton_wminus_m  .push_back( m   ); 
	  n_parton_wminus_n  =size;
	}
      
      else if(coll_name=="Higgs")
	{
	  n_parton_higgs_pt  .push_back( pt  );
	  n_parton_higgs_eta .push_back( eta );
	  n_parton_higgs_phi .push_back( phi );
	  n_parton_higgs_m   .push_back( m   ); 
	  n_parton_higgs_n   =size;               
	}
      
      else if(coll_name=="Zb_Z")
	{
	  n_Zb_Z_pt  .push_back( pt  );
	  n_Zb_Z_eta .push_back( eta );
	  n_Zb_Z_phi .push_back( phi );
	  n_Zb_Z_m   .push_back( m   );
	}
      else if(coll_name=="Zb_wzjets")
	{
	  n_Zb_wzjets_pt  .push_back( pt  );
	  n_Zb_wzjets_eta .push_back( eta );
	  n_Zb_wzjets_phi .push_back( phi );
	  n_Zb_wzjets_m   .push_back( m   );
	  n_Zb_wzjets_n   =size;               
	}
      else
	{
	  std::cout<<"Trying to fill the non-existing particle collection "<< coll_name<< " exit now!"<<std::endl;
	  exit(0);
	}
    }
  return;
}

void TruthAna_NtupleManager::FillHCollection(std::vector<TLorentzVector> vtlv, std::string coll_name)
{
  if(coll_name=="TTFromH")
    {
      n_parton_ttfromH_pt .push_back(vtlv[2].Pt());
      n_parton_ttfromH_eta.push_back(vtlv[2].Rapidity());
      n_parton_ttfromH_phi.push_back(vtlv[2].Phi());
      n_parton_ttfromH_m  .push_back(vtlv[2].M());
      n_parton_ttfromH_n  =vtlv.size();
      n_parton_ttfromH_deltaeta.push_back(vtlv[0].Rapidity()-vtlv[1].Rapidity());  
      n_parton_ttfromH_deltaphi.push_back(vtlv[0].DeltaPhi(vtlv[1]));  
      n_parton_ttfromH_deltar  .push_back(vtlv[0].DeltaR(vtlv[1]));  
    }

  else if(coll_name=="TTNotFromH")
    {
      n_parton_ttnotfromH_pt .push_back(vtlv[2].Pt());
      n_parton_ttnotfromH_eta.push_back(vtlv[2].Rapidity());
      n_parton_ttnotfromH_phi.push_back(vtlv[2].Phi());
      n_parton_ttnotfromH_m  .push_back(vtlv[2].M());
      n_parton_ttnotfromH_n  =vtlv.size();
      n_parton_ttnotfromH_deltaeta.push_back(vtlv[0].Rapidity()-vtlv[1].Rapidity());  
      n_parton_ttnotfromH_deltaphi.push_back(vtlv[0].DeltaPhi(vtlv[1]));  
      n_parton_ttnotfromH_deltar  .push_back(vtlv[0].DeltaR(vtlv[1]));  
    }

  else if(coll_name=="BBNotFromH")
    {
      n_parton_bbnotfromH_pt .push_back(vtlv[2].Pt());
      n_parton_bbnotfromH_eta.push_back(vtlv[2].Rapidity());
      n_parton_bbnotfromH_phi.push_back(vtlv[2].Phi());
      n_parton_bbnotfromH_m  .push_back(vtlv[2].M());
      n_parton_bbnotfromH_n  =vtlv.size();
      n_parton_bbnotfromH_deltaeta.push_back(vtlv[0].Rapidity()-vtlv[1].Rapidity());  
      n_parton_bbnotfromH_deltaphi.push_back(vtlv[0].DeltaPhi(vtlv[1]));  
      n_parton_bbnotfromH_deltar  .push_back(vtlv[0].DeltaR(vtlv[1]));  
    }

  else if(coll_name=="TCNotFromH")
    {
      n_parton_tcnotfromH_pt .push_back(vtlv[2].Pt());
      n_parton_tcnotfromH_eta.push_back(vtlv[2].Rapidity());
      n_parton_tcnotfromH_phi.push_back(vtlv[2].Phi());
      n_parton_tcnotfromH_m  .push_back(vtlv[2].M());
      n_parton_tcnotfromH_n  =vtlv.size();
      n_parton_tcnotfromH_deltaeta.push_back(vtlv[0].Rapidity()-vtlv[1].Rapidity());  
      n_parton_tcnotfromH_deltaphi.push_back(vtlv[0].DeltaPhi(vtlv[1]));  
      n_parton_tcnotfromH_deltar  .push_back(vtlv[0].DeltaR(vtlv[1]));  
    }

  else if(coll_name=="FromH")
    {
      n_parton_fromH_pt .push_back(vtlv[2].Pt());
      n_parton_fromH_eta.push_back(vtlv[2].Rapidity());
      n_parton_fromH_phi.push_back(vtlv[2].Phi());
      n_parton_fromH_m  .push_back(vtlv[2].M());
      n_parton_fromH_n  =vtlv.size();
      n_parton_fromH_deltaeta.push_back(vtlv[0].Rapidity()-vtlv[1].Rapidity());  
      n_parton_fromH_deltaphi.push_back(vtlv[0].DeltaPhi(vtlv[1]));  
      n_parton_fromH_deltar  .push_back(vtlv[0].DeltaR(vtlv[1]));  
    }
  else 	
    {
      std::cout<<"Trying to fill the non-existing particle collection "<< coll_name<< " exit now!"<<std::endl;
      exit(0);
    }
  
  return;
}

//Temporary implementation
void TruthAna_NtupleManager::FillEventCollection(float mc_event_weight)
{
  n_mc_event_weight=mc_event_weight;
  return;
}

void TruthAna_NtupleManager::FillScalarCollection(float variable, std::string coll_name)
{
  if     (coll_name=="Angana_lep_top_dphi"      ){ n_angana_lep_top_dphi      =variable;}
  else if(coll_name=="Angana_lep_top_dr"        ){ n_angana_lep_top_dr        =variable;}
  else if(coll_name=="Angana_nu_top_dphi"       ){ n_angana_nu_top_dphi       =variable;}
  else if(coll_name=="Angana_nu_top_dr"         ){ n_angana_nu_top_dr         =variable;}
  else if(coll_name=="Angana_lep_top_dphi_topcm"){ n_angana_lep_top_dphi_topcm=variable;}
  else if(coll_name=="Angana_nu_top_dphi_topcm" ){ n_angana_nu_top_dphi_topcm =variable;}
  else if(coll_name=="HT" ){ n_HT =variable;}
  else
    {
      std::cout<<"Trying to fill the non-existing particle collection "<< coll_name<< " exit now!"<<std::endl;
      exit(0);
    }
  return;
}

void TruthAna_NtupleManager::FillEventCollectionHack(std::vector<int> parton_H_decays)
{
  int size=parton_H_decays.size();
  
  for(int i=0; i<size; i++)
    {
      n_parton_H_decays.push_back(parton_H_decays[i]);
    }
}

void TruthAna_NtupleManager::ClearCollections()
{
  n_mc_event_weight=0.;
  
  n_neutrinos_pt .clear();                                                                           
  n_neutrinos_eta.clear();                                                                           
  n_neutrinos_phi.clear();                                                                           
  n_neutrinos_m  .clear();                                                                           
  n_neutrinos_n  =0;

  n_muons_pt .clear();                                                                               
  n_muons_eta.clear();                                                                               
  n_muons_phi.clear();                                                                               
  n_muons_m  .clear();                                                                               
  n_muons_n  =0;                                                                               

  n_electrons_pt .clear();                                                                           
  n_electrons_eta.clear();                                                                           
  n_electrons_phi.clear();                                                                           
  n_electrons_m  .clear();                                                                           
  n_electrons_n  =0;

  n_taus_pt .clear();                                                                                
  n_taus_eta.clear();                                                                                
  n_taus_phi.clear();                                                                                
  n_taus_m  .clear();           
  n_taus_n  =0;
  
  n_wzjets_pt .clear();                                                                              
  n_wzjets_eta.clear();                                                                              
  n_wzjets_phi.clear();                                                                              
  n_wzjets_m  .clear();         
  n_wzjets_n  =0;      

  n_particle_wboson_pt .clear(); 
  n_particle_wboson_eta.clear(); 
  n_particle_wboson_phi.clear(); 
  n_particle_wboson_m  .clear(); 
  n_particle_wboson_n  =0;       
  
  //Other collections
  
  //Generic parton collections

  n_parton_decay    =0;

  n_parton_higgs_pt .clear();                                                                               
  n_parton_higgs_eta.clear();                                                                               
  n_parton_higgs_phi.clear();                                                                               
  n_parton_higgs_m  .clear();                    
  n_parton_higgs_n  =0;

  n_parton_u_pt .clear();                                                                               
  n_parton_u_eta.clear();                                                                               
  n_parton_u_phi.clear();                                                                               
  n_parton_u_m  .clear();                    
  n_parton_u_n  =0;

  n_parton_au_pt .clear();                                                                               
  n_parton_au_eta.clear();                                                                               
  n_parton_au_phi.clear();                                                                               
  n_parton_au_m  .clear();                    
  n_parton_au_n =0;

  n_parton_d_pt .clear();                                                                               
  n_parton_d_eta.clear();                                                                               
  n_parton_d_phi.clear();                                                                               
  n_parton_d_m  .clear();                    
  n_parton_d_n  =0;

  n_parton_ad_pt .clear();                                                                               
  n_parton_ad_eta.clear();                                                                               
  n_parton_ad_phi.clear();                                                                               
  n_parton_ad_m  .clear();                    
  n_parton_ad_n =0;

  n_parton_c_pt .clear();                                                                               
  n_parton_c_eta.clear();                                                                               
  n_parton_c_phi.clear();                                                                               
  n_parton_c_m  .clear();                    
  n_parton_c_n  =0;

  n_parton_ac_pt .clear();                                                                               
  n_parton_ac_eta.clear();                                                                               
  n_parton_ac_phi.clear();                                                                               
  n_parton_ac_m  .clear();                    
  n_parton_ac_n =0;

  n_parton_s_pt .clear();                                                                               
  n_parton_s_eta.clear();                                                                               
  n_parton_s_phi.clear();                                                                               
  n_parton_s_m  .clear();                    
  n_parton_s_n  =0;

  n_parton_as_pt .clear();                                                                               
  n_parton_as_eta.clear();                                                                               
  n_parton_as_phi.clear();                                                                               
  n_parton_as_m  .clear();                    
  n_parton_as_n =0;

  n_parton_top_pt .clear();                                                                               
  n_parton_top_eta.clear();                                                                               
  n_parton_top_phi.clear();                                                                               
  n_parton_top_m  .clear();                    
  n_parton_top_n  =0;

  n_parton_atop_pt .clear();                                                                               
  n_parton_atop_eta.clear();                                                                               
  n_parton_atop_phi.clear();                                                                               
  n_parton_atop_m  .clear();                    
  n_parton_atop_n   =0;      

  n_parton_b_pt .clear();                                                                               
  n_parton_b_eta.clear();                                                                               
  n_parton_b_phi.clear();                                                                               
  n_parton_b_m  .clear();                    
  n_parton_b_n  =0;

  n_parton_ab_pt .clear();                                                                               
  n_parton_ab_eta.clear();                                                                               
  n_parton_ab_phi.clear();                                                                               
  n_parton_ab_m  .clear();                    
  n_parton_ab_n =0;

  n_parton_wplus_pt  .clear(); 
  n_parton_wplus_eta .clear();
  n_parton_wplus_phi .clear();
  n_parton_wplus_m   .clear();
  n_parton_wplus_n   =0;      

  n_parton_wminus_pt .clear();
  n_parton_wminus_eta.clear();
  n_parton_wminus_phi.clear();
  n_parton_wminus_m  .clear();
  n_parton_wminus_n  =0;      
  
  //bbHtt and ttHtt collections
  n_parton_ttfromH_pt .clear();                                                                           
  n_parton_ttfromH_eta.clear();                                                                             
  n_parton_ttfromH_phi.clear();                                                                             
  n_parton_ttfromH_m  .clear();                    
  n_parton_ttfromH_n  =0;
  n_parton_ttfromH_poscosphi .clear();                    
  n_parton_ttfromH_deltaeta  .clear();                    
  n_parton_ttfromH_deltaphi  .clear();                    
  n_parton_ttfromH_deltar    .clear();                    

  //ttHtt specific
  n_parton_ttnotfromH_pt .clear();                                                                           
  n_parton_ttnotfromH_eta.clear();                                                                         
  n_parton_ttnotfromH_phi.clear();                                                                         
  n_parton_ttnotfromH_m  .clear();                    
  n_parton_ttnotfromH_n  =0;
  n_parton_ttnotfromH_deltaeta  .clear();                    
  n_parton_ttnotfromH_deltaphi  .clear();                    
  n_parton_ttnotfromH_deltar    .clear();                    

  //bbHtt specific
  n_parton_bbnotfromH_pt .clear();                                                                           
  n_parton_bbnotfromH_eta.clear();                                                                         
  n_parton_bbnotfromH_phi.clear();                                                                         
  n_parton_bbnotfromH_m  .clear();                    
  n_parton_bbnotfromH_n  =0;       
  n_parton_bbnotfromH_deltaeta.clear();                    
  n_parton_bbnotfromH_deltaphi.clear();                    
  n_parton_bbnotfromH_deltar  .clear();                    

  //tcHbb specific
  n_parton_tcnotfromH_pt .clear();                                                                          
  n_parton_tcnotfromH_eta.clear();                                                                        
  n_parton_tcnotfromH_phi.clear();                                                                        
  n_parton_tcnotfromH_m  .clear();                   
  n_parton_tcnotfromH_n  =0;          
  n_parton_tcnotfromH_deltaeta.clear();
  n_parton_tcnotfromH_deltaphi.clear();
  n_parton_tcnotfromH_deltar  .clear();
  n_parton_H_decays.clear();

  n_parton_fromH_pt .clear();
  n_parton_fromH_eta.clear();
  n_parton_fromH_phi.clear();
  n_parton_fromH_m  .clear();
  n_parton_fromH_n  =0;      
  n_parton_fromH_deltaeta.clear(); 
  n_parton_fromH_deltaphi.clear(); 
  n_parton_fromH_deltar  .clear();

  //Zb collections
  n_Zb_Z_pt  .clear();
  n_Zb_Z_eta .clear();
  n_Zb_Z_phi .clear();
  n_Zb_Z_m   .clear();
  n_Zb_wzjets_pt .clear();
  n_Zb_wzjets_eta.clear();
  n_Zb_wzjets_phi.clear();
  n_Zb_wzjets_m  .clear();
  n_Zb_wzjets_n  =0;

  n_parton_topdecaychain_lepton_pt .clear();
  n_parton_topdecaychain_lepton_eta.clear();
  n_parton_topdecaychain_lepton_phi.clear();
  n_parton_topdecaychain_lepton_m  .clear();

  n_parton_topdecaychain_neutrino_pt .clear();
  n_parton_topdecaychain_neutrino_eta.clear();
  n_parton_topdecaychain_neutrino_phi.clear();
  n_parton_topdecaychain_neutrino_m  .clear();

  n_HT =0.;

  n_angana_lep_top_dphi =0.;
  n_angana_lep_top_dr   =0.;
  n_angana_nu_top_dphi  =0.;
  n_angana_nu_top_dr    =0.;

  n_angana_lep_top_dphi_topcm =0.;
  n_angana_nu_top_dphi_topcm  =0.;

  return;
}
