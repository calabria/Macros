{

  TFile * f1 = TFile::Open("histo_data_AN1.root");
  TFile * f2 = TFile::Open("histo_data_FR1.root");
  TFile * f3 = TFile::Open("DiBosonsNoWW.root");
  TFile * f4 = TFile::Open("histo_data_AnDir.root");//Na serv a nudd

  TCanvas * canvas = new TCanvas("canvas","canvas",700,700);

  f1->cd();
  f1->cd("CompCandHistosAfterSelLt");
  TH2F * histoData2D = (TH2F*)gDirectory->Get("hDiTauCandSSEtaVsPtAsym");	   	
  std::cout<<"X bins: "<<histoData2D->GetNbinsX()<<" Y bins: "<<histoData2D->GetNbinsY()<<std::endl;

  f2->cd("CompCandHistosAfterSelLt1");
  TH2F * histoFake2D_v1 = (TH2F*)gDirectory->Get("hDiTauCandSSEtaVsPtAsym");	
  f2->cd();
  f2->cd("CompCandHistosAfterSelLt2");
  TH2F * histoFake2D_v2 = (TH2F*)gDirectory->Get("hDiTauCandSSEtaVsPtAsym");	
  f2->cd();
  f2->cd("CompCandHistosAfterSelLt3");  
  TH2F * histoFake2D_v3 = (TH2F*)gDirectory->Get("hDiTauCandSSEtaVsPtAsym");	

  f3->cd();
  f3->cd("CompCandHistosAfterSelLt");
  TH2F * histoDiBosons2D = (TH2F*)gDirectory->Get("hDiTauCandSSEtaVsPtAsym");

  f4->cd();
  f4->cd("CompCandHistosAfterSelLt");
  TH2F * histoAnDir2D = (TH2F*)gDirectory->Get("hDiTauCandSSEtaVsPt");//Analisi diretta

  THStack * hs_v1 = new THStack("","");
  THStack * hs_v2 = new THStack("","");
  THStack * hs_v3 = new THStack("","");

  hs_v1->Add(histoFake2D_v1);
  hs_v1->Add(histoDiBosons2D);
  hs_v2->Add(histoFake2D_v2);
  hs_v2->Add(histoDiBosons2D);
  hs_v3->Add(histoFake2D_v3);
  hs_v3->Add(histoDiBosons2D);

  TH2F * stack_v1 = (TH2F*)hs_v1->GetStack()->Last()->Clone();
  TH2F * stack_v2 = (TH2F*)hs_v2->GetStack()->Last()->Clone();
  TH2F * stack_v3 = (TH2F*)hs_v3->GetStack()->Last()->Clone();

  TH2F * histoRatio_v1 = (TH2F*)histoData2D->Clone();
  TH2F * histoRatio_v2 = (TH2F*)histoData2D->Clone();
  TH2F * histoRatio_v3 = (TH2F*)histoData2D->Clone();

  /*stack_v1->RebinX(5);
  stack_v2->RebinX(5);
  stack_v3->RebinX(5);

  stack_v1->RebinY(4);
  stack_v2->RebinY(4);
  stack_v3->RebinY(4);

  histoAnDir2D->RebinX(5);
  histoRatio_v1->RebinX(5);
  histoRatio_v2->RebinX(5);
  histoRatio_v3->RebinX(5);

  histoAnDir2D->RebinY(4);
  histoRatio_v1->RebinY(4);
  histoRatio_v2->RebinY(4);
  histoRatio_v3->RebinY(4);*/

  histoRatio_v1->Draw("TEXT");

  std::cout<<"X bins: "<<histoRatio_v1->GetNbinsX()<<" Y bins: "<<histoRatio_v1->GetNbinsY()<<std::endl;

  int xBins = histoRatio_v1->GetNbinsX();
  int yBins = histoRatio_v1->GetNbinsY();

  histoRatio_v1->Divide(stack_v1);
  histoRatio_v2->Divide(stack_v2);
  histoRatio_v3->Divide(stack_v3);

  TCanvas * canvasLego = new TCanvas("canvasLego","canvasLego",700,700);

  histoRatio_v1->Draw("LEGO");
  histoRatio_v2->SetLineColor(2);
  histoRatio_v2->Draw("SAMELEGO");
  histoRatio_v3->SetLineColor(3);
  histoRatio_v3->Draw("SAMELEGO");

  TH2F * matrix_v1 = (TH2F*)histoRatio_v1->Clone();
  TH2F * matrix_v2 = (TH2F*)histoRatio_v1->Clone();
  TH2F * matrix_v3 = (TH2F*)histoRatio_v1->Clone();

  std::ofstream outputTXT1;
  std::ofstream outputTXT2;
  std::ofstream outputTXT3;
  outputTXT1.open("matrix1.txt");
  outputTXT2.open("matrix2.txt");
  outputTXT3.open("matrix3.txt");

  float dN1tot2 = 0;
  float ave1 = 0;
  float weight1 = 0;

  for(int i=1; i<=xBins; i++){

	float binMin = (i-1)*histoRatio_v1->GetBinWidth(i);
	float binMax = (i)*histoRatio_v1->GetBinWidth(i);
	outputTXT1<<"p_T in "<<"["<<binMin<<","<<binMax<<"]: ";

	for(int j=1; j<=yBins; j++){

		std::cout<<"("<<i<<","<<j<<")"<<std::endl;
		std::cout<<i*histoRatio_v1->GetBinWidth(i)<<" , "<<(-3+6/yBins*j)<<std::endl;
		std::cout<<histoRatio_v1->GetBinContent(i,j)<<" +/- "<<histoRatio_v1->GetBinError(i,j)<<std::endl;
		matrix_v1->SetBinContent(i,j,histoRatio_v1->GetBinContent(i,j));
		matrix_v1->SetBinError(i,j,histoRatio_v1->GetBinError(i,j));

		outputTXT1<<" | "<<histoRatio_v1->GetBinContent(i,j)<<" +/- "<<histoRatio_v1->GetBinError(i,j);

		if(histoAnDir2D->GetBinError(i,j)){
		float df1 = histoRatio_v1->GetBinError(i,j) / histoRatio_v1->GetBinContent(i,j);
		float dN0 = histoAnDir2D->GetBinError(i,j) / histoAnDir2D->GetBinContent(i,j);
		float dN12 = df1*df1 + dN0*dN0;
   		dN1tot2 += dN12;
		}
		if(histoRatio_v1->GetBinContent(i,j)){
		float weight = 1/(histoRatio_v1->GetBinError(i,j)*histoRatio_v1->GetBinError(i,j));
		ave1 += (histoRatio_v1->GetBinContent(i,j)*weight);
		weight1 += weight;
		}

	} 

	outputTXT1<<std::endl;

  }

  ave1 /= weight1;


  float dN2tot2 = 0;
  float ave2 = 0;
  float weight2 = 0;

  for(int i=1; i<=xBins; i++){

	float binMin = (i-1)*histoRatio_v2->GetBinWidth(i);
	float binMax = (i)*histoRatio_v2->GetBinWidth(i);
	outputTXT2<<"p_T in "<<"["<<binMin<<","<<binMax<<"]: ";

	for(int j=1; j<=yBins; j++){

		std::cout<<"("<<i<<","<<j<<")"<<std::endl;
		std::cout<<i*histoRatio_v2->GetBinWidth(i)<<" , "<<(-3+6/yBins*j)<<std::endl;
		std::cout<<histoRatio_v2->GetBinContent(i,j)<<" +/- "<<histoRatio_v2->GetBinError(i,j)<<std::endl;
		matrix_v2->SetBinContent(i,j,histoRatio_v2->GetBinContent(i,j));
		matrix_v2->SetBinError(i,j,histoRatio_v2->GetBinError(i,j));

		outputTXT2<<" | "<<histoRatio_v2->GetBinContent(i,j)<<" +/- "<<histoRatio_v2->GetBinError(i,j);

		if(histoAnDir2D->GetBinError(i,j)){
		float df2 = histoRatio_v2->GetBinError(i,j) / histoRatio_v2->GetBinContent(i,j);
		float dN0 = histoAnDir2D->GetBinError(i,j) / histoAnDir2D->GetBinContent(i,j);
		float dN22 = df2*df2 + dN0*dN0;
   		dN2tot2 += dN22;
		}
		if(histoRatio_v2->GetBinContent(i,j)){
		float weight = 1/(histoRatio_v2->GetBinError(i,j)*histoRatio_v2->GetBinError(i,j));
		ave2 += (histoRatio_v2->GetBinContent(i,j)*weight);
		weight2 += weight;
		}


	} 

	outputTXT2<<std::endl;

  }

  ave2 /= weight2;


  float dN3tot2 = 0;
  float ave3 = 0;
  float weight3 = 0;

  for(int i=1; i<=xBins; i++){

	float binMin = (i-1)*histoRatio_v3->GetBinWidth(i);
	float binMax = (i)*histoRatio_v3->GetBinWidth(i);
	outputTXT3<<"p_T in "<<"["<<binMin<<","<<binMax<<"]: ";

	for(int j=1; j<=yBins; j++){

		std::cout<<"("<<i<<","<<j<<")"<<std::endl;
		std::cout<<i*histoRatio_v3->GetBinWidth(i)<<" , "<<(-3+6/yBins*j)<<std::endl;
		std::cout<<histoRatio_v3->GetBinContent(i,j)<<" +/- "<<histoRatio_v3->GetBinError(i,j)<<std::endl;
		matrix_v3->SetBinContent(i,j,histoRatio_v3->GetBinContent(i,j));
		matrix_v3->SetBinError(i,j,histoRatio_v3->GetBinError(i,j));

		outputTXT3<<" | "<<histoRatio_v3->GetBinContent(i,j)<<" +/- "<<histoRatio_v3->GetBinError(i,j);

		if(histoAnDir2D->GetBinError(i,j)){
		float df3 = histoRatio_v3->GetBinError(i,j) / histoRatio_v3->GetBinContent(i,j);
		float dN0 = histoAnDir2D->GetBinError(i,j) / histoAnDir2D->GetBinContent(i,j);
		float dN32 = df3*df3 + dN0*dN0;
   		dN3tot2 += dN32;
		}
		if(histoRatio_v3->GetBinContent(i,j)){
		float weight = 1/(histoRatio_v3->GetBinError(i,j)*histoRatio_v3->GetBinError(i,j));
		ave3 += (histoRatio_v3->GetBinContent(i,j)*weight);
		weight3 += weight;
		}

	} 

	outputTXT3<<std::endl;

  }

  ave3 /= weight3;

  std::cout<<"SysErr1: "<<sqrt(dN1tot2)<<std::endl;
  std::cout<<"SysErr2: "<<sqrt(dN2tot2)<<std::endl;
  std::cout<<"SysErr3: "<<sqrt(dN3tot2)<<std::endl;
  std::cout<<"Ave1: "<<ave1<<" +/- "<<sqrt(1/weight1)<<std::endl;
  std::cout<<"Ave2: "<<ave2<<" +/- "<<sqrt(1/weight2)<<std::endl;
  std::cout<<"Ave3: "<<ave3<<" +/- "<<sqrt(1/weight3)<<std::endl;

  gStyle->SetPaintTextFormat("4.3f");

  TCanvas * canvas1 = new TCanvas("canvas1","canvas1",1300,700);
  matrix_v1->SetStats(kFALSE);
  matrix_v1->SetTitle("Method 1");
  matrix_v1->Draw("TEXTCOLZE");
  canvas1->SaveAs("matrix_v1.png");

  TCanvas * canvas2 = new TCanvas("canvas2","canvas2",1300,700);
  matrix_v2->SetStats(kFALSE);
  matrix_v2->SetTitle("Method 2");
  matrix_v2->Draw("TEXTCOLZE");
  canvas2->SaveAs("matrix_v2.png");

  TCanvas * canvas3 = new TCanvas("canvas3","canvas3",1300,700);
  matrix_v3->SetStats(kFALSE);
  matrix_v3->SetTitle("Method 3");
  matrix_v3->Draw("TEXTCOLZE");
  canvas3->SaveAs("matrix_v3.png");

  outputTXT1.close();
  outputTXT2.close();
  outputTXT3.close();


}
