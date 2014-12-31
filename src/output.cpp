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


#include "output.h"
#include "comm.h"
#include "version.h"
#include <cstring>

using namespace PASCAL_NS;

/* ----------------------------------------------------------------------
   Constructor / Destructor
------------------------------------------------------------------------- */

Output::Output(ParScale *ptr) : ParScaleBase(ptr),
    screen_(0),
    logfile_(0)
{

    version_ = new char[strlen(PASCAL_VERSION)+100];
    sprintf(version_,"Version: %s",PASCAL_VERSION);

    screen_ = stdout;
    if (0 == screen_)
        printf("Cannot open screen");
    else
        fprintf(screen_,"ParScale (%s)\n",version_);//", screen %d, this %d\n", version_,screen_,this);

    logfile_ = fopen("log.pascal","w");
    if (0 == logfile_)
        write_screen_one("Cannot open logfile");
    else
        fprintf(logfile_,"ParScale (%s)\n",version_);
}

Output::~Output()
{

    if (screen_) fclose(screen_);
    screen_ = 0;
    if (logfile_) fclose(logfile_);
    logfile_ = 0;
}

/* ----------------------------------------------------------------------
   write out to screen
------------------------------------------------------------------------- */

void Output::write_screen_one(const char *message) const
{
    if(comm().is_proc_0())
        printf("%s\n",message);
}

/* ---------------------------------------------------------------------- */
void Output::write_screen_all(const char *message) const
{
    fprintf(screen_,"[Process %d/%d] %s\n",comm().me(), comm().nprocs(),message);
}

/* ---------------------------------------------------------------------- */
void Output::write_log_one(const char *message) const
{
    if(comm().is_proc_0())
        fprintf(logfile_,"%s\n",message);
}

/* ---------------------------------------------------------------------- */
void Output::write_log_all(const char *message) const
{
    fprintf(logfile_,"[Process %d/%d] %s\n",comm().me(), comm().nprocs(),message);
}

/* ---------------------------------------------------------------------- */
void Output::write_time_one(double *message)
{
    fprintf(logfile_,"%g \n",*message);
}
