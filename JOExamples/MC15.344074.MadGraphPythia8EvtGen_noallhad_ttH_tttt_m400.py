from MadGraphControl.MadGraphUtils import *
import fnmatch
import os
import fileinput

nevents=50000
mode=0


### DSID lists (extensions can include systematics samples)
test=[344074]

fcard = None
if runArgs.runNumber in test:
    fcard = """
    set group_subprocesses Auto
    set ignore_six_quark_processes False
    set loop_optimized_output True
    set gauge unitary
    set complex_mass_scheme False
    import model sm
    define p = g u c d s u~ c~ d~ s~
    define wdec = e+ mu+ ta+ e- mu- ta- ve vm vt ve~ vm~ vt~ g u c d s b u~ c~ d~ s~ b~
    import model 2HDMtypeII 
    generate p p > t t~ h2, (h2 > t t~, (t > b w+, w+ > wdec wdec), (t~ > b~ w-, w- > wdec wdec)), (t > b w+, w+ > wdec wdec), (t~ > b~ w-, w- > wdec wdec) 
    output -f"""
else: 
    raise RuntimeError("runNumber %i not recognised in these jobOptions."%runArgs.runNumber)

process_dir = new_process(fcard)

beamEnergy=-999
if hasattr(runArgs,'ecmEnergy'):
    beamEnergy = runArgs.ecmEnergy / 2.
else: 
    raise RuntimeError("No center of mass energy found.")

#Fetch default LO run_card.dat and set parameters
extras = { 'lhe_version':'2.0', 
           'cut_decays':'F', 
           'pdlabel':"'cteq6l1'"}
build_run_card(run_card_old=get_default_runcard(process_dir),run_card_new='run_card.dat',
               nevts=nevents,rand_seed=runArgs.randomSeed,beamEnergy=beamEnergy,extras=extras)

print_cards()
    
runName='run_01'     


str_param_card='MadGraph_2HDM_for_multitops_paramcard_400_new.dat'
for root, dirnames, filenames in os.walk('.'):
    for filename in fnmatch.filter(filenames, str_param_card):
        param_grid_location=(os.path.join(root, filename))

#generate(run_card_loc='run_card.dat',param_card_loc=None,mode=mode,proc_dir=process_dir,run_name=runName)
generate(run_card_loc='run_card.dat',param_card_loc=param_grid_location,mode=mode,proc_dir=process_dir,run_name=runName)
arrange_output(run_name=runName,proc_dir=process_dir,outputDS=runName+'._00001.events.tar.gz')  

   


#### Shower 
evgenConfig.description = 'MadGraph_tttt'
evgenConfig.keywords+=['Higgs','jets']
evgenConfig.inputfilecheck = runName
runArgs.inputGeneratorFile=runName+'._00001.events.tar.gz'

include("MC15JobOptions/Pythia8_A14_NNPDF23LO_EvtGen_Common.py")
include("MC15JobOptions/Pythia8_MadGraph.py")

#--------------------------------------------------------------
# Event filter
#--------------------------------------------------------------
include('MC15JobOptions/TTbarWToLeptonFilter.py')
filtSeq.TTbarWToLeptonFilter.NumLeptons = -1 #no-allhad
filtSeq.TTbarWToLeptonFilter.Ptcut = 0.
evgenConfig.generators  = [ "MadGraph", "Pythia8", "EvtGen"] 
