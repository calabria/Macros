#include <vector>
#include <fstream>
#include <sstream>
#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"
#include "TPaveStats.h"
#include "TStyle.h"

using namespace std;

TH1F * providePlots(TTree * fullTreeSgn, string sbranch, float a, float b, float c){

  Int_t nentries = (Int_t)fullTreeSgn->GetEntries();
  cout<<nentries<<endl;
  TH1F * hTemp = new TH1F("hTemp","hTemp distribution",a,b,c); 
  hTemp->GetXaxis()->SetTitle("diff [cm]");
  float binWidth = hTemp->GetBinWidth(1);
  hTemp->GetYaxis()->SetTitle(Form("Entries/%.2f cm", binWidth));

  int len;
  Float_t myvar;
  TBranch * branch=fullTreeSgn->GetBranch(sbranch.c_str());
  fullTreeSgn->SetMakeClass(1); // For the proper setup.
  fullTreeSgn->SetBranchAddress("Tau",&len);
  branch->SetAddress(&myvar);

  for (Int_t i=0;i<nentries;i++) {
	branch->GetEntry(i);
	//cout << "myvar = "<< myvar << endl;
	hTemp->Fill(myvar);
  }

  return hTemp;
  delete hTemp;

}

void makePlots(){

  // signal
  TFile fsgn("/cmshome/calabria/Code_53X_TauIdDec2012_OnlyAnalysis/CMSSW_5_3_7_patch4/src/WHAnalysis/AddUserTauLifeTimeVariables/histoOSTot.root");
  TTree *fullTreeSgn = (TTree*)fsgn.Get("treeCreator/vhtree");

  TFile *McP = new TFile("dummy1.root","RECREATE");

  TTree* fullTreeSgnCut = fullTreeSgn->CopyTree("Tau.isThreeProng > 0");
  TTree* fullTreeSgnCut1 = fullTreeSgn->CopyTree("Tau.isThreeProng > 0 && nVertex < 10");
  TTree* fullTreeSgnCut2 = fullTreeSgn->CopyTree("Tau.isThreeProng > 0 && nVertex > 10 && nVertex < 20");
  TTree* fullTreeSgnCut3 = fullTreeSgn->CopyTree("Tau.isThreeProng > 0 && nVertex > 20");

  Int_t nentries = (Int_t)fullTreeSgn->GetEntries();
  Int_t nentriesCut = (Int_t)fullTreeSgnCut->GetEntries();
  cout<<nentries<<" "<<nentriesCut<<endl;

  TH1F * hdiffPVx = new TH1F("diffPVx","genPV.x-recoPV.x",80,-0.01,0.01); 
  TH1F * hdiffPVy = new TH1F("diffPVy","genPV.y-recoPV.y",80,-0.01,0.01); 
  TH1F * hdiffPVz = new TH1F("diffPVz","genPV.z-recoPV.z",80,-0.01,0.01); 
  TH1F * hdiffSVx = new TH1F("diffSVx","genSV.u_{1}-recoSV.u_{1}",200,-0.1,0.1); 
  TH1F * hdiffSVy = new TH1F("diffSVy","genSV.u_{2}-recoSV.u_{2}",200,-0.1,0.1); 
  TH1F * hdiffSVz = new TH1F("diffSVZ","genSV.u_{3}-recoSV.u_{3}",40,-1,1); 

  hdiffPVx->GetXaxis()->SetTitle("diff [cm]");
  hdiffPVy->GetXaxis()->SetTitle("diff [cm]");
  hdiffPVz->GetXaxis()->SetTitle("diff [cm]");
  hdiffSVx->GetXaxis()->SetTitle("diff [cm]");
  hdiffSVy->GetXaxis()->SetTitle("diff [cm]");
  hdiffSVz->GetXaxis()->SetTitle("diff [cm]");
  float binWidth = hdiffPVx->GetBinWidth(1);
  float binWidth2 = hdiffSVx->GetBinWidth(1);
  float binWidth3 = hdiffSVy->GetBinWidth(1);
  float binWidth4 = hdiffSVz->GetBinWidth(1);
  hdiffPVx->GetYaxis()->SetTitle(Form("Entries/%.5f cm", binWidth));
  hdiffPVy->GetYaxis()->SetTitle(Form("Entries/%.5f cm", binWidth));
  hdiffPVz->GetYaxis()->SetTitle(Form("Entries/%.5f cm", binWidth));
  hdiffSVx->GetYaxis()->SetTitle(Form("Entries/%.4f cm", binWidth2));
  hdiffSVy->GetYaxis()->SetTitle(Form("Entries/%.4f cm", binWidth3));
  hdiffSVz->GetYaxis()->SetTitle(Form("Entries/%.4f cm", binWidth4));

  int len;
  Float_t myvar;
  Float_t myvar2;
  Float_t myvar3;
  Float_t myvar4;
  Float_t myvar5;
  Float_t myvar6;
  TBranch * branch=fullTreeSgn->GetBranch("Tau.diffPVx");
  TBranch * branch2=fullTreeSgn->GetBranch("Tau.diffPVy");
  TBranch * branch3=fullTreeSgn->GetBranch("Tau.diffPVz");
  TBranch * branch4=fullTreeSgnCut->GetBranch("Tau.diffSVxLocal");
  TBranch * branch5=fullTreeSgnCut->GetBranch("Tau.diffSVyLocal");
  TBranch * branch6=fullTreeSgnCut->GetBranch("Tau.diffSVzLocal");

  fullTreeSgn->SetMakeClass(1); // For the proper setup.
  fullTreeSgnCut->SetMakeClass(1);
  fullTreeSgn->SetBranchAddress("Tau",&len);
  fullTreeSgnCut->SetBranchAddress("Tau",&len);
  branch->SetAddress(&myvar);
  branch2->SetAddress(&myvar2);
  branch3->SetAddress(&myvar3);
  branch4->SetAddress(&myvar4);
  branch5->SetAddress(&myvar5);
  branch6->SetAddress(&myvar6);

  for (Int_t i=0;i<nentries;i++) {
	branch->GetEntry(i);
	branch2->GetEntry(i);
	branch3->GetEntry(i);
	//cout << "myvar = "<< myvar << endl;
	hdiffPVx->Fill(myvar);
	hdiffPVy->Fill(myvar2);
	hdiffPVz->Fill(myvar3);
  }

  for (Int_t i=0;i<nentriesCut;i++) {
	branch4->GetEntry(i);
	branch5->GetEntry(i);
	branch6->GetEntry(i);
	//cout << "myvar = "<< myvar << endl;
	hdiffSVx->Fill(myvar4);
	hdiffSVy->Fill(myvar5);
	hdiffSVz->Fill(myvar6);
  }

  //----------------------------------------------------------------------------------------------------------------

  //hdiffPVx->Draw();
  //c2->SaveAs("diffPVx.png");
  //hdiffPVy->Draw();
  //c2->SaveAs("diffPVy.png");
  //hdiffPVz->Draw();
  //c2->SaveAs("diffPVz.png");

  //----------------------------------------------------------------------------------------------------------------

  TCanvas *c4 = new TCanvas("canvas4","canvas4",10,30,650,600);

  gPad->Update();
  hdiffSVx->Draw();
  hdiffSVx->SetName("All");
  gPad->Update();

  TH1F * hdiffSVx1 = providePlots(fullTreeSgnCut1, "Tau.diffSVxLocal", 200, -0.1, 0.1);
  hdiffSVx1->SetName("nVtx < 10");
  hdiffSVx1->SetLineColor(2);
  hdiffSVx1->Draw("SAMES");
  gPad->Update();
  TPaveStats* st11 = (TPaveStats*) hdiffSVx1->FindObject("stats");
  st11->SetX1NDC(0.1);
  st11->SetX2NDC(0.3);
  st11->SetY1NDC(0.7);
  st11->SetY2NDC(0.9);
  st11->SetTextColor(2);
  st11->Draw();
  gPad->Update();
  TH1F * hdiffSVx2 = providePlots(fullTreeSgnCut2, "Tau.diffSVxLocal", 200, -0.1, 0.1);
  hdiffSVx2->SetLineColor(6);
  hdiffSVx2->SetName("10 < nVtx < 20");
  hdiffSVx2->Draw("SAMES");
  gPad->Update();
  TPaveStats* st12 = (TPaveStats*) hdiffSVx2->FindObject("stats");
  st12->SetX1NDC(0.1);
  st12->SetX2NDC(0.3);
  st12->SetY1NDC(0.5);
  st12->SetY2NDC(0.7);
  st12->SetTextColor(6);
  st12->Draw();
  gPad->Update();
  TH1F * hdiffSVx3 = providePlots(fullTreeSgnCut3, "Tau.diffSVxLocal", 200, -0.1, 0.1);
  hdiffSVx3->SetLineColor(4);
  hdiffSVx3->SetName("nVtx > 20");
  hdiffSVx3->Draw("SAMES");
  gPad->Update();
  TPaveStats* st13 = (TPaveStats*) hdiffSVx3->FindObject("stats");
  st13->SetX1NDC(0.1);
  st13->SetX2NDC(0.3);
  st13->SetY1NDC(0.3);
  st13->SetY2NDC(0.5);
  st13->SetTextColor(4);
  st13->Draw();
  gPad->Update();

  c4->SaveAs("diffSVxLocal.png");

  //----------------------------------------------------------------------------------------------------------------

  TCanvas *c5 = new TCanvas("canvas5","canvas5",10,30,650,600);

  gPad->Update();
  hdiffSVy->Draw();
  hdiffSVy->SetName("All");
  gPad->Update();

  TH1F * hdiffSVy1 = providePlots(fullTreeSgnCut1, "Tau.diffSVyLocal", 200, -0.1, 0.1);
  hdiffSVy1->SetName("nVtx < 10");
  hdiffSVy1->SetLineColor(2);
  hdiffSVy1->Draw("SAMES");
  gPad->Update();
  TPaveStats* st21 = (TPaveStats*) hdiffSVy1->FindObject("stats");
  st21->SetX1NDC(0.1);
  st21->SetX2NDC(0.3);
  st21->SetY1NDC(0.7);
  st21->SetY2NDC(0.9);
  st21->SetTextColor(2);
  st21->Draw();
  gPad->Update();
  TH1F * hdiffSVy2 = providePlots(fullTreeSgnCut2, "Tau.diffSVyLocal", 200, -0.1, 0.1);
  hdiffSVy2->SetLineColor(6);
  hdiffSVy2->SetName("10 < nVtx < 20");
  hdiffSVy2->Draw("SAMES");
  gPad->Update();
  TPaveStats* st22 = (TPaveStats*) hdiffSVy2->FindObject("stats");
  st22->SetX1NDC(0.1);
  st22->SetX2NDC(0.3);
  st22->SetY1NDC(0.5);
  st22->SetY2NDC(0.7);
  st22->SetTextColor(6);
  st22->Draw();
  gPad->Update();
  TH1F * hdiffSVy3 = providePlots(fullTreeSgnCut3, "Tau.diffSVyLocal", 200, -0.1, 0.1);
  hdiffSVy3->SetLineColor(4);
  hdiffSVy3->SetName("nVtx > 20");
  hdiffSVy3->Draw("SAMES");
  gPad->Update();
  TPaveStats* st23 = (TPaveStats*) hdiffSVy3->FindObject("stats");
  st23->SetX1NDC(0.1);
  st23->SetX2NDC(0.3);
  st23->SetY1NDC(0.3);
  st23->SetY2NDC(0.5);
  st23->SetTextColor(4);
  st23->Draw();
  gPad->Update();

  c5->SaveAs("diffSVyLocal.png");

  //----------------------------------------------------------------------------------------------------------------

  TCanvas *c6 = new TCanvas("canvas6","canvas6",10,30,650,600);

  gPad->Update();
  hdiffSVz->Draw();
  hdiffSVz->SetName("All");
  gPad->Update();

  TH1F * hdiffSVz1 = providePlots(fullTreeSgnCut1, "Tau.diffSVzLocal", 40, -1, 1);
  hdiffSVz1->SetName("nVtx < 10");
  hdiffSVz1->SetLineColor(2);
  hdiffSVz1->Draw("SAMES");
  gPad->Update();
  TPaveStats* st31 = (TPaveStats*) hdiffSVz1->FindObject("stats");
  st31->SetX1NDC(0.1);
  st31->SetX2NDC(0.3);
  st31->SetY1NDC(0.7);
  st31->SetY2NDC(0.9);
  st31->SetTextColor(2);
  st31->Draw();
  gPad->Update();
  TH1F * hdiffSVz2 = providePlots(fullTreeSgnCut2, "Tau.diffSVzLocal", 40, -1, 1);
  hdiffSVz2->SetLineColor(6);
  hdiffSVz2->SetName("10 < nVtx < 20");
  hdiffSVz2->Draw("SAMES");
  gPad->Update();
  TPaveStats* st32 = (TPaveStats*) hdiffSVz2->FindObject("stats");
  st32->SetX1NDC(0.1);
  st32->SetX2NDC(0.3);
  st32->SetY1NDC(0.5);
  st32->SetY2NDC(0.7);
  st32->SetTextColor(6);
  st32->Draw();
  gPad->Update();
  TH1F * hdiffSVz3 = providePlots(fullTreeSgnCut3, "Tau.diffSVzLocal", 40, -1, 1);
  hdiffSVz3->SetLineColor(4);
  hdiffSVz3->SetName("nVtx > 20");
  hdiffSVz3->Draw("SAMES");
  gPad->Update();
  TPaveStats* st33 = (TPaveStats*) hdiffSVz3->FindObject("stats");
  st33->SetX1NDC(0.1);
  st33->SetX2NDC(0.3);
  st33->SetY1NDC(0.3);
  st33->SetY2NDC(0.5);
  st33->SetTextColor(4);
  st33->Draw();
  gPad->Update();

  c6->SaveAs("diffSVzLocal.png");

}
