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

    Copyright (C) 2011 Fredrik Johansson

******************************************************************************/

#include <mpir.h>
#include "flint.h"
#include "nmod_mat.h"
#include "nmod_vec.h"
#include "fmpz.h"
#include "fmpz_mat.h"

void
fmpz_mat_multi_mod_ui_precomp(nmod_mat_t * residues, long nres, 
    const fmpz_mat_t mat, fmpz_comb_t comb, fmpz_comb_temp_t temp)
{
    long i, j, k;
    mp_ptr r;

    r = _nmod_vec_init(nres);

    for (i = 0; i < fmpz_mat_nrows(mat); i++)
    {
        for (j = 0; j < fmpz_mat_ncols(mat); j++)
        {
            fmpz_multi_mod_ui(r, fmpz_mat_entry(mat, i, j), comb, temp);
            for (k = 0; k < nres; k++)
                nmod_mat_entry(residues[k], i, j) = r[k];
        }
    }

    _nmod_vec_clear(r);
}

void
fmpz_mat_multi_mod_ui(nmod_mat_t * residues, long nres, const fmpz_mat_t mat)
{
    fmpz_comb_t comb;
    fmpz_comb_temp_t temp;
    mp_ptr primes;
    long i;

    primes = _nmod_vec_init(nres);
    for (i = 0; i < nres; i++)
        primes[i] = residues[i]->mod.n;
    fmpz_comb_init(comb, primes, nres);
    fmpz_comb_temp_init(temp, comb);

    fmpz_mat_multi_mod_ui_precomp(residues, nres, mat, comb, temp);

    fmpz_comb_clear(comb);
    fmpz_comb_temp_clear(temp);
    _nmod_vec_clear(primes);
}