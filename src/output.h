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

#ifndef PASC_OUTPUT_H
#define PASC_OUTPUT_H

#include "stdio.h"
#include "pascal_base.h"
#include "pascal_base_interface.h"

namespace PASCAL_NS
{

class Output : public ParScaleBase, public ParScaleBaseInterface
{
    public:

      Output(ParScale *ptr);
      ~Output();

      void write_screen_one(const char *message) const;
      void write_screen_all(const char *message) const;

      void write_log_one(const char *message) const;
      void write_log_all(const char *message) const;
      void write_time_one(double *message);
      //void write_screen_log_one(const char *message);
      //void write_screen_log_all(const char *message);

      void write_integral_value(const char* ModelEqun,const char* IntegralProperty, double time, double value) ;

    private:

      FILE *screen_;                  // screen output
      FILE *logfile_;                 // logfile
      FILE *codeInfo_;                // JSON-style file for tracking code info
      char *version_;                 // basic identifier of code version
      FILE  *Property_file_;            // Integral property output file
      
};

} //end PASCAL_NS

#endif
