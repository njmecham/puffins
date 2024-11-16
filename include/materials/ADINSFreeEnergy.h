//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "Material.h"
#include "DerivativeMaterialPropertyNameInterface.h"

/**
 * Material class that creates the math free energy and its derivatives
 * for use with ADSplitCHParsed. \f$ F = \beta(c + \frac12)^2(c - \frac12)^2 \f$.
 */
class ADINSFreeEnergy : public Material, public DerivativeMaterialPropertyNameInterface
{
public:
  static InputParameters validParams();

  ADINSFreeEnergy(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();

  /// Coupled variable value for the concentration \f$ c \f$.
  const ADVariableValue & _c;

  /// property name
  const MaterialPropertyName _f_name;

  /// Free energy coefficient
  const Real & _beta;

  /// function value
  ADMaterialProperty<Real> & _prop_F;

  /// function value derivative
  ADMaterialProperty<Real> & _prop_dFdc;
};
