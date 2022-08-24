/*
 * mk_watchdog.c
 *
 *  Created on: 05 февр. 2019 г.
 *      Author: kulikovs
 */

#include "mk_watchdog.h"
#include "fsl_wdog.h"
#include "fsl_rcm.h"

#include "return_code.h"

#define WDOG_WCT_INSTRUCITON_COUNT (256U)

static RCM_Type *rcm_base = RCM;
static int disable_reset = 0;
static void WaitWctClose(WDOG_Type *base);
static void watchdog_kick(void);

uint16_t mk_watchdog_get_reset_count()
{
	return WDOG_GetResetCount(WDOG);
}

uint8_t mk_watchdog_get_reset_reason()
{
	if (!(RCM_GetPreviousResetSources(rcm_base) & kRCM_SourceWdog)) {
		return RESET_NORMAL;
	} else
		return RESET_WATCHDOG;
}

int8_t mk_watchdog_get_reset_reason_buff()
{
	if (!(RCM_GetStickyResetSources(rcm_base) & kRCM_SourceWdog)) {
		return RESET_NORMAL;
	} else
		return RESET_WATCHDOG;
}

void mk_watchdog_clean_reset_count()
{
	WDOG_ClearResetCount(WDOG);
}

void mk_watchdog_clean_reset_reason_buff()
{
	uint32_t mask = kRCM_SourceWdog;
	RCM_ClearStickyResetSources(rcm_base, mask);
	return;
}


int mk_watchdog_init(uint32_t time_ms)
{
#if(LIBS_DISABLE_WDOG == 1)
	return;
#endif

	wdog_config_t config;
	WDOG_GetDefaultConfig(&config);
	config.timeoutValue = time_ms;
	config.enableUpdate = true;
	watchdog_kick();
	config.enableWdog = true;
	WDOG_Init(WDOG, &config);
	WaitWctClose(WDOG);
	return RET_OK;
}


void mk_watchdog_refresh()
{
#if(LIBS_DISABLE_WDOG == 1)
	return;
#endif
	if (!disable_reset)
		watchdog_kick();
	return;
}
void mk_watchdog_make_mk_reset()
{
	disable_reset = 1;
	return;
}

static void WaitWctClose(WDOG_Type *base)
{
	/* Accessing register by bus clock */
	for (uint32_t i = 0; i < WDOG_WCT_INSTRUCITON_COUNT; i++) {
		(void) base->RSTCNT;
	}
}

// Обновление счетчика сторожевого таймера
static void watchdog_kick()
{
#if(LIBS_DISABLE_WDOG == 1)
	return;
#endif

	WDOG_Refresh(WDOG);
	return;
}

