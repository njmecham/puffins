#pragma once

#include "ADKernelValue.h"

/**
 * This class computes the momentum equation capillary residual contribution for the source terms
 * for incompressible Navier-Stokes
 */
class CapillaryMomentumSource : public ADVectorKernelValue
{
public:
  static InputParameters validParams();

  CapillaryMomentumSource(const InputParameters & parameters);

protected:
  ADRealVectorValue precomputeQpResidual() override;

  const ADMaterialProperty<RealVectorValue> & _capillary_momentum_source;
};
