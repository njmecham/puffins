#pragma once

#include "ADKernel.h"

/**
 * This class computes regularized interface curvature that is represented by a level set
 * function.
 */
class PhaseFieldCurvatureRegularization : public ADKernel
{
public:
  static InputParameters validParams();

  PhaseFieldCurvatureRegularization(const InputParameters & parameters);

protected:
  ADReal computeQpResidual() override;

  /// Gradient of regularized gradient of level set
  const ADVectorVariableValue & _grad_c;

  /// regulization parameter
  const Real _varepsilon;
};
