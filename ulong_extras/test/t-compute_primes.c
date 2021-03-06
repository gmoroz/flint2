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
/*****************************************************************************

    Copyright (C) 2009 William Hart
    Copyright (C) 2013 Fredrik Johansson

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "ulong_extras.h"

int main()
{
    slong i, lim = 1000000;
    flint_rand_t state;
    n_primes_t pg;
    mp_limb_t * ref_primes;
    double * ref_inverses;

    printf("compute_primes....");
    fflush(stdout);
    flint_randinit(state);

    ref_primes = flint_malloc(sizeof(mp_limb_t) * lim);
    ref_inverses = flint_malloc(sizeof(double) * lim);

    n_primes_init(pg);
    for (i = 0; i < lim; i++)
    {
        ref_primes[i] = n_primes_next(pg);
        ref_inverses[i] = n_precompute_inverse(ref_primes[i]);
    }
    n_primes_clear(pg);

    for (i = 0; i < 250; i++)
    {
        slong n;
        const mp_limb_t * primes;
        const double * inverses;

        n = n_randtest(state) % lim;

        primes = n_primes_arr_readonly(n + 1);
        inverses = n_prime_inverses_arr_readonly(n + 1);

        if (primes[n] != ref_primes[n] || inverses[n] != ref_inverses[n])
        {
            printf("FAIL!\n");
            printf("n = %ld, p1 = %lu, p2 = %lu\n", n, primes[n], ref_primes[n]);
            printf("inv1 = %g, inv2 = %g\n", inverses[n], ref_inverses[n]);
            abort();
        }

        if (n_randint(state, 20) == 0)
        {
            n_cleanup_primes();
        }
    }

    flint_free(ref_primes);
    flint_free(ref_inverses);
    n_cleanup_primes();

    flint_randclear(state);
    printf("PASS\n");
    return 0;
}

