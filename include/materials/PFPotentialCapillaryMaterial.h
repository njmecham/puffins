#pragma once

#include "INSADStabilized3Eqn.h"

/**
 * This class computes extra residuals from melt pool for the INS equations.
 */
class PFPotentialCapillaryMaterial : public INSADStabilized3Eqn
{
public:
  static InputParameters validParams();

  PFPotentialCapillaryMaterial(const InputParameters & parameters);

protected:
  void computeQpProperties() override;

  /// Phase field variable
  const ADVariableValue & _c;

  /// Gradient of the phase field chemical potential
  const ADVariableGradient & _grad_w;

  /// Capillary momentum source
  ADMaterialProperty<RealVectorValue> & _capillary_momentum_source;
};
