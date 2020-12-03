/* ---------------------------------------------------------------
 * Test for FIR kernel with 16-bit real input and output
 * Reads inputs from a file and logs DUT outputs to the console.
 *
 * September 2020 = original version, verfied in Vitis v2020.1 (CH)
 * ---------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <cardano.h>
#include "include.h"

alignas(16) int16_t buffer_aie_in[NUM_INPUT_WORDS + AIE_POINTER_ADJUST];
alignas(16) int16_t buffer_aie_out[NUM_OUTPUT_WORDS];

int main()
	{
	// Setup and initialize windowed inputs and outputs
	window_internal aie_input;
	window_internal aie_output;
	window_init(&aie_input, 1, buffer_aie_in, (NUM_INPUT_WORDS + AIE_POINTER_ADJUST));
	window_init(&aie_output, 1, buffer_aie_out, NUM_OUTPUT_WORDS);

	// Read test inputs from source file
	int file_buffer;
	FILE *fp = fopen(INPUT_FILE, "r");

	for (int rd_iter = 0; rd_iter < (NUM_INPUT_WORDS + AIE_POINTER_ADJUST); rd_iter++)
		{
		fscanf(fp, "%d\n", &file_buffer);
		window_writeincr((output_window_int16 *)&aie_input, file_buffer);
		}

	// Send the window of data to the kernel
	fir_asym_8t_16x8real(get_input_window_int16(&aie_input), get_output_window_int16(&aie_output));

	// Read the output from the kernel
	for (int out_iter = 0; out_iter < NUM_OUTPUT_WORDS; out_iter++)
		{
		if (out_iter % 8 == 0)
			{
			printf("\n");
			}
		printf("aie_output[%d] = %d\n", out_iter, buffer_aie_out[out_iter]);
		}

	// Close the test data file
	fclose(fp);
	return 0;
	}
