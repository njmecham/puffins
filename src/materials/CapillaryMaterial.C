#include "CapillaryMaterial.h"

registerADMooseObject("puffinsApp", CapillaryMaterial);

InputParameters
CapillaryMaterial::validParams()
{
  InputParameters params = INSADStabilized3Eqn::validParams();
  params.addClassDescription(
      "Computes extra residuals from capillary forces for the INS equations.");
  params.addRequiredCoupledVar("phase_field_gradient",
                               "Regularized gradient of phase field variable");
  params.addRequiredCoupledVar("eta", "Phase field variable");
  params.addRequiredCoupledVar("curvature", "Regularized curvature variable");
  params.addRequiredParam<Real>("surface_tension", "Surface tension coefficient.");
  return params;
}

CapillaryMaterial::CapillaryMaterial(const InputParameters & parameters)
  : INSADStabilized3Eqn(parameters),
    _grad_c(adCoupledVectorValue("phase_field_gradient")),
    _curvature(adCoupledValue("curvature")),
    _eta(adCoupledValue("eta")),
    _sigma(getParam<Real>("surface_tension")),
    _capillary_momentum_source(declareADProperty<RealVectorValue>("capillary_momentum_source"))
{
}

void
CapillaryMaterial::computeQpProperties()
{
  INSADStabilized3Eqn::computeQpProperties();

  _capillary_momentum_source[_qp] = 0;

  ADRealVectorValue surface_tension_term = ADRealVectorValue(0.0);
  RankTwoTensor iden(RankTwoTensor::initIdentity);
  ADRankTwoTensor proj;
  ADRealVectorValue normal = ADRealVectorValue(0.0);

  normal = _grad_c[_qp] /
           (_grad_c[_qp] + RealVectorValue(libMesh::TOLERANCE * libMesh::TOLERANCE)).norm();

  proj.vectorOuterProduct(normal, normal);
  proj = iden - proj;
  surface_tension_term = _sigma * _curvature[_qp] *
                         (_grad_c[_qp] + RealVectorValue(libMesh::TOLERANCE * libMesh::TOLERANCE));

  if (MetaPhysicL::raw_value(_eta[_qp]) < 0.9 && MetaPhysicL::raw_value(_eta[_qp]) > 0.1)
  {
    _capillary_momentum_source[_qp] += surface_tension_term;

    _momentum_strong_residual[_qp] -= _capillary_momentum_source[_qp];
  }
}
