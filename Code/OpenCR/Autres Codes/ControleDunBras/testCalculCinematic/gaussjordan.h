#ifndef __ODAS_UTILS_GAUSSJORDAN
#define __ODAS_UTILS_GAUSSJORDAN

/**
   \file     gaussjordan.h
   \author   François Grondin <francois.grondin2@usherbrooke.ca>
   \version  2.0
   \date     2018-03-18
   \copyright

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct gaussjordan_obj {

  unsigned int nRowsCols;
  float * array;
  float epsilon;

} gaussjordan_obj;

gaussjordan_obj * gaussjordan_construct_zero(const unsigned int nRowsCols, const float epsilon);

void gaussjordan_destroy(gaussjordan_obj * obj);

void gaussjordan_process(gaussjordan_obj * obj, const float * src, float * dest);

#endif
