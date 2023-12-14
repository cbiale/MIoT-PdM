#include "API_sensor_fake.h"

/* ------------------------------- tipos de datos ------------------------------- */

/**
 * @brief Enumeración que representa los estados del sensor ficticio.
 *
 * Define los posibles estados del sensor ficticio, que incluyen "ESPERA" y "LECTURA".
 */
typedef enum {
    ESPERA,      ///< Estado de espera del sensor ficticio.
    LECTURA      ///< Estado de lectura del sensor ficticio.
} estado_sensor_fake_t;


/**
 * @brief Estructura que representa el estado interno del sensor en el sistema.
 *
 * Contiene información relacionada con la temperatura, la humedad, una bandera de nueva lectura y un índice de siguiente valor a leer.
 */
typedef struct {
    float temperatura;       ///< Temperatura actual del sensor.
    float humedad;           ///< Humedad actual del sensor.
    uint8_t nueva_lectura;   ///< Bandera (en formato índice) que indica si se realizó una nueva lectura.
    uint8_t siguiente_valor; ///< índice que determina lugar dentro del arreglo para obtener el siguiente valor de temperatura y humedad.
} estado_interno_t;

/* --------------------------------- Constantes --------------------------------- */

#define SENSOR_FAKE_CONTROL_LECTURAS      5    // mayor valor de contador de lecturas realizadas
#define SENSOR_FAKE_LECTURAS_ARREGLO      7    // cantidad de lecturas fake en el arreglo
#define SENSOR_FAKE_ESPERA_ENTRE_LECTURAS 3000 // espera entre lecturas del sensor

/* ----------------------------- Variables privadas ----------------------------- */

/**
 * @brief Estado actual del sensor ficticio.
 *
 * Representa el estado actual del sensor ficticio en la aplicación.
 */
static estado_sensor_fake_t estado;

/**
 * @brief Estado interno actual del sensor ficticio.
 *
 * Representa el estado interno del sensor ficticio en la aplicación.
 */
static estado_interno_t estado_interno;

/**
 * @brief Maneja la espera entre lecturas del sensor.
 *
 */
static delay_t espera;

/**
 * @brief Valores ficticios de temperatura usados por el sensor.
 *
 */
static float valores_temperatura[SENSOR_FAKE_LECTURAS_ARREGLO] = { 33.3, 33.0,
		29.8, 29.7, 29.9, 31.5, 32.3 };

/**
 * @brief Valores ficticios de humedad usados por el sensor.
 *
 */
static float valores_humedad[SENSOR_FAKE_LECTURAS_ARREGLO] = { 70, 69.5, 67.7,
		67.5, 67.7, 70.5, 71 };

/* ---------------------- Prototipos de funciones privadas ---------------------- */

// Realiza una lectura simulada de un sensor ficticio.
static void sensor_fake_realizar_lectura();

/* ---------------------------------- Funciones --------------------------------- */

// inicia el sensor fake (no realiza nada, es a efectos de homogeneizar)
void sensor_fake_iniciar() {
	estado_interno.temperatura = -1.0;
	estado_interno.humedad = -1.0;
	estado_interno.siguiente_valor = -1;
	estado_interno.nueva_lectura = -1;
	estado = LECTURA;
}

// actualiza el estado del sensor_fake
void sensor_fake_actualizar() {
	switch (estado) {
	case LECTURA:
		sensor_fake_realizar_lectura();
		estado = ESPERA;
		delayInit(&espera, SENSOR_FAKE_ESPERA_ENTRE_LECTURAS);
		if (estado_interno.nueva_lectura < SENSOR_FAKE_CONTROL_LECTURAS) {
			estado_interno.nueva_lectura++;
		} else {
			estado_interno.nueva_lectura = 0;
		}
		break;
	case ESPERA:
		if (delayRead(&espera)) {
			estado = LECTURA;
		}
		break;
	default:
		estado = ESPERA;
	}
}

// retorna el valor actual de temperatura
// permite que se obtenga de forma externa el valor de temperatura
float sensor_fake_obtener_temperatura() {
	return estado_interno.temperatura;
}

// retorna el valor actual de temperatura
// permite que se obtenga de forma externa el valor de humedad
float sensor_fake_obtener_humedad() {
	return estado_interno.humedad;
}

// retorna si ha realizado una nueva lectura
uint8_t sensor_fake_nueva_lectura() {
	return estado_interno.nueva_lectura;
}

/* ------------------------------ Funciones privadas ---------------------------- */


/**
 * @brief Realiza una lectura simulada de un sensor ficticio.
 *
 * Esta función simula la realización de una lectura en un sensor ficticio.
 * Es posible ajustar la lógica interna según las necesidades de simulación.
 *
 * @return void
 */
static void sensor_fake_realizar_lectura() {
	if (estado_interno.siguiente_valor < SENSOR_FAKE_LECTURAS_ARREGLO - 1) {
		estado_interno.siguiente_valor++;
	} else {
		estado_interno.siguiente_valor = 0;
	}
	estado_interno.temperatura = valores_temperatura[estado_interno.siguiente_valor];
	estado_interno.humedad = valores_humedad[estado_interno.siguiente_valor];
}
