#include "PhaseFieldTimeDerivativeSUPG.h"

registerMooseObject("puffinsApp", PhaseFieldTimeDerivativeSUPG);

InputParameters
PhaseFieldTimeDerivativeSUPG::validParams()
{
  InputParameters params = ADTimeKernelGrad::validParams();
  params.addClassDescription(
      "SUPG stablization terms for the time derivative of the phase field equation.");
  params.addRequiredCoupledVar("velocity", "Velocity vector variable.");
  return params;
}

PhaseFieldTimeDerivativeSUPG::PhaseFieldTimeDerivativeSUPG(const InputParameters & parameters)
  : ADTimeKernelGrad(parameters), _velocity(adCoupledVectorValue("velocity"))
{
}

ADRealVectorValue
PhaseFieldTimeDerivativeSUPG::precomputeQpResidual()
{
  ADReal tau =
      _current_elem->hmin() /
      (2 * (_velocity[_qp] + RealVectorValue(libMesh::TOLERANCE * libMesh::TOLERANCE)).norm());
  return tau * _velocity[_qp] * _u_dot[_qp];
}
