  
/////////////////////////////////////////////////////////////
//
// Script for extracting the spotsize of the beam at varying positions
// author : Jonathon Mott
// email : jmott@umass.edu
//
///////////////////////////////////////////////////////////////


// All current xpos & ypos vectors are for run 20507


//Gives the spotsize of each bpm at specific x/y coordinates
void spotsize_grid(int run_num) {
  TFile *f = new TFile(Form("/chafs2/work1/parity/japanOutput/prexinj_%d.000.root",run_num),"READ");

  if (!f || f->IsZombie()) {
    cout << "Error opening file !" << endl;
    return 1;
  }

  TTree *t = (TTree*)f->Get("mul");
  if (!t) {
    std::cout << "Error: TTree not found!" << std::endl;
    return;
  }

  gSystem->mkdir("plots");
  gSystem->mkdir("plots/spotsize");

  TString bpm[]={"2i01aX"};
  int xpos[]={13000,13250,13500,13750,14000};
  int ypos[]={18500,18750,19000,19250,19500};
  //int xpos[]={13000};
  //int ypos[]={18500};
  
  int num_bpm = (sizeof(bpm)/sizeof(*bpm));
  int num_xpos = (sizeof(xpos)/sizeof(*xpos));
  int num_ypos = (sizeof(ypos)/sizeof(*ypos));

  for (int i=0; i<num_bpm; i++) {
    for (int j=0; j<num_xpos; j++) {
      for (int k=0; k<num_ypos; k++) {
        TCanvas *c1 = new TCanvas(Form("%s_X%d_Y%d",bpm[i].Data(),xpos[j],ypos[k]),Form("%s_X%d_Y%d",bpm[i].Data(),xpos[j],ypos[k]));
        c1->cd();
        t->Draw(Form("diff_bpm%s/um",bpm[i].Data()),Form("cleandata && scandata1==%d && scandata2==%d",xpos[j],ypos[k]));         


        const char* currentDir = gSystem->pwd();
        std::string fullPath = std::string(currentDir) + "/" + "plots/spotsize";
        std::string filePath = fullPath + Form("/%s_X%d_Y%d.root",bpm[i].Data(),xpos[j],ypos[k]);
        c1->SaveAs(filePath.c_str());
        delete c1;

      }
    }
  }
}



//Gives the spotsize as a function of x/y positions
void spotsize_fit(int run_num) {
  TFile *f = new TFile(Form("/chafs2/work1/parity/japanOutput/prexinj_%d.000.root",run_num),"READ");

  if (!f || f->IsZombie()) {
    cout << "Error opening file !" << endl;
    return 1;
  }

  TTree *t = (TTree*)f->Get("mul");
  if (!t) {
    std::cout << "Error: TTree not found!" << std::endl;
    return;
  }

  gSystem->mkdir("plots");
  gSystem->mkdir("plots/spotsize");

  TString bpm[]={"2i00X"};
  int xpos[]={13000,13250,13500,13750,14000};
  int ypos[]={18500,18750,19000,19250,19500};

  int num_bpm = (sizeof(bpm)/sizeof(*bpm));
  int num_xpos = (sizeof(xpos)/sizeof(*xpos));
  int num_ypos = (sizeof(ypos)/sizeof(*ypos));

  for (int i=0; i<num_bpm; i++) {
    for (int j=0; j<num_xpos; j++) {
      TCanvas *c1 = new TCanvas(Form("Fit_%s_X%d",bpm[i].Data(),xpos[j]),Form("Fit_%s_X%d",bpm[i].Data(),xpos[j]));
      c1->cd();
      t->Draw(Form("diff_bpm%s/um:scandata2",bpm[i].Data()),Form("cleandata && scandata1==%d",xpos[j]),"prof");
      
      const char* currentDir = gSystem->pwd();
      std::string fullPath = std::string(currentDir) + "/" + "plots/spotsize";
      std::string filePath = fullPath + Form("/Fit_%s_X%d.root",bpm[i].Data(),xpos[j]);
      c1->SaveAs(filePath.c_str());
      delete c1;

    }
    for (int j=0; j<num_ypos; j++) {
      TCanvas *c1 = new TCanvas(Form("Fit_%s_Y%d",bpm[i].Data(),ypos[j]),Form("Fit_%s_Y%d",bpm[i].Data(),ypos[j]));
      c1->cd();
      t->Draw(Form("diff_bpm%s/um:scandata1",bpm[i].Data()),Form("cleandata && scandata2==%d",ypos[j]),"prof"); 

      const char* currentDir = gSystem->pwd();
      std::string fullPath = std::string(currentDir) + "/" + "plots/spotsize";
      std::string filePath = fullPath + Form("/Fit_%s_Y%d.root",bpm[i].Data(),ypos[j]);
      c1->SaveAs(filePath.c_str());
      delete c1;

    }
  }
}




