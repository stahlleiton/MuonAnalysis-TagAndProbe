#include "TROOT.h"
#include "TKey.h"
#include "TFile.h"
#include "TSystem.h"
#include "TTree.h"
#include "TString.h"

//Merge the fits from different files (with the same naming scheme filename_#.root) to one file

void CopyDir(TDirectory *source) {
	//copy all objects and subdirs of directory source as a subdir of the current directory
	source->ls();
	TDirectory *savdir = gDirectory;
	TDirectory *adir = savdir->mkdir(source->GetName());
	adir->cd();
	//loop on all entries of this directory
	TKey *key;
	TIter nextkey(source->GetListOfKeys());
	while ((key = (TKey*)nextkey())) {
		const char *classname = key->GetClassName();
		TClass *cl = gROOT->GetClass(classname);
		if (!cl) continue;
		if (cl->InheritsFrom(TDirectory::Class())) {
			source->cd(key->GetName());
			TDirectory *subdir = gDirectory;
			adir->cd();
			CopyDir(subdir);
			adir->cd();
		}
		else if (cl->InheritsFrom(TTree::Class())) {
			TTree *T = (TTree*)source->Get(key->GetName());
			adir->cd();
			TTree *newT = T->CloneTree(-1, "fast");
			newT->Write();
		}
		else {
			source->cd();
			TObject *obj = key->ReadObj();
			adir->cd();
			obj->Write();
			delete obj;
		}
	}
	adir->SaveSelf(kTRUE);
	savdir->cd();
}

void CopyDirFile(TDirectory *source) {
	//This is here in order to NOT replicate the file name on the top

	source->ls();
	TDirectory *adir = gDirectory;
	adir->cd();
	//loop on all entries of this directory
	TKey *key;
	TIter nextkey(source->GetListOfKeys());
	while ((key = (TKey*)nextkey())) {
		const char *classname = key->GetClassName();
		TClass *cl = gROOT->GetClass(classname);
		if (!cl) continue;
		if (cl->InheritsFrom(TDirectory::Class())) {
			source->cd(key->GetName());
			TDirectory *subdir = gDirectory;
			adir->cd();
			CopyDir(subdir);
			adir->cd();
		}
		else if (cl->InheritsFrom(TTree::Class())) {
			TTree *T = (TTree*)source->Get(key->GetName());
			adir->cd();
			TTree *newT = T->CloneTree(-1, "fast");
			newT->Write();
		}
		else {
			source->cd();
			TObject *obj = key->ReadObj();
			adir->cd();
			obj->Write();
			delete obj;
		}
	}
	adir->SaveSelf(kTRUE);
}

void CopyFile(const char *fname, const TString TreeNameA) {
	//Copy all objects and subdirs of file fname to the subdirectory of the current directory
	TDirectory *target = gDirectory;
	TFile *f = TFile::Open(fname);
	if (!f || f->IsZombie()) {
		printf("Cannot copy file: %s\n", fname);
		target->cd();
		return;
	}
	f->cd(TreeNameA);
	TDirectory *dirToCopy = gDirectory;
	target->cd();
	CopyDirFile(dirToCopy);
	delete f;
	target->cd();
}


void mergeFits(const char *filein, int nFiles, const char *fileout, const TString TreeName ="tpTree") {
   
   TFile *fout = new TFile(fileout,"RECREATE");
      //fout->cd();
   TDirectory *TreeDir = gDirectory->mkdir(TreeName);
   TreeDir->cd();
   
   for (int i = 1; i < (nFiles + 1); i++)
   {
	   TString fileNameIn = TString::Format("%s_%i.root",filein, i);
	   cout << fileNameIn << endl;
	   CopyFile(fileNameIn,TreeName);
   }

   fout->Close();

}
