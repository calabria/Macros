#include <vector>
#include <fstream>
#include <sstream>
#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"
#include "TPaveStats.h"
#include "TStyle.h"
#include "TEfficiency.h"

#include "TStyle.h"

TH1F * makeRatio2(TH1F * plot1, TH1F * plot2, float a1 = 0, float a2 = 2){

	TH1F * plotTMP = (TH1F*)plot2->Clone();
	plotTMP->SetStats(kFALSE);
	plotTMP->SetLineColor(1);
  	plotTMP->SetMaximum(a2);
  	plotTMP->SetMinimum(a1);
	plotTMP->Divide(plot1);
	return plotTMP;

}

void extractPerformance(TH1F * histo1, TH1F * histo2, std::string name, std::string range){

	//denominator numerator

	TH1F * plotTMP = (TH1F*)histo2->Clone();
	plotTMP->Divide(histo1);

	cout<<"Range: "<<range.c_str()<<endl;

	for(int i = 1; i <= plotTMP->GetNbinsX(); i++){

		double etaMin = 0, etaMax = 0;
		double binWidth = plotTMP->GetBinWidth(i);
		double eff1 = histo1->GetBinContent(i);
		double eff2 = histo2->GetBinContent(i);
		double scale = plotTMP->GetBinContent(i);
		etaMin = binWidth*(i-1);
		etaMax = binWidth*i;
		cout<<"|Eta|: "<<etaMin<<"-"<<etaMax<<(" "+name).c_str()<<" NoAge(50): "<<eff1<<" Age(140): "<<eff2<<" ScaleFactor: "<<scale<<endl;

	}

}

//---------------------------------------------------------------------------------------------------------------------------

typedef std::vector<TH1D*> vecHist;

std::vector<TH1D*> projectAndFit(TH2F * Histo2D, std::string postFix = "bin"){

	std::vector<TH1D*> vec;

	for(int i = 1; i <= Histo2D->GetNbinsX(); i++){

		std::stringstream ss;
		ss<<postFix.c_str()<<i;	
		std::string pf = ss.str();

		TH1D * proj1 = Histo2D->ProjectionY(pf.c_str(),i,i);
		if(proj1->GetEntries() == 0) continue;

		//size_t found1 = postFix.find("200GeV");
		//size_t found2 = postFix.find("500GeV");
		//size_t found3 = postFix.find("1000GeV");

		vec.push_back(proj1);

	}

	return vec;

}

TH1F * produceYield(TH1F * h1, TH1F * h2, int num){

	h1->Sumw2();
	h2->Sumw2();
	TH1F * hTemp = (TH1F*)h1->Clone();
	hTemp->Reset();

	for(int i = 1; i < hTemp->GetSize(); i++){

		float diff = (h1->GetBinContent(i) - h2->GetBinContent(i));
		float div = diff/(float)num;
		float err = sqrt(diff)/(float)num;
		hTemp->SetBinContent(i, div);
		hTemp->SetBinError(i, err);

		//std::cout<<diff<<" "<<err<<std::endl;

	}
 
	return hTemp;

}

void makeSuperImp(vecHist p1, vecHist p2, vecHist p3, std::string name){

	gStyle->SetOptStat(112200);
	//gStyle->SetOptFit(12);

	TCanvas * canvasTMP = new TCanvas("canvasTMP","canvas",700,700);
	canvasTMP->SetLogy();

	for(int i = 0; i<(int)p1.size(); i++){

		std::string bin = "_bin";
		std::stringstream ss;
	  	ss<<bin.c_str()<<i;	
		std::string pf = ss.str();

		TH1D * tmp1 = p1[i];
		TH1D * tmp2 = p2[i];
		TH1D * tmp3 = p3[i];

		tmp1->Rebin(10);
		tmp2->Rebin(10);
		tmp3->Rebin(10);

		tmp1->Scale(1/tmp1->GetEntries());
		tmp2->Scale(1/tmp2->GetEntries());
		tmp3->Scale(1/tmp3->GetEntries());

		//tmp1->GetXaxis()->SetRangeUser(-1,+1);
		//tmp2->GetXaxis()->SetRangeUser(-1,+1);
		//tmp3->GetXaxis()->SetRangeUser(-1,+1);
		
		tmp1->SetLineWidth(2);
		tmp2->SetLineWidth(2);
		tmp3->SetLineWidth(2);

		tmp1->SetMaximum(1.0);
	 	tmp1->SetLineColor(9);
		tmp1->SetTitle("");
		tmp1->GetXaxis()->SetTitle("q/p_{T}");
		tmp1->GetYaxis()->SetTitle("entries");
		tmp1->Draw("HIST");

	 	tmp2->SetLineColor(2);
		tmp2->Draw("HISTSAMES");
	 	tmp3->SetLineColor(kGreen-3);
		//tmp3->SetLineStyle(2);
		tmp3->Draw("HISTSAMES");

		canvasTMP->Update();
		TPaveStats *stats1 = (TPaveStats*)tmp1->GetListOfFunctions()->FindObject("stats");
		stats1->SetX1NDC(0.10);
		stats1->SetX2NDC(0.40);
		stats1->SetY1NDC(0.80);
		stats1->SetY2NDC(0.95);
   		stats1->SetFillColor(9);
		canvasTMP->Update();
		TPaveStats *stats2 = (TPaveStats*)tmp2->GetListOfFunctions()->FindObject("stats");
		stats2->SetX1NDC(0.60);
		stats2->SetX2NDC(0.90);
		stats2->SetY1NDC(0.80);
		stats2->SetY2NDC(0.95);
   		stats2->SetFillColor(2);
		canvasTMP->Update();
		TPaveStats *stats3 = (TPaveStats*)tmp3->GetListOfFunctions()->FindObject("stats");
		stats3->SetX1NDC(0.10);
		stats3->SetX2NDC(0.40);
		stats3->SetY1NDC(0.60);
		stats3->SetY2NDC(0.75);
   		stats3->SetFillColor(kGreen-3);

		canvasTMP->SaveAs((name+pf+".png").c_str());

	}

}

void setLeg(TLegend * leg, string header = ""){

	leg->SetFillColor(0);
	leg->SetFillStyle(0);
	leg->SetLineColor(0);
	leg->SetBorderSize(0); 
	leg->SetHeader(header.c_str());
   	leg->SetTextSize(0.03);

}

void changeOffsetY(TAxis * yaxis){

  yaxis->SetTitleOffset(1.5);

}

void changeAxis(TAxis * yaxis, double offSet = 1.5, double offSetLabels = 0.006, double titleSize = 0.035){

// For the axis titles:

  yaxis->SetTitleColor(1);
  yaxis->SetTitleFont(42);
  yaxis->SetTitleSize(titleSize);
  yaxis->SetTitleOffset(offSet);
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);
  // yaxis->SetTitleXOffset(0.9);
  // yaxis->SetTitleYOffset(1.25);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

// For the axis labels:

  yaxis->SetLabelColor(1);
  yaxis->SetLabelFont(42);
  yaxis->SetLabelOffset(offSetLabels);
  yaxis->SetLabelSize(0.035);

// For the axis:

  yaxis->SetAxisColor(1);
  //yaxis->SetStripDecimals(kTRUE);
  yaxis->SetTickLength(0.03);
  yaxis->SetNdivisions(510);
  //yaxis->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  //yaxis->SetPadTickY(1);

}

void setMarkerStyle(TH1F * histo, int color, int style){

	histo->SetMarkerColor(color);
	histo->SetLineColor(color);
	histo->SetLineWidth(2);
	histo->SetMarkerStyle(style);
	histo->SetMarkerSize(1.5);

}

void setMarkerStyle(TEfficiency * histo, int color, int style){

	histo->SetMarkerColor(color);
	histo->SetLineColor(color);
	histo->SetLineWidth(2);
	histo->SetMarkerStyle(style);
	histo->SetMarkerSize(1.5);

}

void setMarkerStyle2(TH1F * histo, Color_t color, int style){

	histo->SetMarkerColor(color);
	histo->SetLineColor(color);
	histo->SetLineWidth(2);
	histo->SetMarkerStyle(style);
	histo->SetMarkerSize(1.5);

}

void setMarkerStyle2(TEfficiency * histo, Color_t color, int style){

	histo->SetMarkerColor(color);
	histo->SetLineColor(color);
	histo->SetLineWidth(2);
	histo->SetMarkerStyle(style);
	histo->SetMarkerSize(1.5);

}

void saveAll(TCanvas * canvas, string name, string type){

	canvas->SaveAs((type + "/" + name + ".png").c_str());
	canvas->SaveAs((type + "/" + name + ".pdf").c_str());

}

TEfficiency * calcEff(TH1F* num, TH1F* den, bool remove = false){

	if(remove){
		removeBin(num, 9);
		removeBin(num, 20);
	}

  	/*for (int i = 1; i < den->GetNbinsX()+1; i++){

		const double errLo = TEfficiency::FeldmanCousins((int)den->GetBinContent(i), 
							       (int)num->GetBinContent(i),
							       0.683,false);
		const double errUp = TEfficiency::FeldmanCousins((int)den->GetBinContent(i), 
							       (int)num->GetBinContent(i),
							       0.683,true);

		std::cout<<" "<<errLo<<" "<<errUp<<std::endl;

	}*/

        TEfficiency* effTMP = 0;
        if(TEfficiency::CheckConsistency(*num,*den))
        {
            	effTMP = new TEfficiency(*num,*den);
		//effTMP->SetStatisticOption(TEfficiency::kFFC);
		//effTMP->SetConfidenceLevel(0.683);
        }

	return effTMP;

}

void removeBin(TH1F * histo, int bin){

	histo->SetBinContent(bin, 0);
	histo->SetBinError(bin, 0);

}

void makeDiff(std::vector<TH1F*> genericVector, std::vector<TH1F*> genericVector2){

	for(int i = 0; i < genericVector.size(); i++){

		//std::cout<<genericVector[i]->GetBinContent(10)<<std::endl;
		genericVector[i]->Add(genericVector2[i], -1);
		//std::cout<<genericVector[i]->GetBinContent(10)<<std::endl;

	}

}

std::vector<TH1F*> makeMismatch(std::vector<TH1F*> genericVector, std::vector<TH1F*> genericVector2){

	//loose tight
	
	std::vector<TH1F*> tmpVec;

	for(int i = 0; i < genericVector.size(); i++){//loop sugli istogrammi

		TH1F * tmp = (TH1F*)genericVector[i]->Clone();
		tmp->Reset();

		for(int j = 1; j < genericVector[i]->GetSize(); j++){

			float bin1 = genericVector[i]->GetBinContent(j);
			float bin2 = genericVector2[i]->GetBinContent(j);

			float ratio = 0;
			float err = 0;
			if(bin1 > 0) {

				ratio = (bin1-bin2)/bin1;
				err = sqrt(bin1*ratio*(1-ratio))/bin1;

			}

			//std::cout<<bin1<<" "<<bin2<<" "<<ratio<<" "<<err<<std::endl;

			tmp->SetBinContent(j, ratio);
			tmp->SetBinError(j, err);

		}

		tmpVec.push_back(tmp);

	}

	//std::cout<<tmpVec.size()<<std::endl;
	return tmpVec;

}

std::vector<TH1F*> sumHistos(std::vector<TH1F*> v1, std::vector<TH1F*> v2, std::vector<TH1F*> v3, std::vector<TH1F*> v4){
	
	std::vector<TH1F*> tmpVec;

	for(int i = 0; i < v1.size(); i++){

		TH1F * tmp = (TH1F*)v1[i]->Clone();
		tmp->Sumw2();
		v1[i]->Sumw2();
		v2[i]->Sumw2();
		v3[i]->Sumw2();
		v4[i]->Sumw2();
		tmp->Add(v2[i]);
		tmp->Add(v3[i]);
		tmp->Add(v4[i]);
		tmpVec.push_back(tmp);

		//std::cout<<v1[i]->GetBinContent(1)<<" "<<v2[i]->GetBinContent(1)<<" "<<v3[i]->GetBinContent(1)<<" "<<v4[i]->GetBinContent(1)<<" "<<tmp->GetBinContent(1)<<std::endl;

	}

	return tmpVec;

}

void setEverything(std::vector<TH1F*> genericVector, double min, double max, bool log, double x1, double y1, double x2, double y2, std::string name3, std::string type, std::string title, std::string save){

		std::vector<int> markers;
		markers.push_back(20);
		markers.push_back(21);
		markers.push_back(22);
		markers.push_back(23);
		markers.push_back(34);
		markers.push_back(24);
		markers.push_back(26);
		markers.push_back(25);

  		gROOT->LoadMacro("tdrstyle.C");
  		setTDRStyle();

  		TPaveText * cmsPreliminaryLabel = new TPaveText(0.13, 0.93, 0.99, 1.02, "NDC");
  		cmsPreliminaryLabel->AddText("CMS PhaseII Simulation                           #sqrt{s} = 14 TeV");
  		cmsPreliminaryLabel->SetTextAlign(12);
  		cmsPreliminaryLabel->SetTextFont(42);
  		cmsPreliminaryLabel->SetTextSize(0.04);
  		cmsPreliminaryLabel->SetFillStyle(0);
  		cmsPreliminaryLabel->SetBorderSize(0);
		float a1 = 0.223, a2 = 0.42, b1 = 0.99, b2 = 0.52; 
		if(save.find("Fakes") != std::string::npos){

			a1 = 0.172;
			a2 = 0.82;
			b1 = 0.99; 
			b2 = 0.92;

		}
  		TPaveText * label = new TPaveText(a1, a2, b1, b2, "NDC");
  		label->AddText("Single Muon p_{T} = 100 GeV");
  		label->SetTextAlign(12);
  		label->SetTextFont(62);
  		label->SetTextSize(0.03);
  		label->SetFillStyle(0);
  		label->SetBorderSize(0);

	  	TLegend *leg2 = new TLegend(x1,y1,x2,y2);
		std::string header = "";
		if(name3 == "Muon10") header = "Muon p_{T} = 10 GeV/c";
		//else if(name3 == "Muon100") header = "Muon p_{T} = 100 GeV/c";
		else if(name3 == "Muon100") header = "Standalone Muon reconstruction";
		else if (name3 == "DY") header = "Z/#gamma* #rightarrow #mu#mu";

		std::string addString2 = "";
		/*if(type.find("MuonLoose") != std::string::npos) addString2 = ", Loose Muon ID";
		else if(type.find("MuonTight") != std::string::npos) addString2 = ", Tight Muon ID";
		else addString2 = "";*/

		std::string addString3 = "";
		if(type.find("5") != std::string::npos) addString3 = ", p_{T}^{#mu} > 5 GeV/c";
		//else if(type.find("10") != std::string::npos) addString3 = ", p_{T}^{#mu} > 10 GeV/c";
		else if(type.find("20") != std::string::npos) addString3 = ", p_{T}^{#mu} > 20 GeV/c";
		else addString3 = "";

  		setLeg(leg2, header+addString2+addString3);

		TCanvas * canvas2 = new TCanvas("canvas2","canvas",700,700);
		//canvas2->Divide(1,2);
		//canvas2->cd(1);
		//gPad->SetGridx();
		//gPad->SetGridy();

		if(log) gPad->SetLogy();
		else gPad->SetLogy(kFALSE);
		changeOffsetY(genericVector[1]->GetYaxis());
		genericVector[1]->SetStats(kFALSE);
		genericVector[1]->SetMinimum(min);
		genericVector[1]->SetMaximum(max);

		double maxScale = genericVector[1]->GetXaxis()->GetXmax();
		cout<<maxScale<<endl;

		if(maxScale == 2.5){

			genericVector[1]->GetXaxis()->SetTitle("Muon |#eta|");
			genericVector[1]->GetXaxis()->SetRange(16,22);
        		//TF1 *myfit = new TF1("myfit","pol0", 1.5, 2.1);
			//genericVector[1]->Fit("myfit","R");

		}
		else if(maxScale == 2500){

			genericVector[1]->GetXaxis()->SetTitle("Muon p_{T} [GeV/c]");
			genericVector[1]->GetXaxis()->SetRangeUser(0,100);

		}
		else if(maxScale == 200){

			genericVector[1]->GetXaxis()->SetTitle("Number of pile-up collisions");
			removeBin(genericVector[0], 9);
			removeBin(genericVector[1], 9);
			removeBin(genericVector[2], 9);
			removeBin(genericVector[3], 9);
			removeBin(genericVector[4], 9);

			removeBin(genericVector[0], 20);
			removeBin(genericVector[1], 20);
			removeBin(genericVector[2], 20);
			removeBin(genericVector[3], 20);
			removeBin(genericVector[4], 20);

		}
		else if(maxScale == 20){

			genericVector[1]->GetXaxis()->SetTitle("#chi^{2}/ndof");
			genericVector[1]->GetXaxis()->SetRangeUser(0,5);

			genericVector[0]->Sumw2();
			genericVector[0]->Scale(1/(float)genericVector[0]->GetEntries());
			genericVector[1]->Sumw2();
			genericVector[1]->Scale(1/(float)genericVector[1]->GetEntries());
			genericVector[2]->Sumw2();
			genericVector[2]->Scale(1/(float)genericVector[2]->GetEntries());
			genericVector[3]->Sumw2();
			genericVector[3]->Scale(1/(float)genericVector[3]->GetEntries());
			genericVector[4]->Sumw2();
			genericVector[4]->Scale(1/(float)genericVector[4]->GetEntries());

			genericVector[1]->SetMinimum(min);
			genericVector[1]->SetMaximum(max);

		}

		genericVector[1]->GetYaxis()->SetTitle(title.c_str());
		genericVector[1]->SetTitle("");
		setMarkerStyle(genericVector[1], 1, markers[5]);
		changeAxis(genericVector[1]->GetXaxis(), 1.0, 0.005, 0.045);
		changeAxis(genericVector[1]->GetYaxis(), 1.0, 0.005, 0.045);
		genericVector[1]->Draw("E1P");
  		cmsPreliminaryLabel->Draw();
		label->Draw();
		//hRMSNoGEM->SetMaximum(hRMSGEM->GetMaximum());
		setMarkerStyle(genericVector[2], 2, markers[1]);
		genericVector[2]->Draw("E1PSAME");

		setMarkerStyle(genericVector[3], 8, markers[2]);
		//genericVector[3]->Draw("E1PSAME");

		setMarkerStyle(genericVector[4], 2, markers[7]);
		genericVector[4]->Draw("E1PSAME");

		setMarkerStyle(genericVector[0], 1, markers[0]);
		genericVector[0]->Draw("E1PSAME");
		leg2->AddEntry(genericVector[0], "PU50, With GE1/1", "p");
		leg2->AddEntry(genericVector[1], "PU50, No GE1/1", "p");
  		leg2->AddEntry(genericVector[2], "PU140, With GE1/1", "p");
  		//leg2->AddEntry(genericVector[3], "2023 (PU140)", "p");
  		leg2->AddEntry(genericVector[4], "PU140, No GE1/1", "p");
		leg2->Draw();

		/*canvas2->cd(2);
  		TH1F * ratioComp1 = makeRatio2(genericVector[1], genericVector[2], 0, 2);
  		ratioComp1->SetMarkerColor(1);
  		ratioComp1->GetXaxis()->SetTitle("|#eta|");
  		ratioComp1->GetYaxis()->SetTitle("chargeMisID^{staMuonsGEM} / chargeMisID^{staMuonsNoGEM}");
  		ratioComp1->Draw("E1P");*/

		saveAll(canvas2,(save + name3).c_str(), type);

}

void setEverything2(std::vector<TEfficiency*> genericVector, double min, double max, bool log, double x1, double y1, double x2, double y2, std::string name3, std::string type, std::string title, std::string save){

		std::vector<int> markers;
		markers.push_back(20);
		markers.push_back(21);
		markers.push_back(22);
		markers.push_back(23);
		markers.push_back(34);
		markers.push_back(24);
		markers.push_back(26);
		markers.push_back(25);

  		gROOT->LoadMacro("tdrstyle.C");
  		setTDRStyle();

  		TPaveText * cmsPreliminaryLabel = new TPaveText(0.13, 0.93, 0.99, 1.02, "NDC");
  		cmsPreliminaryLabel->AddText("CMS PhaseII Simulation                           #sqrt{s} = 14 TeV");
  		cmsPreliminaryLabel->SetTextAlign(12);
  		cmsPreliminaryLabel->SetTextFont(42);
  		cmsPreliminaryLabel->SetTextSize(0.04);
  		cmsPreliminaryLabel->SetFillStyle(0);
  		cmsPreliminaryLabel->SetBorderSize(0);
		float a1 = 0.223, a2 = 0.42, b1 = 0.99, b2 = 0.52; 
		if(save.find("Fakes") != std::string::npos){

			a1 = 0.172;
			a2 = 0.82;
			b1 = 0.99; 
			b2 = 0.92;

		}
  		TPaveText * label = new TPaveText(a1, a2, b1, b2, "NDC");
  		label->AddText("Single Muon p_{T} = 100 GeV");
  		label->SetTextAlign(12);
  		label->SetTextFont(62);
  		label->SetTextSize(0.03);
  		label->SetFillStyle(0);
  		label->SetBorderSize(0);

	  	TLegend *leg2 = new TLegend(x1,y1,x2,y2);
		std::string header = "";
		if(name3 == "Muon10") header = "Muon p_{T} = 10 GeV/c";
		else if(name3 == "Muon100") header = "Muon p_{T} = 100 GeV/c";
		else if (name3 == "DY") header = "Z/#gamma* #rightarrow #mu#mu";

		std::string addString2 = "";
		/*if(type.find("MuonLoose") != std::string::npos) addString2 = ", Loose Muon ID";
		else if(type.find("MuonTight") != std::string::npos) addString2 = ", Tight Muon ID";
		else addString2 = "";*/

		std::string addString3 = "";
		if(type.find("5") != std::string::npos) addString3 = ", p_{T}^{#mu} > 5 GeV/c";
		//else if(type.find("10") != std::string::npos) addString3 = ", p_{T}^{#mu} > 10 GeV/c";
		else if(type.find("20") != std::string::npos) addString3 = ", p_{T}^{#mu} > 20 GeV/c";
		else addString3 = "";

  		setLeg(leg2, header+addString2+addString3);

		TCanvas * canvas3 = new TCanvas("canvas3","canvas",700,700);
		//canvas3->Divide(1,2);
		//canvas3->cd(1);
		//gPad->SetGridx();
		//gPad->SetGridy();

		if(log) gPad->SetLogy();
		else gPad->SetLogy(kFALSE);

		genericVector[1]->Draw("AP");
		gPad->Update();
		changeAxis(genericVector[1]->GetPaintedGraph()->GetXaxis(), 1.0, 0.005);
		changeAxis(genericVector[1]->GetPaintedGraph()->GetYaxis());
		//genericVector[1]->SetStats(kFALSE);
		genericVector[1]->GetPaintedGraph()->SetMinimum(min);
		genericVector[1]->GetPaintedGraph()->SetMaximum(max);

		double maxScale = genericVector[1]->GetPaintedGraph()->GetXaxis()->GetXmax();
		cout<<maxScale<<endl;

		if(maxScale < 3){

			genericVector[1]->GetPaintedGraph()->GetXaxis()->SetTitle("Muon |#eta|");
			genericVector[1]->GetPaintedGraph()->GetXaxis()->SetLimits(1.5,2.2);

		}
		else if(maxScale > 900){

			genericVector[1]->GetPaintedGraph()->GetXaxis()->SetTitle("Muon p_{T} [GeV/c]");
			genericVector[1]->GetPaintedGraph()->GetXaxis()->SetLimits(0,100);

		}
		else if(maxScale == 97){

			genericVector[1]->GetPaintedGraph()->GetXaxis()->SetTitle("Number of pile-up collisions");
			genericVector[1]->GetPaintedGraph()->GetXaxis()->SetLimits(0,200);

		}
		else if(maxScale == 20){

			genericVector[1]->GetXaxis()->SetTitle("#chi^{2}/ndof");
			genericVector[1]->GetXaxis()->SetRangeUser(0,5);

			genericVector[0]->Sumw2();
			genericVector[0]->Scale(1/(float)genericVector[0]->GetEntries());
			genericVector[1]->Sumw2();
			genericVector[1]->Scale(1/(float)genericVector[1]->GetEntries());
			genericVector[2]->Sumw2();
			genericVector[2]->Scale(1/(float)genericVector[2]->GetEntries());
			genericVector[3]->Sumw2();
			genericVector[3]->Scale(1/(float)genericVector[3]->GetEntries());
			genericVector[4]->Sumw2();
			genericVector[4]->Scale(1/(float)genericVector[4]->GetEntries());

		}

		genericVector[1]->GetPaintedGraph()->GetYaxis()->SetTitle(title.c_str());
		genericVector[1]->GetPaintedGraph()->SetTitle("");
		setMarkerStyle(genericVector[1], 1, markers[5]);

  		cmsPreliminaryLabel->Draw();
		label->Draw();
		//hRMSNoGEM->SetMaximum(hRMSGEM->GetMaximum());
		setMarkerStyle(genericVector[2], 2, markers[1]);
		genericVector[2]->Draw("SAME");

		setMarkerStyle(genericVector[3], 8, markers[2]);
		//genericVector[3]->Draw("SAME");

		setMarkerStyle(genericVector[4], 2, markers[7]);
		genericVector[4]->Draw("E1PSAME");

		setMarkerStyle(genericVector[0], 1, markers[0]);
		genericVector[0]->Draw("E1PSAME");
		leg2->AddEntry(genericVector[0], "PU50, With GE1/1", "p");
		leg2->AddEntry(genericVector[1], "PU50, No GE1/1", "p");
  		leg2->AddEntry(genericVector[2], "PU140, With GE1/1", "p");
  		//leg2->AddEntry(genericVector[3], "2023 (PU140)", "p");
  		leg2->AddEntry(genericVector[4], "PU140, No GE1/1", "p");
		leg2->Draw();

		/*canvas3->cd(2);
  		TH1F * ratioComp1 = makeRatio2(genericVector[1], genericVector[2], 0, 2);
  		ratioComp1->SetMarkerColor(1);
  		ratioComp1->GetXaxis()->SetTitle("|#eta|");
  		ratioComp1->GetYaxis()->SetTitle("chargeMisID^{staMuonsGEM} / chargeMisID^{staMuonsNoGEM}");
  		ratioComp1->Draw("E1P");*/

		saveAll(canvas3,(save + name3).c_str(), type);

}

//---------------------------------------------------------------------------------------------------------------------------

void makePlots(std::vector<std::string> allNames, std::string name3){

  std::vector<TH1F*> chargeMisIDProb_vs_eta;
  std::vector<TH1F*> effic_vs_eta;
  std::vector<TH1F*> effic_vs_eta_050;
  std::vector<TH1F*> effic_vs_eta_050_pt10;
  std::vector<TH1F*> effic_vs_vtx;
  std::vector<TH1F*> effic_vs_vtxB;
  std::vector<TH1F*> effic_vs_vtxO;
  std::vector<TH1F*> effic_vs_vtxE;
  std::vector<TH1F*> efficFakes_vs_eta;
  std::vector<TH1F*> efficFakes_vs_eta_050;
  std::vector<TH1F*> efficFakes_vs_eta_050_pt10;
  std::vector<TH1F*> chi2;

  std::vector<TH1F*> quality_vs_eta;

  std::vector<TH1F*> efficFakes1_vs_eta;
  std::vector<TH1F*> efficFakes2_vs_eta;
  std::vector<TH1F*> efficFakes3_vs_eta;
  std::vector<TH1F*> efficFakes4_vs_eta;

  std::vector<TH1F*> qOverPtRes_vs_eta;
  std::vector<TH1F*> qOverPtResRMS_vs_eta;
  std::vector<TH1F*> numRecoPt_vs_eta;
  std::vector<TH1F*> numRecoPtAsso_vs_eta;
  std::vector<TH1F*> yield_vs_eta;
  std::vector<TH1F*> yield_vs_eta_050;
  std::vector<TH1F*> yield_vs_eta_050_pt10;

  std::vector<TH1F*> chargeMisIDProb_vs_pt;
  std::vector<TH1F*> effic_vs_pt;
  std::vector<TH1F*> efficFakes_vs_pt;
  std::vector<TH1F*> qOverPtRes_vs_pt;
  std::vector<TH1F*> qOverPtResRMS_vs_pt;
  std::vector<TH1F*> numRecoPt_vs_pt;
  std::vector<TH1F*> numRecoPtAsso_vs_pt;
  std::vector<TH1F*> yield_vs_pt;

  std::vector<TH1F*> effic_vs_eta1;
  std::vector<TH1F*> effic_vs_eta2;
  std::vector<TH1F*> effic_vs_eta3;
  std::vector<TH1F*> effic_vs_eta4;
  std::vector<TH1F*> numRecoPt1_vs_eta;
  std::vector<TH1F*> numRecoPtAsso1_vs_eta;
  std::vector<TH1F*> numRecoPt2_vs_eta;
  std::vector<TH1F*> numRecoPtAsso2_vs_eta;
  std::vector<TH1F*> numRecoPt3_vs_eta;
  std::vector<TH1F*> numRecoPtAsso3_vs_eta;
  std::vector<TH1F*> numRecoPt4_vs_eta;
  std::vector<TH1F*> numRecoPtAsso4_vs_eta;
  std::vector<TH1F*> yield1_vs_eta;
  std::vector<TH1F*> yield2_vs_eta;
  std::vector<TH1F*> yield3_vs_eta;
  std::vector<TH1F*> yield4_vs_eta;

  std::vector<TH1F*> efficB_vs_pt;
  std::vector<TH1F*> efficO_vs_pt;
  std::vector<TH1F*> efficE_vs_pt;
  std::vector<TH1F*> numRecoPtB_vs_pt;
  std::vector<TH1F*> numRecoPtAssoB_vs_pt;
  std::vector<TH1F*> yieldB_vs_pt;
  std::vector<TH1F*> numRecoPtO_vs_pt;
  std::vector<TH1F*> numRecoPtAssoO_vs_pt;
  std::vector<TH1F*> yieldO_vs_pt;
  std::vector<TH1F*> numRecoPtE_vs_pt;
  std::vector<TH1F*> numRecoPtAssoE_vs_pt;
  std::vector<TH1F*> yieldE_vs_pt;

  std::vector<TEfficiency*> effErr_vs_eta;
  std::vector<TEfficiency*> effErr_vs_eta_050;
  std::vector<TEfficiency*> effErr_vs_pt;
  std::vector<TEfficiency*> effErr_vs_vtx;

  for(int i = 0; i < allNames.size()-1; i++){

  	TFile * f1 = TFile::Open(allNames[i].c_str());
  	f1->cd(("/DQMData/Run 1/Muons/Run summary/RecoMuonV/MultiTrack/"+allNames[5]).c_str());

  	TH1F * numEvt_NoGEM = (TH1F*)gDirectory->Get("numEvt");
  	//std::cout<<numEvt_NoGEM->GetBinContent(2)<<std::endl;
  	int numEvt = numEvt_NoGEM->GetBinContent(2);
  	std::cout<<i<<" "<<numEvt<<std::endl;

	chargeMisIDProb_vs_eta.push_back((TH1F*)gDirectory->Get("chargeMisIDProb_vs_eta_sim"));
	effic_vs_eta.push_back((TH1F*)gDirectory->Get("effic"));
	effic_vs_eta_050.push_back((TH1F*)gDirectory->Get("effic_Q05"));
	effic_vs_eta_050_pt10.push_back((TH1F*)gDirectory->Get("effic_Q05Pt10"));
	chi2.push_back((TH1F*)gDirectory->Get("chi2"));
	effic_vs_vtx.push_back((TH1F*)gDirectory->Get("efficVtx"));
	effic_vs_vtxB.push_back((TH1F*)gDirectory->Get("efficVtx_barrel"));
	effic_vs_vtxO.push_back((TH1F*)gDirectory->Get("efficVtx_overlap"));
	effic_vs_vtxE.push_back((TH1F*)gDirectory->Get("efficVtx_endcap"));
	efficFakes_vs_eta.push_back((TH1F*)gDirectory->Get("fakerate"));
	efficFakes_vs_eta_050.push_back((TH1F*)gDirectory->Get("fakerate050"));
	efficFakes_vs_eta_050_pt10.push_back((TH1F*)gDirectory->Get("fakerate050Pt10"));

	TH2F * qualityVsEta = (TH2F*)gDirectory->Get("qualityVsEta");
	TH1F * tmp = (TH1F*)qualityVsEta->ProfileX();
	quality_vs_eta.push_back(tmp);

	efficFakes1_vs_eta.push_back((TH1F*)gDirectory->Get("fakerateBin1"));
	efficFakes2_vs_eta.push_back((TH1F*)gDirectory->Get("fakerateBin2"));
	efficFakes3_vs_eta.push_back((TH1F*)gDirectory->Get("fakerateBin3"));
	efficFakes4_vs_eta.push_back((TH1F*)gDirectory->Get("fakerateBin4"));

	qOverPtRes_vs_eta.push_back((TH1F*)gDirectory->Get("qOverPtres_vs_eta_sim_Sigma"));
	qOverPtResRMS_vs_eta.push_back((TH1F*)gDirectory->Get("qOverPtres_vs_eta_sim_RMS"));
	numRecoPt_vs_eta.push_back((TH1F*)gDirectory->Get("num_reco_eta"));
	numRecoPtAsso_vs_eta.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_eta"));
	yield_vs_eta.push_back(produceYield((TH1F*)gDirectory->Get("num_reco_eta"), (TH1F*)gDirectory->Get("num_assoc(recoToSim)_eta"), numEvt));
	yield_vs_eta_050.push_back(produceYield((TH1F*)gDirectory->Get("num_reco_eta"), (TH1F*)gDirectory->Get("num_assoc(recoToSim)_eta_050"), numEvt));
	yield_vs_eta_050_pt10.push_back(produceYield((TH1F*)gDirectory->Get("num_reco_eta_pt10"), (TH1F*)gDirectory->Get("num_assoc(recoToSim)_eta_pt10"), numEvt));

	chargeMisIDProb_vs_pt.push_back((TH1F*)gDirectory->Get("chargeMisIDProb_vs_pt_sim"));
	effic_vs_pt.push_back((TH1F*)gDirectory->Get("efficPt"));
	efficFakes_vs_pt.push_back((TH1F*)gDirectory->Get("fakeratePt"));
	qOverPtRes_vs_pt.push_back((TH1F*)gDirectory->Get("qOverPtres_vs_pt_sim_Sigma"));
	qOverPtResRMS_vs_pt.push_back((TH1F*)gDirectory->Get("qOverPtres_vs_pt_sim_RMS"));
	numRecoPt_vs_pt.push_back((TH1F*)gDirectory->Get("num_reco_pT"));
	numRecoPtAsso_vs_pt.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_pT"));
	yield_vs_pt.push_back(produceYield((TH1F*)gDirectory->Get("num_reco_pT"), (TH1F*)gDirectory->Get("num_assoc(recoToSim)_pT"), numEvt));

	effic_vs_eta1.push_back((TH1F*)gDirectory->Get("efficBin1"));
	effic_vs_eta2.push_back((TH1F*)gDirectory->Get("efficBin2"));
	effic_vs_eta3.push_back((TH1F*)gDirectory->Get("efficBin3"));
	effic_vs_eta4.push_back((TH1F*)gDirectory->Get("efficBin4"));
	numRecoPt1_vs_eta.push_back((TH1F*)gDirectory->Get("num_reco_eta_bin1"));
	numRecoPtAsso1_vs_eta.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_eta_bin1"));
	numRecoPt2_vs_eta.push_back((TH1F*)gDirectory->Get("num_reco_eta_bin2"));
	numRecoPtAsso2_vs_eta.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_eta_bin2"));
	numRecoPt3_vs_eta.push_back((TH1F*)gDirectory->Get("num_reco_eta_bin3"));
	numRecoPtAsso3_vs_eta.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_eta_bin3"));
	numRecoPt4_vs_eta.push_back((TH1F*)gDirectory->Get("num_reco_eta_bin4"));
	numRecoPtAsso4_vs_eta.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_eta_bin4"));
	yield1_vs_eta.push_back(produceYield((TH1F*)gDirectory->Get("num_reco_eta_bin1"), (TH1F*)gDirectory->Get("num_assoc(recoToSim)_eta_bin1"), numEvt));
	yield2_vs_eta.push_back(produceYield((TH1F*)gDirectory->Get("num_reco_eta_bin2"), (TH1F*)gDirectory->Get("num_assoc(recoToSim)_eta_bin2"), numEvt));
	yield3_vs_eta.push_back(produceYield((TH1F*)gDirectory->Get("num_reco_eta_bin3"), (TH1F*)gDirectory->Get("num_assoc(recoToSim)_eta_bin3"), numEvt));
	yield4_vs_eta.push_back(produceYield((TH1F*)gDirectory->Get("num_reco_eta_bin4"), (TH1F*)gDirectory->Get("num_assoc(recoToSim)_eta_bin4"), numEvt));

	efficB_vs_pt.push_back((TH1F*)gDirectory->Get("efficPtBarrel"));
	efficO_vs_pt.push_back((TH1F*)gDirectory->Get("efficPtOverlap"));
	efficE_vs_pt.push_back((TH1F*)gDirectory->Get("efficPtEndcap"));
	numRecoPtB_vs_pt.push_back((TH1F*)gDirectory->Get("num_reco_pT_barrel"));
	numRecoPtAssoB_vs_pt.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_pT_barrel"));
	yieldB_vs_pt.push_back(produceYield((TH1F*)gDirectory->Get("num_reco_pT_barrel"), (TH1F*)gDirectory->Get("num_assoc(recoToSim)_pT_barrel"), numEvt));
	numRecoPtO_vs_pt.push_back((TH1F*)gDirectory->Get("num_reco_pT_overlap"));
	numRecoPtAssoO_vs_pt.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_pT_overlap"));
	yieldO_vs_pt.push_back(produceYield((TH1F*)gDirectory->Get("num_reco_pT_overlap"), (TH1F*)gDirectory->Get("num_assoc(recoToSim)_pT_overlap"), numEvt));
	numRecoPtE_vs_pt.push_back((TH1F*)gDirectory->Get("num_reco_pT_endcap"));
	numRecoPtAssoE_vs_pt.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_pT_endcap"));
	yieldE_vs_pt.push_back(produceYield((TH1F*)gDirectory->Get("num_reco_pT_endcap"), (TH1F*)gDirectory->Get("num_assoc(recoToSim)_pT_endcap"), numEvt));

	TEfficiency * effEta = calcEff((TH1F*)gDirectory->Get("num_assoc(simToReco)_eta"), (TH1F*)gDirectory->Get("num_simul_eta"));
	effErr_vs_eta.push_back(effEta);
	TEfficiency * effEta050 = calcEff((TH1F*)gDirectory->Get("num_assoc(simToReco)_eta_Q05"), (TH1F*)gDirectory->Get("num_simul_eta"));
	effErr_vs_eta_050.push_back(effEta050);
	TEfficiency * effPt = calcEff((TH1F*)gDirectory->Get("num_assoc(simToReco)_pT"), (TH1F*)gDirectory->Get("num_simul_pT"));
	effErr_vs_pt.push_back(effPt);
	TEfficiency * effVtx = calcEff((TH1F*)gDirectory->Get("num_assoc(simToReco)_vtx"), (TH1F*)gDirectory->Get("num_simul_vtx"), true);
	effErr_vs_vtx.push_back(effVtx);

  }

  //TH2F * qOverPtResRMS_vs_eta[0]_2D = (TH2F*)gDirectory->Get("qOverPtresXL_vs_eta_sim");
  //vecHist v5 = projectAndFit(qOverPtResRMS_vs_eta[0]_2D);
  //makeSuperImp(v1, v2, v3, ("distr_"+name3).c_str(), allNames[5]);

  /*extractPerformance(effic_vs_eta_GEM5, effic_vs_eta_GEM, "Efficiency", "5 < pT < 10 GeV/c");
  extractPerformance(effic_vs_vtx_GEM5, effic_vs_vtx_GEM, "Efficiency", "10 < pT < 20 GeV/c");
  extractPerformance(effic_vs_vtxB_GEM5, effic_vs_vtxB_GEM, "Efficiency", "20 < pT < 40 GeV/c");
  extractPerformance(effic_vs_vtxE_GEM5, effic_vs_vtxE_GEM, "Efficiency", "pT > 40 GeV/c");

  extractPerformance(qOverPtRes_vs_eta_GEM5, qOverPtRes_vs_eta_GEM, "Resolution", "pT > 0");

  extractPerformance(yield_vs_eta_GEM5, yield_vs_eta_GEM, "Bkg Yield", "5 < pT < 10 GeV/c");
  extractPerformance(yield2_vs_eta_GEM5, yield2_vs_eta_GEM, "Bkg Yield", "10 < pT < 20 GeV/c");
  extractPerformance(yield3_vs_eta_GEM5, yield3_vs_eta_GEM, "Bkg Yield", "20 < pT < 40 GeV/c");
  extractPerformance(yield4_vs_eta_GEM5, yield4_vs_eta_GEM, "Bkg Yield", "pT > 40 GeV/c");*/

//---------------------------------------------------------------------------------------------------------------------------

 	std::vector<TH1F*> numRecoTOT_vs_eta = sumHistos(numRecoPt1_vs_eta, numRecoPt2_vs_eta, numRecoPt3_vs_eta, numRecoPt4_vs_eta);
  	std::vector<TH1F*> numRecoAssoTOT_vs_eta = sumHistos(numRecoPtAsso1_vs_eta, numRecoPtAsso2_vs_eta, numRecoPtAsso3_vs_eta, numRecoPtAsso4_vs_eta);
	std::vector<TH1F*> fakeRateTOT_vs_eta = makeMismatch(numRecoTOT_vs_eta, numRecoAssoTOT_vs_eta);

	std::string addString = "";
	if(allNames[5].find("MuonLoose") != std::string::npos) addString = "Loose Muon ";
	else if(allNames[5].find("MuonTight") != std::string::npos) addString = "Tight Muon ";
	else addString = "Muon ";

	setEverything2(effErr_vs_eta, 0.0, 1.0, false, 0.25, 0.20, 0.75, 0.45, name3, allNames[5], (addString + "Efficiency"), "efficErr_");
	setEverything2(effErr_vs_eta_050, 0.4, 1.0, false, 0.25, 0.20, 0.75, 0.45, name3, allNames[5], (addString + "Efficiency"), "efficErr050_");
	setEverything2(effErr_vs_pt, 0.0, 1.0, false, 0.25, 0.20, 0.75, 0.45, name3, allNames[5], (addString + "Efficiency"), "efficPtErr_");
	setEverything2(effErr_vs_vtx, 0.9, 1.0, false, 0.25, 0.20, 0.75, 0.45, name3, allNames[5], (addString + "Efficiency"), "efficVtxErr_");

	setEverything(chargeMisIDProb_vs_eta, 0.000001, 0.1, true, 0.20, 0.70, 0.70, 0.90, name3, allNames[5], "Charge mis-ID Prob.", "chargeMisID_");
	setEverything(effic_vs_eta, 0.0, 1.0, false, 0.25, 0.20, 0.75, 0.45, name3, allNames[5], (addString + "Efficiency"), "effic_");
	setEverything(effic_vs_eta_050, 0.4, 1.0, false, 0.25, 0.20, 0.75, 0.45, name3, allNames[5], (addString + "Efficiency"), "effic050_");
	setEverything(effic_vs_eta_050_pt10, 0.4, 1.0, false, 0.25, 0.20, 0.75, 0.45, name3, allNames[5], (addString + "Efficiency"), "effic050Pt10_");
	setEverything(efficFakes_vs_eta, 0.0, 1.0, false, 0.20, 0.60, 0.75, 0.85, name3, allNames[5], "Fake Rate", "efficFakes_");
	setEverything(efficFakes_vs_eta_050, 0.0, 1.0, false, 0.20, 0.60, 0.75, 0.85, name3, allNames[5], "Fake Rate", "efficFakes050_");
	setEverything(efficFakes_vs_eta_050_pt10, 0.0, 1.0, false, 0.20, 0.60, 0.75, 0.85, name3, allNames[5], "Fake Rate", "efficFakes050Pt10_");

	setEverything(quality_vs_eta, 0.0, 1.0, false, 0.25, 0.20, 0.75, 0.45, name3, allNames[5], (addString + "Quality"), "qualityVsEta_");

	setEverything(efficFakes1_vs_eta, 0.0, 1.0, false, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "Fake Rate [(5 < p_{T} < 10) GeV/c]", "efficFakes1_");
	setEverything(efficFakes2_vs_eta, 0.0, 1.0, false, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "Fake Rate [(10 < p_{T} < 15) GeV/c]", "efficFakes2_");
	setEverything(efficFakes3_vs_eta, 0.0, 1.0, false, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "Fake Rate [(15 < p_{T} < 20) GeV/c]", "efficFakes3_");
	setEverything(efficFakes4_vs_eta, 0.0, 1.0, false, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "Fake Rate [p_{T} > 20 GeV/c]", "efficFakes4_");
	setEverything(fakeRateTOT_vs_eta, 0.0, 1.0, false, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "Fake Rate [p_{T} > 5 GeV/c]", "efficFakesTOT_");

	setEverything(effic_vs_vtx, 0.9, 1.0, false, 0.25, 0.20, 0.75, 0.45, name3, allNames[5], (addString + "Efficiency"), "efficVtx_");
	setEverything(effic_vs_vtxB, 0.9, 1.0, false, 0.25, 0.20, 0.75, 0.45, name3, allNames[5], (addString + "Efficiency (Barrel)"), "efficVtxB_");
	setEverything(effic_vs_vtxO, 0.9, 1.0, false, 0.25, 0.20, 0.75, 0.45, name3, allNames[5], (addString + "Efficiency (Overlap)"), "efficVtxO_");
	setEverything(effic_vs_vtxE, 0.9, 1.0, false, 0.25, 0.20, 0.75, 0.45, name3, allNames[5], (addString + "Efficiency (Endcap)"), "efficVtxE_");

	setEverything(qOverPtRes_vs_eta, 0.1, 1.0, true, 0.15, 0.70, 0.65, 0.95, name3, allNames[5], "#sigma(p_{T})/p_{T}", "invRes_");
	setEverything(qOverPtResRMS_vs_eta, 0.1, 0.2, true, 0.15, 0.70, 0.65, 0.95, name3, allNames[5], "q/p_{T} RMS", "invResRMS_");

	setEverything(yield_vs_eta, 0.005, 0.5, true, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "Average Muon Bkg Multiplicity", "yield_");
	setEverything(yield_vs_eta_050, 0.0, 0.40, false, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "Average Muon Bkg Multiplicity", "yield050_");

	double max = 0.05;
	if(allNames[5].find("MuonLoose") || allNames[5].find("MuonTight") || allNames[5].find("extracted")) max = 0.02;

	setEverything(yield_vs_eta_050_pt10, 0.0, max, false, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "Average Muon Bkg Multiplicity (Q > 50%, p_{T} > 10 GeV/c)", "yield050Pt10_");

	setEverything(chargeMisIDProb_vs_pt, 0.000001, 0.1, true, 0.20, 0.70, 0.70, 0.90, name3, allNames[5], "Charge mis-ID Prob.", "chargeMisIDPt_");
	setEverything(effic_vs_pt, 0.0, 1.0, false, 0.25, 0.20, 0.75, 0.45, name3, allNames[5], (addString + "Efficiency"), "efficPt_");
	setEverything(efficFakes_vs_pt, 0.0, 1.0, false, 0.25, 0.75, 0.85, 0.95, name3, allNames[5], "Fake Rate", "efficFakesPt_");

	setEverything(qOverPtRes_vs_pt, 0.003, 0.1, true, 0.25, 0.70, 0.75, 0.95, name3, allNames[5], "#sigma(p_{T})/p_{T}", "invResPt_");
	setEverything(qOverPtResRMS_vs_pt, 0.005, 0.1, true, 0.25, 0.70, 0.75, 0.95, name3, allNames[5], "q/p_{T} RMS", "invResRMSPt_");

	setEverything(yield_vs_pt, 0.000001, 50.0, true, 0.40, 0.75, 0.90, 0.95, name3, allNames[5], "Average Muon Bkg Multiplicity", "yieldPt_");
 
 	setEverything(effic_vs_eta1, 0.9, 1.0, false, 0.25, 0.20, 0.75, 0.45, name3, allNames[5], (addString + "Efficiency [(5 < p_{T} < 10) GeV/c]"), "effic1_");
	setEverything(effic_vs_eta2, 0.9, 1.0, false, 0.25, 0.20, 0.75, 0.45, name3, allNames[5], (addString + "Efficiency [(10 < p_{T} < 20) GeV/c]"), "effic2_");
	setEverything(effic_vs_eta3, 0.9, 1.0, false, 0.25, 0.20, 0.75, 0.45, name3, allNames[5], (addString + "Efficiency [(20 < p_{T} < 40) GeV/c]"), "effic3_");
	setEverything(effic_vs_eta4, 0.9, 1.0, false, 0.25, 0.20, 0.75, 0.45, name3, allNames[5], (addString + "Efficiency [p_{T} > 40 GeV/c]"), "effic4_");

	setEverything(yield1_vs_eta, 0.000001, 1.0, true, 0.40, 0.75, 0.90, 0.95, name3, allNames[5], "Average Muon Bkg Multiplicity [(5 < p_{T} < 10) GeV/c]", "yield1_");
	setEverything(yield2_vs_eta, 0.000001, 1.0, true, 0.40, 0.75, 0.90, 0.95, name3, allNames[5], "Average Muon Bkg Multiplicity [(10 < p_{T} < 20) GeV/c]", "yield2_");
	setEverything(yield3_vs_eta, 0.000001, 1.0, true, 0.40, 0.75, 0.90, 0.95, name3, allNames[5], "Average Muon Bkg Multiplicity [(20 < p_{T} < 40) GeV/c]", "yield3_");
	setEverything(yield4_vs_eta, 0.000001, 1.0, true, 0.40, 0.75, 0.90, 0.95, name3, allNames[5], "Average Muon Bkg Multiplicity [p_{T} > 40 GeV/c]", "yield4_");

	setEverything(efficB_vs_pt, 0.0, 1.0, false, 0.25, 0.20, 0.75, 0.45, name3, allNames[5], (addString + "Efficiency (Barrel)"), "efficPtB_");
	setEverything(efficO_vs_pt, 0.0, 1.0, false, 0.25, 0.20, 0.75, 0.45, name3, allNames[5], (addString + "Efficiency (Overlap)"), "efficPtO_");
	setEverything(efficE_vs_pt, 0.0, 1.0, false, 0.25, 0.20, 0.75, 0.45, name3, allNames[5], (addString + "Efficiency (Endcap)"), "efficPtE_");

	setEverything(yieldB_vs_pt, 0.000001, 50.0, true, 0.40, 0.75, 0.90, 0.95, name3, allNames[5], "Average Muon Bkg Multiplicity (Barrel)", "yieldPtB_");
	setEverything(yieldO_vs_pt, 0.000001, 50.0, true, 0.40, 0.75, 0.90, 0.95, name3, allNames[5], "Average Muon Bkg Multiplicity (Overlap)", "yieldPtO_");
	setEverything(yieldE_vs_pt, 0.000001, 50.0, true, 0.40, 0.75, 0.90, 0.95, name3, allNames[5], "Average Muon Bkg Multiplicity (Endcap)", "yieldPtE_");

	setEverything(chi2, 0.0, 0.25, false, 0.35, 0.75, 0.85, 0.95, name3, allNames[5], (addString + "#chi^{2}/ndof"), "chi2_");
	setEverything(numRecoPtAsso_vs_pt, 0.1, 50000.0, true, 0.35, 0.75, 0.85, 0.95, name3, allNames[5], "Entries", "numReco_");

}

void makePlots2(std::vector<std::string> allNames, std::vector<std::string> allNames2, std::string name3){

  std::vector<TH1F*> effic_vs_eta;
  std::vector<TH1F*> efficFakes_vs_eta;
  std::vector<TH1F*> efficFakes1_vs_eta;
  std::vector<TH1F*> efficFakes2_vs_eta;
  std::vector<TH1F*> efficFakes3_vs_eta;
  std::vector<TH1F*> efficFakes4_vs_eta;

  std::vector<TH1F*> numRecoAsso_vs_eta;
  std::vector<TH1F*> numRecoAsso1_vs_eta;
  std::vector<TH1F*> numRecoAsso2_vs_eta;
  std::vector<TH1F*> numRecoAsso3_vs_eta;
  std::vector<TH1F*> numRecoAsso4_vs_eta;

  std::vector<TH1F*> numSimAsso_vs_eta;
  std::vector<TH1F*> numSimAsso1_vs_eta;
  std::vector<TH1F*> numSimAsso2_vs_eta;
  std::vector<TH1F*> numSimAsso3_vs_eta;
  std::vector<TH1F*> numSimAsso4_vs_eta;

  std::vector<TH1F*> numRecoAsso_vs_pt;
  std::vector<TH1F*> numRecoAsso1_vs_pt;
  std::vector<TH1F*> numRecoAsso2_vs_pt;
  std::vector<TH1F*> numRecoAsso3_vs_pt;

  std::vector<TH1F*> numSimAsso_vs_pt;
  std::vector<TH1F*> numSimAsso1_vs_pt;
  std::vector<TH1F*> numSimAsso2_vs_pt;
  std::vector<TH1F*> numSimAsso3_vs_pt;

  std::vector<TH1F*> chi2;

  //1 = loose, 2 = tight 

  for(int i = 0; i < allNames.size()-1; i++){

  	TFile * f1 = TFile::Open(allNames[i].c_str());
  	f1->cd(("/DQMData/Run 1/Muons/Run summary/RecoMuonV/MultiTrack/"+allNames[5]).c_str());

	effic_vs_eta.push_back((TH1F*)gDirectory->Get("effic"));
	efficFakes_vs_eta.push_back((TH1F*)gDirectory->Get("fakerate"));
	efficFakes1_vs_eta.push_back((TH1F*)gDirectory->Get("fakerateBin1"));
	efficFakes2_vs_eta.push_back((TH1F*)gDirectory->Get("fakerateBin2"));
	efficFakes3_vs_eta.push_back((TH1F*)gDirectory->Get("fakerateBin3"));
	efficFakes4_vs_eta.push_back((TH1F*)gDirectory->Get("fakerateBin4"));

	numRecoAsso_vs_eta.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_eta"));
	numRecoAsso1_vs_eta.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_eta_bin1"));
	numRecoAsso2_vs_eta.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_eta_bin2"));
	numRecoAsso3_vs_eta.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_eta_bin3"));
	numRecoAsso4_vs_eta.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_eta_bin4"));

	numSimAsso_vs_eta.push_back((TH1F*)gDirectory->Get("num_assoc(simToReco)_eta"));
	numSimAsso1_vs_eta.push_back((TH1F*)gDirectory->Get("num_assoc(simToReco)_eta_bin1"));
	numSimAsso2_vs_eta.push_back((TH1F*)gDirectory->Get("num_assoc(simToReco)_eta_bin2"));
	numSimAsso3_vs_eta.push_back((TH1F*)gDirectory->Get("num_assoc(simToReco)_eta_bin3"));
	numSimAsso4_vs_eta.push_back((TH1F*)gDirectory->Get("num_assoc(simToReco)_eta_bin4"));

	numRecoAsso_vs_pt.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_pT"));
	numRecoAsso1_vs_pt.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_pT_barrel"));
	numRecoAsso2_vs_pt.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_pT_overlap"));
	numRecoAsso3_vs_pt.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_pT_endcap"));

	numSimAsso_vs_pt.push_back((TH1F*)gDirectory->Get("num_assoc(simToReco)_pT"));
	numSimAsso1_vs_pt.push_back((TH1F*)gDirectory->Get("num_assoc(simToReco)_pT_barrel"));
	numSimAsso2_vs_pt.push_back((TH1F*)gDirectory->Get("num_assoc(simToReco)_pT_overlap"));
	numSimAsso3_vs_pt.push_back((TH1F*)gDirectory->Get("num_assoc(simToReco)_pT_endcap"));

	chi2.push_back((TH1F*)gDirectory->Get("chi2"));

  }

  std::vector<TH1F*> numRecoAssoTOT_vs_eta = sumHistos(numRecoAsso1_vs_eta, numRecoAsso2_vs_eta, numRecoAsso3_vs_eta, numRecoAsso4_vs_eta);
  std::vector<TH1F*> numSimAssoTOT_vs_eta = sumHistos(numSimAsso1_vs_eta, numSimAsso2_vs_eta, numSimAsso3_vs_eta, numSimAsso4_vs_eta);

  std::vector<TH1F*> effic_vs_eta_2;
  std::vector<TH1F*> efficFakes_vs_eta_2;
  std::vector<TH1F*> efficFakes1_vs_eta_2;
  std::vector<TH1F*> efficFakes2_vs_eta_2;
  std::vector<TH1F*> efficFakes3_vs_eta_2;
  std::vector<TH1F*> efficFakes4_vs_eta_2;

  std::vector<TH1F*> numRecoAsso_vs_eta_2;
  std::vector<TH1F*> numRecoAsso1_vs_eta_2;
  std::vector<TH1F*> numRecoAsso2_vs_eta_2;
  std::vector<TH1F*> numRecoAsso3_vs_eta_2;
  std::vector<TH1F*> numRecoAsso4_vs_eta_2;

  std::vector<TH1F*> numSimAsso_vs_eta_2;
  std::vector<TH1F*> numSimAsso1_vs_eta_2;
  std::vector<TH1F*> numSimAsso2_vs_eta_2;
  std::vector<TH1F*> numSimAsso3_vs_eta_2;
  std::vector<TH1F*> numSimAsso4_vs_eta_2;

  std::vector<TH1F*> numRecoAsso_vs_pt_2;
  std::vector<TH1F*> numRecoAsso1_vs_pt_2;
  std::vector<TH1F*> numRecoAsso2_vs_pt_2;
  std::vector<TH1F*> numRecoAsso3_vs_pt_2;

  std::vector<TH1F*> numSimAsso_vs_pt_2;
  std::vector<TH1F*> numSimAsso1_vs_pt_2;
  std::vector<TH1F*> numSimAsso2_vs_pt_2;
  std::vector<TH1F*> numSimAsso3_vs_pt_2;

  std::vector<TH1F*> chi2_2;

  for(int i = 0; i < allNames2.size()-1; i++){

  	TFile * f1 = TFile::Open(allNames2[i].c_str());
  	f1->cd(("/DQMData/Run 1/Muons/Run summary/RecoMuonV/MultiTrack/"+allNames2[5]).c_str());

	effic_vs_eta_2.push_back((TH1F*)gDirectory->Get("effic"));
	efficFakes_vs_eta_2.push_back((TH1F*)gDirectory->Get("fakerate"));
	efficFakes1_vs_eta_2.push_back((TH1F*)gDirectory->Get("fakerateBin1"));
	efficFakes2_vs_eta_2.push_back((TH1F*)gDirectory->Get("fakerateBin2"));
	efficFakes3_vs_eta_2.push_back((TH1F*)gDirectory->Get("fakerateBin3"));
	efficFakes4_vs_eta_2.push_back((TH1F*)gDirectory->Get("fakerateBin4"));

	numRecoAsso_vs_eta_2.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_eta"));
	numRecoAsso1_vs_eta_2.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_eta_bin1"));
	numRecoAsso2_vs_eta_2.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_eta_bin2"));
	numRecoAsso3_vs_eta_2.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_eta_bin3"));
	numRecoAsso4_vs_eta_2.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_eta_bin4"));

	numSimAsso_vs_eta_2.push_back((TH1F*)gDirectory->Get("num_assoc(simToReco)_eta"));
	numSimAsso1_vs_eta_2.push_back((TH1F*)gDirectory->Get("num_assoc(simToReco)_eta_bin1"));
	numSimAsso2_vs_eta_2.push_back((TH1F*)gDirectory->Get("num_assoc(simToReco)_eta_bin2"));
	numSimAsso3_vs_eta_2.push_back((TH1F*)gDirectory->Get("num_assoc(simToReco)_eta_bin3"));
	numSimAsso4_vs_eta_2.push_back((TH1F*)gDirectory->Get("num_assoc(simToReco)_eta_bin4"));

	numRecoAsso_vs_pt_2.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_pT"));
	numRecoAsso1_vs_pt_2.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_pT_barrel"));
	numRecoAsso2_vs_pt_2.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_pT_overlap"));
	numRecoAsso3_vs_pt_2.push_back((TH1F*)gDirectory->Get("num_assoc(recoToSim)_pT_endcap"));

	numSimAsso_vs_pt_2.push_back((TH1F*)gDirectory->Get("num_assoc(simToReco)_pT"));
	numSimAsso1_vs_pt_2.push_back((TH1F*)gDirectory->Get("num_assoc(simToReco)_pT_barrel"));
	numSimAsso2_vs_pt_2.push_back((TH1F*)gDirectory->Get("num_assoc(simToReco)_pT_overlap"));
	numSimAsso3_vs_pt_2.push_back((TH1F*)gDirectory->Get("num_assoc(simToReco)_pT_endcap"));

	chi2_2.push_back((TH1F*)gDirectory->Get("chi2"));

  }

  std::vector<TH1F*> numRecoAssoTOT_vs_eta_2 = sumHistos(numRecoAsso1_vs_eta_2, numRecoAsso2_vs_eta_2, numRecoAsso3_vs_eta_2, numRecoAsso4_vs_eta_2);
  std::vector<TH1F*> numSimAssoTOT_vs_eta_2 = sumHistos(numSimAsso1_vs_eta_2, numSimAsso2_vs_eta_2, numSimAsso3_vs_eta_2, numSimAsso4_vs_eta_2);

	std::string addString = "";
	if(allNames[5].find("MuonLoose") != std::string::npos) addString = "Loose Muon ";
	else if(allNames[5].find("MuonTight") != std::string::npos) addString = "Tight Muon ";
	else addString = "Muon ";

	makeDiff(effic_vs_eta, effic_vs_eta_2);
	makeDiff(efficFakes_vs_eta_2, efficFakes_vs_eta);
	makeDiff(efficFakes1_vs_eta_2, efficFakes1_vs_eta);
	makeDiff(efficFakes2_vs_eta_2, efficFakes2_vs_eta);
	makeDiff(efficFakes3_vs_eta_2, efficFakes3_vs_eta);
	makeDiff(efficFakes4_vs_eta_2, efficFakes4_vs_eta);

	makeDiff(chi2, chi2_2);
	makeDiff(numRecoAsso_vs_pt, numRecoAsso_vs_pt_2);

	std::vector<TH1F*> mismatchReco = makeMismatch(numRecoAsso_vs_eta, numRecoAsso_vs_eta_2);
	std::vector<TH1F*> mismatchReco1 = makeMismatch(numRecoAsso1_vs_eta, numRecoAsso1_vs_eta_2);
	std::vector<TH1F*> mismatchReco2 = makeMismatch(numRecoAsso2_vs_eta, numRecoAsso2_vs_eta_2);
	std::vector<TH1F*> mismatchReco3 = makeMismatch(numRecoAsso3_vs_eta, numRecoAsso3_vs_eta_2);
	std::vector<TH1F*> mismatchReco4 = makeMismatch(numRecoAsso4_vs_eta, numRecoAsso4_vs_eta_2);
	std::vector<TH1F*> mismatchRecoTOT = makeMismatch(numRecoAssoTOT_vs_eta, numRecoAssoTOT_vs_eta_2);

	std::vector<TH1F*> mismatchSim = makeMismatch(numSimAsso_vs_eta, numSimAsso_vs_eta_2);
	std::vector<TH1F*> mismatchSim1 = makeMismatch(numSimAsso1_vs_eta, numSimAsso1_vs_eta_2);
	std::vector<TH1F*> mismatchSim2 = makeMismatch(numSimAsso2_vs_eta, numSimAsso2_vs_eta_2);
	std::vector<TH1F*> mismatchSim3 = makeMismatch(numSimAsso3_vs_eta, numSimAsso3_vs_eta_2);
	std::vector<TH1F*> mismatchSim4 = makeMismatch(numSimAsso4_vs_eta, numSimAsso4_vs_eta_2);
	std::vector<TH1F*> mismatchSimTOT = makeMismatch(numSimAssoTOT_vs_eta, numSimAssoTOT_vs_eta_2);

	std::vector<TH1F*> mismatchReco_pt = makeMismatch(numRecoAsso_vs_pt, numRecoAsso_vs_pt_2);
	std::vector<TH1F*> mismatchReco1_pt = makeMismatch(numRecoAsso1_vs_pt, numRecoAsso1_vs_pt_2);
	std::vector<TH1F*> mismatchReco2_pt = makeMismatch(numRecoAsso2_vs_pt, numRecoAsso2_vs_pt_2);
	std::vector<TH1F*> mismatchReco3_pt = makeMismatch(numRecoAsso3_vs_pt, numRecoAsso3_vs_pt_2);

	std::vector<TH1F*> mismatchSim_pt = makeMismatch(numSimAsso_vs_pt, numSimAsso_vs_pt_2);
	std::vector<TH1F*> mismatchSim1_pt = makeMismatch(numSimAsso1_vs_pt, numSimAsso1_vs_pt_2);
	std::vector<TH1F*> mismatchSim2_pt = makeMismatch(numSimAsso2_vs_pt, numSimAsso2_vs_pt_2);
	std::vector<TH1F*> mismatchSim3_pt = makeMismatch(numSimAsso3_vs_pt, numSimAsso3_vs_pt_2);

	setEverything(chi2, 0.0, 0.25, false, 0.35, 0.75, 0.85, 0.95, name3, allNames[5], (addString + "#chi^{2}/ndof"), "chi2Diff_");
	setEverything(numRecoAsso_vs_pt, 0.1, 50000.0, true, 0.35, 0.75, 0.85, 0.95, name3, allNames[5], "Entries", "numRecoDiff_");

	setEverything(effic_vs_eta, 0.0, 1.0, false, 0.25, 0.20, 0.75, 0.45, name3, allNames[5], (addString + "Efficiency"), "efficDiff_");
	setEverything(efficFakes_vs_eta_2, 0.0, 1.0, false, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "Fake Rate", "efficFakesDiff_");

	setEverything(efficFakes1_vs_eta_2, 0.0, 1.0, false, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "Fake Rate [(5 < p_{T} < 10) GeV/c]", "efficFakesDiff1_");
	setEverything(efficFakes2_vs_eta_2, 0.0, 1.0, false, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "Fake Rate [(10 < p_{T} < 15) GeV/c]", "efficFakesDiff2_");
	setEverything(efficFakes3_vs_eta_2, 0.0, 1.0, false, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "Fake Rate [(15 < p_{T} < 20) GeV/c]", "efficFakesDiff3_");
	setEverything(efficFakes4_vs_eta_2, 0.0, 1.0, false, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "Fake Rate [p_{T} > 20 GeV/c]", "efficFakesDiff4_");


	setEverything(mismatchReco, 0.001, 10.0, true, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "STA-TRK Mismatch (SGN + BKG muons)", "mismatchReco_");
	setEverything(mismatchReco1, 0.001, 10.0, true, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "STA-TRK Mismatch (SGN + BKG muons)", "mismatchReco1_");
	setEverything(mismatchReco2, 0.001, 10.0, true, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "STA-TRK Mismatch (SGN + BKG muons)", "mismatchReco2_");
	setEverything(mismatchReco3, 0.001, 10.0, true, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "STA-TRK Mismatch (SGN + BKG muons)", "mismatchReco3_");
	setEverything(mismatchReco4, 0.001, 10.0, true, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "STA-TRK Mismatch (SGN + BKG muons)", "mismatchReco4_");
	setEverything(mismatchRecoTOT, 0.001, 10.0, true, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "STA-TRK Mismatch (SGN + BKG muons, p_{T} > 5 GeV/c)", "mismatchRecoTOT_");

	setEverything(mismatchSim, 0.001, 10.0, true, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "STA-TRK Mismatch (only SGN muons)", "mismatchSim_");
	setEverything(mismatchSim1, 0.001, 10.0, true, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "STA-TRK Mismatch (only SGN muons)", "mismatchSim1_");
	setEverything(mismatchSim2, 0.001, 10.0, true, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "STA-TRK Mismatch (only SGN muons)", "mismatchSim2_");
	setEverything(mismatchSim3, 0.001, 10.0, true, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "STA-TRK Mismatch (only SGN muons)", "mismatchSim3_");
	setEverything(mismatchSim4, 0.001, 10.0, true, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "STA-TRK Mismatch (only SGN muons)", "mismatchSim4_");
	setEverything(mismatchSimTOT, 0.001, 10.0, true, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "STA-TRK Mismatch (only SGN muons, p_{T} > 5 GeV/c)", "mismatchSimTOT_");


	setEverything(mismatchReco_pt, 0.001, 10.0, true, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "STA-TRK Mismatch (SGN + BKG muons)", "mismatchReco_pt_");
	setEverything(mismatchReco1_pt, 0.001, 10.0, true, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "STA-TRK Mismatch (SGN + BKG muons, Barrel)", "mismatchReco1_pt_");
	setEverything(mismatchReco2_pt, 0.001, 10.0, true, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "STA-TRK Mismatch (SGN + BKG muons, Overlap)", "mismatchReco2_pt_");
	setEverything(mismatchReco3_pt, 0.001, 10.0, true, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "STA-TRK Mismatch (SGN + BKG muons, Endcap)", "mismatchReco3_pt_");

	setEverything(mismatchSim_pt, 0.001, 10.0, true, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "STA-TRK Mismatch (only SGN muons)", "mismatchSim_pt_");
	setEverything(mismatchSim1_pt, 0.001, 10.0, true, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "STA-TRK Mismatch (only SGN muons, Barrel)", "mismatchSim1_pt_");
	setEverything(mismatchSim2_pt, 0.001, 10.0, true, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "STA-TRK Mismatch (only SGN muons, Overlap)", "mismatchSim2_pt_");
	setEverything(mismatchSim3_pt, 0.001, 10.0, true, 0.15, 0.75, 0.65, 0.95, name3, allNames[5], "STA-TRK Mismatch (only SGN muons, Endcap)", "mismatchSim3_pt_");

}

void makeAll(std::string type = "bestMuonLoose_AssociatorByPull"){

	std::string path1 = "/home/cesare/Scrivania/ByHits2/";
	std::string path0 = "/home/cesare/Scrivania/ByHits2/";
	//std::string path0 = "/home/cesare/Scrivania/ByChi2_LaVendetta3/2019WithoutGEMs/";
	std::string path2 = "/home/cesare/Scrivania/ByHits2/";
	//std::string path3 = "/home/cesare/Scrivania/ByChi2_LaVendetta3/2019Age/";
	std::string path4 = "/home/cesare/Scrivania/ByHits2/";
	std::string path3 = "/home/cesare/Scrivania/ByHits2/";
	//std::string path4 = "/home/cesare/Scrivania/ByChi2_LaVendetta3/2023NoUpgrade/";

	std::string nome5_2019 = "DQM_V0001_R000000001__GlobalValidation__Test__RECO_MuMinus100_2019.root";
	std::string nome5_2019No = "DQM_V0001_R000000001__GlobalValidation__Test__RECO_MuMinus100_2019_NoUpg.root";
	std::string nome5_2019Age = "DQM_V0001_R000000001__GlobalValidation__Test__RECO_MuMinus100_2019Age.root";
	std::string nome5_2023 = "DQM_V0001_R000000001__GlobalValidation__Test__RECO_MuMinus100_2019Age_NoUpg.root";
	std::string nome5_2023No = "DQM_V0001_R000000001__GlobalValidation__Test__RECO_MuMinus100_2019Age_NoUpg.root";
	
	//Order: 2019, 2019NoUpg, 2019Age, 2023, 2023NoUpg

	std::vector<std::string> allNames;
	allNames.push_back((path1+nome5_2019));
	allNames.push_back((path0+nome5_2019No));
	allNames.push_back((path2+nome5_2019Age));
	allNames.push_back((path3+nome5_2023));
	allNames.push_back((path4+nome5_2023No));
	allNames.push_back(type);

	makePlots(allNames,"Muon100");

}

void makeAll2(std::string type = "bestMuonLoose_AssociatorByPull", std::string type2 = "bestMuonLoose_AssociatorByPull"){

	std::string path1 = "/home/cesare/Scrivania/ByHits2/";
	std::string path0 = "/home/cesare/Scrivania/ByHits2/";
	//std::string path0 = "/home/cesare/Scrivania/ByChi2_LaVendetta3/2019WithoutGEMs/";
	std::string path2 = "/home/cesare/Scrivania/ByHits2/";
	//std::string path3 = "/home/cesare/Scrivania/ByChi2_LaVendetta3/2019Age/";
	std::string path4 = "/home/cesare/Scrivania/ByHits2/";
	std::string path3 = "/home/cesare/Scrivania/ByHits2/";
	//std::string path4 = "/home/cesare/Scrivania/ByChi2_LaVendetta3/2023NoUpgrade/";

	std::string nome5_2019 = "DQM_V0001_R000000001__GlobalValidation__Test__RECO_MuMinus100_2019.root";
	std::string nome5_2019No = "DQM_V0001_R000000001__GlobalValidation__Test__RECO_MuMinus100_2019_NoUpg.root";
	std::string nome5_2019Age = "DQM_V0001_R000000001__GlobalValidation__Test__RECO_MuMinus100_2019Age.root";
	std::string nome5_2023 = "DQM_V0001_R000000001__GlobalValidation__Test__RECO_MuMinus100_2019Age_NoUpg.root";
	std::string nome5_2023No = "DQM_V0001_R000000001__GlobalValidation__Test__RECO_MuMinus100_2019Age_NoUpg.root";
	
	//Order: 2019, 2019NoUpg, 2019Age, 2023, 2023NoUpg

	std::vector<std::string> allNames;
	allNames.push_back((path1+nome5_2019));
	allNames.push_back((path0+nome5_2019No));
	allNames.push_back((path2+nome5_2019Age));
	allNames.push_back((path3+nome5_2023));
	allNames.push_back((path4+nome5_2023No));
	allNames.push_back(type);

	std::vector<std::string> allNames2;
	allNames2.push_back((path1+nome5_2019));
	allNames2.push_back((path0+nome5_2019No));
	allNames2.push_back((path2+nome5_2019Age));
	allNames2.push_back((path3+nome5_2023));
	allNames2.push_back((path4+nome5_2023No));
	allNames2.push_back(type2);

	makePlots2(allNames,allNames2,"Muon100");

}

void makeAllAll(){

	//makeAll("trackerMuons_AssociatorByPull");
	//makeAll("TrackerMuonArbitrated_AssociatorByPull");
	//makeAll("TMOneStationTight_AssociatorByPull");
	//makeAll("TMLastStationAngTight_AssociatorByPull");

	makeAll("extractedSTAMuons2StatTiming_tpToStaUpdSel2MuonAssociation2StTime"); //valid hit + muon purity
	makeAll("extractedSTAMuons2StatTiming_tpToStaUpdMuonAssociation2StTime"); //valid hit
	makeAll("extractedSTAMuons2Stat_tpToStaUpdSel2MuonAssociation2St"); //default
	makeAll("extractedSTAMuons2Stat_tpToStaUpdMuonAssociation2St"); //default

	/*makeAll("extractedGlobalMuons_tpToGlbSelMuonAssociation"); //track purity + valid hit + matching
	makeAll("extractedGlobalMuons_tpToGlbSel2MuonAssociation"); //track purity + valid hit
	makeAll("extractedGlobalMuons_tpToGlbSel3MuonAssociation"); //track and muon purity + valid hit + matching
	makeAll("extractedGlobalMuons_tpToGlbSel4MuonAssociation"); //track and muon purity + valid hit 
	makeAll("extractedGlobalMuons_tpToGlbMuonAssociation"); //default

	makeAll("bestMuonLoose_tpToLooseMuonAssociation");
	makeAll("bestMuonTight_tpToTightMuonAssociation");

	makeAll("bestMuonLoose_tpToLooseSelMuonAssociation");
	makeAll("bestMuonTight_tpToTightSelMuonAssociation");

	makeAll("bestMuonLoose_tpToLooseSel2MuonAssociation");
	makeAll("bestMuonTight_tpToTightSel2MuonAssociation");

	makeAll("bestMuonLoose_tpToLooseSel3MuonAssociation");
	makeAll("bestMuonTight_tpToTightSel3MuonAssociation");
	
	makeAll2("extractedGlobalMuons_tpToGlbSel2MuonAssociation", "extractedGlobalMuons_tpToGlbSelMuonAssociation");
	makeAll2("extractedGlobalMuons_tpToGlbSel4MuonAssociation", "extractedGlobalMuons_tpToGlbSel3MuonAssociation");*/
}

