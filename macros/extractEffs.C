#include "TnPEffDraw_singleFile.C"

void extractEffs(const char* filein, const char* fileout) {
   TFile *f = new TFile(filein);
   TFile *fout = new TFile(fileout,"RECREATE");
   TIter next(f->GetListOfKeys()); TObject *obj;
   while ((obj = next()))
   {
      obj = ((TKey*) obj)->ReadObj();
      if (TString(obj->ClassName()) == "TDirectoryFile")
      {
         // first-level directory
         TDirectoryFile *tdir = dynamic_cast<TDirectoryFile*>(obj);
         tdir->cd();
         TIter next2(tdir->GetListOfKeys()); TObject *obj2;
         while ((obj2 = next2()))
         {
            obj2 = ((TKey*) obj2)->ReadObj();
            if (TString(obj2->ClassName()) == "TDirectoryFile")
            {
               TDirectoryFile *tdir2 = dynamic_cast<TDirectoryFile*>(obj2);
               // second level directory
               RooDataSet* ds = (RooDataSet*) tdir2->Get("fit_eff");
               TString dirname(tdir2->GetName());
               TString varname;
               if (dirname.Contains("absetadep")) varname = "abseta";
               else if (dirname.Contains("ptdep")) varname = "pt";
               else if (dirname.Contains("etadep")) varname = "eta";
               else if (dirname.Contains("nPV")) varname = "tag_nVertices";
               else if (dirname.Contains("centdepHF") || dirname.Contains("HFdep")) varname = "tag_hiHF";
               else if (dirname.Contains("centdep") || dirname.Contains("nTracksdep")) varname = "tag_hiNtracks";
               else varname = "pt";
               cout << dirname << " " << varname << endl;
               TGraphAsymmErrors *tg0 = plotEff_1bin(ds,1,varname.Data());
               fout->WriteTObject(tg0,dirname);
            }
         }
      }
   }

   fout->Write();
   fout->Close();
   f->Close();
}
