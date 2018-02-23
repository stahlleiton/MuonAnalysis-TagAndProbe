#include "TnPEffDraw_singleFile.C"

void pPb_vs_PbP (const char* file_pPb, const char* file_PbP, const char* fullpathtodataset="tpTree/Iso_etadep/fit_eff") {
   TFile *_file0 = TFile::Open(file_pPb);
   TFile *_file1 = TFile::Open(file_PbP);
   TH1F *haxes = new TH1F("haxes","haxes;#eta;Efficiency",1,-2.4,2.4);
   haxes->GetYaxis()->SetRangeUser(0.9,1);
   TCanvas *c1 = new TCanvas();
   haxes->Draw();

   TGraphAsymmErrors *tg0 = plotEff_1bin((RooDataSet*) _file0->Get(fullpathtodataset),1,"eta");
   tg0->SetLineColor(kRed);
   tg0->SetMarkerColor(kRed);
   tg0->Draw("P");
   TGraphAsymmErrors *tg1 = plotEff_1bin((RooDataSet*) _file1->Get(fullpathtodataset),1,"eta");
   tg1->SetLineColor(kBlue);
   tg1->SetMarkerColor(kBlue);
   tg1->Draw("P");

   TLegend *tleg = new TLegend(0.67,0.19,0.86,0.36);
   tleg->SetBorderSize(0);
   tleg->AddEntry(tg0,"pPb","lp");
   tleg->AddEntry(tg1,"PbP","lp");
   tleg->Draw();

   cout << "Differences: \neta : diff : differr" << endl;

   // now check differences
   TH1F *hpull = new TH1F("hpull","pulls;Pull;Entries",20,-5,5);
   for (int i=0; i<tg0->GetN(); i++) {
      double dy = tg0->GetY()[i] - tg1->GetY()[i];
      double erry0 = (tg0->GetEYlow()[i]+tg0->GetEYhigh()[i])/2.;
      double erry1 = (tg1->GetEYlow()[i]+tg1->GetEYhigh()[i])/2.;
      double erry = sqrt(erry0*erry0+erry1*erry1);
      hpull->Fill(dy/erry);

      // also print the differences
      cout << "[" << tg0->GetX()[i]-tg0->GetEXlow()[i] << ", " << tg0->GetX()[i]+tg0->GetEXhigh()[i] << "] : " << dy << " : " << erry << endl;
   }
   TCanvas *c2 = new TCanvas();
   hpull->Draw();
   hpull->Fit("gaus");
}
