#ifndef ROOTLOGAXISBINS_H
#define ROOTLOGAXISBINS_H

#include <TAxis.h>

/**
 * Reformats the bins of the input axis to a logarithmic scale.
 * This should be done before the histogram is filled.
 */

void ROOTLogAxisBins(TAxis *axis);

#endif /* ROOTLOGAXISBINS_H */