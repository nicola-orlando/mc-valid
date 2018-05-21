#include <EventLoopAlgs/NTupleSvc.h>
#include <EventLoop/OutputStream.h>

void RunScript (const std::string& submitDir)
{
  // Set up the job for xAOD access:
  xAOD::Init().ignore();

  // create a new sample handler to describe the data files we use
  SH::SampleHandler sh;
  //const char* inputFilePath_1 = gSystem->ExpandPathName("eos/atlas/user/o/orlando/FCNC_validation/signal_v1/");
  //SH::ScanDir().filePattern("*").scan(sh, inputFilePath_1);
  
  const char* inputFilePath_1 = gSystem->ExpandPathName("eos/atlas/user/o/orlando/LowMassHplus/v2/user.orlando._test_999892_v2_EXT0/");
  const char* inputFilePath_2 = gSystem->ExpandPathName("eos/atlas/user/o/orlando/LowMassHplus/v2/TestNoPolarisation/");
  SH::ScanDir().filePattern("*TRUTH1*").scan(sh, inputFilePath_1);
  SH::ScanDir().filePattern("*TRUTH1*").scan(sh, inputFilePath_2);

 
  // set the name of the tree in our files
  // in the xAOD the TTree containing the EDM containers is "CollectionTree"
  sh.setMetaString ("nc_tree", "CollectionTree");
  sh.print ();

  EL::Job job;
  job.sampleHandler (sh); // use SampleHandler in this job
  job.options()->setDouble (EL::Job::optMaxEvents, 10000000000); // for testing purposes, limit to run over the first 500 events only!

  // define an output and an ntuple associated to that output
  EL::OutputStream output  ("myOutput");
  job.outputAdd (output);
  EL::NTupleSvc *ntuple = new EL::NTupleSvc ("myOutput");
  job.algsAdd (ntuple);

  MyxAODTruthAnalysis *alg = new MyxAODTruthAnalysis;
  job.algsAdd (alg);

  alg->outputName = "myOutput"; // give the name of the output to our algorithm

  EL::DirectDriver driver;
  driver.submit (job, submitDir);
}
