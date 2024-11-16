/****************************************************************************/
/*                        DO NOT MODIFY THIS HEADER                         */
/*                                                                          */
/* MALAMUTE: MOOSE Application Library for Advanced Manufacturing UTilitiEs */
/*                                                                          */
/*           Copyright 2021 - 2024, Battelle Energy Alliance, LLC           */
/*                           ALL RIGHTS RESERVED                            */
/****************************************************************************/

#pragma once

#include "INSADStabilized3Eqn.h"

/**
 * This class computes extra residuals from melt pool for the INS equations.
 */
class CapillaryMaterial : public INSADStabilized3Eqn
{
public:
  static InputParameters validParams();

  CapillaryMaterial(const InputParameters & parameters);

protected:
  void computeQpProperties() override;

  /// Phase field variable
  const ADVariableValue & _eta;

  /// Gradient of the phase field variable
  const ADVectorVariableValue & _grad_c;

  /// Curvature variable
  const ADVariableValue & _curvature;

  /// Surface tension coefficient
  const Real & _sigma;

  /// Capillary momentum source
  ADMaterialProperty<RealVectorValue> & _capillary_momentum_source;
};
