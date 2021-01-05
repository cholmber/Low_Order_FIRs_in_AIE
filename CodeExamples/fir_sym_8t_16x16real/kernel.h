#pragma once

// Kernel-specific based on intrinsics
#define AIE_RD_BUFFER_V             16
#define AIE_MUL_LANES               8
#define AIE_POINTER_ADJUST          (AIE_RD_BUFFER_V - AIE_MUL_LANES)

// FIR-specific
#define FIR_COEFF_BIT_SHIFT         15

// Simulation parameters
#define NUM_INPUT_WORDS             32
#define NUM_OUTPUT_WORDS            (NUM_INPUT_WORDS)
#define AIE_LOOP_CYCLES             (NUM_INPUT_WORDS / AIE_MUL_LANES)
#define INPUT_FILE                  "./SimInputs.txt"

// Kernel prototype
void fir_sym_8t_16x16real(input_window_int16 *in, output_window_int16 *out);
