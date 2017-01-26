#include "tnp_weight.h"
#include "TF1.h"
#include "TLegend.h"
#include "TH1.h"
#include "TCanvas.h"

Double_t tnp_weight_pbpb_wrapper(Double_t *x, Double_t *par) {
   if (par[2]<0.5) return tnp_weight_trg_pbpb(x[0],par[0],par[1]);
   else if (par[2]<1.5) return tnp_weight_muid_pbpb(x[0],par[0],par[1]);
   else if (par[2]<2.4) return tnp_weight_sta_pp(x[0],par[0],par[1]);
   else return tnp_weight_trk_pbpb(par[1]);
}
Double_t tnp_weight_pp_wrapper(Double_t *x, Double_t *par) {
   if (par[2]<0.5) return tnp_weight_trg_pp(x[0],par[0],par[1]);
   else if (par[2]<1.5) return tnp_weight_muid_pp(x[0],par[0],par[1]);
   else if (par[2]<2.5) return tnp_weight_sta_pp(x[0],par[0],par[1]);
   else return tnp_weight_trk_pp(par[1]);
}

float ptmin(float etamax) {
   float ans=0;
   if (etamax<1.2) ans = 3.5;
   else if (etamax<2.1) ans = 5.77-1.89*fabs(etamax);
   else ans = 1.8;
   // ans = (int) (ans*10.);
   // ans = ans/10.;
   return ans;
}

void plotSFs() {
   TCanvas *c1 = new TCanvas();
   TH1F *haxes = new TH1F("haxes",";p_{T} [GeV/c];Scale factor",1,0,30);
   TH1F *haxes20 = new TH1F("haxes20",";p_{T} [GeV/c];Scale factor",1,0,20);

   float *etamin=NULL, *etamax=NULL;
   float eta, ptminval, ptmaxval;

   etamin = new float[4]; etamin[0]=0.; etamin[1]=1.2; etamin[2]=1.8; etamin[3]=2.1;
   etamax = new float[4]; etamax[0]=1.2; etamax[1]=1.8; etamax[2]=2.1; etamax[3] = 2.4;

   const char* tags[4] = {"trg_","muid_","sta_","trk_"};
   const char* names[4] = {"Trigger","MuID","STA","Inner tracking"};
   const double range[4] = {0.5,0.15,0.15,0.05};

   for (int j=0; j<4; j++) {
      // pbpb
      for (int ieta=0; ieta<4; ieta++) {
         if (ieta<2) {
            haxes->GetYaxis()->SetRangeUser(1-1.2*range[j],1+range[j]);
            haxes->Draw();
         } else {
            haxes20->GetYaxis()->SetRangeUser(1-1.2*range[j],1+range[j]);
            haxes20->Draw();
         }

         TLegend *tleg = new TLegend(0.58,0.16,0.91,0.47);
         tleg->SetBorderSize(0);

         eta = (etamax[ieta]+etamin[ieta])/2.;
         ptminval = ptmin(etamax[ieta]);
         ptmaxval = (ieta<2) ? 30 : 20;
         if (j<3) { // no toys for TRK
            for (int i=1; i<=100; i++) {
               TF1 *fnom = new TF1(Form("f%i",i),tnp_weight_pbpb_wrapper,ptminval,ptmaxval,3);
               fnom->SetParameters(eta,i,j);
               fnom->SetLineColor(kBlack);
               fnom->Draw("same");
            }
         }
         TF1 *fp = new TF1("fp",tnp_weight_pbpb_wrapper,ptminval,ptmaxval,3);
         fp->SetParameters(eta,-1,j);
         fp->SetLineColor(kCyan);
         fp->Draw("same");
         TF1 *fm = new TF1("fm",tnp_weight_pbpb_wrapper,ptminval,ptmaxval,3);
         fm->SetParameters(eta,-2,j);
         fm->SetLineColor(kCyan);
         fm->Draw("same");
         TF1 *fbinned = new TF1("fbinned",tnp_weight_pbpb_wrapper,ptminval,ptmaxval,3);
         fbinned->SetParameters(eta,-10,j);
         fbinned->SetLineColor(kGreen+2);
         if (j==0) fbinned->Draw("same"); // binned only for Trg
         TF1 *fnom = new TF1("fnom",tnp_weight_pbpb_wrapper,ptminval,ptmaxval,3);
         fnom->SetParameters(eta,0,j);
         fnom->SetLineColor(kRed);
         fnom->Draw("same");

         tleg->SetHeader(Form("#splitline{PbPb, %s}{#eta #in [%.1f,%.1f], p_{T}>%.1f GeV/c}",names[j],etamin[ieta],etamax[ieta],ptminval));
         tleg->AddEntry(fnom,"Nominal","l");
         if (j<3) tleg->AddEntry("f1","stat (100 toys)","l");
         tleg->AddEntry(fp,"syst (+/1#sigma)","l");
         if (j==0) tleg->AddEntry(fbinned,"binned","l");
         tleg->Draw();
         c1->SaveAs(Form("tnp_pbpb_%seta%.1f-%.1f.pdf",tags[j],etamin[ieta],etamax[ieta]));
         c1->SaveAs(Form("tnp_pbpb_%seta%.1f-%.1f.png",tags[j],etamin[ieta],etamax[ieta]));
      } // eta loop

      // pp
      for (int ieta=0; ieta<4; ieta++) {
         if (ieta<2) {
            haxes->GetYaxis()->SetRangeUser(1-1.2*range[j],1+range[j]);
            haxes->Draw();
         } else {
            haxes20->GetYaxis()->SetRangeUser(1-1.2*range[j],1+range[j]);
            haxes20->Draw();
         }

         TLegend *tleg = new TLegend(0.58,0.16,0.91,0.47);
         tleg->SetBorderSize(0);

         eta = (etamax[ieta]+etamin[ieta])/2.;
         ptminval = ptmin(etamax[ieta]);
         ptmaxval = (ieta<2) ? 30 : 20;
         if (j<3) {
            for (int i=1; i<=100; i++) {
               TF1 *fnom = new TF1(Form("f%i",i),tnp_weight_pp_wrapper,ptminval,ptmaxval,3);
               fnom->SetParameters(eta,i,j);
               fnom->SetLineColor(kBlack);
               fnom->Draw("same");
            }
         }
         TF1 *fp = new TF1("fp",tnp_weight_pp_wrapper,ptminval,ptmaxval,3);
         fp->SetParameters(eta,-1,j);
         fp->SetLineColor(kCyan);
         fp->Draw("same");
         TF1 *fm = new TF1("fm",tnp_weight_pp_wrapper,ptminval,ptmaxval,3);
         fm->SetParameters(eta,-2,j);
         fm->SetLineColor(kCyan);
         fm->Draw("same");
         TF1 *fbinned = new TF1("fbinned",tnp_weight_pp_wrapper,ptminval,ptmaxval,3);
         if (j==0) {
            fbinned->SetParameters(eta,-10,j);
            fbinned->SetLineColor(kGreen+2);
            fbinned->Draw("same");
         }
         TF1 *fnom = new TF1("fnom",tnp_weight_pp_wrapper,ptminval,ptmaxval,3);
         fnom->SetParameters(eta,0,j);
         fnom->SetLineColor(kRed);
         fnom->Draw("same");

         tleg->SetHeader(Form("#splitline{pp, %s}{#eta #in [%.1f,%.1f], p_{T}>%.1f GeV/c}",names[j],etamin[ieta],etamax[ieta],ptminval));
         tleg->AddEntry(fnom,"Nominal","l");
         if (j<3) tleg->AddEntry("f1","stat (100 toys)","l");
         tleg->AddEntry(fp,"syst (+/1#sigma)","l");
         if (j==0) tleg->AddEntry(fbinned,"binned","l");
         tleg->Draw();
         c1->SaveAs(Form("tnp_pp_%seta%.1f-%.1f.pdf",tags[j],etamin[ieta],etamax[ieta]));
         c1->SaveAs(Form("tnp_pp_%seta%.1f-%.1f.png",tags[j],etamin[ieta],etamax[ieta]));
      } // eta loop
   } // eff type loop
}
