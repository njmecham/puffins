#pragma once

#include "ADKernelGrad.h"

/**
 * SUPG stabilization for the advection portion of the split CH equation.
 */
class CoupledAdvectionSUPG : public ADKernelGrad
{
public:
  static InputParameters validParams();

  CoupledAdvectionSUPG(const InputParameters & parameters);

protected:
  virtual ADRealVectorValue precomputeQpResidual() override;

  /// Velocity vector variable
  const ADVectorVariableValue & _velocity;

  /// Gradient of coupled concentration
  const ADVectorVariableValue & _grad_c;
};
