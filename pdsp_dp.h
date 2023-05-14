/** @file pdsp_dp.h
 *
 * @author Falk Kyburz
 * @brief Double pulse generation module.
 * @details The pulse generator uses the following timing:
 *  pin
 *  ^
 *  |   |--------------------|           |-----------|
 *  |   |                    |           |           |
 *  |   |         p1         |           |    p2     |
 *  |   |                    |           |           |
 * -|---|--------------------|--------- -|-----------|-----------|--> t [us]
 *       <-------p1_ton-----> <-p1_toff-> <--p1_ton-> <-p1_toff->
 *
 * @copyright
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <https://unlicense.org>
 */

#ifndef PDSP_DP_H
#define PDSP_DP_H

/*==============================================================================
 INCLUDE FILES
 =============================================================================*/
#include <stdint.h>

/*==============================================================================
 CONFIGURATION
 =============================================================================*/
/** Enable serial communication. Uncomment to enable control from a terminal
 * (serial) interface.
 */
#define PDSP_DP_TERMINAL_ENABLED

/** Set terminal to verbose mode. */
#define PDSP_DP_TERMINAL_VERBOSE
/** Pin set function. Must be direct register access for performance. Uncomment
 * if there is no hardware available. */
// #define PDSP_DP_CONFIG_SET_PIN()

/** Pin clear function. Must be direct register access for performance.
 * Uncomment if there is no hardware available. */
// #define PDSP_DP_CONFIG_CLEAR_PIN()

#define PDSP_DP_DEFAULT_P1_TON_US 1000
#define PDSP_DP_DEFAULT_P1_TOFF_US 1000
#define PDSP_DP_DEFAULT_P2_TON_US 1000
#define PDSP_DP_DEFAULT_P2_TOFF_US 1000000

/*==============================================================================
 PUBLIC TYPES
 =============================================================================*/

/** Double pulse test data struct. */
typedef struct pdsp_dp_tag
{
    /** Calibration value for the microsecond delay function. */
    int32_t i32_delay_us_calib_static;
    /** Calibration value for the microsecond delay function. */
    int32_t i32_delay_us_calib_loops;
    /** The on time of the first pulse in microseconds. */
    int32_t i32_p1_ton_us;
    /** The off time of the first pulse in microseconds. */
    int32_t i32_p1_toff_us;
    /** The on time of the second pulse in microseconds. */
    int32_t i32_p2_ton_us;
    /** The off time of the second pulse in microseconds. */
    int32_t i32_p2_toff_us;
    /** Trigger state */
    uint8_t u8_trig;
} pdsp_dp_t;

/*==============================================================================
 PUBLIC FUNCTIONS
 =============================================================================*/

/**
 * @brief Initialize the double pulse module.
 * @param ps_data Pointer to double pulse data struct.
 * @param i32_delay_us_calib_static The static calibration value for delay
 * function.
 * @param i32_delay_us_calib_loops The dynamic calibration value for delay
 * function.
 */
extern void pdsp_dp_init(pdsp_dp_t *ps_data, int32_t i32_delay_us_calib_static,
                         int32_t i32_delay_us_calib_loops);

/**
 * @brief Task the double pulse module to be called periodically.
 * @details Blocks until pulse if finished if triggered. I the trigger input is
 * constantly true, it results in a continuous double pulse waveform. For
 * terminal control, set trigger to false.
 * @param ps_data Pointer to double pulse data struct.
 * @param u8_trigger Trigger input (non-retriggerable).
 */
extern void pdsp_dp_task(pdsp_dp_t *ps_data);

/**
 * @brief Set the on time of the first pulse.
 * @param ps_data Pointer to double pulse data struct.
 * @param i32_p1_ton_us The on time of the first pulse in microseconds.
 */
extern void pdsp_dp_set_p1_ton_us(pdsp_dp_t *ps_data, int32_t i32_p1_ton_us);

/**
 * @brief Set the off time of the first pulse.
 * @param ps_data Pointer to double pulse data struct.
 * @param i32_p1_toff_us The on time of the first pulse in microseconds.
 */
extern void pdsp_dp_set_p1_toff_us(pdsp_dp_t *ps_data, int32_t i32_p1_toff_us);

/**
 * @brief Set the on time of the second pulse.
 * @param ps_data Pointer to double pulse data struct.
 * @param i32_p2_ton_us The on time of the first pulse in microseconds.
 */
extern void pdsp_dp_set_p2_ton_us(pdsp_dp_t *ps_data, int32_t i32_p2_ton_us);

/**
 * @brief Set the off time of the second pulse.
 * @param ps_data Pointer to double pulse data struct.
 * @param i32_p2_toff_us The on time of the first pulse in microseconds.
 */
extern void pdsp_dp_set_p2_toff_us(pdsp_dp_t *ps_data, int32_t i32_p2_toff_us);

/**
 * @brief Trigger the double pulse waveform.
 * @param ps_data Pointer to double pulse data struct.
 */
extern void pdsp_dp_trig(pdsp_dp_t *ps_data);

#ifdef PDSP_DP_TERMINAL_ENABLED
extern void pdsp_dp_terminal_task(pdsp_dp_t *ps_data);
#endif /* PDSP_DP_TERMINAL_ENABLED */

#endif /* PDSP_DP_H */