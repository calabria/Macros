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
#include "TEfficiency.h"

// tdrGrid: Turns the grid lines on (true) or off (false)

void tdrGrid(bool gridOn) {
  tdrStyle->SetPadGridX(gridOn);
  tdrStyle->SetPadGridY(gridOn);
}

// fixOverlay: Redraws the axis

void fixOverlay() {
  gPad->RedrawAxis();
}

void setTDRStyle() {
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

// For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas
  tdrStyle->SetCanvasDefW(600); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);

// For the Pad:
  tdrStyle->SetPadBorderMode(0);
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);

// For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);

// For the histo:
  // tdrStyle->SetHistFillColor(1);
  // tdrStyle->SetHistFillStyle(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  // tdrStyle->SetLegoInnerR(Float_t rad = 0.5);
  // tdrStyle->SetNumberContours(Int_t number = 20);

  tdrStyle->SetEndErrorSize(2);
//  tdrStyle->SetErrorMarker(20);
  tdrStyle->SetErrorX(0.5);
  
  tdrStyle->SetMarkerStyle(20);

//For the fit/function:
  tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncColor(2);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

//For the date:
  tdrStyle->SetOptDate(0);
  // tdrStyle->SetDateX(Float_t x = 0.01);
  // tdrStyle->SetDateY(Float_t y = 0.01);

// For the statistics box:
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatFont(42);
  tdrStyle->SetStatFontSize(0.025);
  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(1);
  tdrStyle->SetStatH(0.1);
  tdrStyle->SetStatW(0.15);
  // tdrStyle->SetStatStyle(Style_t style = 1001);
  // tdrStyle->SetStatX(Float_t x = 0);
  // tdrStyle->SetStatY(Float_t y = 0);

// Margins:
  tdrStyle->SetPadTopMargin(0.05);
  tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetPadLeftMargin(0.16);
  tdrStyle->SetPadRightMargin(0.02);

// For the Global title:

  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);
  // tdrStyle->SetTitleH(0); // Set the height of the title box
  // tdrStyle->SetTitleW(0); // Set the width of the title box
  // tdrStyle->SetTitleX(0); // Set the position of the title box
  // tdrStyle->SetTitleY(0.985); // Set the position of the title box
  // tdrStyle->SetTitleStyle(Style_t style = 1001);
  // tdrStyle->SetTitleBorderSize(2);

// For the axis titles:

  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.25);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

// For the axis labels:

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.05, "XYZ");

// For the axis:

  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

// Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);

// Postscript options:
  tdrStyle->SetPaperSize(20.,20.);
  // tdrStyle->SetLineScalePS(Float_t scale = 3);
  // tdrStyle->SetLineStyleString(Int_t i, const char* text);
  // tdrStyle->SetHeaderPS(const char* header);
  // tdrStyle->SetTitlePS(const char* pstitle);

  // tdrStyle->SetBarOffset(Float_t baroff = 0.5);
  // tdrStyle->SetBarWidth(Float_t barwidth = 0.5);
  // tdrStyle->SetPaintTextFormat(const char* format = "g");
  // tdrStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // tdrStyle->SetTimeOffset(Double_t toffset);
  // tdrStyle->SetHistMinimumZero(kTRUE);

  tdrStyle->cd();

}

struct MyPar{

	double sigma;
	double sigmaErr;
	double sigmaFR;
	double sigmaErrFR;
	double DeltaSigma;
	TH1D * histo;

};

MyPar extractSigma(TH1D * hist, std::string postFix = "none"){

	gStyle->SetOptStat(112210);
	gStyle->SetOptFit(12);
	gStyle->SetStatW(0.2); 
	gStyle->SetStatH(0.5);

	std::string name = "fit_";

   	MyPar obj;

	double mean = hist->GetMean();
	double rms = hist->GetRMS();
  	TCanvas * canvasTMP = new TCanvas("canvasTMP","canvas",700,700);

	hist->SetLineColor(1);
	hist->SetLineWidth(2);
	hist->Draw();
        gStyle->SetFuncWidth(2);
        TF1 *myfitFR = new TF1("myfitFR","gaus", -2, +2);
        hist->Fit("myfitFR");
        TF1 *myfit = new TF1("myfit","gaus", mean-2*rms, mean+2*rms);
        hist->Fit("myfit", "R");

	obj.sigma = myfit->GetParameter(2);
	obj.sigmaErr = myfit->GetParError(2);
	obj.sigmaFR = myfitFR->GetParameter(2);
	obj.sigmaErrFR = myfitFR->GetParError(2);
	double delta = abs(myfit->GetParameter(2) - myfitFR->GetParameter(2));
	obj.DeltaSigma = sqrt(delta*delta + obj.sigmaErr*obj.sigmaErr);
	obj.histo = hist;

	//hist->GetXaxis()->SetRangeUser(-0.5, +0.5);
	//hist->Draw();
	canvasTMP->SaveAs((name + postFix + ".pdf").c_str());
	return obj;

}

MyPar extractSigmaBis(TH1D * hist, std::string postFix = "none"){

	gStyle->SetOptStat(112210);
	gStyle->SetOptFit(12);
	gStyle->SetStatW(0.2); 
	gStyle->SetStatH(0.5);

	std::string name = "fit_";

   	MyPar obj;

	double mean = hist->GetMean();
	double rms = hist->GetRMS();
  	TCanvas * canvasTMP = new TCanvas("canvasTMP","canvas",700,700);

	hist->SetLineColor(1);
	hist->SetLineWidth(2);
	hist->Draw();
        gStyle->SetFuncWidth(2);
        TF1 *myfitFR = new TF1("myfitFR","gaus", -2, +2);
        hist->Fit("myfitFR");

        TF1 *myfitPRV = new TF1("myfitPRV","gaus", mean-2*rms, mean+2*rms);
        hist->Fit("myfitPRV", "R");

	double meanPRV = myfitPRV->GetParameter(1);
	double sigmaPRV = myfitPRV->GetParameter(2);
	double sigmaErrPRV = myfitPRV->GetParError(2);

        TF1 *myfit = new TF1("myfit","gaus", meanPRV-3*sigmaPRV/2, meanPRV+3*sigmaPRV/2);
        hist->Fit("myfit", "R");

	obj.sigma = myfit->GetParameter(2);
	obj.sigmaErr = myfit->GetParError(2);
	obj.sigmaFR = myfitFR->GetParameter(2);
	obj.sigmaErrFR = myfitFR->GetParError(2);
	double delta = abs(myfit->GetParameter(2) - myfitFR->GetParameter(2));
	obj.DeltaSigma = sqrt(delta*delta + obj.sigmaErr*obj.sigmaErr);
	obj.histo = hist;

	//hist->GetXaxis()->SetRangeUser(-0.5, +0.5);
	//hist->Draw();
	canvasTMP->SaveAs((name + postFix + ".pdf").c_str());
	return obj;

}

typedef std::vector<double> vdouble;

vdouble composeHistos(MyPar p1, MyPar p2, std::string pt){

	gStyle->SetOptStat(112210);
	gStyle->SetOptFit(12);

	vdouble temp;

	TH1D * h1 = p1.histo;
	TH1D * h2 = p2.histo;
	double mean1 = h1->GetMean();
	double rms1 = h1->GetRMS();
	double mean2 = h2->GetMean();
	double rms2 = h2->GetRMS();
	double range1 = mean1 + 2*rms1;
	double range2 = mean2 + 2*rms2;
	double minRange = (range1 > range2 ? range2 : range1);	

  	TCanvas * canvasTMP = new TCanvas("canvasTMP","canvas",700,700);
	h1->Draw();
        TF1 *myfit1 = new TF1("myfit1","gaus", -minRange, +minRange);
        h1->Fit("myfit1", "R");

	temp.push_back(myfit1->GetParameter(2));
	temp.push_back(myfit1->GetParError(2));

	h2->Draw("SAME");
        TF1 *myfit2 = new TF1("myfit2","gaus", -minRange, +minRange);
        h2->Fit("myfit2", "R");

	//canvasTMP->SaveAs(("fit_" + pt + ".pdf").c_str());

	temp.push_back(myfit2->GetParameter(2));
	temp.push_back(myfit2->GetParError(2));
	return temp;
	//Eventually uncertainties shoudl be calculated as deltaSigma also here

}

TH1F * makeRatio(TH1F * plot1, TH1F * plot2){

	TH1F * plotTMP = (TH1F*)plot2->Clone();
	plotTMP->Divide(plot1);
	return plotTMP;

}

TH1D * makeRatio2(TH1D * plot1, TH1D * plot2){

	TH1D * plotTMP = (TH1D*)plot2->Clone();
  	plotTMP->SetMaximum(1.05);
  	plotTMP->SetMinimum(0.9);
	plotTMP->Divide(plot1);
	return plotTMP;

}

void makeSuperImp(MyPar p1, MyPar p2, std::string name){

	gStyle->SetOptStat(112200);
	gStyle->SetOptFit(12);

	TH1D * tmp1 = p1.histo;
	TH1D * tmp2 = p2.histo;

	tmp1->Scale(1/tmp1->GetEntries());
	tmp2->Scale(1/tmp2->GetEntries());

	TCanvas * canvasTMP = new TCanvas("canvasTMP","canvas",700,700);
	canvasTMP->SetLogy();
	tmp1->SetMaximum(1);
 	tmp1->SetLineColor(4);
	tmp1->Draw("HIST");
 	tmp2->SetLineColor(2);
	tmp2->Draw("HISTSAMES");
	TPaveStats *stats1 = (TPaveStats*)tmp1->GetListOfFunctions()->FindObject("stats");
	stats1->SetX1NDC(0.15);
	stats1->SetX2NDC(0.50);
	TPaveStats *stats2 = (TPaveStats*)tmp2->GetListOfFunctions()->FindObject("stats");
	stats2->SetX1NDC(0.65);
	stats2->SetX2NDC(1.00);

	canvasTMP->SaveAs(name.c_str());

}

TH1D * makeRatio3(TEfficiency * plot1, TEfficiency * plot2){

 	TH1D * plotTMP1 = new TH1D("plotTMP1","plotTMP1",441,-2.5,2202.5);
 	TH1D * plotTMP2 = new TH1D("plotTMP2","plotTMP2",441,-2.5,2202.5);

	for(int i = 1; i <= plotTMP1->GetSize(); i++){

		double eff1 = plot1->GetEfficiency(i);
		double eff2 = plot2->GetEfficiency(i);

		//std::cout<<"eff1: "<<eff1<<" eff2: "<<eff2<<std::endl;

		double err1 = (plot1->GetEfficiencyErrorLow(i) + plot1->GetEfficiencyErrorUp(i))/2;
		double err2 = (plot2->GetEfficiencyErrorLow(i) + plot2->GetEfficiencyErrorUp(i))/2;

		plotTMP1->SetBinContent(i,eff1);
		plotTMP1->SetBinError(i,err1);
		plotTMP2->SetBinContent(i,eff2);
		plotTMP2->SetBinError(i,err2);

  	}

  	plotTMP2->SetMaximum(4);
  	plotTMP2->SetMinimum(0.01);
	plotTMP2->Divide(plotTMP1);
	return plotTMP2;

}

void makePlots(){

  setTDRStyle();

  TFile * f1_ = TFile::Open("histoWithGEMs_tot.root");
  f1_->cd("STAMuonAnalyzer");

  TH1F * pTRec_NoGEM = (TH1F*)gDirectory->Get("pTRec");
  TH1F * pTSim_NoGEM = (TH1F*)gDirectory->Get("pTSim");
  TH1F * pTRes_NoGEM = (TH1F*)gDirectory->Get("pTRes");
  TH1F * invPTRes_NoGEM = (TH1F*)gDirectory->Get("invPTRes");
  TH1F * pTDiff_NoGEM = (TH1F*)gDirectory->Get("pTDiff");
  TH1F * PSimEta_NoGEM = (TH1F*)gDirectory->Get("PSimEta");
  TH1F * PRecEta_NoGEM = (TH1F*)gDirectory->Get("PRecEta");
  TH1F * PDeltaEta_NoGEM = (TH1F*)gDirectory->Get("PDeltaEta");
  TH1F * PSimPhi_NoGEM = (TH1F*)gDirectory->Get("PSimPhi");
  TH1F * PRecPhi_NoGEM = (TH1F*)gDirectory->Get("PRecPhi");
  TH1F * NumSimTracks_NoGEM = (TH1F*)gDirectory->Get("NumSimTracks");
  TH1F * NumMuonSimTracks_NoGEM = (TH1F*)gDirectory->Get("NumMuonSimTracks");
  TH1F * NumRecTracks_NoGEM = (TH1F*)gDirectory->Get("NumRecTracks");
  TH2F * PtResVsPt_NoGEM = (TH2F*)gDirectory->Get("PtResVsPt");
  TH2F * InvPtResVsPt_NoGEM = (TH2F*)gDirectory->Get("InvPtResVsPt");

  TH2F * PtResVsPtNoCharge_NoGEM = (TH2F*)gDirectory->Get("PtResVsPtNoCharge");
  TH2F * InvPtResVsPtNoCharge_NoGEM = (TH2F*)gDirectory->Get("InvPtResVsPtNoCharge");

  TH2F * DPhiVsPt_NoGEM = (TH2F*)gDirectory->Get("DPhiVsPt");
  TH1F * DenPt_NoGEM = (TH1F*)gDirectory->Get("DenPt");
  TH1F * DenEta_NoGEM = (TH1F*)gDirectory->Get("DenEta");
  TH1F * NumPt_NoGEM = (TH1F*)gDirectory->Get("NumPt");
  TH1F * NumEta_NoGEM = (TH1F*)gDirectory->Get("NumEta");
  TH1F * PullGEM_NoGEM = (TH1F*)gDirectory->Get("PullGEMx");
  TH1F * GEMRecHitEta_NoGEM = (TH1F*)gDirectory->Get("GEMRecHitEta");
  TH2F * DeltaCharge_NoGEM = (TH2F*)gDirectory->Get("DeltaCharge");
  TH2F * RecoPtVsSimPt_NoGEM = (TH2F*)gDirectory->Get("RecoPtVsSimPt");
  TH2F * DeltaPtVsSimPt_NoGEM = (TH2F*)gDirectory->Get("DeltaPtVsSimPt");
  TH2F * DRMatchVsPt_NoGEM = (TH2F*)gDirectory->Get("DRMatchVsPt");

  pTRec_NoGEM->GetXaxis()->SetTitle("p_{T}^{Reco} [GeV/c]");
  pTSim_NoGEM->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  pTRes_NoGEM->GetXaxis()->SetTitle("(p_{T}^{Reco} - p_{T}^{Sim}) / p_{T}^{Sim}");
  invPTRes_NoGEM->GetXaxis()->SetTitle("(q^{Reco}/p_{T}^{Reco} - q^{Sim}/p_{T}^{Sim}) / q^{Sim}/p_{T}^{Sim}");
  pTDiff_NoGEM->GetXaxis()->SetTitle("p_{T}^{Reco} - p_{T}^{Sim} [GeV/c]");
  PSimEta_NoGEM->GetXaxis()->SetTitle("#eta^{Sim}");
  PRecEta_NoGEM->GetXaxis()->SetTitle("#eta^{Rec0}");
  PDeltaEta_NoGEM->GetXaxis()->SetTitle("#Delta#eta");
  PSimPhi_NoGEM->GetXaxis()->SetTitle("#phi^{Sim}");
  PRecPhi_NoGEM->GetXaxis()->SetTitle("#phi^{Reco}");
  NumSimTracks_NoGEM->GetXaxis()->SetTitle("# SimTracks");
  NumMuonSimTracks_NoGEM->GetXaxis()->SetTitle("# SimMuonTracks");
  NumRecTracks_NoGEM->GetXaxis()->SetTitle("# RecoTracks");
  PtResVsPt_NoGEM->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  InvPtResVsPt_NoGEM->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  DPhiVsPt_NoGEM->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  PullGEM_NoGEM->GetXaxis()->SetTitle("#Delta x / #sigma (Sim-GEMRecHit)");

  PtResVsPt_NoGEM->GetYaxis()->SetTitle("< p_{t} res. >");
  InvPtResVsPt_NoGEM->GetYaxis()->SetTitle("< 1/p_{t} res. >");
  DPhiVsPt_NoGEM->GetYaxis()->SetTitle("<#Delta#phi>");

  //DeltaCharge_NoGEM->RebinX(5);

  TH1F * NumPt_NoGEM2 = (TH1F*)NumPt_NoGEM->Clone();
  TH1F * NumEta_NoGEM2 = (TH1F*)NumEta_NoGEM->Clone();

  NumPt_NoGEM2->GetYaxis()->SetTitle("#varepsilon");
  NumEta_NoGEM2->GetYaxis()->SetTitle("#varepsilon");

  TH2F * PtResVsPt_NoGEM2 = (TH2F*)PtResVsPt_NoGEM->Clone();
  TH2F * InvPtResVsPt_NoGEM2 = (TH2F*)InvPtResVsPt_NoGEM->Clone();
  TH2F * DPhiVsPt_NoGEM2 = (TH2F*)DPhiVsPt_NoGEM->Clone();

  NumPt_NoGEM2->Divide(DenPt_NoGEM);
  NumEta_NoGEM2->Divide(DenEta_NoGEM);

  TProfile * prof1_NoGEM = PtResVsPt_NoGEM2->ProfileX();
  TProfile * prof2_NoGEM = InvPtResVsPt_NoGEM2->ProfileX();

  TProfile * prof1NoCharge_NoGEM = PtResVsPtNoCharge_NoGEM->ProfileX();
  TProfile * prof2NoCharge_NoGEM = InvPtResVsPtNoCharge_NoGEM->ProfileX();

  TProfile * prof2bis_NoGEM = InvPtResVsPt_NoGEM2->ProfileX("profile",-1,-1,"s");
  TProfile * prof3_NoGEM = DPhiVsPt_NoGEM2->ProfileX();

  TProfile * prof4_NoGEM = RecoPtVsSimPt_NoGEM->ProfileX();
  TProfile * prof5_NoGEM = DeltaPtVsSimPt_NoGEM->ProfileX();

  std::vector<TH1F*> vecResNoGEM;
  for(int i=1; i<=PtResVsPt_NoGEM->GetNbinsX(); i++){

  	TH1F * temp = (TH1F*)pTRes_NoGEM->Clone();
	int col = i;
	if(i==10) col=41;
	if(i==5) col=46;
	temp->SetLineColor(col);
	temp->SetLineWidth(2);

	for(int j=1; j<=PtResVsPt_NoGEM->GetNbinsY(); j++){

		float bin = PtResVsPt_NoGEM->GetBinContent(i,j);

		temp->SetBinContent(bin,i);
		//std::cout<<bin<<std::endl;

	}

	vecResNoGEM.push_back(temp);

  }

  TH1F * DeltaChargePercentage_NoGEM = new TH1F("DeltaChargePercentage_NoGEM","Frac. Wrong Charge (SIM-RECO)",461,-2.5,2302.5);

  TH1F * numNoGem = (TH1F*)DeltaChargePercentage_NoGEM->Clone();
  TH1F * denNoGem = (TH1F*)DeltaChargePercentage_NoGEM->Clone();

  for(int i=1; i<=DeltaCharge_NoGEM->GetNbinsX(); i++){

	int num1 = DeltaCharge_NoGEM->GetBinContent(i,2);
	int num2 = DeltaCharge_NoGEM->GetBinContent(i,4); //zero
	int num3 = DeltaCharge_NoGEM->GetBinContent(i,6);

	numNoGem->SetBinContent(i,num1+num3);
	denNoGem->SetBinContent(i,num1+num2+num3);

	//double perc = (double) (num1 + num3)/(num1 + num2 + num3);
	//cout<<num1<<" "<<num2<<" "<<num3<<endl;
	//cout<<std::setprecision(5)<<perc<<endl;
	//DeltaChargePercentage_NoGEM->SetBinContent(i,perc);

  }

  TEfficiency* pEffCharge_NoGEM = 0;
 
  //h_pass and h_total are valid and consistent histograms
  if(TEfficiency::CheckConsistency(*numNoGem,*denNoGem))
  {
    	pEffCharge_NoGEM = new TEfficiency(*numNoGem,*denNoGem);
    	// this will write the TEfficiency object to "myfile.root"
    	// AND pEff will be attached to the current directory
   	//pEffPt_GEM->Draw();
  }

  /////////////////////////////////////////////////////////////////////////////////////

  TFile * f2_ = TFile::Open("histoWithGEMs_tot.root");
  f2_->cd("STAMuonAnalyzerWithGEMs");
  TH1F * pTRec_GEM = (TH1F*)gDirectory->Get("pTRec");
  TH1F * pTSim_GEM = (TH1F*)gDirectory->Get("pTSim");
  TH1F * pTRes_GEM = (TH1F*)gDirectory->Get("pTRes");
  TH1F * invPTRes_GEM = (TH1F*)gDirectory->Get("invPTRes");
  TH1F * pTDiff_GEM = (TH1F*)gDirectory->Get("pTDiff");
  TH1F * PSimEta_GEM = (TH1F*)gDirectory->Get("PSimEta");
  TH1F * PRecEta_GEM = (TH1F*)gDirectory->Get("PRecEta");
  TH1F * PDeltaEta_GEM = (TH1F*)gDirectory->Get("PDeltaEta");
  TH1F * PSimPhi_GEM = (TH1F*)gDirectory->Get("PSimPhi");
  TH1F * PRecPhi_GEM = (TH1F*)gDirectory->Get("PRecPhi");
  TH1F * NumSimTracks_GEM = (TH1F*)gDirectory->Get("NumSimTracks");
  TH1F * NumMuonSimTracks_GEM = (TH1F*)gDirectory->Get("NumMuonSimTracks");
  TH1F * NumRecTracks_GEM = (TH1F*)gDirectory->Get("NumRecTracks");
  TH2F * PtResVsPt_GEM = (TH2F*)gDirectory->Get("PtResVsPt");
  TH2F * InvPtResVsPt_GEM = (TH2F*)gDirectory->Get("InvPtResVsPt");

  TH2F * PtResVsPtNoCharge_GEM = (TH2F*)gDirectory->Get("PtResVsPtNoCharge");
  TH2F * InvPtResVsPtNoCharge_GEM = (TH2F*)gDirectory->Get("InvPtResVsPtNoCharge");

  TH2F * DPhiVsPt_GEM = (TH2F*)gDirectory->Get("DPhiVsPt");
  TH1F * DenPt_GEM = (TH1F*)gDirectory->Get("DenPt");
  TH1F * DenEta_GEM = (TH1F*)gDirectory->Get("DenEta");
  TH1F * DenPhi_GEM = (TH1F*)gDirectory->Get("DenPhi");
  TH1F * DenPhiPlus_GEM = (TH1F*)gDirectory->Get("DenPhiPlus");
  TH1F * DenPhiMinus_GEM = (TH1F*)gDirectory->Get("DenPhiMinus");
  TH1F * NumPt_GEM = (TH1F*)gDirectory->Get("NumPt");
  TH1F * NumEta_GEM = (TH1F*)gDirectory->Get("NumEta");
  TH1F * NumPhi_GEM = (TH1F*)gDirectory->Get("NumPhi");
  TH1F * NumPhiPlus_GEM = (TH1F*)gDirectory->Get("NumPhiPlus");
  TH1F * NumPhiMinus_GEM = (TH1F*)gDirectory->Get("NumPhiMinus");

  TH1F * DenSimPt_GEM = (TH1F*)gDirectory->Get("DenSimPt");
  TH1F * DenSimEta_GEM = (TH1F*)gDirectory->Get("DenSimEta");
  TH1F * DenSimPhiPlus_GEM = (TH1F*)gDirectory->Get("DenSimPhiPlus");
  TH1F * DenSimPhiMinus_GEM = (TH1F*)gDirectory->Get("DenSimPhiMinus");
  TH1F * NumSimPt_GEM = (TH1F*)gDirectory->Get("NumSimPt");
  TH1F * NumSimEta_GEM = (TH1F*)gDirectory->Get("NumSimEta");
  TH1F * NumSimPhiPlus_GEM = (TH1F*)gDirectory->Get("NumSimPhiPlus");
  TH1F * NumSimPhiMinus_GEM = (TH1F*)gDirectory->Get("NumSimPhiMinus");

  TH1F * NumSimPt1_GEM = (TH1F*)gDirectory->Get("NumSimPtSt1");
  TH1F * NumSimPt2_GEM = (TH1F*)gDirectory->Get("NumSimPtSt2");
  TH1F * NumSimPt3_GEM = (TH1F*)gDirectory->Get("NumSimPtSt3");

  TH1F * PullGEM_GEM = (TH1F*)gDirectory->Get("PullGEMx");
  TH1F * GEMRecHitEta_GEM = (TH1F*)gDirectory->Get("GEMRecHitEta");
  TH1F * GEMRecHitPhi_GEM = (TH1F*)gDirectory->Get("GEMRecHitPhi");
  TH2F * DeltaCharge_GEM = (TH2F*)gDirectory->Get("DeltaCharge");
  TH2F * RecPhi2DPlusLayer1_GEM = (TH2F*)gDirectory->Get("RecHitPhi2DPlusLayer1");
  TH2F * RecPhi2DMinusLayer1_GEM = (TH2F*)gDirectory->Get("RecHitPhi2DMinusLayer1");
  TH2F * RecPhi2DPlusLayer2_GEM = (TH2F*)gDirectory->Get("RecHitPhi2DPlusLayer2");
  TH2F * RecPhi2DMinusLayer2_GEM = (TH2F*)gDirectory->Get("RecHitPhi2DMinusLayer2");
  TH2F * RecoPtVsSimPt_GEM = (TH2F*)gDirectory->Get("RecoPtVsSimPt");
  TH2F * DeltaPtVsSimPt_GEM = (TH2F*)gDirectory->Get("DeltaPtVsSimPt");
  TH2F * DRMatchVsPt_GEM = (TH2F*)gDirectory->Get("DRMatchVsPt");

  TH1F * NumPt_GEM2 = (TH1F*)NumPt_GEM->Clone();
  TH1F * NumEta_GEM2 = (TH1F*)NumEta_GEM->Clone();

  NumPt_GEM2->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  NumEta_GEM2->GetXaxis()->SetTitle("#eta");
  NumPt_GEM2->GetYaxis()->SetTitle("#varepsilon");
  NumEta_GEM2->GetYaxis()->SetTitle("#varepsilon");

  PtResVsPt_GEM->GetYaxis()->SetTitle("< p_{t} res. >");
  InvPtResVsPt_GEM->GetYaxis()->SetTitle("< 1/p_{t} res. >");
  DPhiVsPt_GEM->GetYaxis()->SetTitle("<#Delta#phi>");

  //DeltaCharge_GEM->RebinX(5);

  TH2F * PtResVsPt_GEM2 = (TH2F*)PtResVsPt_GEM->Clone();
  TH2F * InvPtResVsPt_GEM2 = (TH2F*)InvPtResVsPt_GEM->Clone();
  TH2F * DPhiVsPt_GEM2 = (TH2F*)DPhiVsPt_GEM->Clone();

  TProfile * prof1_GEM = PtResVsPt_GEM2->ProfileX();
  TProfile * prof2_GEM = InvPtResVsPt_GEM2->ProfileX();

  TProfile * prof1NoCharge_GEM = PtResVsPtNoCharge_GEM->ProfileX();
  TProfile * prof2NoCharge_GEM = InvPtResVsPtNoCharge_GEM->ProfileX();

  TProfile * prof2bis_GEM = InvPtResVsPt_GEM2->ProfileX("profile",-1,-1,"s");
  TProfile * prof3_GEM = DPhiVsPt_GEM2->ProfileX();

  TProfile * prof4_GEM = RecoPtVsSimPt_GEM->ProfileX();
  TProfile * prof5_GEM = DeltaPtVsSimPt_GEM->ProfileX();

  pTRec_GEM->SetLineColor(2);
  pTSim_GEM->SetLineColor(2);
  pTRes_GEM->SetLineColor(2);
  invPTRes_GEM->SetLineColor(2);
  pTDiff_GEM->SetLineColor(2);
  PSimEta_GEM->SetLineColor(2);
  PRecEta_GEM->SetLineColor(2);
  PDeltaEta_GEM->SetLineColor(2);
  PSimPhi_GEM->SetLineColor(2);
  PRecPhi_GEM->SetLineColor(2);
  NumSimTracks_GEM->SetLineColor(2);
  NumMuonSimTracks_GEM->SetLineColor(2);
  NumRecTracks_GEM->SetLineColor(2);
  PullGEM_GEM->SetLineColor(2);
  GEMRecHitEta_GEM->SetLineColor(2);
  GEMRecHitPhi_GEM->SetLineColor(2);
  prof1_GEM->SetLineColor(2);
  prof2_GEM->SetLineColor(2);
  prof3_GEM->SetLineColor(2);

  GEMRecHitEta_GEM->GetXaxis()->SetTitle("#eta_{GEMRecHit}");
  GEMRecHitEta_GEM->SetStats(kFALSE);
  GEMRecHitPhi_GEM->GetXaxis()->SetTitle("#phi_{GEMRecHit}");
  GEMRecHitPhi_GEM->SetStats(kFALSE);
  PullGEM_GEM->GetXaxis()->SetTitle("#Delta x / #sigma (Sim-GEMRecHit)");

  TEfficiency* pEffPt_GEM = 0;
 
  //h_pass and h_total are valid and consistent histograms
  if(TEfficiency::CheckConsistency(*NumPt_GEM,*DenPt_GEM))
  {
    	pEffPt_GEM = new TEfficiency(*NumPt_GEM,*DenPt_GEM);
    	// this will write the TEfficiency object to "myfile.root"
    	// AND pEff will be attached to the current directory
   	//pEffPt_GEM->Draw();
  }

  TEfficiency* pEffEta_GEM = 0;
 
  //h_pass and h_total are valid and consistent histograms
  if(TEfficiency::CheckConsistency(*NumEta_GEM,*DenEta_GEM))
  {
    	pEffEta_GEM = new TEfficiency(*NumEta_GEM,*DenEta_GEM);
    	// this will write the TEfficiency object to "myfile.root"
    	// AND pEff will be attached to the current directory
   	//pEffEta_GEM->Draw();
  }

  TEfficiency* pEffPhi_GEM = 0;
 
  //h_pass and h_total are valid and consistent histograms
  if(TEfficiency::CheckConsistency(*NumPhi_GEM,*DenPhi_GEM))
  {
    	pEffPhi_GEM = new TEfficiency(*NumPhi_GEM,*DenPhi_GEM);
    	// this will write the TEfficiency object to "myfile.root"
    	// AND pEff will be attached to the current directory
   	//pEffPt_GEM->Draw();
  }

  TEfficiency* pEffPhiPlus_GEM = 0;
 
  NumPhiPlus_GEM->Rebin();
  DenPhiPlus_GEM->Rebin();
  //h_pass and h_total are valid and consistent histograms
  if(TEfficiency::CheckConsistency(*NumPhiPlus_GEM,*DenPhiPlus_GEM))
  {
    	pEffPhiPlus_GEM = new TEfficiency(*NumPhiPlus_GEM,*DenPhiPlus_GEM);
    	// this will write the TEfficiency object to "myfile.root"
    	// AND pEff will be attached to the current directory
   	//pEffPt_GEM->Draw();
  }

  TEfficiency* pEffPhiMinus_GEM = 0;
 
  NumPhiMinus_GEM->Rebin();
  DenPhiMinus_GEM->Rebin();
  //h_pass and h_total are valid and consistent histograms
  if(TEfficiency::CheckConsistency(*NumPhiMinus_GEM,*DenPhiMinus_GEM))
  {
    	pEffPhiMinus_GEM = new TEfficiency(*NumPhiMinus_GEM,*DenPhiMinus_GEM);
    	// this will write the TEfficiency object to "myfile.root"
    	// AND pEff will be attached to the current directory
   	//pEffPt_GEM->Draw();
  }

  TEfficiency* pEffSimPt_GEM = 0;
 
  //h_pass and h_total are valid and consistent histograms
  if(TEfficiency::CheckConsistency(*NumSimPt_GEM,*DenSimPt_GEM))
  {
    	pEffSimPt_GEM = new TEfficiency(*NumSimPt_GEM,*DenSimPt_GEM);
    	// this will write the TEfficiency object to "myfile.root"
    	// AND pEff will be attached to the current directory
   	//pEffPt_GEM->Draw();
  }

  TEfficiency* pEffSimEta_GEM = 0;
 
  //h_pass and h_total are valid and consistent histograms
  if(TEfficiency::CheckConsistency(*NumSimEta_GEM,*DenSimEta_GEM))
  {
    	pEffSimEta_GEM = new TEfficiency(*NumSimEta_GEM,*DenSimEta_GEM);
    	// this will write the TEfficiency object to "myfile.root"
    	// AND pEff will be attached to the current directory
   	//pEffEta_GEM->Draw();
  }

  TEfficiency* pEffSimPhiPlus_GEM = 0;
 
  NumSimPhiPlus_GEM->Rebin();
  DenSimPhiPlus_GEM->Rebin();
  //h_pass and h_total are valid and consistent histograms
  if(TEfficiency::CheckConsistency(*NumSimPhiPlus_GEM,*DenSimPhiPlus_GEM))
  {
    	pEffSimPhiPlus_GEM = new TEfficiency(*NumSimPhiPlus_GEM,*DenSimPhiPlus_GEM);
    	// this will write the TEfficiency object to "myfile.root"
    	// AND pEff will be attached to the current directory
   	//pEffPt_GEM->Draw();
  }

  TEfficiency* pEffSimPhiMinus_GEM = 0;
 
  NumSimPhiMinus_GEM->Rebin();
  DenSimPhiMinus_GEM->Rebin();
  //h_pass and h_total are valid and consistent histograms
  if(TEfficiency::CheckConsistency(*NumSimPhiMinus_GEM,*DenSimPhiMinus_GEM))
  {
    	pEffSimPhiMinus_GEM = new TEfficiency(*NumSimPhiMinus_GEM,*DenSimPhiMinus_GEM);
    	// this will write the TEfficiency object to "myfile.root"
    	// AND pEff will be attached to the current directory
   	//pEffPt_GEM->Draw();
  }

//-------------------------------------------------------------------------------------------------------------------

  TEfficiency* pEffSimPt1_GEM = 0;
 
  //h_pass and h_total are valid and consistent histograms
  if(TEfficiency::CheckConsistency(*NumSimPt1_GEM,*DenSimPt_GEM))
  {
    	pEffSimPt1_GEM = new TEfficiency(*NumSimPt1_GEM,*DenSimPt_GEM);
    	// this will write the TEfficiency object to "myfile.root"
    	// AND pEff will be attached to the current directory
   	//pEffPt_GEM->Draw();
  }

//-------------------------------------------------------------------------------------------------------------------

  TEfficiency* pEffSimPt2_GEM = 0;
 
  //h_pass and h_total are valid and consistent histograms
  if(TEfficiency::CheckConsistency(*NumSimPt2_GEM,*DenSimPt_GEM))
  {
    	pEffSimPt2_GEM = new TEfficiency(*NumSimPt2_GEM,*DenSimPt_GEM);
    	// this will write the TEfficiency object to "myfile.root"
    	// AND pEff will be attached to the current directory
   	//pEffPt_GEM->Draw();
  }

//-------------------------------------------------------------------------------------------------------------------

  TEfficiency* pEffSimPt3_GEM = 0;
 
  //h_pass and h_total are valid and consistent histograms
  if(TEfficiency::CheckConsistency(*NumSimPt3_GEM,*DenSimPt_GEM))
  {
    	pEffSimPt3_GEM = new TEfficiency(*NumSimPt3_GEM,*DenSimPt_GEM);
    	// this will write the TEfficiency object to "myfile.root"
    	// AND pEff will be attached to the current directory
   	//pEffPt_GEM->Draw();
  }

//-------------------------------------------------------------------------------------------------------------------

  std::vector<TH1F*> vecResGEM;
  for(int i=1; i<=PtResVsPt_GEM->GetNbinsX(); i++){

	TH1F * temp = (TH1F*)pTRes_GEM->Clone();
	int col = i;
	if(i==10) col=41;
	if(i==5) col=46;
	temp->SetLineColor(col);
	temp->SetLineWidth(2);

	for(int j=1; j<=PtResVsPt_GEM->GetNbinsY(); j++){

		float bin = PtResVsPt_GEM->GetBinContent(i,j);

		temp->SetBinContent(bin,i);

	}

	vecResGEM.push_back(temp);

  }

  //std::cout<<vecResNoGEM.size()<<" "<<vecResGEM.size()<<std::endl;

  TH1F * DeltaChargePercentage_GEM = new TH1F("DeltaChargePercentage_GEM","Frac. Wrong Charge (SIM-RECO)",461,-2.5,2302.5);
  TH1F * numGem = (TH1F*)DeltaChargePercentage_GEM->Clone();
  TH1F * denGem = (TH1F*)DeltaChargePercentage_GEM->Clone();
  for(int i=1; i<=DeltaCharge_GEM->GetNbinsX(); i++){

	int num1 = DeltaCharge_GEM->GetBinContent(i,2);
	int num2 = DeltaCharge_GEM->GetBinContent(i,4); //zero
	int num3 = DeltaCharge_GEM->GetBinContent(i,6);

	numGem->SetBinContent(i,num1+num3);
	denGem->SetBinContent(i,num1+num2+num3);

	//double perc = (double) (num1 + num3)/(num1 + num2 + num3);
	//DeltaChargePercentage_GEM->SetBinContent(i,perc);

  }

  TEfficiency* pEffCharge_GEM = 0;
 
  //h_pass and h_total are valid and consistent histograms
  if(TEfficiency::CheckConsistency(*numGem,*denGem))
  {
    	pEffCharge_GEM = new TEfficiency(*numGem,*denGem);
    	// this will write the TEfficiency object to "myfile.root"
    	// AND pEff will be attached to the current directory
   	//pEffPt_GEM->Draw();
  }


  /////////////////////////////////////////////////////////////////////////////////////

  TLegend *leg2 = new TLegend(0.45,0.85,0.95,1.00);
  leg2->SetFillColor(0);
  leg2->SetLineColor(1);
  leg2->AddEntry(pTRec_NoGEM, "StandAloneMuons (2019Det)", "l");
  leg2->AddEntry(pTRec_GEM, "StandAloneMuons (2019Det+GE1/1)", "l");

  TCanvas * canvas = new TCanvas("canvas1","canvas",700,700);
  canvas->SetLogy();
  //canvas1->SetLogx();
  pTRec_NoGEM->Scale(1/pTRec_NoGEM->GetEntries());
  pTRec_GEM->Scale(1/pTRec_GEM->GetEntries());
  pTRec_NoGEM->Draw("HIST");
  pTRec_GEM->Draw("HISTSAME");
  leg2->Draw();
  canvas->SaveAs("plot1.pdf");

  //TCanvas * canvas2 = new TCanvas("canvas2","canvas",700,700);
  pTSim_NoGEM->Scale(1/pTSim_NoGEM->GetEntries());
  pTSim_GEM->Scale(1/pTSim_GEM->GetEntries());
  pTSim_NoGEM->Draw("HIST");
  pTSim_GEM->Draw("HISTSAME");
  leg2->Draw();
  canvas->SaveAs("plot2.pdf");

  //TCanvas * canvas3 = new TCanvas("canvas3","canvas",700,700);
  pTRes_NoGEM->GetXaxis()->SetTitle("(p_{T}^{Reco} - p_{T}^{Sim}) / p_{T}^{Sim}");
  pTRes_NoGEM->Scale(1/pTRes_NoGEM->GetEntries());
  pTRes_GEM->Scale(1/pTRes_GEM->GetEntries());
  pTRes_NoGEM->Draw("HIST");
  pTRes_GEM->Draw("HISTSAME");
  leg2->Draw();
  canvas->SaveAs("plot3.pdf");

  //TCanvas * canvas4 = new TCanvas("canvas4","canvas",700,700);
  invPTRes_NoGEM->GetXaxis()->SetTitle("(q^{Reco}/p_{T}^{Reco} - q^{Sim}/p_{T}^{Sim}) / q^{Sim}/p_{T}^{Sim}");
  invPTRes_NoGEM->Scale(1/invPTRes_NoGEM->GetEntries());
  invPTRes_GEM->Scale(1/invPTRes_GEM->GetEntries());
  invPTRes_NoGEM->Draw("HIST");
  invPTRes_GEM->Draw("HISTSAME");
  leg2->Draw();
  canvas->SaveAs("plot4.pdf");

  //TCanvas * canvas5 = new TCanvas("canvas5","canvas",700,700);
  pTDiff_NoGEM->Scale(1/pTDiff_NoGEM->GetEntries());
  pTDiff_GEM->Scale(1/pTDiff_GEM->GetEntries());
  pTDiff_NoGEM->Draw("HIST");
  pTDiff_GEM->Draw("HISTSAME");
  leg2->Draw();
  canvas->SaveAs("plot5.pdf");

  canvas->SetLogy(0);

  //TCanvas * canvas7 = new TCanvas("canvas7","canvas",700,700);
  PSimEta_NoGEM->Scale(1/PSimEta_NoGEM->GetEntries());
  PSimEta_GEM->Scale(1/PSimEta_GEM->GetEntries());
  PSimEta_NoGEM->Draw("HIST");
  PSimEta_GEM->Draw("HISTSAME");
  canvas->SaveAs("plot7.pdf");

  //TCanvas * canvas8 = new TCanvas("canvas8","canvas",700,700);
  PRecEta_NoGEM->Draw();
  PRecEta_GEM->Draw("SAME");
  leg2->Draw();
  canvas->SaveAs("plot8.pdf");

  //TCanvas * canvas9 = new TCanvas("canvas9","canvas",700,700);
  //PDeltaEta_NoGEM->Draw();
  //PDeltaEta_GEM->Draw("SAME");
  //leg2->Draw();
  //canvas->SaveAs("plot9.pdf");

  //TCanvas * canvas10 = new TCanvas("canvas10","canvas",700,700);
  PSimPhi_NoGEM->SetMinimum(0);
  PSimPhi_NoGEM->Draw();
  PSimPhi_GEM->Draw("SAME");
  canvas->SaveAs("plot10.pdf");

  //TCanvas * canvas11 = new TCanvas("canvas11","canvas",700,700);
  PRecPhi_NoGEM->SetMinimum(0);
  PRecPhi_NoGEM->Draw();
  PRecPhi_GEM->Draw("SAME");
  leg2->Draw();
  canvas->SaveAs("plot11.pdf");

  //TCanvas * canvas12 = new TCanvas("canvas12","canvas",700,700);
  NumSimTracks_NoGEM->Draw();
  NumSimTracks_GEM->Draw("SAME");
  canvas->SaveAs("plot12.pdf");

  //TCanvas * canvas13 = new TCanvas("canvas13","canvas",700,700);
  NumMuonSimTracks_NoGEM->Draw();
  NumMuonSimTracks_GEM->Draw("SAME");
  canvas->SaveAs("plot13.pdf");

  //TCanvas * canvas14 = new TCanvas("canvas14","canvas",700,700);
  NumRecTracks_NoGEM->SetStats(kFALSE);
  NumRecTracks_NoGEM->Draw();
  NumRecTracks_NoGEM->GetXaxis()->SetTitle("# RecoTracks");
  NumRecTracks_GEM->SetLineColor(2);
  NumRecTracks_GEM->SetLineStyle(2);
  NumRecTracks_GEM->Draw("SAME");
  leg2->Draw();
  canvas->SaveAs("plot14.pdf");

  TLegend *leg22 = new TLegend(0.45,0.85,0.95,1.00);
  leg22->SetFillColor(0);
  leg22->SetLineColor(1);
  leg22->AddEntry(prof1_NoGEM, "StandAloneMuons (2019Det)", "pl");
  leg22->AddEntry(prof1_GEM, "StandAloneMuons (2019Det+GE1/1)", "pl");

  canvas->Clear();
  canvas->Update();

  TLegend *leg4 = new TLegend(0.2,0.60,0.6,0.95);
  leg4->SetFillColor(0);
  leg4->SetLineColor(1);

  //TCanvas * canvas21bis = new TCanvas("canvas21bis","canvas",700,700);
  TH1F * rmsNoGem = new TH1F("rmsNoGem","",461,-2.5,2302.5);
  TH1F * rmsGem = new TH1F("rmsGem","",461,-2.5,2302.5);
  for(int i=1; i<=prof2bis_NoGEM->GetNbinsX(); i++){

	TH1D * noGemTmp = InvPtResVsPt_NoGEM2->ProjectionY("projNoGemTmp",i,i);
	TH1D * GemTmp = InvPtResVsPt_GEM2->ProjectionY("projGemTmp",i,i);

	std::cout<<noGemTmp->GetRMSError()<<" "<<GemTmp->GetRMSError()<<std::endl;

	double rms1 = prof2bis_NoGEM->GetBinError(i);
	double rms2 = prof2bis_GEM->GetBinError(i);

	//cout<<rms1<<" "<<rms2<<endl;

	rmsNoGem->SetBinContent(i,rms1);
	rmsGem->SetBinContent(i,rms2);
	rmsNoGem->SetBinError(i,noGemTmp->GetRMSError());
	rmsGem->SetBinError(i,GemTmp->GetRMSError());

  }
  TH1F * ratio21Bis = makeRatio(rmsNoGem, rmsGem);
  canvas->Divide(1,2);
  TPad * pRMS1 = canvas->cd(1);
  pRMS1->SetLogx();
  rmsNoGem->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  rmsNoGem->GetYaxis()->SetTitle("RMS");
  rmsNoGem->GetXaxis()->SetRangeUser(2.5,2300);
  rmsNoGem->SetMarkerSize(1);
  rmsNoGem->SetMarkerColor(9);
  rmsGem->SetMarkerSize(1);
  rmsNoGem->SetMarkerStyle(20);
  rmsGem->SetMarkerStyle(20);
  rmsNoGem->SetStats(kFALSE);
  rmsNoGem->SetMinimum(0.01);
  rmsNoGem->SetMaximum(4);
  rmsNoGem->Draw("E1P");
  rmsGem->SetMarkerColor(2);
  rmsGem->Draw("E1PSAME");
  leg4->AddEntry(rmsNoGem,"StandAloneMuons (2019Det)","pl");
  leg4->AddEntry(rmsGem,"StandAloneMuons (2019Det+GE1/1)","pl");
  leg4->Draw();
  TPad * pRMS2 = canvas->cd(2);
  pRMS2->SetLogx();
  ratio21Bis->SetMinimum(0.8);
  ratio21Bis->GetXaxis()->SetRangeUser(2.5,2300);
  ratio21Bis->Draw("E1PTEXT");
  ratio21Bis->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  ratio21Bis->GetYaxis()->SetTitle("RMS_{staMuonGEM} / RMS_{staMuonNoGEM}");
  canvas->SaveAs("plot21bis.pdf");

  canvas->Clear();
  canvas->Update();

  //TCanvas * canvas23Sim = new TCanvas("canvas23Sim","canvas",700,700);
  pEffSimPt_GEM->Draw("AP");
  gPad->Update();
  pEffSimPt_GEM->GetPaintedGraph()->GetXaxis()->SetLabelSize(0.03);
  pEffSimPt_GEM->GetPaintedGraph()->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  gPad->Update();
  pEffSimPt_GEM->GetPaintedGraph()->GetYaxis()->SetTitle("#varepsilon");
  gPad->Update();
  canvas->SaveAs("plot23Sim.pdf");

  //TCanvas * canvas24Sim = new TCanvas("canvas24Sim","canvas",700,700);
  //canvas24->SetLogy();
  pEffSimEta_GEM->Draw("AP");
  gPad->Update();
  pEffSimEta_GEM->GetPaintedGraph()->GetXaxis()->SetTitle("#eta^{Sim}");
  gPad->Update();
  pEffSimEta_GEM->GetPaintedGraph()->GetYaxis()->SetTitle("#varepsilon");
  canvas->SaveAs("plot24Sim.pdf");

//---------------------------------------------------------------------------------------------------------------------------

  TLegend *legEff1 = new TLegend(0.60,0.7,0.8,0.8);
  legEff1->SetFillColor(0);
  legEff1->SetLineColor(1);
  legEff1->SetHeader("GE1/1");

  //TCanvas * canvas23Sim = new TCanvas("canvas23Sim","canvas",700,700);
  pEffSimPt1_GEM->Draw("AP");
  gPad->Update();
  pEffSimPt1_GEM->GetPaintedGraph()->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  pEffSimPt1_GEM->GetPaintedGraph()->GetXaxis()->SetLabelSize(0.03);
  gPad->Update();
  pEffSimPt1_GEM->GetPaintedGraph()->GetYaxis()->SetTitle("#varepsilon");
  gPad->Update();
  legEff1->Draw();
  gPad->Update();
  canvas->SaveAs("plot23Sim_1.pdf");

  legEff1->SetHeader("GE2/1short");

  //TCanvas * canvas23Sim = new TCanvas("canvas23Sim","canvas",700,700);
  pEffSimPt2_GEM->Draw("AP");
  gPad->Update();
  pEffSimPt2_GEM->GetPaintedGraph()->GetXaxis()->SetLabelSize(0.03);
  pEffSimPt2_GEM->GetPaintedGraph()->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  gPad->Update();
  pEffSimPt2_GEM->GetPaintedGraph()->GetYaxis()->SetTitle("#varepsilon");
  gPad->Update();
  legEff1->Draw();
  gPad->Update();
  canvas->SaveAs("plot23Sim_2.pdf");

  legEff1->SetHeader("GE2/1long");

  //TCanvas * canvas23Sim = new TCanvas("canvas23Sim","canvas",700,700);
  pEffSimPt3_GEM->Draw("AP");
  gPad->Update();
  pEffSimPt3_GEM->GetPaintedGraph()->GetXaxis()->SetLabelSize(0.03);
  pEffSimPt3_GEM->GetPaintedGraph()->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  gPad->Update();
  pEffSimPt3_GEM->GetPaintedGraph()->GetYaxis()->SetTitle("#varepsilon");
  gPad->Update();
  legEff1->Draw();
  gPad->Update();
  canvas->SaveAs("plot23Sim_3.pdf");

  TLegend *legEff = new TLegend(0.60,0.69,0.95,0.99);
  legEff->SetFillColor(0);
  legEff->SetLineColor(1);

  //TCanvas * canvas23Sim = new TCanvas("canvas23Sim","canvas",700,700);
  pEffSimPt1_GEM->Draw("AP");
  gPad->Update();
  pEffSimPt1_GEM->GetPaintedGraph()->GetXaxis()->SetLabelSize(0.03);
  pEffSimPt1_GEM->GetPaintedGraph()->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  gPad->Update();
  pEffSimPt1_GEM->GetPaintedGraph()->GetYaxis()->SetTitle("#varepsilon");
  gPad->Update();
  pEffSimPt2_GEM->SetMarkerColor(2);
  pEffSimPt2_GEM->Draw("SAME");
  pEffSimPt3_GEM->SetMarkerColor(6);
  pEffSimPt3_GEM->Draw("SAME");
  gPad->Update();
  legEff->AddEntry(pEffSimPt1_GEM, "GE1/1", "p");
  legEff->AddEntry(pEffSimPt2_GEM, "GE2/1short", "p");
  legEff->AddEntry(pEffSimPt3_GEM, "GE2/1long", "p");
  legEff->Draw();
  gPad->Update();

  canvas->SaveAs("plot23Sim_tot.pdf");

  //exit(0);

//-------------------------------------------------------------------------------------------------------------------------------

  canvas->Clear();
  canvas->Update();

  TLegend *leg23 = new TLegend(0.6,0.20,0.95,0.6);
  leg23->SetFillColor(0);
  leg23->SetLineColor(1);

  canvas->Divide(1,2);
  TPad * p1 = canvas->cd(1);
  p1->SetLogy();
  p1->SetLogx();
  pEffCharge_NoGEM->SetLineColor(9);
  pEffCharge_NoGEM->SetMarkerColor(9);
  gPad->Update();
  pEffCharge_NoGEM->Draw("AP");
  gPad->Update();
  pEffCharge_NoGEM->GetPaintedGraph()->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  gPad->Update();
  pEffCharge_NoGEM->GetPaintedGraph()->SetMinimum(0.0001);
  pEffCharge_NoGEM->GetPaintedGraph()->SetMaximum(0.6);
  gPad->Update();
  pEffCharge_NoGEM->GetPaintedGraph()->GetYaxis()->SetTitle("Charge misidentification prob.");
  gPad->Update();
  pEffCharge_GEM->SetLineColor(2);
  pEffCharge_GEM->SetMarkerColor(2);
  gPad->Update();
  pEffCharge_GEM->Draw("SAME");
  gPad->Update();
  leg23->AddEntry(pEffCharge_NoGEM, "StandAloneMuons (2019Det)", "pl");
  leg23->AddEntry(pEffCharge_GEM, "StandAloneMuons (2019Det+GE1/1)", "pl");
  leg23->Draw();
  TPad * p2 = canvas->cd(2);
  //p2->SetLogy();
  p2->SetLogx();
  TH1D * ratio30 = makeRatio3(pEffCharge_NoGEM, pEffCharge_GEM);
  ratio30->SetMaximum(1.0);
  ratio30->SetMinimum(0.8);
  ratio30->GetXaxis()->SetRangeUser(2.5,2300);
  ratio30->Draw("E1PTEXT");
  ratio30->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  ratio30->GetYaxis()->SetTitle("Prob._{staMuonGEM} / Prob._{staMuonNoGEM}");
  canvas->SaveAs("plot30.pdf");

  canvas->Clear();
  canvas->Update();

  //TCanvas * canvas35 = new TCanvas("canvas35","canvas",1400,700);
  //canvas24->SetLogy();
  pEffPhiPlus_GEM->Draw("AP");
  gPad->Update();
  pEffPhiPlus_GEM->GetPaintedGraph()->GetXaxis()->SetTitle("#phi^{Reco}");
  gPad->Update();
  pEffPhiPlus_GEM->SetTitle("GLB Muons Plus Region");
  gPad->Update();
  pEffPhiPlus_GEM->GetPaintedGraph()->GetYaxis()->SetTitle("#varepsilon (#eta > 0)");
  canvas->SaveAs("plot35.pdf");

  //TCanvas * canvas36 = new TCanvas("canvas36","canvas",1400,700);
  //canvas24->SetLogy();
  pEffPhiMinus_GEM->Draw("AP");
  gPad->Update();
  pEffPhiMinus_GEM->GetPaintedGraph()->GetXaxis()->SetTitle("#phi^{Reco}");
  gPad->Update();
  pEffPhiMinus_GEM->SetTitle("GLB Muons Minus Region");
  gPad->Update();
  pEffPhiMinus_GEM->GetPaintedGraph()->GetYaxis()->SetTitle("#varepsilon (#eta < 0)");
  canvas->SaveAs("plot36.pdf");

  //TCanvas * canvas35Sim = new TCanvas("canvas35Sim","canvas",1400,700);
  //canvas24->SetLogy();
  pEffSimPhiPlus_GEM->Draw("AP");
  gPad->Update();
  pEffSimPhiPlus_GEM->GetPaintedGraph()->GetXaxis()->SetTitle("#phi^{Sim}");
  gPad->Update();
  pEffSimPhiPlus_GEM->SetTitle("STA Muons Plus Region");
  gPad->Update();
  pEffSimPhiPlus_GEM->GetPaintedGraph()->GetYaxis()->SetTitle("#varepsilon (#eta > 0)");
  canvas->SaveAs("plot35Sim.pdf");

  //TCanvas * canvas36Sim = new TCanvas("canvas36Sim","canvas",1400,700);
  //canvas24->SetLogy();
  pEffSimPhiMinus_GEM->Draw("AP");
  gPad->Update();
  pEffSimPhiMinus_GEM->GetPaintedGraph()->GetXaxis()->SetTitle("#phi^{Sim}");
  gPad->Update();
  pEffSimPhiMinus_GEM->SetTitle("STA Muons Minus Region");
  gPad->Update();
  pEffSimPhiMinus_GEM->GetPaintedGraph()->GetYaxis()->SetTitle("#varepsilon (#eta < 0)");
  canvas->SaveAs("plot36Sim.pdf");

  gStyle->SetPalette(1,0); 

  gPad->SetLogx();
  DRMatchVsPt_GEM->SetStats(kFALSE);
  DRMatchVsPt_GEM->GetYaxis()->SetTitle("# Matched RecoTracks per Muon SimTrack in #Delta R < 0.1 (GEM)");
  DRMatchVsPt_GEM->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  DRMatchVsPt_GEM->Draw("TEXTCOLZ");
  canvas->SaveAs("plot43.pdf");

  DRMatchVsPt_NoGEM->SetStats(kFALSE);
  DRMatchVsPt_NoGEM->GetYaxis()->SetTitle("# Matched RecoTracks per Muon SimTrack in #Delta R < 0.1 (NoGEM)");
  DRMatchVsPt_NoGEM->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  DRMatchVsPt_NoGEM->Draw("TEXTCOLZ");
  canvas->SaveAs("plot44.pdf");

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////

  TCanvas * canvasFit = new TCanvas("canvasFit","canvas",700,700);
  canvasFit->Divide(1,2);

  f1_->cd();
  canvasFit->cd(1);
  TH2F * PtResVsPt_NoGEM_Clone = (TH2F*)PtResVsPt_NoGEM->Clone();
  PtResVsPt_NoGEM_Clone->GetYaxis()->SetTitle("(p_{T}^{Reco} - p_{T}^{Sim}) / p_{T}^{Sim}");
  PtResVsPt_NoGEM_Clone->Draw("COLZ");
  canvasFit->cd(2);
  //f1->SetRange(xmin,xmax);
  PtResVsPt_NoGEM_Clone->FitSlicesY(0, 0, -1, 0, "R");
  TH1D *PtResVsPt_NoGEM_Sigma = (TH1D*)gDirectory->Get("PtResVsPt_2");
  PtResVsPt_NoGEM_Sigma->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  PtResVsPt_NoGEM_Sigma->GetYaxis()->SetTitle("#sigma_{Res}");
  PtResVsPt_NoGEM_Sigma->Draw();

  canvasFit->SaveAs("PtResVsPt_NoGEM.pdf");

  canvasFit->cd(1);
  TH2F * InvPtResVsPt_NoGEM_Clone = (TH2F*)InvPtResVsPt_NoGEM->Clone();
  InvPtResVsPt_NoGEM_Clone->GetYaxis()->SetTitle("(q^{Reco}/p_{T}^{Reco} - q^{Sim}/p_{T}^{Sim}) / q^{Sim}/p_{T}^{Sim}");
  InvPtResVsPt_NoGEM_Clone->Draw("COLZ");
  canvasFit->cd(2);
  //f1->SetRange(xmin,xmax);
  InvPtResVsPt_NoGEM_Clone->FitSlicesY(0, 0, -1, 0, "R");
  TH1D *InvPtResVsPt_NoGEM_Sigma = (TH1D*)gDirectory->Get("InvPtResVsPt_2");
  InvPtResVsPt_NoGEM_Sigma->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  InvPtResVsPt_NoGEM_Sigma->GetYaxis()->SetTitle("#sigma_{InvRes}");
  InvPtResVsPt_NoGEM_Sigma->Draw();

  canvasFit->SaveAs("InvPtResVsPt_NoGEM.pdf");

  f2_->cd(); 
  canvasFit->cd(1);
  TH2F * PtResVsPt_GEM_Clone = (TH2F*)PtResVsPt_GEM->Clone();
  PtResVsPt_GEM_Clone->GetYaxis()->SetTitle("(p_{T}^{Reco} - p_{T}^{Sim}) / p_{T}^{Sim}");
  PtResVsPt_GEM_Clone->Draw("COLZ");
  canvasFit->cd(2);
  //f1->SetRange(xmin,xmax);
  PtResVsPt_GEM_Clone->FitSlicesY(0, 0, -1, 0, "R");
  TH1D *PtResVsPt_GEM_Sigma = (TH1D*)gDirectory->Get("PtResVsPt_2");
  PtResVsPt_GEM_Sigma->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  PtResVsPt_GEM_Sigma->GetYaxis()->SetTitle("#sigma_{Res}");
  PtResVsPt_GEM_Sigma->Draw();

  canvasFit->SaveAs("PtResVsPt_GEM.pdf");

  canvasFit->cd(1);
  TH2F * InvPtResVsPt_GEM_Clone = (TH2F*)InvPtResVsPt_GEM->Clone();
  InvPtResVsPt_GEM_Clone->GetYaxis()->SetTitle("(q^{Reco}/p_{T}^{Reco} - q^{Sim}/p_{T}^{Sim}) / q^{Sim}/p_{T}^{Sim}");
  InvPtResVsPt_GEM_Clone->Draw("COLZ");
  canvasFit->cd(2);
  //f1->SetRange(xmin,xmax);
  InvPtResVsPt_GEM_Clone->FitSlicesY(0, 0, -1, 0, "R");
  TH1D *InvPtResVsPt_GEM_Sigma = (TH1D*)gDirectory->Get("InvPtResVsPt_2");
  InvPtResVsPt_GEM_Sigma->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  InvPtResVsPt_GEM_Sigma->GetYaxis()->SetTitle("#sigma_{InvRes}");
  InvPtResVsPt_GEM_Sigma->Draw();

  canvasFit->SaveAs("InvPtResVsPt_GEM.pdf");

  canvasFit->Clear();
  canvasFit->Update();

  canvasFit->Divide(1,2);
  canvasFit->cd(1);
  PtResVsPt_NoGEM_Sigma->SetMaximum(6.05);
  PtResVsPt_NoGEM_Sigma->SetMarkerColor(9);
  PtResVsPt_NoGEM_Sigma->SetMarkerSize(0.7);
  PtResVsPt_NoGEM_Sigma->Draw("E1P");
  PtResVsPt_GEM_Sigma->SetMarkerColor(2);
  PtResVsPt_GEM_Sigma->SetMarkerSize(0.7);
  PtResVsPt_GEM_Sigma->Draw("E1PSAME");
  leg4->Draw();
  canvasFit->cd(2);
  TH1D * ratioComp1 = makeRatio2(PtResVsPt_NoGEM_Sigma, PtResVsPt_GEM_Sigma);
  ratioComp1->SetMarkerColor(1);
  ratioComp1->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  ratioComp1->GetYaxis()->SetTitle("#sigma_{Res}^{GEM} / #sigma_{Res}^{NoGEM}");
  ratioComp1->Draw("E1P");
  canvasFit->SaveAs("comparison_res.pdf");

  canvasFit->Clear();
  canvasFit->Update();

  canvasFit->Divide(1,2);
  canvasFit->cd(1);
  InvPtResVsPt_NoGEM_Sigma->SetMaximum(7.00);
  InvPtResVsPt_NoGEM_Sigma->SetMinimum(0.01);
  InvPtResVsPt_NoGEM_Sigma->SetMarkerColor(9);
  InvPtResVsPt_NoGEM_Sigma->SetMarkerSize(0.7);
  InvPtResVsPt_NoGEM_Sigma->Draw("E1P");
  InvPtResVsPt_GEM_Sigma->SetMarkerColor(2);
  InvPtResVsPt_GEM_Sigma->SetMarkerSize(0.7);
  InvPtResVsPt_GEM_Sigma->Draw("E1PSAME");
  leg4->Draw();
  canvasFit->cd(2);
  TH1D * ratioComp2 = makeRatio2(InvPtResVsPt_NoGEM_Sigma, InvPtResVsPt_GEM_Sigma);
  ratioComp2->SetMarkerColor(1);
  ratioComp2->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  ratioComp2->GetYaxis()->SetTitle("#sigma_{InvRes}^{GEM} / #sigma_{InvRes}^{NoGEM}");
  ratioComp2->Draw("E1P");

  canvasFit->SaveAs("comparison_invres.pdf");

  canvasFit->Clear();
  canvasFit->Update();

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////

  TLegend *leg5 = new TLegend(0.75,0.50,0.95,0.90);
  leg5->SetFillColor(kWhite);
  leg5->SetLineColor(kWhite);
  leg5->SetHeader("StandAloneMuons (2019Det)");

  canvasFit->Divide(1,2);
  canvasFit->cd(1);
  canvasFit_1->SetLogy();
  TH1D * proj1 = PtResVsPt_NoGEM_Clone->ProjectionY("proj1",1,2);
  proj1->SetLineColor(1);
  leg5->AddEntry(proj1,"p_{T} = 5 GeV/c","l");
  TH1D * proj2 = PtResVsPt_NoGEM_Clone->ProjectionY("proj2",3,4);
  proj2->SetLineColor(2);
  leg5->AddEntry(proj2,"p_{T} = 10 GeV/c","l");
  TH1D * proj3 = PtResVsPt_NoGEM_Clone->ProjectionY("proj3",9,11);
  proj3->SetLineColor(3);
  leg5->AddEntry(proj3,"p_{T} = 50 GeV/c","l");
  TH1D * proj4 = PtResVsPt_NoGEM_Clone->ProjectionY("proj4",19,21);
  proj4->SetLineColor(4);
  leg5->AddEntry(proj4,"p_{T} = 100 GeV/c","l");
  TH1D * proj5 = PtResVsPt_NoGEM_Clone->ProjectionY("proj5",39,41);
  proj5->SetLineColor(5);
  leg5->AddEntry(proj5,"p_{T} = 200 GeV/c","l");
  TH1D * proj6 = PtResVsPt_NoGEM_Clone->ProjectionY("proj6",99,101);
  proj6->SetLineColor(6);
  leg5->AddEntry(proj6,"p_{T} = 500 GeV/c","l");
  TH1D * proj7 = PtResVsPt_NoGEM_Clone->ProjectionY("proj7",159,161);
  proj7->SetLineColor(7);
  leg5->AddEntry(proj7,"p_{T} = 800 GeV/c","l");
  TH1D * proj8 = PtResVsPt_NoGEM_Clone->ProjectionY("proj8",199,201);
  proj7->SetLineColor(8);
  leg5->AddEntry(proj8,"p_{T} = 1000 GeV/c","l");
  TH1D * proj9 = PtResVsPt_NoGEM_Clone->ProjectionY("proj9",399,401);
  proj9->SetLineColor(9);
  leg5->AddEntry(proj9,"p_{T} = 2000 GeV/c","l");

  proj1->Draw();
  proj2->Draw("SAME");
  proj3->Draw("SAME");
  proj4->Draw("SAME");
  proj5->Draw("SAME");
  proj6->Draw("SAME");
  proj7->Draw("SAME");
  proj8->Draw("SAME");
  proj9->Draw("SAME");

  leg5->Draw();

  canvasFit->cd(2);
  canvasFit_2->SetLogy();
  TH1D * projI1 = InvPtResVsPt_NoGEM_Clone->ProjectionY("projI1",1,2);
  projI1->SetLineColor(1);
  TH1D * projI2 = InvPtResVsPt_NoGEM_Clone->ProjectionY("projI2",3,4);
  projI2->SetLineColor(2);
  TH1D * projI3 = InvPtResVsPt_NoGEM_Clone->ProjectionY("projI3",9,11);
  projI3->SetLineColor(3);
  TH1D * projI4 = InvPtResVsPt_NoGEM_Clone->ProjectionY("projI4",19,21);
  projI4->SetLineColor(4);
  TH1D * projI5 = InvPtResVsPt_NoGEM_Clone->ProjectionY("projI5",39,41);
  projI5->SetLineColor(5);
  TH1D * projI6 = InvPtResVsPt_NoGEM_Clone->ProjectionY("projI6",99,101);
  projI6->SetLineColor(6);
  TH1D * projI7 = InvPtResVsPt_NoGEM_Clone->ProjectionY("projI7",159,161);
  projI7->SetLineColor(7);
  TH1D * projI8 = InvPtResVsPt_NoGEM_Clone->ProjectionY("projI8",199,201);
  projI8->SetLineColor(8);
  TH1D * projI9 = InvPtResVsPt_NoGEM_Clone->ProjectionY("projI9",399,401);
  projI9->SetLineColor(9);

  projI1->Draw();
  projI2->Draw("SAME");
  projI3->Draw("SAME");
  projI4->Draw("SAME");
  projI5->Draw("SAME");
  projI6->Draw("SAME");
  projI7->Draw("SAME");
  projI8->Draw("SAME");
  projI9->Draw("SAME");

  leg5->Draw();

  canvasFit->SaveAs("resNoGEM.pdf");

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////

  leg5->SetHeader("StandAloneMuons (2019Det+GE1/1)");

  canvasFit->cd(1);
  canvasFit_1->SetLogy();
  TH1D * projGEM1 = PtResVsPt_GEM_Clone->ProjectionY("projGEM1",1,2);
  projGEM1->SetLineColor(1);
  TH1D * projGEM2 = PtResVsPt_GEM_Clone->ProjectionY("projGEM2",3,4);
  projGEM2->SetLineColor(2);
  TH1D * projGEM3 = PtResVsPt_GEM_Clone->ProjectionY("projGEM3",9,11);
  projGEM3->SetLineColor(3);
  TH1D * projGEM4 = PtResVsPt_GEM_Clone->ProjectionY("projGEM4",19,21);
  projGEM4->SetLineColor(4);
  TH1D * projGEM5 = PtResVsPt_GEM_Clone->ProjectionY("projGEM5",39,41);
  projGEM5->SetLineColor(5);
  TH1D * projGEM6 = PtResVsPt_GEM_Clone->ProjectionY("projGEM6",99,101);
  projGEM6->SetLineColor(6);
  TH1D * projGEM7 = PtResVsPt_GEM_Clone->ProjectionY("projGEM7",159,161);
  projGEM7->SetLineColor(7);
  TH1D * projGEM8 = PtResVsPt_GEM_Clone->ProjectionY("projGEM8",199,201);
  projGEM8->SetLineColor(8);
  TH1D * projGEM9 = PtResVsPt_GEM_Clone->ProjectionY("projGEM9",399,401);
  projGEM9->SetLineColor(9);

  projGEM1->Draw();
  projGEM2->Draw("SAME");
  projGEM3->Draw("SAME");
  projGEM4->Draw("SAME");
  projGEM5->Draw("SAME");
  projGEM6->Draw("SAME");
  projGEM7->Draw("SAME");
  projGEM8->Draw("SAME");
  projGEM9->Draw("SAME");

  leg5->Draw();

  canvasFit->cd(2);
  canvasFit_1->SetLogy();
  TH1D * projGEMI1 = InvPtResVsPt_GEM_Clone->ProjectionY("projGEMI1",1,2);
  projGEMI1->SetLineColor(1);
  TH1D * projGEMI2 = InvPtResVsPt_GEM_Clone->ProjectionY("projGEMI2",3,4);
  projGEMI2->SetLineColor(2);
  TH1D * projGEMI3 = InvPtResVsPt_GEM_Clone->ProjectionY("projGEMI3",9,11);
  projGEMI3->SetLineColor(3);
  TH1D * projGEMI4 = InvPtResVsPt_GEM_Clone->ProjectionY("projGEMI4",19,21);
  projGEMI4->SetLineColor(4);
  TH1D * projGEMI5 = InvPtResVsPt_GEM_Clone->ProjectionY("projGEMI5",39,41);
  projGEMI5->SetLineColor(5);
  TH1D * projGEMI6 = InvPtResVsPt_GEM_Clone->ProjectionY("projGEMI6",99,101);
  projGEMI6->SetLineColor(6);
  TH1D * projGEMI7 = InvPtResVsPt_GEM_Clone->ProjectionY("projGEMI7",159,161);
  projGEMI7->SetLineColor(7);
  TH1D * projGEMI8 = InvPtResVsPt_GEM_Clone->ProjectionY("projGEMI8",199,201);
  projGEMI8->SetLineColor(8);
  TH1D * projGEMI9 = InvPtResVsPt_GEM_Clone->ProjectionY("projGEMI9",399,401);
  projGEMI9->SetLineColor(9);

  projGEMI1->Draw();
  projGEMI2->Draw("SAME");
  projGEMI3->Draw("SAME");
  projGEMI4->Draw("SAME");
  projGEMI5->Draw("SAME");
  projGEMI6->Draw("SAME");
  projGEMI7->Draw("SAME");
  projGEMI8->Draw("SAME");
  projGEMI9->Draw("SAME");

  leg5->Draw();

  canvasFit->SaveAs("resGEM.pdf");

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////

  //TCanvas * canvasFit2 = new TCanvas("canvasFit2","canvas",1300,700);
  //canvasFit2->Divide(4,2);
  //canvasFit2->cd(1);
  MyPar sigmaNoGEM1 = extractSigma(proj1,"sigmaNoGEM1");
  //canvasFit2->cd(2);
  MyPar sigmaNoGEM2 = extractSigma(proj2,"sigmaNoGEM2");
  //canvasFit2->cd(3);
  MyPar sigmaNoGEM3 = extractSigma(proj3,"sigmaNoGEM3");
  //canvasFit2->cd(4);
  MyPar sigmaNoGEM4 = extractSigmaBis(proj4,"sigmaNoGEM4");
  //canvasFit2->cd(5);
  MyPar sigmaNoGEM5 = extractSigmaBis(proj5,"sigmaNoGEM5");
  //canvasFit2->cd(6);
  MyPar sigmaNoGEM6 = extractSigmaBis(proj6,"sigmaNoGEM6");
  //canvasFit2->cd(7);
  MyPar sigmaNoGEM7 = extractSigmaBis(proj7,"sigmaNoGEM7");
  //canvasFit2->cd(8);
  MyPar sigmaNoGEM8 = extractSigmaBis(proj8,"sigmaNoGEM8");
  //canvasFit2->cd(9);
  MyPar sigmaNoGEM9 = extractSigmaBis(proj9,"sigmaNoGEM9");
  //canvasFit2->SaveAs("fitResNoGEM.pdf");

  //canvasFit2->cd(1);
  MyPar sigmaNoGEMI1 = extractSigma(projI1,"sigmaNoGEMI1");
  //canvasFit2->cd(2);
  MyPar sigmaNoGEMI2 = extractSigma(projI2,"sigmaNoGEMI2");
  //canvasFit2->cd(3);
  MyPar sigmaNoGEMI3 = extractSigma(projI3,"sigmaNoGEMI3");
  //canvasFit2->cd(4);
  MyPar sigmaNoGEMI4 = extractSigmaBis(projI4,"sigmaNoGEMI4");
  //canvasFit2->cd(5);
  MyPar sigmaNoGEMI5 = extractSigmaBis(projI5,"sigmaNoGEMI5");
  //canvasFit2->cd(6);
  MyPar sigmaNoGEMI6 = extractSigmaBis(projI6,"sigmaNoGEMI6");
  //canvasFit2->cd(7);
  MyPar sigmaNoGEMI7 = extractSigmaBis(projI7,"sigmaNoGEMI7");
  //canvasFit2->cd(8);
  MyPar sigmaNoGEMI8 = extractSigmaBis(projI8,"sigmaNoGEMI8");
  //canvasFit2->cd(9);
  MyPar sigmaNoGEMI9 = extractSigmaBis(projI9,"sigmaNoGEMI9");
  //canvasFit2->SaveAs("fitInvResNoGEM.pdf");

  //canvasFit2->cd(1);
  MyPar sigmaGEM1 = extractSigma(projGEM1,"sigmaGEM1");
  //canvasFit2->cd(2);
  MyPar sigmaGEM2 = extractSigma(projGEM2,"sigmaGEM2");
  //canvasFit2->cd(3);
  MyPar sigmaGEM3 = extractSigma(projGEM3,"sigmaGEM3");
  //canvasFit2->cd(4);
  MyPar sigmaGEM4 = extractSigmaBis(projGEM4,"sigmaGEM4");
  //canvasFit2->cd(5);
  MyPar sigmaGEM5 = extractSigmaBis(projGEM5,"sigmaGEM5");
  //canvasFit2->cd(6);
  MyPar sigmaGEM6 = extractSigmaBis(projGEM6,"sigmaGEM6");
  //canvasFit2->cd(7);
  MyPar sigmaGEM7 = extractSigmaBis(projGEM7,"sigmaGEM7");
  //canvasFit2->cd(8);
  MyPar sigmaGEM8 = extractSigmaBis(projGEM8,"sigmaGEM8");
  //canvasFit2->cd(9);
  MyPar sigmaGEM9 = extractSigmaBis(projGEM9,"sigmaGEM9");
  //canvasFit2->SaveAs("fitResGEM.pdf");

  //canvasFit2->cd(1);
  MyPar sigmaGEMI1 = extractSigma(projGEMI1,"sigmaGEMI1");
  //canvasFit2->cd(2);
  MyPar sigmaGEMI2 = extractSigma(projGEMI2,"sigmaGEMI2");
  //canvasFit2->cd(3);
  MyPar sigmaGEMI3 = extractSigma(projGEMI3,"sigmaGEMI3");
  //canvasFit2->cd(4);
  MyPar sigmaGEMI4 = extractSigmaBis(projGEMI4,"sigmaGEMI4");
  //canvasFit2->cd(5);
  MyPar sigmaGEMI5 = extractSigmaBis(projGEMI5,"sigmaGEMI5");
  //canvasFit2->cd(6);
  MyPar sigmaGEMI6 = extractSigmaBis(projGEMI6,"sigmaGEMI6");
  //canvasFit2->cd(7);
  MyPar sigmaGEMI7 = extractSigmaBis(projGEMI7,"sigmaGEMI7");
  //canvasFit2->cd(8);
  MyPar sigmaGEMI8 = extractSigmaBis(projGEMI8,"sigmaGEMI8");
  //canvasFit2->cd(9);
  MyPar sigmaGEMI9 = extractSigmaBis(projGEMI9,"sigmaGEMI9");
  //canvasFit2->SaveAs("fitInvResGEM.pdf");

  makeSuperImp(sigmaNoGEMI1, sigmaGEMI1, "invResComp_5.pdf");
  makeSuperImp(sigmaNoGEMI2, sigmaGEMI2, "invResComp_10.pdf");
  makeSuperImp(sigmaNoGEMI3, sigmaGEMI3, "invResComp_50.pdf");
  makeSuperImp(sigmaNoGEMI4, sigmaGEMI4, "invResComp_100.pdf");
  makeSuperImp(sigmaNoGEMI5, sigmaGEMI5, "invResComp_200.pdf");
  makeSuperImp(sigmaNoGEMI6, sigmaGEMI6, "invResComp_500.pdf");
  makeSuperImp(sigmaNoGEMI7, sigmaGEMI7, "invResComp_800.pdf");
  makeSuperImp(sigmaNoGEMI8, sigmaGEMI8, "invResComp_1000.pdf");
  makeSuperImp(sigmaNoGEMI9, sigmaGEMI9, "invResComp_2000.pdf");

  TCanvas * canvasFit3 = new TCanvas("canvasFit3","canvas",700,700);
  gStyle->SetOptStat(0);
  canvasFit3->Divide(1,2);
  canvasFit3->cd(1);
  TH1D * PtResVsPt_NoGEM_Sigma2 = (TH1D*)PtResVsPt_NoGEM_Sigma->Clone();
  PtResVsPt_NoGEM_Sigma2->SetMaximum(7.00);
  PtResVsPt_NoGEM_Sigma2->SetBinContent(2,sigmaNoGEM1.sigma);
  PtResVsPt_NoGEM_Sigma2->SetBinError(2,sigmaNoGEM1.DeltaSigma);
  PtResVsPt_NoGEM_Sigma2->SetBinContent(3,sigmaNoGEM2.sigma);
  PtResVsPt_NoGEM_Sigma2->SetBinError(3,sigmaNoGEM2.DeltaSigma);
  PtResVsPt_NoGEM_Sigma2->SetBinContent(11,sigmaNoGEM3.sigma);
  PtResVsPt_NoGEM_Sigma2->SetBinError(11,sigmaNoGEM3.DeltaSigma);
  PtResVsPt_NoGEM_Sigma2->SetBinContent(21,sigmaNoGEM4.sigma);
  PtResVsPt_NoGEM_Sigma2->SetBinError(21,sigmaNoGEM4.DeltaSigma);
  PtResVsPt_NoGEM_Sigma2->SetBinContent(41,sigmaNoGEM5.sigma);
  PtResVsPt_NoGEM_Sigma2->SetBinError(41,sigmaNoGEM5.DeltaSigma);
  PtResVsPt_NoGEM_Sigma2->SetBinContent(101,sigmaNoGEM6.sigma);
  PtResVsPt_NoGEM_Sigma2->SetBinError(101,sigmaNoGEM6.DeltaSigma);
  PtResVsPt_NoGEM_Sigma2->SetBinContent(161,sigmaNoGEM7.sigma);
  PtResVsPt_NoGEM_Sigma2->SetBinError(161,sigmaNoGEM7.DeltaSigma);
  PtResVsPt_NoGEM_Sigma2->SetBinContent(201,sigmaNoGEM8.sigma);
  PtResVsPt_NoGEM_Sigma2->SetBinError(201,sigmaNoGEM8.DeltaSigma);
  PtResVsPt_NoGEM_Sigma2->SetBinContent(401,sigmaNoGEM9.sigma);
  PtResVsPt_NoGEM_Sigma2->SetBinError(401,sigmaNoGEM9.DeltaSigma);
  PtResVsPt_NoGEM_Sigma2->Draw("E1P");
  TH1D * PtResVsPt_GEM_Sigma2 = (TH1D*)PtResVsPt_GEM_Sigma->Clone();
  PtResVsPt_GEM_Sigma2->SetBinContent(2,sigmaGEM1.sigma);
  PtResVsPt_GEM_Sigma2->SetBinError(2,sigmaGEM1.DeltaSigma);
  PtResVsPt_GEM_Sigma2->SetBinContent(3,sigmaGEM2.sigma);
  PtResVsPt_GEM_Sigma2->SetBinError(3,sigmaGEM2.DeltaSigma);
  PtResVsPt_GEM_Sigma2->SetBinContent(11,sigmaGEM3.sigma);
  PtResVsPt_GEM_Sigma2->SetBinError(11,sigmaGEM3.DeltaSigma);
  PtResVsPt_GEM_Sigma2->SetBinContent(21,sigmaGEM4.sigma);
  PtResVsPt_GEM_Sigma2->SetBinError(21,sigmaGEM4.DeltaSigma);
  PtResVsPt_GEM_Sigma2->SetBinContent(41,sigmaGEM5.sigma);
  PtResVsPt_GEM_Sigma2->SetBinError(41,sigmaGEM5.DeltaSigma);
  PtResVsPt_GEM_Sigma2->SetBinContent(101,sigmaGEM6.sigma);
  PtResVsPt_GEM_Sigma2->SetBinError(101,sigmaGEM6.DeltaSigma);
  PtResVsPt_GEM_Sigma2->SetBinContent(161,sigmaGEM7.sigma);
  PtResVsPt_GEM_Sigma2->SetBinError(161,sigmaGEM7.DeltaSigma);
  PtResVsPt_GEM_Sigma2->SetBinContent(201,sigmaGEM8.sigma);
  PtResVsPt_GEM_Sigma2->SetBinError(201,sigmaGEM8.DeltaSigma);
  PtResVsPt_GEM_Sigma2->SetBinContent(401,sigmaGEM9.sigma);
  PtResVsPt_GEM_Sigma2->SetBinError(401,sigmaGEM9.DeltaSigma);
  PtResVsPt_GEM_Sigma2->Draw("E1PSAME");
  leg4->Draw();
  canvasFit3->cd(2);
  TH1D * ratioComp3 = makeRatio2(PtResVsPt_NoGEM_Sigma2, PtResVsPt_GEM_Sigma2);
  ratioComp3->SetMarkerColor(1);
  ratioComp3->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  ratioComp3->GetYaxis()->SetTitle("#sigma_{Res}^{GEM} / #sigma_{Res}^{NoGEM}");
  ratioComp3->Draw("E1P");
  
  canvasFit3->SaveAs("comparisonRange_res.pdf");

  canvasFit3->Clear();
  canvasFit3->Update();

  canvasFit3->Divide(1,2);
  TPad * pCore1 = canvasFit3->cd(1);
  pCore1->SetLogx();
  pCore1->SetLogy();
  TH1D * InvPtResVsPt_NoGEM_Sigma2 = (TH1D*)InvPtResVsPt_NoGEM_Sigma->Clone();
  InvPtResVsPt_NoGEM_Sigma2->GetXaxis()->SetRangeUser(2.5,2300);
  InvPtResVsPt_NoGEM_Sigma2->SetMaximum(10.00);
  InvPtResVsPt_NoGEM_Sigma2->SetMinimum(0.05);
  InvPtResVsPt_NoGEM_Sigma2->SetBinContent(2,sigmaNoGEMI1.sigma);
  InvPtResVsPt_NoGEM_Sigma2->SetBinError(2,sigmaNoGEMI1.DeltaSigma);
  InvPtResVsPt_NoGEM_Sigma2->SetBinContent(3,sigmaNoGEMI2.sigma);
  InvPtResVsPt_NoGEM_Sigma2->SetBinError(3,sigmaNoGEMI2.DeltaSigma);
  InvPtResVsPt_NoGEM_Sigma2->SetBinContent(11,sigmaNoGEMI3.sigma);
  InvPtResVsPt_NoGEM_Sigma2->SetBinError(11,sigmaNoGEMI3.DeltaSigma);
  InvPtResVsPt_NoGEM_Sigma2->SetBinContent(21,sigmaNoGEMI4.sigma);
  InvPtResVsPt_NoGEM_Sigma2->SetBinError(21,sigmaNoGEMI4.DeltaSigma);
  InvPtResVsPt_NoGEM_Sigma2->SetBinContent(41,sigmaNoGEMI5.sigma);
  InvPtResVsPt_NoGEM_Sigma2->SetBinError(41,sigmaNoGEMI5.DeltaSigma);
  InvPtResVsPt_NoGEM_Sigma2->SetBinContent(101,sigmaNoGEMI6.sigma);
  InvPtResVsPt_NoGEM_Sigma2->SetBinError(101,sigmaNoGEMI6.DeltaSigma);
  InvPtResVsPt_NoGEM_Sigma2->SetBinContent(161,sigmaNoGEMI7.sigma);
  InvPtResVsPt_NoGEM_Sigma2->SetBinError(161,sigmaNoGEMI7.DeltaSigma);
  InvPtResVsPt_NoGEM_Sigma2->SetBinContent(201,sigmaNoGEMI8.sigma);
  InvPtResVsPt_NoGEM_Sigma2->SetBinError(201,sigmaNoGEMI8.DeltaSigma);
  InvPtResVsPt_NoGEM_Sigma2->SetBinContent(401,sigmaNoGEMI9.sigma);
  InvPtResVsPt_NoGEM_Sigma2->SetBinError(401,sigmaNoGEMI9.DeltaSigma);
  InvPtResVsPt_NoGEM_Sigma2->Draw("E1P");
  TH1D * InvPtResVsPt_GEM_Sigma2 = (TH1D*)InvPtResVsPt_GEM_Sigma->Clone();
  InvPtResVsPt_GEM_Sigma2->SetBinContent(2,sigmaGEMI1.sigma);
  InvPtResVsPt_GEM_Sigma2->SetBinError(2,sigmaGEMI1.DeltaSigma);
  InvPtResVsPt_GEM_Sigma2->SetBinContent(3,sigmaGEMI2.sigma);
  InvPtResVsPt_GEM_Sigma2->SetBinError(3,sigmaGEMI2.DeltaSigma);
  InvPtResVsPt_GEM_Sigma2->SetBinContent(11,sigmaGEMI3.sigma);
  InvPtResVsPt_GEM_Sigma2->SetBinError(11,sigmaGEMI3.DeltaSigma);
  InvPtResVsPt_GEM_Sigma2->SetBinContent(21,sigmaGEMI4.sigma);
  InvPtResVsPt_GEM_Sigma2->SetBinError(21,sigmaGEMI4.DeltaSigma);
  InvPtResVsPt_GEM_Sigma2->SetBinContent(41,sigmaGEMI5.sigma);
  InvPtResVsPt_GEM_Sigma2->SetBinError(41,sigmaGEMI5.DeltaSigma);
  InvPtResVsPt_GEM_Sigma2->SetBinContent(101,sigmaGEMI6.sigma);
  InvPtResVsPt_GEM_Sigma2->SetBinError(101,sigmaGEMI6.DeltaSigma);
  InvPtResVsPt_GEM_Sigma2->SetBinContent(161,sigmaGEMI7.sigma);
  InvPtResVsPt_GEM_Sigma2->SetBinError(161,sigmaGEMI7.DeltaSigma);
  InvPtResVsPt_GEM_Sigma2->SetBinContent(201,sigmaGEMI8.sigma);
  InvPtResVsPt_GEM_Sigma2->SetBinError(201,sigmaGEMI8.DeltaSigma);
  InvPtResVsPt_GEM_Sigma2->SetBinContent(401,sigmaGEMI9.sigma);
  InvPtResVsPt_GEM_Sigma2->SetBinError(401,sigmaGEMI9.DeltaSigma);
  InvPtResVsPt_GEM_Sigma2->Draw("E1PSAME");
  leg4->Draw();
  TPad * pCore2 = canvasFit3->cd(2);
  pCore2->SetLogx();
  TH1D * ratioComp4 = makeRatio2(InvPtResVsPt_NoGEM_Sigma2, InvPtResVsPt_GEM_Sigma2);
  ratioComp4->SetMarkerColor(1);
  ratioComp4->GetXaxis()->SetRangeUser(2.5,2300);
  ratioComp4->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  ratioComp4->GetYaxis()->SetTitle("#sigma_{InvRes}^{staMuonGEM} / #sigma_{InvRes}^{staMuonNoGEM}");
  ratioComp4->Draw("E1PTEXT");

  canvasFit3->SaveAs("comparisonRange_invres.pdf");

  canvasFit3->Clear();
  canvasFit3->Update();

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////

  vdouble vecRes5GeV = composeHistos(sigmaNoGEM1, sigmaGEM1, "Res_5GeV");
  vdouble vecRes10GeV = composeHistos(sigmaNoGEM2, sigmaGEM2, "Res_10GeV");
  vdouble vecRes50GeV = composeHistos(sigmaNoGEM3, sigmaGEM3, "Res_50GeV");
  vdouble vecRes100GeV = composeHistos(sigmaNoGEM4, sigmaGEM4, "Res_100GeV");
  vdouble vecRes200GeV = composeHistos(sigmaNoGEM5, sigmaGEM5, "Res_200GeV");
  vdouble vecRes500GeV = composeHistos(sigmaNoGEM6, sigmaGEM6, "Res_500GeV");
  vdouble vecRes800GeV = composeHistos(sigmaNoGEM7, sigmaGEM7, "Res_800GeV");
  vdouble vecRes1000GeV = composeHistos(sigmaNoGEM8, sigmaGEM8, "Res_1000GeV");
  vdouble vecRes2000GeV = composeHistos(sigmaNoGEM9, sigmaGEM9, "Res_2000GeV");

  vdouble vecInvRes5GeV = composeHistos(sigmaNoGEMI1, sigmaGEMI1, "InvRes_5GeV");
  vdouble vecInvRes10GeV = composeHistos(sigmaNoGEMI2, sigmaGEMI2, "InvRes_10GeV");
  vdouble vecInvRes50GeV = composeHistos(sigmaNoGEMI3, sigmaGEMI3, "InvRes_50GeV");
  vdouble vecInvRes100GeV = composeHistos(sigmaNoGEMI4, sigmaGEMI4, "InvRes_100GeV");
  vdouble vecInvRes200GeV = composeHistos(sigmaNoGEMI5, sigmaGEMI5, "InvRes_200GeV");
  vdouble vecInvRes500GeV = composeHistos(sigmaNoGEMI6, sigmaGEMI6, "InvRes_500GeV");
  vdouble vecInvRes800GeV = composeHistos(sigmaNoGEMI7, sigmaGEMI7, "InvRes_800GeV");
  vdouble vecInvRes1000GeV = composeHistos(sigmaNoGEMI8, sigmaGEMI8, "InvRes_1000GeV");
  vdouble vecInvRes2000GeV = composeHistos(sigmaNoGEMI9, sigmaGEMI9, "InvRes_2000GeV");

  TCanvas * canvasFit4 = new TCanvas("canvasFit4","canvas",700,700);
  gStyle->SetOptStat(0);
  canvasFit4->Divide(1,2);
  canvasFit4->cd(1);
  TH1D * PtResVsPt_NoGEM_Sigma3 = (TH1D*)PtResVsPt_NoGEM_Sigma->Clone();
  PtResVsPt_NoGEM_Sigma3->SetMaximum(7.00);
  PtResVsPt_NoGEM_Sigma3->SetBinContent(2,vecRes5GeV[0]);
  PtResVsPt_NoGEM_Sigma3->SetBinError(2,vecRes5GeV[1]);
  PtResVsPt_NoGEM_Sigma3->SetBinContent(3,vecRes10GeV[0]);
  PtResVsPt_NoGEM_Sigma3->SetBinError(3,vecRes10GeV[1]);
  PtResVsPt_NoGEM_Sigma3->SetBinContent(11,vecRes50GeV[0]);
  PtResVsPt_NoGEM_Sigma3->SetBinError(11,vecRes50GeV[1]);
  PtResVsPt_NoGEM_Sigma3->SetBinContent(21,vecRes100GeV[0]);
  PtResVsPt_NoGEM_Sigma3->SetBinError(21,vecRes100GeV[1]);
  PtResVsPt_NoGEM_Sigma3->SetBinContent(41,vecRes200GeV[0]);
  PtResVsPt_NoGEM_Sigma3->SetBinError(41,vecRes200GeV[1]);
  PtResVsPt_NoGEM_Sigma3->SetBinContent(101,vecRes500GeV[0]);
  PtResVsPt_NoGEM_Sigma3->SetBinError(101,vecRes500GeV[1]);
  PtResVsPt_NoGEM_Sigma3->SetBinContent(161,vecRes800GeV[0]);
  PtResVsPt_NoGEM_Sigma3->SetBinError(161,vecRes800GeV[1]);
  PtResVsPt_NoGEM_Sigma3->SetBinContent(201,vecRes1000GeV[0]);
  PtResVsPt_NoGEM_Sigma3->SetBinError(201,vecRes1000GeV[1]);
  PtResVsPt_NoGEM_Sigma3->SetBinContent(401,vecRes2000GeV[0]);
  PtResVsPt_NoGEM_Sigma3->SetBinError(401,vecRes2000GeV[1]);
  PtResVsPt_NoGEM_Sigma3->Draw("E1P");
  TH1D * PtResVsPt_GEM_Sigma3 = (TH1D*)PtResVsPt_GEM_Sigma->Clone();
  PtResVsPt_GEM_Sigma3->SetBinContent(2,vecRes5GeV[2]);
  PtResVsPt_GEM_Sigma3->SetBinError(2,vecRes5GeV[3]);
  PtResVsPt_GEM_Sigma3->SetBinContent(3,vecRes10GeV[2]);
  PtResVsPt_GEM_Sigma3->SetBinError(3,vecRes10GeV[3]);
  PtResVsPt_GEM_Sigma3->SetBinContent(11,vecRes50GeV[2]);
  PtResVsPt_GEM_Sigma3->SetBinError(11,vecRes50GeV[3]);
  PtResVsPt_GEM_Sigma3->SetBinContent(21,vecRes100GeV[2]);
  PtResVsPt_GEM_Sigma3->SetBinError(21,vecRes100GeV[3]);
  PtResVsPt_GEM_Sigma3->SetBinContent(41,vecRes200GeV[2]);
  PtResVsPt_GEM_Sigma3->SetBinError(41,vecRes200GeV[3]);
  PtResVsPt_GEM_Sigma3->SetBinContent(101,vecRes500GeV[2]);
  PtResVsPt_GEM_Sigma3->SetBinError(101,vecRes500GeV[3]);
  PtResVsPt_GEM_Sigma3->SetBinContent(161,vecRes800GeV[2]);
  PtResVsPt_GEM_Sigma3->SetBinError(161,vecRes800GeV[3]);
  PtResVsPt_GEM_Sigma3->SetBinContent(201,vecRes1000GeV[2]);
  PtResVsPt_GEM_Sigma3->SetBinError(201,vecRes1000GeV[3]);
  PtResVsPt_GEM_Sigma3->SetBinContent(401,vecRes2000GeV[2]);
  PtResVsPt_GEM_Sigma3->SetBinError(401,vecRes2000GeV[3]);
  PtResVsPt_GEM_Sigma3->Draw("E1PSAME");
  leg4->Draw();
  canvasFit4->cd(2);
  TH1D * ratioComp5 = makeRatio2(PtResVsPt_NoGEM_Sigma3, PtResVsPt_GEM_Sigma3);
  ratioComp5->SetMarkerColor(1);
  ratioComp5->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  ratioComp5->GetYaxis()->SetTitle("#sigma_{Res}^{GEM} / #sigma_{Res}^{NoGEM}");
  ratioComp5->Draw("E1P");
  canvasFit4->SaveAs("comparisonMinRange_res.pdf");

  canvasFit4->Clear();
  canvasFit4->Update();

  canvasFit4->Divide(1,2);
  canvasFit4->cd(1);
  TH1D * InvPtResVsPt_NoGEM_Sigma3 = (TH1D*)InvPtResVsPt_NoGEM_Sigma->Clone();
  InvPtResVsPt_NoGEM_Sigma3->SetMaximum(7.00);
  InvPtResVsPt_NoGEM_Sigma3->SetBinContent(2,vecInvRes5GeV[0]);
  InvPtResVsPt_NoGEM_Sigma3->SetBinError(2,vecInvRes5GeV[1]);
  InvPtResVsPt_NoGEM_Sigma3->SetBinContent(3,vecInvRes10GeV[0]);
  InvPtResVsPt_NoGEM_Sigma3->SetBinError(3,vecInvRes10GeV[1]);
  InvPtResVsPt_NoGEM_Sigma3->SetBinContent(11,vecInvRes50GeV[0]);
  InvPtResVsPt_NoGEM_Sigma3->SetBinError(11,vecInvRes50GeV[1]);
  InvPtResVsPt_NoGEM_Sigma3->SetBinContent(21,vecInvRes100GeV[0]);
  InvPtResVsPt_NoGEM_Sigma3->SetBinError(21,vecInvRes100GeV[1]);
  InvPtResVsPt_NoGEM_Sigma3->SetBinContent(41,vecInvRes200GeV[0]);
  InvPtResVsPt_NoGEM_Sigma3->SetBinError(41,vecInvRes200GeV[1]);
  InvPtResVsPt_NoGEM_Sigma3->SetBinContent(101,vecInvRes500GeV[0]);
  InvPtResVsPt_NoGEM_Sigma3->SetBinError(101,vecInvRes500GeV[1]);
  InvPtResVsPt_NoGEM_Sigma3->SetBinContent(161,vecInvRes800GeV[0]);
  InvPtResVsPt_NoGEM_Sigma3->SetBinError(161,vecInvRes800GeV[1]);
  InvPtResVsPt_NoGEM_Sigma3->SetBinContent(201,vecInvRes1000GeV[0]);
  InvPtResVsPt_NoGEM_Sigma3->SetBinError(201,vecInvRes1000GeV[1]);
  InvPtResVsPt_NoGEM_Sigma3->SetBinContent(401,vecInvRes2000GeV[0]);
  InvPtResVsPt_NoGEM_Sigma3->SetBinError(401,vecInvRes2000GeV[1]);
  InvPtResVsPt_NoGEM_Sigma3->Draw("E1P");
  TH1D * InvPtResVsPt_GEM_Sigma3 = (TH1D*)InvPtResVsPt_GEM_Sigma->Clone();
  InvPtResVsPt_GEM_Sigma3->SetBinContent(2,vecInvRes5GeV[2]);
  InvPtResVsPt_GEM_Sigma3->SetBinError(2,vecInvRes5GeV[3]);
  InvPtResVsPt_GEM_Sigma3->SetBinContent(3,vecInvRes10GeV[2]);
  InvPtResVsPt_GEM_Sigma3->SetBinError(3,vecInvRes10GeV[3]);
  InvPtResVsPt_GEM_Sigma3->SetBinContent(11,vecInvRes50GeV[2]);
  InvPtResVsPt_GEM_Sigma3->SetBinError(11,vecInvRes50GeV[3]);
  InvPtResVsPt_GEM_Sigma3->SetBinContent(21,vecInvRes100GeV[2]);
  InvPtResVsPt_GEM_Sigma3->SetBinError(21,vecInvRes100GeV[3]);
  InvPtResVsPt_GEM_Sigma3->SetBinContent(41,vecInvRes200GeV[2]);
  InvPtResVsPt_GEM_Sigma3->SetBinError(41,vecInvRes200GeV[3]);
  InvPtResVsPt_GEM_Sigma3->SetBinContent(101,vecInvRes500GeV[2]);
  InvPtResVsPt_GEM_Sigma3->SetBinError(101,vecInvRes500GeV[3]);
  InvPtResVsPt_GEM_Sigma3->SetBinContent(161,vecInvRes800GeV[2]);
  InvPtResVsPt_GEM_Sigma3->SetBinError(161,vecInvRes800GeV[3]);
  InvPtResVsPt_GEM_Sigma3->SetBinContent(201,vecInvRes1000GeV[2]);
  InvPtResVsPt_GEM_Sigma3->SetBinError(201,vecInvRes1000GeV[3]);
  InvPtResVsPt_GEM_Sigma3->SetBinContent(401,vecInvRes2000GeV[2]);
  InvPtResVsPt_GEM_Sigma3->SetBinError(401,vecInvRes2000GeV[3]);
  InvPtResVsPt_GEM_Sigma3->Draw("E1PSAME");
  leg4->Draw();
  canvasFit4->cd(2);
  TH1D * ratioComp6 = makeRatio2(InvPtResVsPt_NoGEM_Sigma3, InvPtResVsPt_GEM_Sigma3);
  ratioComp6->SetMarkerColor(1);
  ratioComp6->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
  ratioComp6->GetYaxis()->SetTitle("#sigma_{InvRes}^{GEM} / #sigma_{InvRes}^{NoGEM}");
  ratioComp6->Draw("E1P");

  canvasFit4->SaveAs("comparisonMinRange_invres.pdf");

}
