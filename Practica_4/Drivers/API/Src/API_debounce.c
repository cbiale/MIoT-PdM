/*
 * API_debounce.c
 *
 *  Created on: Nov 8, 2023
 *      Author: cbiale
 */
#include "API_debounce.h"

/*
 * Definiciones para acceso al botón y led 1
 */
#define USER_Btn_Pin GPIO_PIN_13
#define USER_Btn_GPIO_Port GPIOC

/* Se saca debido a uso de readKey()
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
*/

/*
 * Enumeración que define los estados posibles
 */
typedef enum
{
    BUTTON_UP,
    BUTTON_FALLING,
    BUTTON_DOWN,
    BUTTON_RISING
} debounceState_t;

/* El tiempo de anti-rebote debe ser de 40 ms con un retardo no bloqueante como los
 * implementados en la práctica 3.
 */
const uint32_t duracionRetardo = 40u;
/*
 * Variable que mantiene el estado de la MEF
 */
static debounceState_t estado;
/*
 * Retardo usado para en control anti-retote
 */
static delay_t retardo;
/*
 * Variable interna usada por readKey() la inicializo en este punto
 */
static bool_t estadoReadKey = false;

/*
 * acciones realizadas al presionar el botón
 */
static void buttonPressed() {
	// La logica de velocidad la saco del driver para ello uso readKey()

	/* dejo como referencia lo original
	// se verifica la velocidad actual y se cambia por la no usada
	if (duracionVelocidadBaja == duracionVelocidadActual) {
		duracionVelocidadActual = duracionVelocidadAlta;
	} else {
		duracionVelocidadActual = duracionVelocidadBaja;
	}
	// se cambia el retardo asociado al toggleo del led
	delayWrite(&retardoLed, duracionVelocidadActual);
	*/
	estadoReadKey = true;
}

/*
 * acciones realizadas al liberar el botón
 */
static void buttonReleassed() {
}

/*
 * Inicio de la MEF
 */
void debounceFSM_init() {
	// estado inicial
	estado = BUTTON_UP;

	// se saca por uso de readKey()
	/*
	// velocidad inicial
	duracionVelocidadActual = duracionVelocidadBaja;
	// inicio y lectura para activar del retardo de toggleo
	delayInit(&retardoLed, duracionVelocidadActual);
	delayRead(&retardoLed);
	*/
}

/*
 * Actualiza la MEF
 */
void debounceFSM_update() {
	switch (estado) {
	case BUTTON_UP:
		// realiza una lectura del botón y si se encuentra presionado
		if (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin) != 0) {
			// cambia de estado
			estado = BUTTON_FALLING;
			// inicia y lee retardo anti-rebote
			delayInit(&retardo, duracionRetardo);
			delayRead(&retardo);
		}
		break;
	case BUTTON_FALLING:
		// verifica que se cumpla el retardo anti-rebote
		if (delayRead(&retardo)) {
			// realiza una lectura del botón y si se encuentra presionado
			if (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin) != 0) {
				// cambia de estado
				estado = BUTTON_DOWN;
				// invoca al evento asociado a el nuevo estado
				buttonPressed();
			} else {
				// si no se encuentra presionado el botón vuelve al estado original
				estado = BUTTON_UP;
			}
		}
		break;
	case BUTTON_DOWN:
		// realiza una lectura del botón y si no se encuentra presionado
		if (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin) == 0) {
			// cambia de estado
			estado = BUTTON_RISING;
			// inicia y lee retardo anti-rebote
			delayInit(&retardo, duracionRetardo);
			delayRead(&retardo);
		}
		break;
	case BUTTON_RISING:
		// verifica que se cumpla el retardo anti-rebote
		if (delayRead(&retardo)) {
			// realiza una lectura del botón y si no se encuentra presionado
			if (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin) == 0) {
				// cambia de estado
				estado = BUTTON_UP;
				// invoca al evento asociado a el nuevo estado
				buttonReleassed();
			} else {
				// si no se encuentra presionado el botón vuelve al estado original
				estado = BUTTON_DOWN;
			}
		}
		break;
	default:
		debounceFSM_init();
		break;
	}

}

/* La función readKey debe leer una variable interna del módulo y devolver true o false si la tecla fue presionada.  Si devuelve true, debe resetear (poner en false) el estado de la variable.*/
bool_t readKey() {
	// variable bool_t que se debe poner en false cuando se llame a la función readKey();
	// retorno el estado pero cambio la variable interna a false
	bool_t retornar = estadoReadKey;
	estadoReadKey = false;
	return retornar;
}

