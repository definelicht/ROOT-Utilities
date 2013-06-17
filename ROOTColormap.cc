#include "ROOTColormap.hh"
#include <cassert>

unsigned ROOTColormap::TranslateToIndex(const float f, const float min,
    const float max, const unsigned bins) {

  float percentage = (f - min) / (max - min);
  if (percentage < 0) percentage = 0;
  unsigned index = unsigned(percentage * (float)(bins - 1) + 0.5f);

  return index;
}

unsigned ROOTColormap::GetRawIndex(const unsigned x, const unsigned y,
    const unsigned z) const {
  unsigned index = x + y*xbins + z*xbins*ybins;
  assert(index < size);
  return index;
}

unsigned ROOTColormap::GetXBin(const float f) const {
  return TranslateToIndex(f,xmin,xmax,xbins);
}

unsigned ROOTColormap::GetYBin(const float f) const {
  return TranslateToIndex(f,ymin,ymax,ybins);
}

unsigned ROOTColormap::GetZBin(const float f) const {
  return TranslateToIndex(f,zmin,zmax,zbins);
}
  
ROOTColormap::ROOTColormap(
    const unsigned xbins_,
    const float xmin_,
    const float xmax_,
    const unsigned ybins_,
    const float ymin_,
    const float ymax_,
    const unsigned zbins_,
    const float zmin_,
    const float zmax_)
    : xbins(xbins_), xmin(xmin_), xmax(xmax_),
      ybins(ybins_), ymin(ymin_), ymax(ymax_),
      zbins(zbins_), zmin(zmin_), zmax(zmax_),
      size(xbins_*ybins_*zbins_) {

  grid = new float[size];
  for (int i=0;i<size;i++) grid[i] = 0;

}

ROOTColormap::~ROOTColormap() {
  delete grid;
}

void ROOTColormap::Fill(const float x, const float y, const float z,
    const float E) {
  unsigned xbin = GetXBin(x);
  unsigned ybin = GetYBin(y);
  unsigned zbin = GetZBin(z);
  assert(E >= 0);
  assert(E == E);
  grid[GetRawIndex(xbin,ybin,zbin)] += E;
}

float ROOTColormap::Get(const unsigned xbin, const unsigned ybin,
    const unsigned zbin) const {
  assert(xbin < xbins && ybin < ybins && zbin < zbins);
  return grid[GetRawIndex(xbin,ybin,zbin)];
}

float ROOTColormap::Get(const float x, const float y, const float z) const {
  unsigned xbin = GetXBin(x);
  unsigned ybin = GetYBin(y);
  unsigned zbin = GetZBin(z);
  return Get(xbin,ybin,zbin);
}

TH2F* ROOTColormap::BuildXYHistogram() const {
  TH2F *hist = new TH2F(
    "XY Colormap",
    "XY Colormap;x;y",
    xbins,xmin,xmax,
    ybins,ymin,ymax
  );
  for (unsigned i=0;i<xbins;i++) {
    for (unsigned j=0;j<ybins;j++) {
      float sum = 0;
      for (unsigned k=0;k<zbins;k++) {
        sum += Get(i,j,k);
      }
      hist->SetBinContent(i,j,sum);
    }
  }
  return hist;
}

TH2F* ROOTColormap::BuildXZHistogram() const {
  TH2F *hist = new TH2F(
    "XZ Colormap",
    "XZ Colormap;x;z",
    xbins,xmin,xmax,
    zbins,zmin,zmax
  );
  for (unsigned i=0;i<xbins;i++) {
    for (unsigned j=0;j<zbins;j++) {
      float sum = 0;
      for (unsigned k=0;k<ybins;k++) {
        sum += Get(i,k,j);
      }
      hist->SetBinContent(i,j,sum);
    }
  }
  return hist;
}

TH2F* ROOTColormap::BuildYZHistogram() const {
  TH2F *hist = new TH2F(
    "YZ Colormap",
    "YZ Colormap;y;z",
    ybins,ymin,ymax,
    zbins,zmin,zmax
  );
  for (unsigned i=0;i<ybins;i++) {
    for (unsigned j=0;j<zbins;j++) {
      float sum = 0;
      for (unsigned k=0;k<xbins;k++) {
        sum += Get(k,i,j);
      }
      hist->SetBinContent(i,j,sum);
    }
  }
  return hist;
}

TH3F* ROOTColormap::Build3DHistogram() const {
  TH3F *hist = new TH3F(
    "3D Colormap",
    "3D Colormap;x;y;z",
    xbins,xmin,xmax,
    ybins,ymin,ymax,
    zbins,zmin,zmax
  );
  for (unsigned i=0;i<xbins;i++) {
    for (unsigned j=0;j<ybins;j++) {
      for (unsigned k=0;k<zbins;k++) {
        hist->SetBinContent(i,j,k,Get(i,j,k));
      }
    }
  }
  return hist;
}