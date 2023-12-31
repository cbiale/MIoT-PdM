/*
 * API_sistema.c
 *
 *  Created on: Dec 6, 2023
 *      Author: cbiale
 */

#include <API_sistema.h>

void sistema_iniciar() {
	// inicia el sistema: I2c, lcd, uart, interfaz
	I2C_iniciar();
	lcd_iniciar();
	uart_iniciar();
//	sensor_fake_iniciar();
	sensor_fake_iniciar();
	debounceFSM_init();
	interfaz_iniciar();
}

void sistema_actualizar() {
	interfaz_actualizar();
	sensor_fake_actualizar();
	// sensor_fake_actualizar();
	debounceFSM_update();
}

