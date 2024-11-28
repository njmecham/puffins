//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADINSFreeEnergy.h"

registerMooseObject("puffinsApp", ADINSFreeEnergy);

InputParameters
ADINSFreeEnergy::validParams()
{
  InputParameters params = Material::validParams();
  params.addClassDescription("Material that implements the math free energy and its derivatives: "
                             "\n$F = \beta(c + \frac12)^2(c - \frac12)^2$");
  params.addParam<MaterialPropertyName>("f_name", "F", "function property name");
  params.addParam<MaterialPropertyName>("dFdc_name", "dFdc", "function derivative property name");
  params.addRequiredCoupledVar("c", "Concentration variable");
  params.addRequiredParam<Real>("beta", "Free energy coefficient");
  return params;
}

ADINSFreeEnergy::ADINSFreeEnergy(const InputParameters & parameters)
  : Material(parameters),
    _c(adCoupledValue("c")),
    _f_name(getParam<MaterialPropertyName>("f_name")),
    _dFdc_name(getParam<MaterialPropertyName>("dFdc_name")),
    _beta(getParam<Real>("beta")),
    _prop_F(declareADProperty<Real>(_f_name)),
    _prop_dFdc(
        declareADProperty<Real>(derivativePropertyNameFirst(_f_name, this->coupledName("c", 0)))),
    _duplicate_dFdc(declareADProperty<Real>(_dFdc_name))
{
}

void
ADINSFreeEnergy::computeQpProperties()
{
  _prop_F[_qp] = _beta * (_c[_qp] + 0.5) * (_c[_qp] + 0.5) * (_c[_qp] - 0.5) * (_c[_qp] - 0.5);
  _prop_dFdc[_qp] = 4 * _beta * _c[_qp] * (_c[_qp] - 0.5) * (_c[_qp] + 0.5);
  _duplicate_dFdc[_qp] = _prop_dFdc[_qp];
}
