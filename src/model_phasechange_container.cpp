/*------------------------------------------------------------------------------------*\

                                      /$$$$$$                      /$$
                                     /$$__  $$                    | $$
        /$$$$$$   /$$$$$$   /$$$$$$ | $$  \__/  /$$$$$$$  /$$$$$$ | $$  /$$$$$$
       /$$__  $$ |____  $$ /$$__  $$|  $$$$$$  /$$_____/ |____  $$| $$ /$$__  $$
      | $$  \ $$  /$$$$$$$| $$  \__/ \____  $$| $$        /$$$$$$$| $$| $$$$$$$$
      | $$  | $$ /$$__  $$| $$       /$$  \ $$| $$       /$$__  $$| $$| $$_____/
      | $$$$$$$/|  $$$$$$$| $$      |  $$$$$$/|  $$$$$$$|  $$$$$$$| $$|  $$$$$$$
      | $$____/  \_______/|__/       \______/  \_______/ \_______/|__/ \_______/
      | $$
      | $$
      |__/        A Compilation of Particle Scale Models

   Copyright (C): 2014 DCS Computing GmbH (www.dcs-computing.com), Linz, Austria
                  2014 Graz University of Technology (ippt.tugraz.at), Graz, Austria
---------------------------------------------------------------------------------------
License
    ParScale is licensed under the GNU LESSER GENERAL PUBLIC LICENSE (LGPL).

    Everyone is permitted to copy and distribute verbatim copies of this license
    document, but changing it is not allowed.

    This version of the GNU Lesser General Public License incorporates the terms
    and conditions of version 3 of the GNU General Public License, supplemented
    by the additional permissions listed below.

    You should have received a copy of the GNU Lesser General Public License
    along with ParScale. If not, see <http://www.gnu.org/licenses/lgpl.html>.

    This code is designed to simulate transport processes (e.g., for heat and
    mass) within porous and no-porous particles, eventually undergoing
    chemical reactions.

    Parts of the code were developed in the frame of the NanoSim project funded
    by the European Commission through FP7 Grant agreement no. 604656.
\*-----------------------------------------------------------------------------------*/



#include "model_phasechange_container.h"
#include "input.h"
#include "style_model_phasechange.h"

using namespace PASCAL_NS;

/* ----------------------------------------------------------------------
   ModelPhaseChangeContainer Constructor
------------------------------------------------------------------------- */

ModelPhaseChangeContainer::ModelPhaseChangeContainer(ParScale *ptr) : ParScaleBase(ptr),
    model_map_(new std::map<std::string,ModelPhaseChangeCreator>())
{
  // fill map with all models listed in style_model_eqn.h
#define MODEL_PHASECHANGE_CLASS
#define ModelPhaseChangeStyle(key,Class) \
  (*model_map_)[#key] = &model_creator<Class>;
#include "style_model_phasechange.h"
#undef ModelPhaseChangeStyle
#undef MODEL_PHASECHANGE_CLASS

}

/* ---------------------------------------------------------------------- */

ModelPhaseChangeContainer::~ModelPhaseChangeContainer()
{
    delete model_map_;

    modelPhaseChangeEqns_.clear();
}

/* ----------------------------------------------------------------------
   one instance per model in style_model_eqn.h
------------------------------------------------------------------------- */

template <typename T>
ModelPhaseChange *ModelPhaseChangeContainer::model_creator(ParScale *ptr, char *name)
{
  return new T(ptr, name);
}

/* ----------------------------------------------------------------------
   settings
------------------------------------------------------------------------- */

void ModelPhaseChangeContainer::parse_command(int narg, char const* const* arg)
{
    int n = strlen(arg[1]) + 1;
    char *modelName = new char[n];
    strcpy(modelName,arg[1]);

    if (model_map_->find(arg[0]) != model_map_->end())
    {
        ModelPhaseChangeCreator model_creator = (*model_map_)[arg[0]];
        modelPhaseChangeEqns_.push_back(model_creator(pascal_ptr(), modelName));

        printf("...this phaseChange model of type %s is registered with ID %lu\n",
                arg[0],
                modelPhaseChangeEqns_.size()-1);

        modelPhaseChangeEqns_[modelPhaseChangeEqns_.size()-1].init(narg, arg, PHASECHANGE, modelPhaseChangeEqns_.size()-1);
    }
    else
        printf("ERROR: ModelPhaseChangeContainer PARSING: model name not found\n");

    delete [] modelName;
}


// ----------------------------------------------------------------------
void ModelPhaseChangeContainer::postParticleDataBuild()
{

    for(uint iEqn=0; iEqn<modelPhaseChangeEqns_.size(); iEqn++)
            modelPhaseChangeEqns_[iEqn].postParticleDataBuild();

}

// ----------------------------------------------------------------------
void ModelPhaseChangeContainer::begin_of_step()
{

    for(uint iEqn=0; iEqn<modelPhaseChangeEqns_.size(); iEqn++)
            modelPhaseChangeEqns_[iEqn].begin_of_step();

}

// ----------------------------------------------------------------------
void ModelPhaseChangeContainer::pre_middle_of_step()
{
}
// ----------------------------------------------------------------------
void ModelPhaseChangeContainer::post_middle_of_step()
{
}// ----------------------------------------------------------------------
void ModelPhaseChangeContainer::end_of_step()
{
}
