#pragma once

#include "ADKernelValue.h"

/**
 * Advection Kernel for the phase field equation.
 *
 * \psi_i \vec{v} \nabla u,
 * where \vec{v} is the interface velocity that is a set of
 * coupled variables.
 */
class PhaseFieldAdvection : public ADKernelValue
{
public:
  static InputParameters validParams();

  PhaseFieldAdvection(const InputParameters & parameters);

protected:
  virtual ADReal precomputeQpResidual() override;

  /// Velocity vector variable
  const ADVectorVariableValue & _velocity;
};
