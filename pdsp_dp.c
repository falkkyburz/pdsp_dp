/** @file pdsp_dp.c
 *
 * @author Falk Kyburz
 * @brief Double pulse generation module.
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

/*==============================================================================
 INCLUDE FILES
 =============================================================================*/
#include "pdsp_dp.h"
#include <stdint.h>
#include <stdlib.h>

#ifdef PDSP_DP_TERMINAL_ENABLED
#include <stdio.h>
#endif /* PDSP_DP_TERMINAL_ENABLED */

/*==============================================================================
 PRIVATE DEFINES
 =============================================================================*/
#ifndef PDSP_DP_CONFIG_SET_PIN
#if defined(PDSP_DP_TERMINAL_ENABLED) && defined(PDSP_DP_TERMINAL_VERBOSE)
#define PDSP_DP_CONFIG_SET_PIN() printf("set pin\n")
#else
#define PDSP_DP_CONFIG_SET_PIN()
#endif
#endif

#ifndef PDSP_DP_CONFIG_CLEAR_PIN
#if defined(PDSP_DP_TERMINAL_ENABLED) && defined(PDSP_DP_TERMINAL_VERBOSE)
#define PDSP_DP_CONFIG_CLEAR_PIN() printf("clear pin\n")
#else
#define PDSP_DP_CONFIG_CLEAR_PIN()
#endif
#endif

/*==============================================================================
 PRIVATE DEFINES
 =============================================================================*/
#ifdef PDSP_DP_TERMINAL_ENABLED
const char *s_header =
    "  |--------------------|           |-----------|\n"
    "  |                    |           |           |\n"
    "  |         p1         |           |    p2     |\n"
    "  |                    |           |           |\n"
    "--|--------------------|--------- -|-----------|-----------|--> t "
    "[us]\n"
    "   <-------p1_ton-----> <-p1_toff-> <--p1_ton-> <-p1_toff->\n"
    "Press 'h' then 'Enter' to configure pulse timing.\n"
    "Press 'c' then 'Enter' to configure pulse timing.\n"
    "Press 'q' then 'Enter' when running on PC to quit.\n"
    "Press 'space' then 'Enter' to trigger double pulse.";
#endif

/*==============================================================================
 PUBLIC FUNCTIONS
 =============================================================================*/

extern void pdsp_dp_init(pdsp_dp_t *ps_data)
{
    ps_data->i32_delay_us_calib_loops = PDSP_DP_DEFAULT_CALIB_LOOPS;
    ps_data->i32_p1_ton_us = PDSP_DP_DEFAULT_P1_TON_US;
    ps_data->i32_p1_toff_us = PDSP_DP_DEFAULT_P1_TOFF_US;
    ps_data->i32_p2_ton_us = PDSP_DP_DEFAULT_P2_TON_US;
    ps_data->i32_p2_toff_us = PDSP_DP_DEFAULT_P2_TOFF_US;
    ps_data->u32_trig = 0;
#ifdef PDSP_DP_TERMINAL_ENABLED
    printf("%s\n", s_header);
#endif
}

extern void pdsp_dp_task(pdsp_dp_t *ps_data)
{
    int32_t i32_count_p1_ton = 0;
    int32_t i32_count_p1_toff = 0;
    int32_t i32_count_p2_ton = 0;
    int32_t i32_count_p2_toff = 0;
    int32_t i32_count = 0;

    /* Run pulse generation*/
    if (ps_data->u32_trig)
    {
        ps_data->u32_trig = 0;
        /* Calculate counts for p1 */

        i32_count_p1_ton =
            ps_data->i32_p1_ton_us * ps_data->i32_delay_us_calib_loops;

        i32_count_p1_toff =
            ps_data->i32_p1_toff_us * ps_data->i32_delay_us_calib_loops;

        i32_count_p2_ton =
            ps_data->i32_p2_ton_us * ps_data->i32_delay_us_calib_loops;

        i32_count_p2_toff =
            ps_data->i32_p2_toff_us * ps_data->i32_delay_us_calib_loops;

#ifdef PDSP_DP_TERMINAL_ENABLED
#ifdef PDSP_DP_TERMINAL_VERBOSE
        printf("p1_ton_us  = %i\n", ps_data->i32_p1_ton_us);
        printf("p1_toff_us = %i\n", ps_data->i32_p1_toff_us);
        printf("p2_ton_us  = %i\n", ps_data->i32_p2_ton_us);
        printf("p2_toff_us = %i\n", ps_data->i32_p2_toff_us);
        printf("i32_count_p1_ton = %i\n", i32_count_p1_ton);
        printf("i32_count_p1_toff = %i\n", i32_count_p1_toff);
        printf("i32_count_p2_ton = %i\n", i32_count_p2_ton);
        printf("i32_count_p2_toff = %i\n", i32_count_p2_toff);
#endif
#endif

        PDSP_DP_CONFIG_SET_PIN();
        for (i32_count = 0; i32_count < i32_count_p1_ton; i32_count++)
        {
            /* Wait, do nothing */
        }
        PDSP_DP_CONFIG_CLEAR_PIN();
        for (i32_count = 0; i32_count < i32_count_p1_toff; i32_count++)
        {
            /* Wait, do nothing */
        }
        PDSP_DP_CONFIG_SET_PIN();
        for (i32_count = 0; i32_count < i32_count_p2_ton; i32_count++)
        {
            /* Wait, do nothing */
        }
        PDSP_DP_CONFIG_CLEAR_PIN();
        for (i32_count = 0; i32_count < i32_count_p2_toff; i32_count++)
        {
            /* Wait, do nothing */
        }
    }
}

extern void pdsp_dp_set_p1_ton_us(pdsp_dp_t *ps_data, int32_t i32_p1_ton_us)
{
    ps_data->i32_p1_ton_us = i32_p1_ton_us;
}

extern void pdsp_dp_set_p1_toff_us(pdsp_dp_t *ps_data, int32_t i32_p1_toff_us)
{
    ps_data->i32_p1_toff_us = i32_p1_toff_us;
}

extern void pdsp_dp_set_p2_ton_us(pdsp_dp_t *ps_data, int32_t i32_p2_ton_us)
{
    ps_data->i32_p2_ton_us = i32_p2_ton_us;
}

extern void pdsp_dp_set_p2_toff_us(pdsp_dp_t *ps_data, int32_t i32_p2_toff_us)
{
    ps_data->i32_p2_toff_us = i32_p2_toff_us;
}

extern void pdsp_dp_trig(pdsp_dp_t *ps_data) { ps_data->u32_trig = 1; }

#ifdef PDSP_DP_TERMINAL_ENABLED
extern void pdsp_dp_terminal_task(pdsp_dp_t *ps_data)
{
    char c_current = 0;
    int status = 1;
    int scan_value = 0;
    printf(">");
    scanf("%c", &c_current);
    if (c_current == 'c')
    {
        printf("p1_ton_us  = ");
        status = scanf("%i", &scan_value);
        if (status == 1)
        {
            scan_value = (scan_value > 0) ? scan_value : 0;
            pdsp_dp_set_p1_ton_us(ps_data, scan_value);
        }
        else
        {
            fflush(stdin);
            clearerr(stdin);
            printf("Failed, value not changed!\n");
        }
        printf("p1_toff_us = ");
        status = scanf("%i", &scan_value);
        if (status == 1)
        {
            scan_value = (scan_value > 0) ? scan_value : 0;
            pdsp_dp_set_p1_toff_us(ps_data, scan_value);
        }
        else
        {
            fflush(stdin);
            clearerr(stdin);
            printf("Failed, value not changed!\n");
        }
        printf("p2_ton_us  = ");
        status = scanf("%i", &scan_value);
        if (status == 1)
        {
            scan_value = (scan_value > 0) ? scan_value : 0;
            pdsp_dp_set_p2_ton_us(ps_data, scan_value);
        }
        else
        {
            fflush(stdin);
            clearerr(stdin);
            printf("Failed, value not changed!\n");
        }
        printf("p2_toff_us = ");
        status = scanf("%i", &scan_value);
        if (status == 1)
        {
            scan_value = (scan_value > 0) ? scan_value : 0;
            pdsp_dp_set_p2_toff_us(ps_data, scan_value);
        }
        else
        {
            fflush(stdin);
            clearerr(stdin);
            printf("Failed, value not changed!\n");
        }
        c_current = 'i';
    }
    if (c_current == 'h')
    {
        printf("Help:");
        printf("%s\n", s_header);
    }
    if (c_current == 'i')
    {
        printf("Timing info:\n");
        printf("p1_ton_us  = %i\n", ps_data->i32_p1_ton_us);
        printf("p1_toff_us = %i\n", ps_data->i32_p1_toff_us);
        printf("p2_ton_us  = %i\n", ps_data->i32_p2_ton_us);
        printf("p2_toff_us = %i\n", ps_data->i32_p2_toff_us);
    }
#ifdef __MINGW64__
    if (c_current == 'q')
    {
        exit(0);
    }
#endif
    if (c_current == ' ')
    {
        printf("Triggered!\n");
        pdsp_dp_trig(ps_data);
    }
}
#endif
