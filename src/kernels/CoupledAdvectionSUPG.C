#include "CoupledAdvectionSUPG.h"

registerMooseObject("puffinsApp", CoupledAdvectionSUPG);

InputParameters
CoupledAdvectionSUPG::validParams()
{
  InputParameters params = ADKernelGrad::validParams();
  params.addClassDescription(
      "SUPG stablization term for the advection portion of the split CH equation.");
  params.addRequiredCoupledVar("velocity", "Velocity vector variable.");
  params.addRequiredCoupledVar("concentration", "Coupled concentration variable");
  return params;
}

CoupledAdvectionSUPG::CoupledAdvectionSUPG(const InputParameters & parameters)
  : ADKernelGrad(parameters),
    _grad_c(adCoupledGradient("concentration")),
    _velocity(adCoupledVectorValue("velocity"))
{
}

ADRealVectorValue
CoupledAdvectionSUPG::precomputeQpResidual()
{
  ADReal tau =
      _current_elem->hmin() /
      (2 * (_velocity[_qp] + RealVectorValue(libMesh::TOLERANCE * libMesh::TOLERANCE)).norm());
  return (tau * _velocity[_qp]) * (_velocity[_qp] * _grad_c[_qp]);
}
