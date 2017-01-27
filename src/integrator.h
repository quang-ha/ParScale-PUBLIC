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

/*-----------------------------------------------------------------------------------
Description
    This class is the basis for all time integrators. Spatial discretization (e.g.
    using the method of lines) has to be supplied separately (i.e., via a
    "modelEquation" object).

-----------------------------------------------------------------------------------*/

#ifndef PASC_INTEGRATOR_H
#define PASC_INTEGRATOR_H

#include "pascal_base_accessible.h"
#include "simulation_state.h"

#include "qjson_includes.h"

namespace PASCAL_NS
{

//numbering of boundary condition types
enum{ CVODE        //0
    };

class ModelEqn;

// derives from ParScaleBaseAccessible so is allowed to
// call non-const functions
class Integrator : public ParScaleBaseAccessible
{
    friend class Driver;

    public:

      Integrator(ParScale *ptr);
      virtual ~Integrator();

      virtual void init(double t0, ModelEqn& m_eqn);

      virtual void integrate_begin(const char* stateType, int nGridPointsUsed, int dataID, bool updatePhaseFraction) {};
      virtual void integrate_middle() {};
      virtual void integrate_end() {};
      virtual int returnParticleID() {return particleID;};

      double *  tempIntraData_;
      double *  tempPhaseDataGas_;
      double *  tempPhaseDataLiquid_;
      double *  tempPhaseDataSolid_;

// Acess function

    private:

    protected:
    int particleID;
    mutable QJsonObject    parameters_;
    mutable QJsonObject    integrator_;

};

} //end PASCAL_NS

#endif
