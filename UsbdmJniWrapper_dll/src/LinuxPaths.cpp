/*
 * LinuxPaths.cpp
 *
 *  Created on: 04/02/2013
 *      Author: pgo
 */

#include <stdlib.h>
#include <string>

std::string getEnvVar( std::string const & key )
{
    char * val = getenv( key.c_str() );
    return val == NULL ? std::string("") : std::string(val);
}

bool getUsbdmApplicationPath(std::string &path) {

   path = "/usr/local/share/usbdm/";
   return true;
}

bool getUsbdmDataPath(std::string &path) {

   std::string home = getEnvVar("HOME");
   path = home + "/.usbdm/";
   return true;
}



