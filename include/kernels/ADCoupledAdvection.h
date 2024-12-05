#pragma once

#include "ADKernel.h"

/**
 * This class computes an advection term for a coupled concentration in the split CH formulation.
 */
class ADCoupledAdvection : public ADKernel
{
public:
  static InputParameters validParams();

  ADCoupledAdvection(const InputParameters & parameters);

protected:
  ADReal computeQpResidual() override;

  /// Gradient of coupled concentration
  const ADVectorVariableValue & _grad_c;

  /// Velocity vector variable
  const ADVectorVariableValue & _velocity;
};
