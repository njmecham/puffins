#include "CapillaryMomentumSource.h"

registerMooseObject("puffinsApp", CapillaryMomentumSource);

InputParameters
CapillaryMomentumSource::validParams()
{
  InputParameters params = ADVectorKernel::validParams();
  params.addClassDescription("Adds capillary momentum source term to the INS momentum equation");
  return params;
}

CapillaryMomentumSource::CapillaryMomentumSource(const InputParameters & parameters)
  : ADVectorKernelValue(parameters),
    _capillary_momentum_source(getADMaterialProperty<RealVectorValue>("capillary_momentum_source"))
{
}

ADRealVectorValue
CapillaryMomentumSource::precomputeQpResidual()
{
  return -_capillary_momentum_source[_qp];
}
