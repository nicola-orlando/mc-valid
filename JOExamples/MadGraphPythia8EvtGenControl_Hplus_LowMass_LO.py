#--------------------------------------------------------------
# on-the-fly generation of H+ MG5 events, montoya@cern.ch
#--------------------------------------------------------------

from MadGraphControl.MadGraphUtils import *
#
nevents=10000
mode=0

### DSID lists (extensions can include systematics samples) -> To be filled

decay_taunu=[]
decay_cb=[]
decay_cs=[]

for x in xrange(344287,344295): decay_taunu.append(x)
for x in xrange(999983,999999): decay_cb.append(x)
for x in xrange(999883,999899): decay_cs.append(x)

fcard = open('proc_card_mg5.dat','w')

#No spin correlation accounted for
if runArgs.runNumber in decay_taunu :
    fcard.write("""
    set group_subprocesses Auto
    set ignore_six_quark_processes False   
    set loop_optimized_output True
    set complex_mass_scheme False
    import model sm
    define p = g u c d s u~ c~ d~ s~
    define j = g u c d s u~ c~ d~ s~
    define l+ = e+ mu+
    define l- = e- mu-
    define vl = ve vm vt
    define vl~ = ve~ vm~ vt~       
    import model 2HDMtypeII             
    generate p p > t t~ 
    output -f""")
    fcard.close()

elif runArgs.runNumber in decay_cb or runArgs.runNumber in decay_cs :
    #removed for the time being
    #add process p p > t t~, (t > b w+, w+ > l+ vl), (t~ > b~ h-)
    fcard.write("""
    set group_subprocesses Auto
    set ignore_six_quark_processes False   
    set loop_optimized_output True
    set complex_mass_scheme False
    import model sm
    define p = g u c d s u~ c~ d~ s~
    define j = g u c d s u~ c~ d~ s~
    define l+ = e+ mu+ ta+
    define l- = e- mu- ta-
    define vl = ve vm vt
    define vl~ = ve~ vm~ vt~       
    import model 2HDMtypeII             
    generate p p > t t~, (t~ > b~ w-, w- > l- vl~), (t > b h+)
    output -f""")
    fcard.close()
else: 
    raise RuntimeError("runNumber %i not recognised in these jobOptions."%runArgs.runNumber)

#generate p p > t~ h+ b [QCD]               
beamEnergy=-999
if hasattr(runArgs,'ecmEnergy'):
    beamEnergy = runArgs.ecmEnergy / 2.
else: 
    raise RuntimeError("No center of mass energy found.")

#--------------------------------------------------------------
# Charge Higgs, and all other masses in GeV
#--------------------------------------------------------------
###
mhc_str = str(runArgs.jobConfig[0])  # JOB OPTION NAME MUST CONTAIN THE MASS WE WANT TO SIMULATE IN FORMAT LIKE: *_H400_*
mhc=0
int(s) 
for s in mhc_str.split("_"):
    ss=s.replace("H","")  
    if ss.isdigit():
        mhc = int(ss)        
        print  "Charged Higgs mass set to %i"%mhc
if mhc==0:
   raise RuntimeError("Charged Higgs mass not set, mhc=0, check joOption name %s"%mhc_str)
###
import math
mh1=1.250e+02                 
mh2=math.sqrt(math.pow(mhc,2)+math.pow(8.0399e+01,2)) 
mh3=mh2


extras = { 'lhe_version':'3.0',                        # These two are not present in NLO cards, 
           'cut_decays':'F',                           # lhe version fixed by arrange_output function   
           'pdlabel':"'nn23lo'",
           'parton_shower':'PYTHIA8',
           'fixed_ren_scale':'F',#use dynamic
           'fixed_fac_scale':'F',
           # 'muR_ref_fixed':str(scale), 
           # 'muF1_ref_fixed':str(scale), 
           # 'muF2_ref_fixed':str(scale),
           'PDF_set_min':'246800',
           'PDF_set_max':'246900'
           }
process_dir = new_process()

build_run_card(run_card_old=get_default_runcard(process_dir),run_card_new='run_card.dat',nevts=nevents,rand_seed=runArgs.randomSeed,beamEnergy=beamEnergy,extras=extras)

#Build param_card.dat from UFO, and set Higgs masses
#write_param_card is part of the 2HDMTypeII model
import os
import sys
sys.path.append( os.environ['MADPATH']+'/models/2HDMtypeII/' )
from write_param_card import ParamCardWriter
ParamCardWriter('param_card.TMP.dat')
masses = {'25':str(mh1)+'  #  mh1',
          '35':str(mh2)+'  #  mh2',
          '36':str(mh2)+'  #  mh2',
          '37':str(mhc)+'  #  mhc'}

decayss={'6': 'DECAY 6 1.508336e+00',
'37': 'DECAY 37 1.300000e+02 # whc'}
build_param_card(param_card_old='param_card.TMP.dat',param_card_new='param_card.dat',masses=masses,decays=decayss) 

print_cards()

runName='run_01'     

generate(run_card_loc='run_card.dat',param_card_loc='param_card.dat',mode=mode,proc_dir=process_dir,run_name=runName)

arrange_output(run_name=runName,lhe_version=3,proc_dir=process_dir,outputDS=runName+'._00001.events.tar.gz')                                             

#### Shower     
include("MC15JobOptions/Pythia8_A14_NNPDF23LO_EvtGen_Common.py")
include("MC15JobOptions/Pythia8_MadGraph.py")

evgenConfig.description = 'MadGraph low mass charged Higgs LO'
evgenConfig.keywords+=['Higgs','MSSM','BSMHiggs','chargedHiggs']
evgenConfig.contact = ['G. Carrillo-Montoya']

evgenConfig.inputfilecheck = runName
runArgs.inputGeneratorFile=runName+'._00001.events.tar.gz'

dotaunu=False
for s in mhc_str.split("_"):
    ss=s.replace(".py","")  
    print ss
    if ss=='taunu' and runArgs.runNumber in decay_taunu:
        dotaunu=True

docb=False
for s in mhc_str.split("_"):
    ss=s.replace(".py","")
    print ss
    if ss=='cb' and runArgs.runNumber in decay_cb:
        docb=True

docs=False
for s in mhc_str.split("_"):
    ss=s.replace(".py","")
    print ss
    if ss=='cs' and runArgs.runNumber in decay_cs:
        docs=True

if dotaunu==False and docb==False and docs==False:
    raise RuntimeError("No decay mode was identified, check jobOption name %s, and/or runNumber %i."%(runArgs.jobConfig[0],runArgs.runNumber))

if dotaunu == True : 
    print "Turning on the top decays for the tau channel"
    genSeq.Pythia8.Commands += ["Higgs:useBSM = on",
                                "6:onMode = off",                   # turn off all top decays
                                "6:onPosIfMatch = 5 37",
                                "6:onNegIfMatch = 5 24",
                                ]
    print "Got the top decays for the tau channel"

if dotaunu:
    genSeq.Pythia8.Commands += ["Higgs:useBSM = on",
                                "37:onMode = off",                   # turn off all mhc decays
                                "37:onIfMatch = 15 16"]              # switch on H+ to taunu
    evgenConfig.keywords+=['tau','neutrino']

elif docb:
    genSeq.Pythia8.Commands += ["Higgs:useBSM = on",
                                "37:onMode = off",                   # turn off all mhc decays               
                                '37:addChannel = 1 1. 0 4 -5']
                                #'37:addChannel = 1 1. 0 -4 5']
    evgenConfig.keywords+=['charm','bottom']
elif docs:
    genSeq.Pythia8.Commands += ["Higgs:useBSM = on",
                                "37:onMode = off",                   # turn off all mhc decays
                                "37:onIfMatch = 3 4"]              # switch on H+ to cs
    evgenConfig.keywords+=['charm']

else :      
    raise RuntimeError("No H+ decays are identified, check jobOption name %s, and/or runNumber %i."%(runArgs.jobConfig[0],runArgs.runNumber))
