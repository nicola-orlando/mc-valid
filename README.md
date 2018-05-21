### Little package to process truth xAOD's and dump relevant particles/partons in a flat ntuple. 
### Based on standard EventLoop class. 

First import from Gitlab, work in progress

**Get the package**

    git clone ssh://git@github.com/nicola-orlando/mc-valid.git


**Classes description**

To be implemented

**Setup**

(first time)

    source first_setup.sh

(otherwise)

    source setup.sh

rc find_packages

rc compile

**Run**

mkdir Run

cd Run

cp ../macros/RunScript.cxx .

(edit RunScript.cxx adding the dir-path where to find the input root files)

root -l '$ROOTCOREDIR/scripts/load_packages.C' 'RunScript.cxx ("test_1")'

**Other scripts**

A script to make plots is 

    macros/newTruthPlots.C it runs with ROOT 5, not tested yet in ROOT 6. 

To run it you can use 

    macros/new_run_plots.sh 

**Instructions** 

A set of instructions to generate events and produce the relevant derivations is given here 

    GenerationInstructions.txt 

A set of JobOptions, param_cards, .. , is here 

    JOExamples  

They have to be taken only as example, but they should work out of the box. 

A set of MC requests performed with the use of this package are

* bbH(tt) and ttH(tt) https://its.cern.ch/jira/browse/ATLMCPROD-2848
* ttH(bb) https://its.cern.ch/jira/browse/ATLMCPROD-3765
* FCNC h(125) https://its.cern.ch/jira/browse/ATLMCPROD-3570
* Low mass H+ in cs cb decays https://its.cern.ch/jira/browse/ATLMCPROD-4042 

**Current inputs** (might be not always up to date)

1. *Z+b pheno* 
   * /afs/cern.ch/work/o/orlando/zb_asym/Deriv_highmass/
   * /afs/cern.ch/work/o/orlando/zb_asym/Deriv_lowmass/
   * /afs/cern.ch/work/o/orlando/zb_asym/Deriv_zmass/

2. *ttbar background*
   * eos/atlas/user/o/orlando/FCNC_validation/signal_v1/

3. *Updated list of FCNC signals*
   * eos/atlas/user/o/orlando/FCNC_validation/README.txt

4. *Samples for bbH interference* 
   * eos/atlas/user/o/orlando/bbH_interference

5. *Samples for HBSM combination* 
   * eos/atlas/user/o/orlando/HBSM_combination

6. *Samples for Low mass H+*
   * eos/atlas/user/o/orlando/LowMassHplus/v2