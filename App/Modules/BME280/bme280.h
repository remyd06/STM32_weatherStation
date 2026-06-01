#ifndef BME280_H
#define BME280_H

# include "gpio.h"
# include "spi.h"

# define BME280_S32_t	int32_t
# define BME280_U32_t	uint32_t
# define BME280_S64_t	int64_t

typedef struct
{
	BME280_S32_t	temp;
	BME280_U32_t	pres;
	BME280_U32_t	hum;
} BME280_data_t;

typedef struct {
    uint16_t dig_T1;
    int16_t  dig_T2;
    int16_t  dig_T3;

    uint16_t dig_P1;
    int16_t  dig_P2;
    int16_t  dig_P3;
    int16_t  dig_P4;
    int16_t  dig_P5;
    int16_t  dig_P6;
    int16_t  dig_P7;
    int16_t  dig_P8;
    int16_t  dig_P9;

    uint8_t  dig_H1;
    int16_t  dig_H2;
    uint8_t  dig_H3;
    int16_t  dig_H4;
    int16_t  dig_H5;
    int8_t   dig_H6;
} BME280_calib_t;

void	BME280_GetID(uint8_t *id);
void	BME280_SetMODE(uint8_t mode, uint8_t osrs_p, uint8_t osrs_t, uint8_t osrs_h);
void	BME280_GetTRIM(BME280_calib_t *calib);
void	BME280_GetDATA();
void	BME280_ConvertDATA(uint8_t *data, BME280_calib_t *calib, BME280_data_t *data_struct);

#endif
