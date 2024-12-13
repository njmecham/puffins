#include "VariableGradientRegularization.h"

registerMooseObject("puffinsApp", VariableGradientRegularization);

InputParameters
VariableGradientRegularization::validParams()
{
  InputParameters params = ADVectorKernel::validParams();
  params.addClassDescription(
      "Performs L2 projection of a variable's gradient onto a new vector variable.");
  params.addRequiredCoupledVar("regularized_var", "The variable to be regularized.");
  return params;
}

VariableGradientRegularization::VariableGradientRegularization(const InputParameters & parameters)
  : ADVectorKernel(parameters), _grad_c(adCoupledGradient("regularized_var"))
{
}

ADReal
VariableGradientRegularization::computeQpResidual()
{
  if (MetaPhysicL::raw_value(_grad_c[_qp].norm()) > libMesh::TOLERANCE)
    return _test[_i][_qp] * (_u[_qp] - _grad_c[_qp]);
  else
    return _test[_i][_qp] * _u[_qp];
}
