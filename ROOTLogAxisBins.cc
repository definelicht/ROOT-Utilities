#include <cmath>
#include "ROOTLogAxisBins.hh"

void ROOTLogAxisBins(TAxis *axis) {

  int n_bins = axis->GetNbins();

  float min = axis->GetXmin();
  float max = axis->GetXmax();

  float *bins_new = new float[n_bins];

  for (int i=0;i<n_bins;i++) {
    bins_new[i] = min + (max - min) * pow((float)i / (float)(n_bins - 1),10);
  }

  axis->Set(n_bins-1,bins_new);

  delete bins_new;

}