#ifndef INCLUDE_H
#define INCLUDE_H

// Kernel-specific based on intrinsics
#define AIE_MUL_LANES               8
#define AIE_POINTER_ADJUST          8

// FIR-specific
#define FIR_COEFF_BIT_SHIFT         7

// Simulation parameters
#define NUM_INPUT_WORDS             32
#define NUM_OUTPUT_WORDS            (NUM_INPUT_WORDS)
#define AIE_LOOP_CYCLES             (NUM_INPUT_WORDS / AIE_MUL_LANES)
#define INPUT_FILE                  "./SimInputs.txt"

// Kernel prototype
void fir_asym_8t_16x8real(input_window_int16 *a, output_window_int16 *c);

#endif // INCLUDE_H

