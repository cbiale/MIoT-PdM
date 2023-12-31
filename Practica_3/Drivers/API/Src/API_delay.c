/*
 * API_delay.c
 *
 *  Created on: Nov 1, 2023
 *      Author: cbiale
 */

#include "API_delay.h"

/**
 * @brief Se ejecuta en caso de que ocurran errores
 *
 * @param Ninguno
 * @retval Ninguno
 */
static void manejadorErrores(void) {
    // en caso de error se encienden los 3 leds
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
	// se espera
	HAL_Delay(2000);
	// se vuelve a cambiar el estado de los 3 leds
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
	// se espera
	HAL_Delay(1000);

	// en un bucle infinito se va cambiando el estado del led 3
	while (true) {
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
		HAL_Delay(1000);
	}
}


void delayInit( delay_t * delay, tick_t duration ) {
	// se comprueba variable existente
	if (delay == NULL) {
		manejadorErrores();
	} else {
		delay->duration = duration;
		delay->running = false;
		delay->startTime = 0; // siempre inicializar con valores
	}
}

bool_t delayRead( delay_t * delay ) {
	// varible que se usa para tener un unico punto de retorno
	bool resultado = false;
	if (delay == NULL) {
		manejadorErrores();
	} else {
		// no es necesario comparar explicitamente, pero es simple de leer
		if (delay->running == false) {
			delay->startTime = HAL_GetTick();
			delay->running = true;
		} else {
			if (HAL_GetTick() - delay->startTime >= delay->duration) {
				delay->running = false;
				resultado = true;
			}
		}
	}
	return resultado;
}

void delayWrite( delay_t * delay, tick_t duration ) {
	if (delay == NULL) {
		manejadorErrores();
	} else {
		delay->duration = duration;
	}
}
