/** @file pdsp_dp_cfg.h
 *
 * @author Falk Kyburz
 * @brief Double pulse generation module configuration file.
 * @details This is a prepared config file for the TMS320F280049 microcontroller
 * running at 100 Mhz. Use the Debug view to trigger by setting the value
 * u32_trig. Timing values can be live adjusted in the debugger as well.
 * Attention: GPIO pin must have external pull-down!
 */

#ifndef PDSP_DP_CFG_H
#define PDSP_DP_CFG_H

/*==============================================================================
 INCLUDE FILES
 =============================================================================*/

#include "driverlib.h"

/*==============================================================================
 CONFIGURATION
 =============================================================================*/

/** Set GPIO number 0-31, 23 is LED4 on the Launchpad XL */
#define GPIO_NUMBER 23

/** Pin set function. Must be direct register access for performance.
 * Uncomment if there is no hardware available. */
#define PDSP_DP_CONFIG_SET_PIN()                                               \
    HWREG(GPIODATA_BASE + GPIO_O_GPASET) = (1ul << GPIO_NUMBER)

/** Pin clear function. Must be direct register access for performance.
 * Uncomment if there is no hardware available. */
#define PDSP_DP_CONFIG_CLEAR_PIN()                                             \
    HWREG(GPIODATA_BASE + GPIO_O_GPACLEAR) = (1ul << GPIO_NUMBER)

#define PDSP_DP_DEFAULT_CALIB_LOOPS 7
#define PDSP_DP_DEFAULT_P1_TON_US 100
#define PDSP_DP_DEFAULT_P1_TOFF_US 10
#define PDSP_DP_DEFAULT_P2_TON_US 10
#define PDSP_DP_DEFAULT_P2_TOFF_US 1000000

#endif /* PDSP_DP_CFG_H */
