/*
 * CPP_LINK.cpp
 *
 *  Created on: Jul 12, 2019
 *      Author: madyn
 */

//#include "configuration.h"
#include "CPP_LINK.hpp"

//#ifdef PROJECT_MODULAR_POWER_LK432
//	#include "Power_CPU_APP.hpp"
//#endif
//
//#if (defined PROJECT_MODULAR_CPU_F767)
//	#include "TRICORDER_MK30_APP.hpp"
//#endif
//
//#if (defined PROJECT_TRICORDER_MK30_5)
//	#include "TRICORDER_MK30_5_APP.hpp"
//#endif
//
//
//#if (defined PROJECT_TRICORDER_MK40)
//	#include "TRICORDER_MK40_APP.hpp"
//#endif
//
//
//#if (defined PROJECT_TRICORDER_MK30_4)
//	#include "TRICORDER_MK30_4_APP.hpp"
//#endif

#include "main.h"

#ifdef __cplusplus
	extern "C"
	{
#endif

	void cpp_link (void)
		{
			APPLICATION_init();
		}

#ifdef __cplusplus
	}
#endif