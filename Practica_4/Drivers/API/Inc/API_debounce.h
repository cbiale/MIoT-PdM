/*
 * API_debounce.h
 *
 *  Created on: Nov 8, 2023
 *      Author: cbiale
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include <stdbool.h> // por uso de bool_t
#include "API_delay.h" // por uso de retardos


void debounceFSM_init();
void debounceFSM_update();

/* La función readKey debe leer una variable interna del módulo y devolver true o false si
 * la tecla fue presionada.  Si devuelve true, debe resetear (poner en false) el estado de
 * la variable.*/
bool_t readKey();

#endif /* API_INC_API_DEBOUNCE_H_ */
