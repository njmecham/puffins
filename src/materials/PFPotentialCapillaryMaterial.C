#include "PFPotentialCapillaryMaterial.h"

registerADMooseObject("puffinsApp", PFPotentialCapillaryMaterial);

InputParameters
PFPotentialCapillaryMaterial::validParams()
{
  InputParameters params = INSADStabilized3Eqn::validParams();
  params.addClassDescription("Computes extra residuals from capillary forces for the INS equations "
                             "using energy potential.");
  params.addRequiredCoupledVar("c", "Phase field concentration");
  params.addRequiredCoupledVar("w", "Phase field chemical potential");
  // params.addRequiredParam<MaterialPropertyName>(
  //     "dFdc_name", "The derivative of the free energy function with respect to the
  //     concentration.");
  return params;
}

PFPotentialCapillaryMaterial::PFPotentialCapillaryMaterial(const InputParameters & parameters)
  : INSADStabilized3Eqn(parameters),
    // _dFdc(getADMaterialProperty<Real>("dFdc_name")),
    _grad_c(adCoupledGradient("c")),
    _w(adCoupledValue("w")),
    _capillary_momentum_source(declareADProperty<RealVectorValue>("capillary_momentum_source"))
{
}

void
PFPotentialCapillaryMaterial::computeQpProperties()
{
  INSADStabilized3Eqn::computeQpProperties();

  _capillary_momentum_source[_qp] = 0;

  ADRealVectorValue surface_tension_term = ADRealVectorValue(0.0);

  surface_tension_term = _grad_c[_qp] * (_w[_qp]);

  _capillary_momentum_source[_qp] += surface_tension_term;

  _momentum_strong_residual[_qp] -= _capillary_momentum_source[_qp];
}
