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

#ifndef PSC_INPUT_PROPERTIES_H
#define PSC_INPUT_PROPERTIES_H

namespace PASCAL_NS
{

  /* ----------------------------------------------------------------------
   definition of enums
  ------------------------------------------------------------------------- */

  // data types

  enum{ INPUT_TYPE_MIN,
        INPUT_TYPE_BOOL,
        INPUT_TYPE_INT,
        INPUT_TYPE_DOUBLE,
        INPUT_TYPE_MAX};


  class InputProperties
  {
      public:

        InputProperties(char *_name, int _input_type,
                        int _n_elem_,int _num_vec,int _len_vec)
        : name_(0),
          input_type_(_input_type),
          n_elem_(_n_elem_),
          num_vec_(_num_vec),
          len_vec_(_len_vec)
        {
            int n = strlen(_name) + 1;
            name_ = new char[n];
            strcpy(name_,_name);
        }

        ~InputProperties()
        {
            delete []name_;
        }

        bool check_correctness() const
        {
            if(input_type_ <= INPUT_TYPE_MIN ||
               input_type_ >= INPUT_TYPE_MAX
              )
                return false;
            return true;
        }

        const char* name() const
        {
            return name_;
        }

      private:

        char *name_;
        int input_type_;
        int n_elem_;
        int num_vec_;
        int len_vec_;
  };
}

#endif
