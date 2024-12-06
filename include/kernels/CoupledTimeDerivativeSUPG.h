#pragma once

#include "ADTimeKernelGrad.h"

/**
 * Applies SUPG stabilization to the coupled time derivative.
 */
class CoupledTimeDerivativeSUPG : public ADTimeKernelGrad
{
public:
  static InputParameters validParams();

  CoupledTimeDerivativeSUPG(const InputParameters & parameters);

protected:
  virtual ADRealVectorValue precomputeQpResidual() override;

  /// Velocity vector variable
  const ADVectorVariableValue & _velocity;

  /// Time derivative of coupled concentration
  const ADVariableValue & _c_dot;
};
