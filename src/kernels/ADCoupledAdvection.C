#include "ADCoupledAdvection.h"

registerMooseObject("puffinsApp", ADCoupledAdvection);

InputParameters
ADCoupledAdvection::validParams()
{
  auto params = ADKernel::validParams();
  params.addClassDescription("Implements the phase field advection equation in split CH "
                             "formulation: $\\vec{v}\\cdot\\nabla "
                             "u = 0$, where the weak form is $(\\psi_i, \\vec{v}\\cdot\\nabla u) = "
                             "0$.");
  params.addRequiredCoupledVar("velocity", "Velocity vector variable.");
  params.addRequiredCoupledVar("concentration", "Coupled concentration variable");
  return params;
}

ADCoupledAdvection::ADCoupledAdvection(const InputParameters & parameters)
  : ADKernel(parameters),
    _grad_c(adCoupledGradient("concentration")),
    _velocity(adCoupledVectorValue("velocity"))
{
}

ADReal
ADCoupledAdvection::computeQpResidual()
{
  return _velocity[_qp] * _grad_c[_qp];
}
