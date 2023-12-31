/*
 * API_sensor_fake.h
 *
 *  Created on: Dec 3, 2023
 *      Author: cbiale
 */

#ifndef API_INC_API_SENSOR_FAKE_H_
#define API_INC_API_SENSOR_FAKE_H_

#include "port.h"
#include "API_delay.h"
#include "API_uart.h"
#include "stdbool.h"


/**
 * @brief Inicia el sensor fake.
 *
 * Realiza las operaciones necesarias para iniciar el sensor fake.
 *
 * @return void
 */
void sensor_fake_iniciar();

/**
 * @brief Obtiene los datos del sensor fake y deja disponible los valores obtenidos.
 *
 * Realiza las operaciones necesarias para obtener los datos del sensor fake y
 * actualiza las variables que contienen los datos de temperatura y humedad.
 *
 * @return void
 */
void sensor_fake_actualizar ();

/**
 * @brief Obtiene la temperatura actual desde el sensor fake.
 *
 * Retorna la temperatura actual medida por el sensor fake.
 *
 * @return Temperatura actual en grados Celsius (float).
 */
float sensor_fake_obtener_temperatura();

/**
 * @brief Obtiene la humedad actual desde el sensor fake.
 *
 * Retorna la humedad actual medida por el sensor fake.
 *
 * @return Humedad actual en porcentaje (float).
 */
float sensor_fake_obtener_humedad();

/**
 * @brief Obtiene la secuencia de lectura del sensor fake.
 *
 * Retorna la secuencia de lectura del sensor fake, se usa para controlar si hay una nueva lectura.
 *
 * @return Secuencia de lectura actual.
 */
uint8_t sensor_fake_nueva_lectura();

#endif /* API_INC_API_SENSOR_FAKE_H_ */
