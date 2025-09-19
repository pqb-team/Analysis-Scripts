#include <string>  
using namespace std;

/////////////////////////////////////////////////////////////
//
// Script for creating sinusoidal fits of bpm & magnet data as a function of event #
// Currently takes only one magnet or bpm, but this can be extended to more as long as the values of params[4] per bpm/magnet are stored in an array or plot
// 
// author : Jonathon Mott
// email : jmott@umass.edu
//
///////////////////////////////////////////////////////////////

void phase_fit(int run_num, int event_min, int event_max, string type, string name, Double_t *params);


//This function takes the following info and performs a sinusoidal fit: Run #, the event range (min/max), the type of object (currently magnet/bpm), and the specific name (of said magnet/bpm)
void simple_phase(int run_num, int event_min, int event_max, string type, string name) {

  Double_t params[4]; //Fit parameters. Stores fit data after the fit has been performed. See definitions below
  phase_fit(run_num, event_min, event_max, type, name, params);

  cout << "\nYour fit parameters are as follows\n" << endl;
  cout << "Amplitude: " << params[0] << endl;
  cout << "Angular Frequency: " << params[1] << endl;
  cout << "Phase: " << params[2] << endl;
  cout << "Offset: " << params[3] << endl;
  cout << "\nDo with this information as you will\n" << endl;

}

//This version of the function uses default values for the analysis
void simple_phase(){
  
  cout << "Using the default parameter values\n" << endl;
  int run_num = 18632;
  int event_min = 7000;
  int event_max = 7100;
  string type = "bpm";
  string name = "bpm11Y";

  Double_t params[4];
  phase_fit(run_num, event_min, event_max, type, name, params);

  cout << "Your fit parameters are as follows" << endl;
  cout << "Amplitude: " << params[0] << endl;
  cout << "Angular Frequency: " << params[1] << endl;
  cout << "Phase: " << params[2] << endl;
  cout << "Offset: " << params[3] << endl;
  cout << "\nDo with this information as you will\n" << endl;

}



void phase_fit(int run_num, int event_min, int event_max,  string type, string name, Double_t *params) {

  TFile *f = new TFile(Form("/chafs2/work1/parity/japanOutput/sbs_CntHouse_%d.root",run_num),"READ"); //Loading the root file

  if (!f || f->IsZombie()) {
    cout << "Error opening file !" << endl;
    return 1;
  }
  TTree *t = (TTree*)f->Get("evt"); //Loading the "evt" TTree
  if (!t) {
    std::cout << "Error: TTree not found!" << std::endl;
    return;
  }

  //Draws the desired data from the TTree and moves it to a histogram for fitting
  t->Draw(Form("%s:Entry$>>h",name.c_str()),Form("ch_cleandata==1 && ch_scandata1==0 && bcm_dg_ds>4 && Entry$>%d && Entry$<%d",event_min,event_max),"goff");
  TH2F* h = (TH2F*)gDirectory->Get("h");

  TF1 *fit = new TF1("fit", "[0]*sin([1]*x + [2]) + [3]", event_min, event_max); //Creating the sinusoidal fit

  //Creating "guess" values for fit parameters
  if (type == "magnet") {
    if (name == "sl20_rf_vernier") {
      fit->SetParameter(0, 3);      // Amplitude guess
      fit->SetParameter(1, 1.55);   // Angular frequency guess (2π*f)
      fit->SetParameter(2, 0.0);    // Phase guess
      fit->SetParameter(3, -256);   // Offset guess
    }
    else {
      fit->SetParameter(0, 10000);  // Amplitude guess
      fit->SetParameter(1, 0.399);  // Angular frequency guess (2π*f)
      fit->SetParameter(2, 0.0);    // Phase guess
      fit->SetParameter(3, 150);    // Offset guess
    }
  }
  else if (type == "bpm") {
    fit->SetParameter(0, 0.1);                       // Amplitude guess
    fit->FixParameter(1, fit->GetParameter(1));  // Angular frequency guess (2π*f)
    fit->SetParameter(2, 0.0);                       // Phase guess
    fit->SetParameter(3, 0.15);                      // Offset guess
  }
  else {
    std::cout << "Error: type not valid" << std::endl;
    return;
  }

  h->Fit("fit", "QN0"); //Applying the fit
  //h->SaveAs("name.extension")

  //Filling params with the fit parameters for use outside this function
  for (int i = 0; i < 4; i++) {
    params[i] = fit->GetParameter(i);
  }

}
