/*
 * THIS FILE IS AUTOMATICALLY GENERATED
 *
 * Generator:    sensirion-driver-generator 0.9.0
 * Product:      sf06_lf
 * Version:      1.0
 */
/*
 * Copyright (c) 2022, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "sf06_lf_i2c.h"
#include "sensirion_common.h"
#include "sensirion_i2c.h"
#include "sensirion_i2c_hal.h"

static uint8_t _i2c_address;

void init_driver(uint8_t i2c_address) {
    _i2c_address = i2c_address;
}

int16_t sf06_lf_start_h2o_continuous_measurement() {
    int16_t local_error = NO_ERROR;
    uint8_t local_buffer[2] = {0};
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command_to_buffer(local_buffer, local_offset, 0x3608);
    local_error =
        sensirion_i2c_write_data(_i2c_address, local_buffer, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(12 * 1000);
    return local_error;
}

int16_t sf06_lf_start_ipa_continuous_measurement() {
    int16_t local_error = NO_ERROR;
    uint8_t local_buffer[2] = {0};
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command_to_buffer(local_buffer, local_offset, 0x3615);
    local_error =
        sensirion_i2c_write_data(_i2c_address, local_buffer, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(12 * 1000);
    return local_error;
}

int16_t sf06_lf_read_measurement_data_raw(int16_t* raw_flow,
                                          int16_t* raw_temperature,
                                          uint16_t* signaling_flags) {
    int16_t local_error = NO_ERROR;
    uint8_t local_buffer[9] = {0};
    local_error =
        sensirion_i2c_read_data_inplace(_i2c_address, local_buffer, 6);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *raw_flow = sensirion_common_bytes_to_int16_t(&local_buffer[0]);
    *raw_temperature = sensirion_common_bytes_to_int16_t(&local_buffer[2]);
    *signaling_flags = sensirion_common_bytes_to_uint16_t(&local_buffer[4]);
    return local_error;
}

int16_t sf06_lf_stop_continuous_measurement() {
    int16_t local_error = NO_ERROR;
    uint8_t local_buffer[2] = {0};
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command_to_buffer(local_buffer, local_offset, 0x3ff9);
    local_error =
        sensirion_i2c_write_data(_i2c_address, local_buffer, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(1 * 1000);
    return local_error;
}

int16_t sf06_lf_start_single_thermal_conductivity_measurement_sync() {
    int16_t local_error = NO_ERROR;
    uint8_t local_buffer[2] = {0};
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command_to_buffer(local_buffer, local_offset, 0x3646);
    local_error =
        sensirion_i2c_write_data(_i2c_address, local_buffer, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(2300 * 1000);
    return local_error;
}

int16_t sf06_lf_start_single_thermal_conductivity_measurement_async() {
    int16_t local_error = NO_ERROR;
    uint8_t local_buffer[2] = {0};
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command_to_buffer(local_buffer, local_offset, 0x3646);
    local_error =
        sensirion_i2c_write_data(_i2c_address, local_buffer, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    return local_error;
}

int16_t sf06_lf_read_thermal_conductivity_measurement_data(
    int16_t* thermal_conductivity, int16_t* raw_temperature,
    int16_t* raw_delta_temperature) {
    int16_t local_error = NO_ERROR;
    uint8_t local_buffer[9] = {0};
    local_error =
        sensirion_i2c_read_data_inplace(_i2c_address, local_buffer, 6);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *thermal_conductivity = sensirion_common_bytes_to_int16_t(&local_buffer[0]);
    *raw_temperature = sensirion_common_bytes_to_int16_t(&local_buffer[2]);
    *raw_delta_temperature =
        sensirion_common_bytes_to_int16_t(&local_buffer[4]);
    return local_error;
}

int16_t sf06_lf_enter_sleep() {
    int16_t local_error = NO_ERROR;
    uint8_t local_buffer[2] = {0};
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command_to_buffer(local_buffer, local_offset, 0x3677);
    local_error =
        sensirion_i2c_write_data(_i2c_address, local_buffer, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    return local_error;
}

int16_t sf06_lf_exit_sleep() {
    uint8_t local_buffer[2] = {0};
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command_to_buffer(local_buffer, local_offset, 0x0);
    sensirion_i2c_write_data(_i2c_address, local_buffer, local_offset);
    // not checking for error as write is not acknowledged on sensor wakeup
    sensirion_i2c_hal_sleep_usec(25 * 1000);
    return NO_ERROR;
}

int16_t sf06_lf_read_product_identifier(uint32_t* product_identifier,
                                        uint8_t* serial_number,
                                        uint16_t serial_number_size) {
    int16_t local_error = 0;
    local_error = sf06_lf_read_product_identifier_prepare();
    if (local_error != NO_ERROR) {
        return local_error;
    }
    local_error = ll_sf06_lf_read_product_identifier(
        product_identifier, serial_number, serial_number_size);
    return local_error;
}

int16_t sf06_lf_read_product_identifier_prepare() {
    int16_t local_error = NO_ERROR;
    uint8_t local_buffer[2] = {0};
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command_to_buffer(local_buffer, local_offset, 0x367c);
    local_error =
        sensirion_i2c_write_data(_i2c_address, local_buffer, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    return local_error;
}

int16_t ll_sf06_lf_read_product_identifier(uint32_t* product_identifier,
                                           uint8_t* serial_number,
                                           uint16_t serial_number_size) {
    int16_t local_error = NO_ERROR;
    uint8_t local_buffer[18] = {0};
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command_to_buffer(local_buffer, local_offset, 0xe102);
    local_error =
        sensirion_i2c_write_data(_i2c_address, local_buffer, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    local_error =
        sensirion_i2c_read_data_inplace(_i2c_address, local_buffer, 12);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *product_identifier = sensirion_common_bytes_to_uint32_t(&local_buffer[0]);
    sensirion_common_copy_bytes(&local_buffer[4], serial_number,
                                serial_number_size);
    return local_error;
}
