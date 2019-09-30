#include "TFile.h"
#include "helper.h"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include <iostream>


void closure2018pbpb() {

  // Open the input file
  TFile f("eff_PbPb_HighPt.root", "READ");
  if (!f.IsOpen() || f.IsZombie()) { std::cout << "[ERROR] File eff_PbPb_HighPt.root was not open" << std::endl; return; }

  // Extract the TEfficiency objects
  std::map< std::string , std::map< std::string , std::map< anaBinT , TEfficiency > > > effM;
  for (const auto& e : {"Trd", "TnP"}) {
    for (const auto& t : effType) {
      for (const auto& c : centBins) {
	for (const auto& b : etaPtBins) {
	  const auto& bin = anaBinT({c, b.first});
	  const auto& etaMin = (b.first.first>2.4 ? b.second[0] : b.first.first);
	  const auto& etaMax = (b.first.first>2.4 ? b.second[b.second.size()-1] : b.first.second);
	  const auto& name = Form("eff%s_%s_Cent_%.0f_%.0f_Eta_%.0f_%.0f", e, t.c_str(), c.first, c.second, etaMin*10., etaMax*10.);
	  const auto& eff = dynamic_cast<TEfficiency*>(f.Get(name));
	  if (!eff) { std::cout << "[ERROR] Efficiency object " << name << " was not found!" << std::endl; return; }
	  effM[e][t][bin] = *eff;
	}
      }
    }
  }

  // Initialize the canvas
  TCanvas c1("c", "c", 800, 800);

  // Loop over the efficiencies
  for (const auto& t : effM.at("Trd")) {
    for (const auto& b : t.second) {
      c1.cd(); c1.Clear();
      const auto& type = t.first;
      const auto& bin = b.first;
      const auto& cntBin = bin.first;
      const auto& varBin = bin.second;
      auto& eff_Trd = effM.at("Trd").at(type).at(bin);
      auto& eff_TnP = effM.at("TnP").at(type).at(bin);
      // Format the efficiencies
      eff_Trd.SetLineColor(kBlack);
      eff_Trd.SetMarkerColor(kBlack);
      eff_Trd.SetMarkerStyle(kFullSquare);
      eff_TnP.SetLineColor(kMagenta);
      eff_TnP.SetMarkerColor(kMagenta);
      // Crate the legend
      TLegend leg(0.2, 0.2, 0.7, 0.5);
      leg.SetBorderSize(0); leg.SetFillColor(0); leg.SetTextSize(0.05);
      if (varBin.first>2.4) { leg.SetHeader(Form("PbPb, %s, %.1f<p_{T}<%.1f, Cent.[%.0f-%.0f]", type.c_str(), varBin.first, varBin.second, cntBin.first, cntBin.second)); }
      else { leg.SetHeader(Form("PbPb, %s, %.1f<|#eta|<%.1f, Cent.[%.0f-%.0f]", type.c_str(), varBin.first, varBin.second, cntBin.first, cntBin.second)); }
      leg.AddEntry(&eff_Trd, "Traditional", "lp");
      leg.AddEntry(&eff_TnP, "Tag and probe (weights)", "lp");
      // Create the ratio plot
      TRatioPlot tr(g2h(eff_Trd.CreateGraph(), 20), g2h(eff_TnP.CreateGraph(), 2));
      setTRatioPlotStyle(&tr);
      // Draw the ratio plot
      c1.Update();
      tr.GetUpperPad()->cd();
      leg.Draw();
      c1.SaveAs(Form("plots/PbPb_%s_Eta_%.0f_%.0fd_Cent_%.0f_%.0f.pdf", type.c_str(), 10.*varBin.first, 10.*varBin.second, cntBin.first, cntBin.second));
    }
  }
}
