#include "TFile.h"
#include "TH1F.h"
#include "TString.h"

TH1F* variance(vector<TH1F*> input, bool doquadsum=false);
TH1F* hmax(TH1F *hpl, TH1F *hmi);
void print(TH1F* hist);
void addcst(TH1F* hist, double cst);
void habs(TH1F* hist);

void validateUncertPbPb_step2() {
   TFile *f = new TFile("histos_pbpb.root");
   f->cd();

   TCanvas *c1 = new TCanvas();
   TH1F *haxes = new TH1F("haxes","haxes",1,0,30);
   haxes->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   haxes->GetYaxis()->SetTitle("Efficiency");
   haxes->GetYaxis()->SetRangeUser(-0.15,0.15);

   TLegend *tleg = new TLegend(0.4,0.2,0.9,0.5);
   tleg->SetBorderSize(0);

   for (int ieta=0; ieta<6; ieta++) { // 6
      TString seta = Form("%d_%d",ieta*4,(ieta+1)*4);
      c1->Clear();
      haxes->Draw();
      tleg->SetHeader(Form("PbPb J/#psi, %.1f<|y|<%.1f",0.4*ieta,0.4*(ieta+1)));

      TH1F *hnom = (TH1F*) f->Get(TString("hnum_")+seta);

      // all, syst
      TH1F *hall_pl = (TH1F*) f->Get(TString("hnum_allpl_")+seta);
      hall_pl->Divide(hnom);
      addcst(hall_pl,-1);
      hall_pl->SetMarkerColor(kCyan+1);
      hall_pl->SetLineColor(kCyan+1);
      // hall_pl->Draw("hist same");
      // print(hall_pl);
      TH1F *hall_mi = (TH1F*) f->Get(TString("hnum_allmi_")+seta);
      hall_mi->Divide(hnom);
      addcst(hall_mi,-1);
      hall_mi->SetMarkerColor(kCyan+1);
      hall_mi->SetLineColor(kCyan+1);
      // hall_mi->Draw("hist same");
      // print(hall_mi);
      TH1F *hall_plmi = hmax(hall_pl,hall_mi);
      hall_plmi->SetMarkerColor(kCyan+1);
      hall_plmi->SetLineColor(kCyan+1);
      hall_plmi->SetLineWidth(2);
      hall_plmi->Draw("hist same");
      if (ieta==0) tleg->AddEntry(hall_plmi,"All-in-one (syst)","l");

      // all, stat
      vector<TH1F*> vhall_stat;
      for (int ivar=1; ivar<=100; ivar++) {
         vhall_stat.push_back((TH1F*) f->Get(TString(Form("hnum_all%i_",ivar))+seta));
         vhall_stat.back()->Divide(hnom);
      }
      TH1F *hall_stat = variance(vhall_stat);
      hall_stat->SetLineColor(kRed);
      hall_stat->SetMarkerColor(kRed);
      hall_stat->SetLineWidth(2);
      hall_stat->Draw("hist same");
      // print(hall_stat);
      if (ieta==0) tleg->AddEntry(hall_stat,"All-in-one (stat)","l");

      // trigger
      TH1F *htrg_pl = (TH1F*) f->Get(TString("hnum_trgpl_")+seta);
      htrg_pl->Divide(hnom);
      addcst(htrg_pl,-1);
      // print(htrg_pl);
      TH1F *htrg_mi = (TH1F*) f->Get(TString("hnum_trgmi_")+seta);
      htrg_mi->Divide(hnom);
      addcst(htrg_mi,-1);
      // print(htrg_mi);
      TH1F *htrg_b = (TH1F*) f->Get(TString("hnum_trgb_")+seta);
      htrg_b->Divide(hnom);
      addcst(htrg_b,-1);
      habs(htrg_b);
      // print(htrg_b);
      TH1F *htrg_max = hmax(htrg_pl,htrg_mi);
      vector<TH1F*> vhtrg_stat;
      for (int ivar=1; ivar<=100; ivar++) {
         vhtrg_stat.push_back((TH1F*) f->Get(TString(Form("hnum_trg%i_",ivar))+seta));
         vhtrg_stat.back()->Divide(hnom);
      }
      TH1F *htrg_stat = variance(vhtrg_stat);

      // MuID
      TH1F *hmuid_nom = (TH1F*) f->Get(TString("hnum_muid0_")+seta);
      hmuid_nom->Divide(hnom);
      addcst(hmuid_nom,-1);
      // print(hmuid_nom);
      TH1F *hmuid_pl = (TH1F*) f->Get(TString("hnum_muidpl_")+seta);
      hmuid_pl->Divide(hnom);
      addcst(hmuid_pl,-1);
      // print(hmuid_pl);
      TH1F *hmuid_mi = (TH1F*) f->Get(TString("hnum_muidmi_")+seta);
      hmuid_mi->Divide(hnom);
      addcst(hmuid_mi,-1);
      // print(hmuid_mi);
      TH1F *hmuid_b = (TH1F*) f->Get(TString("hnum_muidb_")+seta);
      hmuid_b->Divide(hnom);
      addcst(hmuid_b,-1);
      habs(hmuid_b);
      // print(hmuid_b);
      TH1F *hmuid_max = hmax(hmuid_pl,hmuid_mi);
      hmuid_max = hmax(hmuid_max,hmuid_b);
      vector<TH1F*> vhmuid_stat;
      for (int ivar=1; ivar<=100; ivar++) {
         vhmuid_stat.push_back((TH1F*) f->Get(TString(Form("hnum_muid%i_",ivar))+seta));
         vhmuid_stat.back()->Divide(hnom);
      }
      TH1F *hmuid_stat = variance(vhmuid_stat);

      // STA
      TH1F *hsta_nom = (TH1F*) f->Get(TString("hnum_sta0_")+seta);
      hsta_nom->Divide(hnom);
      addcst(hsta_nom,-1);
      // print(hsta_nom);
      TH1F *hsta_pl = (TH1F*) f->Get(TString("hnum_stapl_")+seta);
      hsta_pl->Divide(hnom);
      addcst(hsta_pl,-1);
      // print(hsta_pl);
      TH1F *hsta_mi = (TH1F*) f->Get(TString("hnum_stami_")+seta);
      hsta_mi->Divide(hnom);
      addcst(hsta_mi,-1);
      // print(hsta_mi);
      TH1F *hsta_b = (TH1F*) f->Get(TString("hnum_stab_")+seta);
      hsta_b->Divide(hnom);
      addcst(hsta_b,-1);
      habs(hsta_b);
      // print(hsta_b);
      TH1F *hsta_max = hmax(hsta_pl,hsta_mi);
      hsta_max = hmax(hsta_max,hsta_b);
      vector<TH1F*> vhsta_stat;
      for (int ivar=1; ivar<=100; ivar++) {
         vhsta_stat.push_back((TH1F*) f->Get(TString(Form("hnum_sta%i_",ivar))+seta));
         vhsta_stat.back()->Divide(hnom);
      }
      TH1F *hsta_stat = variance(vhsta_stat);

      // combine all
      vector<TH1F*> vhcombo_syst;
      vhcombo_syst.push_back(htrg_max);
      vhcombo_syst.push_back(htrg_b);
      // vhcombo_syst.push_back(hmuid_nom);
      vhcombo_syst.push_back(hmuid_max);
      // vhcombo_syst.push_back(hmuid_b);
      // vhcombo_syst.push_back(hsta_nom);
      vhcombo_syst.push_back(hsta_max);
      // vhcombo_syst.push_back(hsta_b);
      TH1F *hcombo_syst = variance(vhcombo_syst,true);
      hcombo_syst->SetLineColor(kBlue+2);
      hcombo_syst->SetMarkerColor(kBlue+2);
      hcombo_syst->SetLineWidth(2);
      hcombo_syst->Draw("hist same");
      if (ieta==0) tleg->AddEntry(hcombo_syst,"Combo (syst)","l");
      // print(hcombo_syst);
      vector<TH1F*> vhcombo_stat;
      vhcombo_stat.push_back(htrg_stat);
      vhcombo_stat.push_back(hmuid_stat);
      vhcombo_stat.push_back(hsta_stat);
      TH1F *hcombo_stat = variance(vhcombo_stat,true);
      hcombo_stat->SetLineColor(kMagenta+1);
      hcombo_stat->SetMarkerColor(kMagenta+1);
      hcombo_stat->SetLineWidth(2);
      hcombo_stat->Draw("hist same");
      if (ieta==0) tleg->AddEntry(hcombo_stat,"Combo (stat)","l");
      // print(hcombo_stat);

      tleg->Draw();
      c1->SaveAs(TString("c_") + seta + ".pdf");
   }
}

TH1F* variance(vector<TH1F*> input, bool doquadsum) {
   int n = input.size();
   TH1F *ans = (TH1F*) input[0]->Clone(TString(input[0]->GetName()) + (doquadsum ? "_quadsum" : "_variance"));
   TH1F *ans2 = (TH1F*) input[0]->Clone(TString(input[0]->GetName()) + "tmp");
   for (int i=0; i<=ans->GetNbinsX()+1; i++) {
      ans->SetBinContent(i,0);
      ans2->SetBinContent(i,0);
      ans->SetBinError(i,0);
      ans2->SetBinError(i,0);
   }

   for (int i=0; i<input.size(); i++) {
      for (int j=0; j<=ans->GetNbinsX()+1; j++) {
         ans->SetBinContent(j,ans->GetBinContent(j)+(input[i]->GetBinContent(j)));
         ans2->SetBinContent(j,ans2->GetBinContent(j)+pow(input[i]->GetBinContent(j),2));
      }
   }

   if (doquadsum) {
      for (int j=0; j<=ans->GetNbinsX()+1; j++) {
         ans->SetBinContent(j,sqrt(ans2->GetBinContent(j)));
      }
   } else {
      for (int j=0; j<=ans->GetNbinsX()+1; j++) {
         double xmean = ans->GetBinContent(j)/input.size();
         ans2->SetBinContent(j,max(0.,(ans2->GetBinContent(j) - input.size() * pow(xmean,2)) / (input.size()-1)));
         ans->SetBinContent(j,sqrt(ans2->GetBinContent(j)));
      }
   }

   delete ans2;
   return ans;
}

TH1F* hmax(TH1F *hpl, TH1F *hmi) {
   TH1F *ans = (TH1F*) hpl->Clone(TString(hpl->GetName()) + "max");
   for (int i=0; i<=ans->GetNbinsX()+1; i++) {
      double xpl = hpl->GetBinContent(i);
      double xmi = hmi->GetBinContent(i);
      ans->SetBinContent(i,max(fabs(xpl),fabs(xmi)));
      ans->SetBinError(i,0);
   }
   return ans;
}

void print(TH1F* hist) {
   cout << hist->GetName() << ":" << endl;
   for (int i=1; i<hist->GetNbinsX(); i++) cout << hist->GetBinCenter(i) << "->" << hist->GetBinContent(i) << "+-" << hist->GetBinError(i) << ", ";
   cout << endl;
}

void addcst(TH1F* hist, double cst) {
   for (int i=0; i<=hist->GetNbinsX()+1; i++) hist->SetBinContent(i,hist->GetBinContent(i)+cst);
}

void habs(TH1F* hist) {
   for (int i=0; i<=hist->GetNbinsX()+1; i++) hist->SetBinContent(i,fabs(hist->GetBinContent(i)));
}
