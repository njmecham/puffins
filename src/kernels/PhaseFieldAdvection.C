#include "PhaseFieldAdvection.h"

registerMooseObject("puffinsApp", PhaseFieldAdvection);

InputParameters
PhaseFieldAdvection::validParams()
{
  InputParameters params = ADKernelValue::validParams();
  params.addClassDescription(
      "Implements the phase field advection equation: $\\vec{v}\\cdot\\nabla "
      "u = 0$, where the weak form is $(\\psi_i, \\vec{v}\\cdot\\nabla u) = "
      "0$.");
  params.addRequiredCoupledVar("velocity", "Velocity vector variable.");
  return params;
}

PhaseFieldAdvection::PhaseFieldAdvection(const InputParameters & parameters)
  : ADKernelValue(parameters), _velocity(adCoupledVectorValue("velocity"))
{
}

ADReal
PhaseFieldAdvection::precomputeQpResidual()
{
  return _velocity[_qp] * _grad_u[_qp];
}
