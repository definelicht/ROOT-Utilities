#ifndef ROOTCOLORMAP_H
#define ROOTCOLORMAP_H

#include <TH2.h>
#include <TH3.h>

/**
 * The ROOTColormap saves a value E for a set of three dimensional coordinates
 * (x,y,z), binning all three dimensions according to the input. Two-dimensional
 * histograms can then be drawn for each combination of dimensions.
 */

class ROOTColormap {

public:
  ROOTColormap(
    const unsigned xbins,
    const float xmin,
    const float xmax,
    const unsigned ybins,
    const float ymin,
    const float ymax,
    const unsigned zbins,
    const float zmin,
    const float zmax
  );
  ~ROOTColormap();
  void Fill(const float x, const float y, const float z, const float E);
  float Get(const float x, const float y, const float z) const;
  float Get(const unsigned xbin, const unsigned ybin, const unsigned zbin) const;
  TH2F* BuildXYHistogram() const;
  TH2F* BuildXZHistogram() const;
  TH2F* BuildYZHistogram() const;
  TH3F* Build3DHistogram() const;

private:
  const float xmin, xmax, ymin, ymax, zmin, zmax;
  const unsigned xbins, ybins, zbins;
  const unsigned size;
  float* grid;

  static unsigned TranslateToIndex(const float f, const float min,
      const float max, const unsigned bins);
  unsigned GetRawIndex(const unsigned x, const unsigned y,
      const unsigned z) const;
  unsigned GetXBin(const float f) const;
  unsigned GetYBin(const float f) const;
  unsigned GetZBin(const float f) const;

};

#endif /* ROOTCOLORMAP_H */