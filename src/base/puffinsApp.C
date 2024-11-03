#include "puffinsApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
puffinsApp::validParams()
{
  InputParameters params = MooseApp::validParams();
  params.set<bool>("use_legacy_material_output") = false;
  params.set<bool>("use_legacy_initial_residual_evaluation_behavior") = false;
  return params;
}

puffinsApp::puffinsApp(InputParameters parameters) : MooseApp(parameters)
{
  puffinsApp::registerAll(_factory, _action_factory, _syntax);
}

puffinsApp::~puffinsApp() {}

void
puffinsApp::registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ModulesApp::registerAllObjects<puffinsApp>(f, af, s);
  Registry::registerObjectsTo(f, {"puffinsApp"});
  Registry::registerActionsTo(af, {"puffinsApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
puffinsApp::registerApps()
{
  registerApp(puffinsApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
puffinsApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  puffinsApp::registerAll(f, af, s);
}
extern "C" void
puffinsApp__registerApps()
{
  puffinsApp::registerApps();
}
