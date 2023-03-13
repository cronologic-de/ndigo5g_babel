#ifndef NDIGO_INTERNAL_INTERFACE_H
#define NDIGO_INTERNAL_INTERFACE_H
#include "Ndigo_common_interface.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef void (__stdcall *progress_callback_t) (size_t done, size_t total);
NDIGO_API int ndigo_flash_firmware(ndigo_device *device, unsigned char *firmware, size_t size, unsigned int flashOffset, progress_callback_t callback);
NDIGO_API int ndigo_invalidate_calibration_fw_update(ndigo_device *device);
//NDIGO_API int ndigo_compare_cal_with_flash(unsigned int * fileversion, unsigned int * version, bool * sameCal, bool * flashvalid, unsigned char * filedata, unsigned char * data);
NDIGO_API int ndigo_flash_calibration(ndigo_device *device);
NDIGO_API int ndigo_calibration_size(ndigo_device *device);
NDIGO_API int ndigo_flash_custom_calibration(ndigo_device *device, unsigned char *memory, size_t size);
NDIGO_API int ndigo_read_flash(ndigo_device *device, unsigned char *memory, size_t size, size_t flashOffset);
NDIGO_API int ndigo_enable_sync_pulse(ndigo_device *device, unsigned int pulse_period, bool enable);
NDIGO_API int ndigo_switch_hptdc_sync(ndigo_device* device, bool enable);
NDIGO_API short ndigo_get_hptdc_phase(ndigo_device* device);
NDIGO_API short ndigo_get_adc_phase(ndigo_device* device);
NDIGO_API unsigned __int64 ndigo_get_current_timestamp(ndigo_device* device);
NDIGO_API short ndigo_get_adc_phase(ndigo_device* device);
NDIGO_API int ndigo_get_phase312(ndigo_device* device);
NDIGO_API int ndigo_get_syncphase(ndigo_device* device);
NDIGO_API int ndigo250m_reset_read(ndigo_device *device);
NDIGO_API int ndigo250m_get_phase250(ndigo_device *device);
NDIGO_API int ndigo_set_test_mode(ndigo_device *device, bool ramp);

typedef struct {
	unsigned int adf4360_config;
} ndigo_internal_init_parameters;

/* init the given card without window calibration (or other long running stuff)*/
NDIGO_API ndigo_device *ndigo_custom_init(ndigo_init_parameters *params, ndigo_internal_init_parameters* int_params, int *error_code, const char** error_message, int fast);

/* init the given card without window calibration (or other long running stuff)*/
NDIGO_API ndigo_device *ndigo_avrg_custom_init(ndigo_init_parameters *params,int *error_code, const char** error_message, int fast);

NDIGO_API volatile ndigo_packet *ndigo250m_read_next_packet(ndigo_device *device, int* errorCode, char ** message);

const static double TRIG_DAC_BASELINE = 1.25;
const static double GATE_DAC_BASELINE = 1.25;
const static double TRIG_DAC_OFFSET = -0.35;
const static double GATE_DAC_OFFSET = -0.35;

#ifdef __cplusplus
}
#endif
#endif
