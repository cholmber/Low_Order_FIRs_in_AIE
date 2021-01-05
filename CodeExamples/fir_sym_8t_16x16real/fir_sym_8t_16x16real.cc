#include <adf.h>
#include <stdio.h>
#include "kernel.h"

alignas(16) int16_t taps[16] = { -1371, -63, 6005, 12679, 12679, 6005, -63, -1371,
	0, 0, 0, 0, 0, 0, 0, 0 }; // from lowest order to highest, only first 4 used due to symmetry

void fir_sym_8t_16x16real(input_window_int16 * restrict in, output_window_int16 * restrict out)
	{
		v8acc48 acc;
		v16int16 rd_buffer = undef_v16int16();
		v32int16 fir_data_in = undef_v32int16();
		v8int16 fir_data_out = undef_v8int16();
		v16int16 coeffs = *(v16int16 *)taps;

		for(unsigned i = 0; i<AIE_LOOP_CYCLES; i++)
		chess_prepare_for_pipelining
		{
			window_read(in, rd_buffer);
			fir_data_in = upd_w(fir_data_in, 0, rd_buffer);
			acc = mul8_sym(fir_data_in, 0, 0x03020100, 2, 0x2110, 6, 0x1201, coeffs, 0, 0x00000000, 1);
			fir_data_out = srs(acc, FIR_COEFF_BIT_SHIFT);
			window_writeincr(out, fir_data_out);
			window_incr(in, AIE_POINTER_ADJUST);
		}
	}
	