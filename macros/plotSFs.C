#include "tnp_weight.h"
#include "TF1.h"
#include "TLegend.h"
#include "TH1.h"
#include "TCanvas.h"

Double_t tnp_weight_ppb_wrapper(Double_t *x, Double_t *par) {
   if (par[2]<0.5) return tnp_weight_trg_ppb(x[0], par[1]);
   else if (par[2]<1.5) return tnp_weight_muid_ppb(x[0],par[0],par[1]);
   else return tnp_weight_iso_ppb(x[0],par[0],par[1]);
}

float ptmin(float etamax) {
   float ans=15;
   // if (etamax<1.2) ans = 3.5;
   // else if (etamax<2.1) ans = 5.77-1.89*fabs(etamax);
   // else ans = 1.8;
   // ans = (int) (ans*10.);
   // ans = ans/10.;
   return ans;
}

void plotSFs() {
   TCanvas *c1 = new TCanvas();
   TH1F *haxes = new TH1F("haxes",";p_{T} [GeV/c];Scale factor",1,0,200);
   TH1F *haxeseta = new TH1F("haxes20",";#eta;Scale factor",1,-2.4,2.4);

   float *etamin=NULL, *etamax=NULL;
   float eta, ptminval, ptmaxval;

   etamin = new float[3]; etamin[0]=0.; etamin[1]=1.2; etamin[2]=2.1;
   etamax = new float[3]; etamax[0]=1.2; etamax[1]=2.1; etamax[2]=2.4;;

   const char* tags[3] = {"trg_","muid_","iso_"};
   const char* names[3] = {"Trigger","MuID","Iso"};
   const double range[3] = {0.1,0.1,0.1};

   for (int j=0; j<3; j++) {
      // ppb
      int ietamax = (j==0) ? 0 : 2; // for trigger, only 1 plot (eta dependence)
      for (int ieta=0; ieta<=ietamax; ieta++) {
         if (j>0) {
            haxes->GetYaxis()->SetRangeUser(1-2.*range[j],1+range[j]);
            haxes->Draw();
         } else {
            haxeseta->GetYaxis()->SetRangeUser(0.85,1.1);
            haxeseta->Draw();
         }

         TLegend *tleg = new TLegend(0.58,0.16,0.91,0.47);
         tleg->SetBorderSize(0);

         eta = (etamax[ieta]+etamin[ieta])/2.;
         ptminval = j==0 ? -2.4 : ptmin(etamax[ieta]);
         ptmaxval = j==0 ? 2.4 : 200;
         int imax = (j>0) ? 100 : 2;
         for (int i=1; i<=imax; i++) {
            TF1 *fnom = new TF1(Form("f%i",i),tnp_weight_ppb_wrapper,ptminval,ptmaxval,3);
            fnom->SetParameters(eta,i,j);
            fnom->SetLineColor(kBlack);
            fnom->Draw("same");
         }
         TF1 *fp = new TF1("fp",tnp_weight_ppb_wrapper,ptminval,ptmaxval,3);
         fp->SetParameters(eta,-1,j);
         fp->SetLineColor(kCyan);
         fp->Draw("same");
         TF1 *fm = new TF1("fm",tnp_weight_ppb_wrapper,ptminval,ptmaxval,3);
         fm->SetParameters(eta,-2,j);
         fm->SetLineColor(kCyan);
         fm->Draw("same");
         TF1 *fbinned = new TF1("fbinned",tnp_weight_ppb_wrapper,ptminval,ptmaxval,3);
         fbinned->SetParameters(eta,-10,j);
         fbinned->SetLineColor(kGreen+2);
         if (j>0) fbinned->Draw("same"); // binned only for MuId and Iso
         TF1 *fnom = new TF1("fnom",tnp_weight_ppb_wrapper,ptminval,ptmaxval,3);
         fnom->SetParameters(eta,0,j);
         fnom->SetLineColor(kRed);
         fnom->Draw("same");

         if (j==0) tleg->SetHeader(Form("#splitline{pPb, %s}{#eta #in [-2.4,2.4], p_{T}>15 GeV/c}",names[j]));
         else tleg->SetHeader(Form("#splitline{pPb, %s}{#eta #in [%.1f,%.1f], p_{T}>15 GeV/c}",names[j],etamin[ieta],etamax[ieta]));

         tleg->AddEntry(fnom,"Nominal","l");
         if (j>0) tleg->AddEntry("f1","stat (100 toys)","l");
         else tleg->AddEntry("f1","stat","l");
         tleg->AddEntry(fp,"syst (+/1#sigma)","l");
         if (j>0) tleg->AddEntry(fbinned,"binned","l");
         tleg->Draw();
         c1->SaveAs(Form("tnp_ppb_%seta%.1f-%.1f.pdf",tags[j],etamin[ieta],etamax[ieta]));
         c1->SaveAs(Form("tnp_ppb_%seta%.1f-%.1f.png",tags[j],etamin[ieta],etamax[ieta]));
      } // eta loop
   } // eff type loop
}
