void printGraph(TGraphAsymmErrors *tg, int s=0) {
   for (int i=0; i<tg->GetN(); i++) {
      double x = tg->GetX()[i];
      double y = tg->GetY()[i];
      double xlow = x-tg->GetEXlow()[i];
      double xhigh = x+tg->GetEXhigh()[i];
      double ylow = y-tg->GetEYlow()[i];
      double yhigh = y+tg->GetEYhigh()[i];
      cout << "if (x>" << xlow << "&&x<=" << xhigh << ") num = ";
      if (s==0) cout << y;
      if (s==-1) cout << ylow;
      if (s==1) cout << yhigh;
      cout << ";" << endl;
   }
}
