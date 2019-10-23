/******************************************************************************
 *
 * Module: SmallOperatingSystem
 *
 * File Name: SOS_config.c
 *
 * Description: Operating system configurations source file
 *
 * Author: Ahmed Wael
 *
 *******************************************************************************/

#include "SOS_config.h"
#include "SOS.h"

OS_ConfigType OS_Config = {TIMER1,1};
OS_ConfigType *OS_Config_Ptr = &OS_Config;
Task_ConfigType Task_Config_arr[Tasks_NUM];

