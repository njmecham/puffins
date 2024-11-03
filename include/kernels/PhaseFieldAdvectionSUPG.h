#pragma once

#include "ADKernelGrad.h"

/**
 * SUPG stabilization for the advection portion of the phase field equation.
 */
class PhaseFieldAdvectionSUPG : public ADKernelGrad
{
public:
  static InputParameters validParams();

  PhaseFieldAdvectionSUPG(const InputParameters & parameters);

protected:
  virtual ADRealVectorValue precomputeQpResidual() override;

  /// Velocity vector variable
  const ADVectorVariableValue & _velocity;
};
