#include <cardano.h>
#include <stdio.h>
#include "include.h"

alignas(8) int8_t taps[32] = { 18, 44, 54, 29, -3, -16, -7, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0 }; // from lowest order to highest, only first 8 used

void fir_asym_dual8t_8x8real(input_window_int8 * restrict in, output_window_int8 * restrict out)
	{
		v16acc48 acc;
		v32int8 rd_buffer = undef_v32int8();
		v64int8 fir_data_in = undef_v64int8();
		v16int8 fir_data_out = undef_v16int8();
		v32int8 coeffs = *(v32int8 *)taps;

		for(unsigned i = 0; i<AIE_LOOP_CYCLES; i++)
		chess_prepare_for_pipelining
		chess_flatten_loop
		{
			window_read(in, rd_buffer);
			fir_data_in = upd_w(fir_data_in, 0, rd_buffer);
			acc = mul16(fir_data_in, 0, 0x03020100, 4, 0x2110, coeffs, 0, 0x00000000, 2, 0x1010);
			fir_data_out = bsrs(acc, FIR_COEFF_BIT_SHIFT);
			window_writeincr(out, fir_data_out);
			window_incr(in, AIE_POINTER_ADJUST);
		}
	}
	