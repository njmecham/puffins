#pragma once

#include "ADTimeKernelGrad.h"

/**
 * Applies SUPG stabilization to the time derivative.
 */
class PhaseFieldTimeDerivativeSUPG : public ADTimeKernelGrad
{
public:
  static InputParameters validParams();

  PhaseFieldTimeDerivativeSUPG(const InputParameters & parameters);

protected:
  virtual ADRealVectorValue precomputeQpResidual() override;

  /// Velocity vector variable
  const ADVectorVariableValue & _velocity;
};
