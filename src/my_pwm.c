/*
 * my_pwm.c
 *
 *  Created on: 2 de mar de 2023
 *      Author: liwka
 */


#include "driverlib.h"
#include "my_pwm.h"


#define TIMER_PERIOD 1600
#define DUTY_CYCLE1  400
#define DUTY_CYCLE2  1200


void pwm_init (void)
{
    //P1.2 and P1.3 output
    //P1.2 and P1.3 options select
    GPIO_setAsPeripheralModuleFunctionOutputPin(
        GPIO_PORT_P4,
        GPIO_PIN6 + GPIO_PIN7,
        GPIO_TERNARY_MODULE_FUNCTION
        );

    //Start timer
    Timer_A_initUpModeParam pwm_param = {
     .clockSource = TIMER_A_CLOCKSOURCE_SMCLK,
     .clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1,
     .timerPeriod = TIMER_PERIOD,
     .timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE,
     .captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,
     .timerClear = TIMER_A_DO_CLEAR,
     .startTimer = false
    };
    Timer_A_initUpMode(TIMER_A1_BASE, &pwm_param);

    Timer_A_startCounter(   TIMER_A1_BASE,
        TIMER_A_UP_MODE
        );

    //Initialize compare mode to generate PWM1
    Timer_A_initCompareModeParam initComp1Param = {0};
    initComp1Param.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    initComp1Param.compareInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE;
    initComp1Param.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    initComp1Param.compareValue = DUTY_CYCLE1;
    Timer_A_initCompareMode(TIMER_A1_BASE, &initComp1Param);

    //Initialize compare mode to generate PWM2
    Timer_A_initCompareModeParam initComp2Param = {0};
    initComp2Param.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;
    initComp2Param.compareInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE;
    initComp2Param.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    initComp2Param.compareValue = DUTY_CYCLE2;
    Timer_A_initCompareMode(TIMER_A1_BASE, &initComp2Param);
}

