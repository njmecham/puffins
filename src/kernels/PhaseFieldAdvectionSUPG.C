#include "PhaseFieldAdvectionSUPG.h"

registerMooseObject("puffinsApp", PhaseFieldAdvectionSUPG);

InputParameters
PhaseFieldAdvectionSUPG::validParams()
{
  InputParameters params = ADKernelGrad::validParams();
  params.addClassDescription(
      "SUPG stablization term for the advection portion of the phase field equation.");
  params.addRequiredCoupledVar("velocity", "Velocity vector variable.");
  return params;
}

PhaseFieldAdvectionSUPG::PhaseFieldAdvectionSUPG(const InputParameters & parameters)
  : ADKernelGrad(parameters), _velocity(adCoupledVectorValue("velocity"))
{
}

ADRealVectorValue
PhaseFieldAdvectionSUPG::precomputeQpResidual()
{
  ADReal tau =
      _current_elem->hmin() /
      (2 * (_velocity[_qp] + RealVectorValue(libMesh::TOLERANCE * libMesh::TOLERANCE)).norm());
  return (tau * _velocity[_qp]) * (_velocity[_qp] * _grad_u[_qp]);
}
