/*=============================================================================

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

=============================================================================*/
/******************************************************************************

    Copyright (C) 2011, 2010 Sebastian Pancratz
    Copyright (C) 2009 William Hart

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_mod_poly.h"
#include "ulong_extras.h"

int
main(void)
{
    int i, result;
    flint_rand_t state;

    printf("mul....");
    fflush(stdout);

    flint_randinit(state);

    /* Check aliasing of a and b */
    for (i = 0; i < 2000; i++)
    {
        fmpz_t p;
        fmpz_mod_poly_t a, b, c;

        fmpz_init(p);
        fmpz_randtest_unsigned(p, state, 2 * FLINT_BITS);
        fmpz_add_ui(p, p, 2);

        fmpz_mod_poly_init(a, p);
        fmpz_mod_poly_init(b, p);
        fmpz_mod_poly_init(c, p);
        fmpz_mod_poly_randtest(b, state, n_randint(state, 50));
        fmpz_mod_poly_randtest(c, state, n_randint(state, 50));

        fmpz_mod_poly_mul(a, b, c);
        fmpz_mod_poly_mul(b, b, c);

        result = (fmpz_mod_poly_equal(a, b));
        if (!result)
        {
            printf("FAIL:\n");
            fmpz_mod_poly_print(a), printf("\n\n");
            fmpz_mod_poly_print(b), printf("\n\n");
            abort();
        }

        fmpz_mod_poly_clear(a);
        fmpz_mod_poly_clear(b);
        fmpz_mod_poly_clear(c);
        fmpz_clear(p);
    }

    /* Check aliasing of a and c */
    for (i = 0; i < 2000; i++)
    {
        fmpz_t p;
        fmpz_mod_poly_t a, b, c;

        fmpz_init(p);
        fmpz_randtest_unsigned(p, state, 2 * FLINT_BITS);
        fmpz_add_ui(p, p, 2);

        fmpz_mod_poly_init(a, p);
        fmpz_mod_poly_init(b, p);
        fmpz_mod_poly_init(c, p);
        fmpz_mod_poly_randtest(b, state, n_randint(state, 50));
        fmpz_mod_poly_randtest(c, state, n_randint(state, 50));

        fmpz_mod_poly_mul(a, b, c);
        fmpz_mod_poly_mul(c, b, c);

        result = (fmpz_mod_poly_equal(a, c));
        if (!result)
        {
            printf("FAIL:\n");
            fmpz_mod_poly_print(a), printf("\n\n");
            fmpz_mod_poly_print(c), printf("\n\n");
            abort();
        }

        fmpz_mod_poly_clear(a);
        fmpz_mod_poly_clear(b);
        fmpz_mod_poly_clear(c);
        fmpz_clear(p);
    }

    /* Check (b*c)+(b*d) = b*(c+d) */
    for (i = 0; i < 2000; i++)
    {
        fmpz_mod_poly_t a1, a2, b, c, d;
        fmpz_t p;

        fmpz_init(p);
        fmpz_randtest_unsigned(p, state, 2 * FLINT_BITS);
        fmpz_add_ui(p, p, 2);

        fmpz_mod_poly_init(a1, p);
        fmpz_mod_poly_init(a2, p);
        fmpz_mod_poly_init(b, p);
        fmpz_mod_poly_init(c, p);
        fmpz_mod_poly_init(d, p);
        fmpz_mod_poly_randtest(b, state, n_randint(state, 100));
        fmpz_mod_poly_randtest(c, state, n_randint(state, 100));
        fmpz_mod_poly_randtest(d, state, n_randint(state, 100));

        fmpz_mod_poly_mul(a1, b, c);
        fmpz_mod_poly_mul(a2, b, d);
        fmpz_mod_poly_add(a1, a1, a2);

        fmpz_mod_poly_add(c, c, d);
        fmpz_mod_poly_mul(a2, b, c);

        result = (fmpz_mod_poly_equal(a1, a2));
        if (!result)
        {
            printf("FAIL:\n");
            fmpz_mod_poly_print(a1), printf("\n\n");
            fmpz_mod_poly_print(a2), printf("\n\n");
            abort();
        }

        fmpz_mod_poly_clear(a1);
        fmpz_mod_poly_clear(a2);
        fmpz_mod_poly_clear(b);
        fmpz_mod_poly_clear(c);
        fmpz_mod_poly_clear(d);
        fmpz_clear(p);
    }

    flint_randclear(state);
    _fmpz_cleanup();
    printf("PASS\n");
    return 0;
}
