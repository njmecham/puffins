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
  return params;
}

PFPotentialCapillaryMaterial::PFPotentialCapillaryMaterial(const InputParameters & parameters)
  : INSADStabilized3Eqn(parameters),
    _grad_w(adCoupledGradient("w")),
    _c(adCoupledValue("c")),
    _capillary_momentum_source(declareADProperty<RealVectorValue>("capillary_momentum_source"))
{
}

void
PFPotentialCapillaryMaterial::computeQpProperties()
{
  INSADStabilized3Eqn::computeQpProperties();

  _capillary_momentum_source[_qp] = 0;

  ADRealVectorValue surface_tension_term = ADRealVectorValue(0.0);
  RankTwoTensor iden(RankTwoTensor::initIdentity);
  ADRankTwoTensor proj;
  ADRealVectorValue normal = ADRealVectorValue(0.0);

  surface_tension_term = -_c[_qp] * (_grad_w[_qp]);

  _capillary_momentum_source[_qp] += surface_tension_term;

  _momentum_strong_residual[_qp] -= _capillary_momentum_source[_qp];
}
