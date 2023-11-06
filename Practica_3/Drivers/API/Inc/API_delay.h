/*
 * API_delay.h
 *
 *  Created on: Nov 1, 2023
 *      Author: cbiale
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h" // se agrega para evitar un warning al compilar, portabilidad?

typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

/**
 * @brief Inicializa la estructura que almacena información del retardo
 *        Note: se debe llamar antes que cualquier otra función maneja retardos
 *
 * @param Puntero a la estructura delay_t donde se almacena información del retardo
 * @param Duración del retardo (expresado en ms)
 * @retval Ninguno
 */
void delayInit( delay_t * delay, tick_t duration );

/**
 * @brief Verifica si se completa el retardo configurado
 *
 * @param Puntero a la estructura delay_t donde se almacena información del retardo
 * @retval bool_t donde true si se ha completado y false en el caso contrario
 */
bool_t delayRead( delay_t * delay );

/**
 * @brief Cambia la duración de un retardo existente
 *
 * @param Puntero a la estructura delay_t donde se almacena información del retardo
 * @param Duración del retardo (expresado en ms)
 * @retval Ninguno
 */
void delayWrite( delay_t * delay, tick_t duration );

/**
 * @brief Se ejecuta en caso de que ocurran errores
 *
 * @param Ninguno
 * @retval Ninguno
 */
static void manejadorErrores(void);

#endif /* API_INC_API_DELAY_H_ */