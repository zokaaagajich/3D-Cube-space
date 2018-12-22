#ifndef _TIMERS_H_
#define _TIMERS_H_

#define TIMER_MS 10
#define TIMER_MOVE 1
#define TIMER_Y 2
#define TIMER_ILLUSION 3
#define TIMER_EXPLOSION 4
#define TIMER_MIX 5

/* Tajmer za animiranje inicijalnih rotacija */
void on_timer_move(int value);
/* Tajmer za inicijalnu animaciju pravljenja kocke */
void on_timer_y(int value);
/* Tajmer za animiranje iluzije */
void on_timer_illusion(int value);
/* Tajmer za animiranje eksplozije */
void on_timer_explosion(int value);
/* Tajmer za animiranje kocki koje se prave sa misom */
void on_timer_mix(int value);

#endif
