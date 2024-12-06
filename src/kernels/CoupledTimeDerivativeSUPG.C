#include "CoupledTimeDerivativeSUPG.h"

registerMooseObject("puffinsApp", CoupledTimeDerivativeSUPG);

InputParameters
CoupledTimeDerivativeSUPG::validParams()
{
  InputParameters params = ADTimeKernelGrad::validParams();
  params.addClassDescription(
      "SUPG stablization terms for the time derivative of the split CH equation.");
  params.addRequiredCoupledVar("velocity", "Velocity vector variable.");
  params.addRequiredCoupledVar("concentration", "Coupled concentration variable");
  return params;
}

CoupledTimeDerivativeSUPG::CoupledTimeDerivativeSUPG(const InputParameters & parameters)
  : ADTimeKernelGrad(parameters),
    _velocity(adCoupledVectorValue("velocity")),
    _c_dot(adCoupledDot("concentration"))
{
}

ADRealVectorValue
CoupledTimeDerivativeSUPG::precomputeQpResidual()
{
  ADReal tau =
      _current_elem->hmin() /
      (2 * (_velocity[_qp] + RealVectorValue(libMesh::TOLERANCE * libMesh::TOLERANCE)).norm());
  return tau * _velocity[_qp] * _c_dot[_qp];
}
