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


#ifndef PASC_MODEL_CONTAINER_H
#define PASC_MODEL_CONTAINER_H

#include "stdio.h"
#include "pascal_base.h"
#include "pascal_base_interface.h"
#include "model_base.h"
#include <map>
#include <string>

namespace PASCAL_NS
{

class ModelContainer : public ParScaleBase, public ParScaleBaseInterface
{
    public:

      ModelContainer(ParScale *ptr);
      virtual ~ModelContainer();

      void parse_command(int narg,char const* const* arg);

      void begin_of_step();
      void pre_middle_of_step();
      void post_middle_of_step();
      void end_of_step();
      
      int modelCount() {return models_.size();};

      ModelBase* model(int idx) {return models_[idx];}    

    private:

      typedef ModelBase *(*ModelCreator)(ParScale*, char *name);
      std::map<std::string,ModelCreator> *model_map_;

      template <typename T> static ModelBase *model_creator(ParScale *ptr, char *name);

      vector<ModelBase*> models_;
      

};

} //end PASCAL_NS

#endif
