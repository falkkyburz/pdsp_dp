/** @file pdsp_dp_cfg.h
 *
 * @author Falk Kyburz
 * @brief Double pulse generation module configuration file.

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

#ifndef PDSP_DP_CFG_H
#define PDSP_DP_CFG_H

/*==============================================================================
 INCLUDE FILES
 =============================================================================*/

/* TODO: Include your HAL */

/*==============================================================================
 CONFIGURATION
 =============================================================================*/
/** Enable serial communication. Uncomment to enable control from a terminal
 * (serial) interface.
 */
#define PDSP_DP_TERMINAL_ENABLED

/** Set terminal to verbose mode. */
// #define PDSP_DP_TERMINAL_VERBOSE
/** Pin set function. Must be direct register access for performance.
 * Uncomment if there is no hardware available. */
// #define PDSP_DP_CONFIG_SET_PIN()

/** Pin clear function. Must be direct register access for performance.
 * Uncomment if there is no hardware available. */
// #define PDSP_DP_CONFIG_CLEAR_PIN()

#define PDSP_DP_DEFAULT_CALIB_LOOPS 100
#define PDSP_DP_DEFAULT_P1_TON_US 10
#define PDSP_DP_DEFAULT_P1_TOFF_US 10
#define PDSP_DP_DEFAULT_P2_TON_US 10
#define PDSP_DP_DEFAULT_P2_TOFF_US 1000000

#endif /* PDSP_DP_CFG_H */
