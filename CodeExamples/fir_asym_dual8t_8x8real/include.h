#ifndef INCLUDE_H
#define INCLUDE_H

// Kernel-specific based on intrinsics
#define AIE_MUL_LANES               16
#define AIE_POINTER_ADJUST          16

// FIR-specific
#define FIR_COEFF_BIT_SHIFT         7

// Simulation parameters
#define NUM_INPUT_WORDS             64
#define NUM_OUTPUT_WORDS            (NUM_INPUT_WORDS)
#define AIE_LOOP_CYCLES             (NUM_INPUT_WORDS / AIE_MUL_LANES)
#define INPUT_FILE                  "./SimInputs.txt"

// Kernel prototype
void fir_asym_dual8t_8x8real(input_window_int8 *a, output_window_int8 *c);

#endif // INCLUDE_H

