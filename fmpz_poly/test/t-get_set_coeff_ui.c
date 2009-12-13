/*============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

===============================================================================*/
/****************************************************************************

   Copyright (C) 2009 William Hart

*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "fmpz_poly.h"
#include "ulong_extras.h"

int main(void)
{
   int result;
   printf("get/set_coeff_ui....");
   fflush(stdout);
   
   ulong i, j, coeff;
   ulong n1, n2;
   
   for (i = 0; i < 1000UL; i++) 
   {
      fmpz_poly_t a;
      ulong length;

      fmpz_poly_init(a);
      length = n_randint(100) + 1;

      for (j = 0; j < 1000; j++)
      {
         n1 = n_randtest();
         coeff = n_randint(length);
         fmpz_poly_set_coeff_ui(a, coeff, n1);
         n2 = fmpz_poly_get_coeff_ui(a, coeff);

         result = (n1 == n2);
         if (!result)
         {
            printf("Error: n1 = %lu, n2 = %lu, coeff = %lu, length = %lu\n", n1, n2, coeff, length);
            abort();
         }
      }

      fmpz_poly_clear(a);      
   }
      
   _fmpz_cleanup();
   printf("PASS\n");
   return 0;
}