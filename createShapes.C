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


void saveShapes(std::string channel = "ett", int isFR = 1){

	std::vector<std::string> names, histoNamesForSaving;
	names.push_back("histo_data_AN1.root");
	names.push_back("histo_TauPlusX_RunD_PRv1_FR1_1.root");
	names.push_back("WZ.root");
	names.push_back("ZZ.root");
	names.push_back("WH_110.root");
	names.push_back("WH_115.root");
	names.push_back("WH_120.root");
	names.push_back("WH_125.root");
	names.push_back("WH_130.root");
	names.push_back("WH_135.root");
	names.push_back("WH_140.root");
	names.push_back("WH_145.root");

	histoNamesForSaving.push_back("data_obs");
	histoNamesForSaving.push_back("fakes");
	histoNamesForSaving.push_back("wz");
	histoNamesForSaving.push_back("zz");
	histoNamesForSaving.push_back("WH110");
	histoNamesForSaving.push_back("WH115");
	histoNamesForSaving.push_back("WH120");
	histoNamesForSaving.push_back("WH125");
	histoNamesForSaving.push_back("WH130");
	histoNamesForSaving.push_back("WH135");
	histoNamesForSaving.push_back("WH140");
	histoNamesForSaving.push_back("WH145");

	std::string nameSaving; 
	if(isFR == 1) nameSaving = "vhtt_ltt.inputs-sm-8TeV_M1";
	else if(isFR == 2) nameSaving = "vhtt_ltt.inputs-sm-8TeV_M2";
	else if(isFR == 3) nameSaving = "vhtt_ltt.inputs-sm-8TeV_M3";
	else nameSaving = "vhtt_ltt.inputs-sm-8TeV";

	TFile *newRootFile = new TFile((nameSaving+".root").c_str(),"RECREATE");
	newRootFile->mkdir(channel.c_str());

	for(int i = 0; i < names.size(); i++){

		TFile * f1 = TFile::Open(names[i].c_str());
		std::cout<<"File: "<<names[i].c_str()<<std::endl;
		f1->cd();

		if(i != 1) histoTMP = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt/VisMass");
		else if(i == 1 && isFR == 1){
			//histoTMP = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt1/VisMass");
			TH1F * histoTMPCorr = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt1/VisMassCorr");
			TH1F * histoTMPUp = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt1/VisMassUp");
			TH1F * histoTMPDown = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt1/VisMassDown");

			histoTMP = (TH1F*)histoTMPCorr->Clone();

			/*histoTMPCorr->Draw();
			histoTMPCorr->SetMaximum(4);
			histoTMPUp->SetLineColor(2);
			histoTMPUp->Draw("SAME");
			histoTMPDown->SetLineColor(4);
			histoTMPDown->Draw("SAME");*/
	
			for(int j = 1; j < histoTMP->GetSize()-1; j++){

				float centralValue = histoTMPCorr->GetBinContent(j);
				float upperValue = histoTMPUp->GetBinContent(j);
				float lowerValue = histoTMPDown->GetBinContent(j);

				std::cout<<centralValue<<" "<<(upperValue-centralValue)<<" "<<(centralValue-lowerValue)<<std::endl;

				histoTMP->SetBinError(j, upperValue-centralValue);

			}

			//histoTMP->Draw();

		}
		else if(i == 1 && isFR == 2){
 			//histoTMP = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt2/VisMass");
			TH1F * histoTMPCorr = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt2/VisMassCorr");
			TH1F * histoTMPUp = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt2/VisMassUp");
			TH1F * histoTMPDown = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt2/VisMassDown");

			histoTMP = (TH1F*)histoTMPCorr->Clone();

			for(int j = 1; j < histoTMP->GetSize()-1; j++){

				float centralValue = histoTMPCorr->GetBinContent(j);
				float upperValue = histoTMPUp->GetBinContent(j);
				float lowerValue = histoTMPDown->GetBinContent(j);

				std::cout<<centralValue<<" "<<(upperValue-centralValue)<<" "<<(centralValue-lowerValue)<<std::endl;

				histoTMP->SetBinError(j, upperValue-centralValue);

			}

			//histoTMP->Draw();

		}
		else if(i == 1 && isFR == 3){
			//histoTMP = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt3/VisMass");
			TH1F * histoTMPCorr = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt3/VisMassCorr");
			TH1F * histoTMPUp = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt3/VisMassUp");
			TH1F * histoTMPDown = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt3/VisMassDown");

			histoTMP = (TH1F*)histoTMPCorr->Clone();

			for(int j = 1; j < histoTMP->GetSize()-1; j++){

				float centralValue = histoTMPCorr->GetBinContent(j);
				float upperValue = histoTMPUp->GetBinContent(j);
				float lowerValue = histoTMPDown->GetBinContent(j);

				std::cout<<centralValue<<" "<<(upperValue-centralValue)<<" "<<(centralValue-lowerValue)<<std::endl;

				histoTMP->SetBinError(j, upperValue-centralValue);

			}

			//histoTMP->Draw();

		}

		newRootFile->cd(channel.c_str());
		if(histoTMP) histoTMP->Write(histoNamesForSaving[i].c_str());

	}

	newRootFile->Close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TH1F * buildMassShape(TFile * f1, int type){

	std::stringstream name1;
	name1 << "CompCandHistosAfterSelLt" << type << "/" << "VisMassCorr";
	std::string s1 = name1.str();

	std::cout<<s1.c_str()<<std::endl;

	TH1F * histoTMPCorr = (TH1F*)gDirectory->Get(s1.c_str());
	TH1F * histoToReturn = (TH1F*)histoTMPCorr->Clone();

	for(int k = 1; k < histoToReturn->GetSize()-1; k++){

		double binErr = 0;
	  
		for(int i = 0; i < 5; i++){

			for(int j = 0; j < 6 ; j++){

				std::stringstream name2;
				std::stringstream name3;

				name2 << "CompCandHistosAfterSelLt" << type << "/" << "VisMassUp" << i << j;
				name3 << "CompCandHistosAfterSelLt" << type << "/" << "VisMassDown" << i << j;

				std::string s2 = name2.str();
				std::string s3 = name3.str();

				//std::cout<<name1.str()<<" "<<name2.str()<<" "<<name3.str()<<std::endl;
			
				TH1F * histoTMPUp = (TH1F*)gDirectory->Get(s2.c_str());
				TH1F * histoTMPDown = (TH1F*)gDirectory->Get(s3.c_str());

				float tempErr = (histoTMPUp->GetBinError(k) + histoTMPDown->GetBinError(k)) / 2;
				//std::cout<<tempErr<<std::endl;

				//std::cout<<sqrt(binErr)<<std::endl;
				binErr += tempErr*tempErr;
				//std::cout<<sqrt(binErr)<<std::endl;

			}

	  	}

		std::cout<<"Final Err: "<<sqrt(binErr)<<" %: "<<sqrt(binErr)/histoToReturn->GetBinContent(k)<<std::endl;
		histoToReturn->SetBinError(k,sqrt(binErr));

	}

	return histoToReturn;

}

void buildMatrix(TFile * f1, int type){

    	TCanvas * cvStack = new TCanvas("pads","pads",1250,700);
	cvStack->Divide(5,6);
	  
		for(int i = 0; i < 5; i++){

			for(int j = 0; j < 6 ; j++){

				cvStack->cd( (i+1) + abs(5*(j-5)) );

				//std::cout<<( (i+1) + abs(5*(j-5)) )<<std::endl;

				std::stringstream name1;
				std::stringstream name2;
				std::stringstream name3;

				name1 << "CompCandHistosAfterSelLt" << type << "/" << "VisMassCorr" << i << j;
				name2 << "CompCandHistosAfterSelLt" << type << "/" << "VisMassUp" << i << j;
				name3 << "CompCandHistosAfterSelLt" << type << "/" << "VisMassDown" << i << j;

				std::string s1 = name1.str();
				std::string s2 = name2.str();
				std::string s3 = name3.str();

				//std::cout<<name1.str()<<" "<<name2.str()<<" "<<name3.str()<<std::endl;
			
				TH1F * histoTMPCorr = (TH1F*)gDirectory->Get(s1.c_str());
				TH1F * histoTMPUp = (TH1F*)gDirectory->Get(s2.c_str());
				TH1F * histoTMPDown = (TH1F*)gDirectory->Get(s3.c_str());

				histoTMPCorr->SetLineColor(1);
				histoTMPUp->SetLineColor(2);
				histoTMPDown->SetLineColor(4);

				histoTMPUp->Draw();
				histoTMPCorr->Draw("SAME");
				histoTMPDown->Draw("SAME");

			}

	  	}

	cvStack->Draw();
	std::stringstream ss;
	ss<<"matrix"<<type<<".pdf";
	std::string save = ss.str();
	cvStack->SaveAs(save.c_str());

}

void saveShapes2(std::string channel = "ett", int isFR = 1){

	std::vector<std::string> names, histoNamesForSaving;
	names.push_back("histo_data_AN1.root");
	names.push_back("histo_fr_corr.root");
	names.push_back("WZ.root");
	names.push_back("ZZ.root");
	names.push_back("WH_110.root");
	names.push_back("WH_115.root");
	names.push_back("WH_120.root");
	names.push_back("WH_125.root");
	names.push_back("WH_130.root");
	names.push_back("WH_135.root");
	names.push_back("WH_140.root");
	names.push_back("WH_145.root");

	histoNamesForSaving.push_back("data_obs");
	histoNamesForSaving.push_back("fakes");
	histoNamesForSaving.push_back("wz");
	histoNamesForSaving.push_back("zz");
	histoNamesForSaving.push_back("WH110");
	histoNamesForSaving.push_back("WH115");
	histoNamesForSaving.push_back("WH120");
	histoNamesForSaving.push_back("WH125");
	histoNamesForSaving.push_back("WH130");
	histoNamesForSaving.push_back("WH135");
	histoNamesForSaving.push_back("WH140");
	histoNamesForSaving.push_back("WH145");

	std::string nameSaving; 
	if(isFR == 1) nameSaving = "vhtt_ltt.inputs-sm-8TeV_M1G";
	else if(isFR == 2) nameSaving = "vhtt_ltt.inputs-sm-8TeV_M2G";
	else if(isFR == 3) nameSaving = "vhtt_ltt.inputs-sm-8TeV_M3G";
	else nameSaving = "vhtt_ltt.inputs-sm-8TeV";

	TFile *newRootFile = new TFile((nameSaving+".root").c_str(),"RECREATE");
	newRootFile->mkdir(channel.c_str());

	for(int i = 0; i < names.size(); i++){

		TFile * f1 = TFile::Open(names[i].c_str());
		std::cout<<"File: "<<names[i].c_str()<<std::endl;
		f1->cd();

		if(i != 1) histoTMP = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt/VisMass");
		else if(i == 1 && isFR == 1){

			//histoTMP = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt1/VisMass");
			TH1F * histoTMPCorr = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt1/VisMassCorr");
			TH1F * histoTMPUp = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt1/VisMassUp");
			TH1F * histoTMPDown = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt1/VisMassDown");

			histoTMP = (TH1F*)histoTMPCorr->Clone();

			for(int j = 1; j < histoTMP->GetSize()-1; j++){

				float centralValue = histoTMPCorr->GetBinContent(j);
				float upperValue = histoTMPUp->GetBinContent(j);
				float lowerValue = histoTMPDown->GetBinContent(j);

				//std::cout<<centralValue<<" "<<(upperValue-centralValue)<<" "<<(centralValue-lowerValue)<<std::endl;
				std::cout<<"ConsErr: "<<(upperValue-centralValue)<<" %: "<<(upperValue-centralValue)*100/centralValue<<std::endl;

				histoTMP->SetBinError(j, upperValue-centralValue);

			}

    			TCanvas * cvStack = new TCanvas("M1","M1",1250,700);

			histoTMP->GetXaxis()->SetTitle("M_{vis}^{#tau_{had}#tau_{had}} [GeV/c^{2}]");
			histoTMP->GetYaxis()->SetTitle("Entries/40 GeV/c^{2}");
			histoTMP->SetLineWidth(3);
			histoTMP->Draw();

			histoTMP = buildMassShape(f1,1); //
			histoTMP->SetLineColor(2);
			histoTMP->SetLineWidth(4);
			histoTMP->SetFillStyle(3004);
			histoTMP->SetFillColor(2);
			histoTMP->Draw("SAMEE2");

			cvStack->SaveAs("mass1.png");

			//buildMatrix(f1,1);

		}
		else if(i == 1 && isFR == 2){

			//histoTMP = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt2/VisMass");
			TH1F * histoTMPCorr = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt2/VisMassCorr");
			TH1F * histoTMPUp = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt2/VisMassUp");
			TH1F * histoTMPDown = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt2/VisMassDown");

			histoTMP = (TH1F*)histoTMPCorr->Clone();

			for(int j = 1; j < histoTMP->GetSize()-1; j++){

				float centralValue = histoTMPCorr->GetBinContent(j);
				float upperValue = histoTMPUp->GetBinContent(j);
				float lowerValue = histoTMPDown->GetBinContent(j);

				//std::cout<<centralValue<<" "<<(upperValue-centralValue)<<" "<<(centralValue-lowerValue)<<std::endl;
				std::cout<<"ConsErr: "<<(upperValue-centralValue)<<" %: "<<(upperValue-centralValue)*100/centralValue<<std::endl;

				histoTMP->SetBinError(j, upperValue-centralValue);

			}

    			TCanvas * cvStack = new TCanvas("M1","M1",1250,700);

			histoTMP->GetXaxis()->SetTitle("M_{vis}^{#tau_{had}#tau_{had}} [GeV/c^{2}]");
			histoTMP->GetYaxis()->SetTitle("Entries/40 GeV/c^{2}");
			histoTMP->Draw();
			histoTMP->SetLineWidth(3);

			histoTMP = buildMassShape(f1,2); //
			histoTMP->SetLineColor(2);
			histoTMP->SetLineWidth(4);
			histoTMP->SetFillStyle(3004);
			histoTMP->SetFillColor(2);
			histoTMP->Draw("SAMEE2");

			cvStack->SaveAs("mass2.png");

			//buildMatrix(f1,2);

		}
		else if(i == 1 && isFR == 3){

			//histoTMP = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt3/VisMass");
			TH1F * histoTMPCorr = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt3/VisMassCorr");
			TH1F * histoTMPUp = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt3/VisMassUp");
			TH1F * histoTMPDown = (TH1F*)gDirectory->Get("CompCandHistosAfterSelLt3/VisMassDown");

			histoTMP = (TH1F*)histoTMPCorr->Clone();

			for(int j = 1; j < histoTMP->GetSize()-1; j++){

				float centralValue = histoTMPCorr->GetBinContent(j);
				float upperValue = histoTMPUp->GetBinContent(j);
				float lowerValue = histoTMPDown->GetBinContent(j);

				//std::cout<<centralValue<<" "<<(upperValue-centralValue)<<" "<<(centralValue-lowerValue)<<std::endl;
				std::cout<<"ConsErr: "<<(upperValue-centralValue)<<" %: "<<(upperValue-centralValue)*100/centralValue<<std::endl;

				histoTMP->SetBinError(j, upperValue-centralValue);

			}

    			TCanvas * cvStack = new TCanvas("M1","M1",1250,700);

			histoTMP->GetXaxis()->SetTitle("M_{vis}^{#tau_{had}#tau_{had}} [GeV/c^{2}]");
			histoTMP->GetYaxis()->SetTitle("Entries/40 GeV/c^{2}");
			histoTMP->Draw();
			histoTMP->SetLineWidth(3);

			histoTMP = buildMassShape(f1,3); //
			histoTMP->SetLineColor(2);
			histoTMP->SetLineWidth(4);
			histoTMP->SetFillStyle(3004);
			histoTMP->SetFillColor(2);
			histoTMP->Draw("SAMEE2");

			cvStack->SaveAs("mass3.png");

			//buildMatrix(f1,3);

		}

		newRootFile->cd(channel.c_str());
		if(histoTMP) histoTMP->Write(histoNamesForSaving[i].c_str());

	}

	newRootFile->Close();
}

