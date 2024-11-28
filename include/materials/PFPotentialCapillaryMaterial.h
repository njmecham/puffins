#pragma once

#include "INSADStabilized3Eqn.h"
#include "DerivativeMaterialPropertyNameInterface.h"

/**
 * This class computes extra residuals from interface for the INS equations.
 */
class PFPotentialCapillaryMaterial : public INSADStabilized3Eqn
{
public:
  static InputParameters validParams();

  PFPotentialCapillaryMaterial(const InputParameters & parameters);

protected:
  void computeQpProperties() override;

  /// Phase field variable
  const ADVariableGradient & _grad_c;

  /// Gradient of the phase field chemical potential
  const ADVariableValue & _w;

  /// Free energy derivative
  const ADMaterialProperty<Real> & _dFdc;

  /// Capillary momentum source
  ADMaterialProperty<RealVectorValue> & _capillary_momentum_source;
};
