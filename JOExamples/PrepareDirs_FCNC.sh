PROC="410696
410697
410698
410699"

for f in $PROC
do 
    echo "Processing  $f "
    mkdir ${f}
    cp MadGraphControl_ttFCNC_NLO.py ${f}/
    cp MadGraph_param_card_ttFCNC_NLO.dat ${f}/ 
    cp MC15.${f}.aMcAtNloPythia8EvtGen_TopFCNC_HLepFilter_NNPDF30ME_A14_test.py ${f}/  
    cp SetUpDeriv.sh ${f}/ 
    cp SetUp.sh ${f}/ 
    cd ${f}
    
    echo "Generate_tf.py --ecmEnergy=13000. --maxEvents=200 --runNumber=${f} --firstEvent=1 --randomSeed=${f} --outputEVNTFile=EVNT.root --jobConfig=MC15.${f}.aMcAtNloPythia8EvtGen_TopFCNC_HLepFilter_NNPDF30ME_A14_test.py" >> run_${f}.sh

    cd ../
done

