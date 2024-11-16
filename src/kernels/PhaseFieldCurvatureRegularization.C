#include "PhaseFieldCurvatureRegularization.h"

registerMooseObject("puffinsApp", PhaseFieldCurvatureRegularization);

InputParameters
PhaseFieldCurvatureRegularization::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addClassDescription("Computes regularized interface curvature that is represented by a "
                             "phase field function.");
  params.addRequiredCoupledVar("phase_field_regularized_gradient",
                               "Vector variable of phase field's regularized gradient.");
  params.addRequiredParam<Real>("varepsilon", "Regulization parameter.");
  return params;
}

PhaseFieldCurvatureRegularization::PhaseFieldCurvatureRegularization(
    const InputParameters & parameters)
  : ADKernel(parameters),
    _grad_c(adCoupledVectorValue("phase_field_regularized_gradient")),
    _varepsilon(getParam<Real>("varepsilon"))
{
}

ADReal
PhaseFieldCurvatureRegularization::computeQpResidual()
{
  const auto grad_c_norm = MooseUtils::isZero(_grad_c[_qp]) ? ADReal(1e-42) : _grad_c[_qp].norm();
  if (MetaPhysicL::raw_value(grad_c_norm) > libMesh::TOLERANCE)
  {
    ADRealVectorValue n = (_grad_c[_qp]) / grad_c_norm;
    return _test[_i][_qp] * _u[_qp] - _grad_test[_i][_qp] * (n - _varepsilon * _grad_u[_qp]);
  }
  else
    return _test[_i][_qp] * _u[_qp] + _grad_test[_i][_qp] * _varepsilon * _grad_u[_qp];
}
