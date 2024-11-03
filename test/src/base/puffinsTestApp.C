//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "puffinsTestApp.h"
#include "puffinsApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"

InputParameters
puffinsTestApp::validParams()
{
  InputParameters params = puffinsApp::validParams();
  params.set<bool>("use_legacy_material_output") = false;
  params.set<bool>("use_legacy_initial_residual_evaluation_behavior") = false;
  return params;
}

puffinsTestApp::puffinsTestApp(InputParameters parameters) : MooseApp(parameters)
{
  puffinsTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

puffinsTestApp::~puffinsTestApp() {}

void
puffinsTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  puffinsApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"puffinsTestApp"});
    Registry::registerActionsTo(af, {"puffinsTestApp"});
  }
}

void
puffinsTestApp::registerApps()
{
  registerApp(puffinsApp);
  registerApp(puffinsTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
puffinsTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  puffinsTestApp::registerAll(f, af, s);
}
extern "C" void
puffinsTestApp__registerApps()
{
  puffinsTestApp::registerApps();
}
