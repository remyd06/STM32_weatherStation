/**
 * @file    bme280.c
 * @brief   BME280 driver over SPI1 (temperature, pressure, humidity).
 * @note    The integer compensation formulas (BME280_compensate_*) are
 *          Bosch's reference implementation from the BME280 datasheet,
 *          used as provided.
 */

#include "bme280.h"

/** @brief Running fine-resolution temperature, shared between the three compensation functions (set by T, read by P and H). */
BME280_S32_t	t_fine;

/**
 * @brief Assert the BME280 chip-select (SPI transaction start).
 */
void	CS_SPI1_BME280_LOW()
{
	GPIOC->BSRR = (0b1 << 20); /* BR4: reset PC4 -> CS low */
}

/**
 * @brief Release the BME280 chip-select (SPI transaction end).
 */
void	CS_SPI1_BME280_HIGH()
{
	GPIOC->BSRR = (0b1 << 4); /* BS4: set PC4 -> CS high */
}

/**
 * @brief Read the BME280 chip ID register (expected value: 0x60).
 * @param id Output: chip ID byte read from the sensor.
 */
void	BME280_GetID(uint8_t *id)
{
	uint8_t addr = 0xD0 | 0x80; /* reg 0xD0 (id), MSB set = SPI read */

	CS_SPI1_BME280_LOW();

	SPI_Transmit(SPI1, &addr);
	SPI_Receive(SPI1);

	SPI_Transmit(SPI1, &(uint8_t){0x00});
	*id = SPI_Receive(SPI1);

	CS_SPI1_BME280_HIGH();
}

/**
 * @brief Configure the sensor's power mode and oversampling for humidity,
 *        pressure and temperature (ctrl_hum and ctrl_meas registers).
 * @param mode   Power mode (sleep/forced/normal).
 * @param osrs_p Pressure oversampling.
 * @param osrs_t Temperature oversampling.
 * @param osrs_h Humidity oversampling.
 * @note  ctrl_hum only takes effect after ctrl_meas is written, per datasheet.
 */
void	BME280_SetMODE(uint8_t mode, uint8_t osrs_p, uint8_t osrs_t, uint8_t osrs_h)
{
	uint8_t	addr_ctrl_hum = 0x72;  /* write address of ctrl_hum (0xF2 & 0x7F) */

	CS_SPI1_BME280_LOW();

	SPI_Transmit(SPI1, &addr_ctrl_hum);
	SPI_Receive(SPI1);

	SPI_Transmit(SPI1, &osrs_h);
	SPI_Receive(SPI1);

	CS_SPI1_BME280_HIGH();

	uint8_t	addr_ctrl_meas = 0x74; /* write address of ctrl_meas (0xF4 & 0x7F) */
	uint8_t	config_ctrl_meas = (osrs_t << 5) | (osrs_p << 2) | mode;

	CS_SPI1_BME280_LOW();

	SPI_Transmit(SPI1, &addr_ctrl_meas);
	SPI_Receive(SPI1);

	SPI_Transmit(SPI1, &config_ctrl_meas);
	SPI_Receive(SPI1);

	CS_SPI1_BME280_HIGH();
}

/**
 * @brief Read the factory calibration/trim registers (0x88-0xA1 for T/P/H1,
 *        0xE1-0xE7 for H2-H6) into a BME280_calib_t.
 * @param calib Output: calibration parameters used by the compensation functions.
 * @note  Must be called once at startup, before BME280_ConvertDATA().
 */
void	BME280_GetTRIM(BME280_calib_t *calib)
{
	uint8_t 		lsb;
	uint8_t			msb;

	CS_SPI1_BME280_LOW();

	SPI_Transmit(SPI1, &(uint8_t){0x88});
	SPI_Receive(SPI1);

	//	dig_T1
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	lsb = (SPI_Receive(SPI1));
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	msb = (SPI_Receive(SPI1));
	calib->dig_T1 = (msb << 8) | lsb;

	//	dig_T2
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	lsb = (SPI_Receive(SPI1));
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	msb = (SPI_Receive(SPI1));
	calib->dig_T2 = (msb << 8) | lsb;

	//	dig_T3
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	lsb = (SPI_Receive(SPI1));
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	msb = (SPI_Receive(SPI1));
	calib->dig_T3 = (msb << 8) | lsb;

	//	dig_P1
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	lsb = (SPI_Receive(SPI1));
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	msb = (SPI_Receive(SPI1));
	calib->dig_P1 = (msb << 8) | lsb;

	//	dig_P2
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	lsb = (SPI_Receive(SPI1));
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	msb = (SPI_Receive(SPI1));
	calib->dig_P2 = (msb << 8) | lsb;

	//	dig_P3
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	lsb = (SPI_Receive(SPI1));
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	msb = (SPI_Receive(SPI1));
	calib->dig_P3 = (msb << 8) | lsb;

	//	dig_P4
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	lsb = (SPI_Receive(SPI1));
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	msb = (SPI_Receive(SPI1));
	calib->dig_P4 = (msb << 8) | lsb;

	//	dig_P5
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	lsb = (SPI_Receive(SPI1));
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	msb = (SPI_Receive(SPI1));
	calib->dig_P5 = (msb << 8) | lsb;

	//	dig_P6
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	lsb = (SPI_Receive(SPI1));
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	msb = (SPI_Receive(SPI1));
	calib->dig_P6 = (msb << 8) | lsb;

	//	dig_P7
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	lsb = (SPI_Receive(SPI1));
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	msb = (SPI_Receive(SPI1));
	calib->dig_P7 = (msb << 8) | lsb;

	//	dig_P8
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	lsb = (SPI_Receive(SPI1));
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	msb = (SPI_Receive(SPI1));
	calib->dig_P8 = (msb << 8) | lsb;

	//	dig_P9
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	lsb = (SPI_Receive(SPI1));
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	msb = (SPI_Receive(SPI1));
	calib->dig_P9 = (msb << 8) | lsb;

	SPI_Transmit(SPI1, &(uint8_t){0x00}); /* skip reserved byte 0xA0 */
	SPI_Receive(SPI1);

	//	dig_H1
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	msb = (SPI_Receive(SPI1));
	calib->dig_H1 = msb;

	CS_SPI1_BME280_HIGH();

	CS_SPI1_BME280_LOW();

	SPI_Transmit(SPI1, &(uint8_t){0xE1});
	SPI_Receive(SPI1);

	//	dig_H2
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	lsb = (SPI_Receive(SPI1));
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	msb = (SPI_Receive(SPI1));
	calib->dig_H2 = (msb << 8) | lsb;


	//	dig_H3
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	msb = (SPI_Receive(SPI1));
	calib->dig_H3 = msb;

	//	dig_H4
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	msb = (SPI_Receive(SPI1));
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	lsb = (SPI_Receive(SPI1));
	calib->dig_H4 = (msb << 4) | (lsb & 0x0F);

	//	dig_H5
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	msb = (SPI_Receive(SPI1));
	calib->dig_H5 = (msb << 4) | (lsb & 0x0F);

	//	dig_H6
	SPI_Transmit(SPI1, &(uint8_t){0x00});
	msb = (SPI_Receive(SPI1));
	calib->dig_H6 = msb;

	CS_SPI1_BME280_HIGH();
}

/**
 * @brief Read the 8 raw ADC bytes (pressure, temperature, humidity) starting
 *        at register 0xF7.
 * @param data Output: raw bytes in [temp_msb, temp_lsb, temp_xlsb,
 *             pres_msb, pres_lsb, pres_xlsb, hum_msb, hum_lsb] order,
 *             matching BME280_ConvertDATA()'s expected layout.
 */
void	BME280_GetDATA(uint8_t *data)
{

	CS_SPI1_BME280_LOW();

	SPI_Transmit(SPI1, &(uint8_t){0xF7}); //wake
	SPI_Receive(SPI1);

	SPI_Transmit(SPI1, &(uint8_t){0x00}); //pres msb
	data[3] = SPI_Receive(SPI1);
	SPI_Transmit(SPI1, &(uint8_t){0x00}); //pres lsb
	data[4] = SPI_Receive(SPI1);
	SPI_Transmit(SPI1, &(uint8_t){0x00}); //pres xlsb
	data[5] = SPI_Receive(SPI1);

	SPI_Transmit(SPI1, &(uint8_t){0x00}); //temp msb
	data[0] = SPI_Receive(SPI1);
	SPI_Transmit(SPI1, &(uint8_t){0x00}); //temp lsb
	data[1] = SPI_Receive(SPI1);
	SPI_Transmit(SPI1, &(uint8_t){0x00}); //temp xlsb
	data[2] = SPI_Receive(SPI1);

	SPI_Transmit(SPI1, &(uint8_t){0x00}); //hum msb
	data[6] = SPI_Receive(SPI1);
	SPI_Transmit(SPI1, &(uint8_t){0x00}); //hum lsb
	data[7] = SPI_Receive(SPI1);

	CS_SPI1_BME280_HIGH();
}

/**
 * @brief Bosch reference compensation formula (integer, fixed-point).
 * @param adc_T Raw 20-bit temperature ADC value.
 * @param calib Calibration parameters from BME280_GetTRIM().
 * @return      Temperature in DegC, resolution 0.01 DegC (e.g. 5123 = 51.23 DegC).
 * @note        Also updates the shared t_fine used by the P and H compensation.
 */
BME280_S32_t BME280_compensate_T_int32(BME280_S32_t adc_T, BME280_calib_t *calib)
{
    BME280_S32_t var1, var2, T;

    var1 = ((((adc_T >> 3) - ((BME280_S32_t)calib->dig_T1 << 1))) *
            ((BME280_S32_t)calib->dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((BME280_S32_t)calib->dig_T1)) *
              ((adc_T >> 4) - ((BME280_S32_t)calib->dig_T1))) >> 12) *
            ((BME280_S32_t)calib->dig_T3)) >> 14;
    t_fine = var1 + var2;
    T = (t_fine * 5 + 128) >> 8;

    return T;
}

/**
 * @brief Bosch reference compensation formula (integer, Q24.8 fixed-point).
 * @param adc_P Raw 20-bit pressure ADC value.
 * @param calib Calibration parameters from BME280_GetTRIM().
 * @return      Pressure in Pa as Q24.8 (divide by 256 for Pa), or 0 if the
 *              computation is undefined (division by zero guarded below).
 * @note        Requires BME280_compensate_T_int32() to have been called first
 *              (uses the shared t_fine).
 */
BME280_U32_t BME280_compensate_P_int64(BME280_S32_t adc_P, BME280_calib_t *calib)
{
    BME280_S64_t var1, var2, p;

    var1 = ((BME280_S64_t)t_fine) - 128000;
    var2 = var1 * var1 * (BME280_S64_t)calib->dig_P6;
    var2 = var2 + ((var1 * (BME280_S64_t)calib->dig_P5) << 17);
    var2 = var2 + (((BME280_S64_t)calib->dig_P4) << 35);
    var1 = ((var1 * var1 * (BME280_S64_t)calib->dig_P3) >> 8)
         + ((var1 * (BME280_S64_t)calib->dig_P2) << 12);
    var1 = (((((BME280_S64_t)1) << 47) + var1))
         * ((BME280_S64_t)calib->dig_P1) >> 33;
    if (var1 == 0)
        return 0;
    p = 1048576 - adc_P;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = (((BME280_S64_t)calib->dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = (((BME280_S64_t)calib->dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8)
      + (((BME280_S64_t)calib->dig_P7) << 4);

    return (BME280_U32_t)p;
}

/**
 * @brief Bosch reference compensation formula (integer, Q22.10 fixed-point).
 * @param adc_H Raw 16-bit humidity ADC value.
 * @param calib Calibration parameters from BME280_GetTRIM().
 * @return      Relative humidity as Q22.10 (divide by 1024 for %RH), clamped
 *              to the sensor's valid range [0, 100] %RH.
 * @note        Requires BME280_compensate_T_int32() to have been called first
 *              (uses the shared t_fine).
 */
BME280_U32_t BME280_compensate_H_int32(BME280_S32_t adc_H, BME280_calib_t *calib)
{
    BME280_S32_t v_x1_u32r;

    v_x1_u32r = (t_fine - ((BME280_S32_t)76800));
    v_x1_u32r = (((((adc_H << 14)
                - (((BME280_S32_t)calib->dig_H4) << 20)
                - (((BME280_S32_t)calib->dig_H5) * v_x1_u32r))
                + ((BME280_S32_t)16384)) >> 15)
              * (((((((v_x1_u32r * ((BME280_S32_t)calib->dig_H6)) >> 10)
              * (((v_x1_u32r * ((BME280_S32_t)calib->dig_H3)) >> 11)
              + ((BME280_S32_t)32768))) >> 10)
              + ((BME280_S32_t)2097152))
              * ((BME280_S32_t)calib->dig_H2)
              + 8192) >> 14));
    v_x1_u32r = (v_x1_u32r
              - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7)
              * ((BME280_S32_t)calib->dig_H1)) >> 4));
    v_x1_u32r = (v_x1_u32r < 0) ? 0 : v_x1_u32r;
    v_x1_u32r = (v_x1_u32r > 419430400) ? 419430400 : v_x1_u32r;

    return (BME280_U32_t)(v_x1_u32r >> 12);
}

/**
 * @brief Assemble the 20-bit raw ADC values from BME280_GetDATA()'s byte
 *        buffer and run them through the Bosch compensation formulas.
 * @param data        Raw bytes from BME280_GetDATA().
 * @param calib       Calibration parameters from BME280_GetTRIM().
 * @param data_struct Output: compensated temperature/pressure/humidity.
 */
void	BME280_ConvertDATA(uint8_t *data, BME280_calib_t *calib, BME280_data_t *data_struct)
{
	BME280_S32_t	tempT = (data[0] << 12) | (data[1] << 4) | (data[2] >> 4);
	BME280_U32_t	tempP = (data[3] << 12) | (data[4] << 4) | (data[5] >> 4);
	BME280_U32_t	tempH = (data[6] << 8) | (data[7] << 0);

	data_struct->temp = BME280_compensate_T_int32(tempT, calib);
	data_struct->pres = BME280_compensate_P_int64(tempP, calib);
	data_struct->hum = BME280_compensate_H_int32(tempH, calib);
}
