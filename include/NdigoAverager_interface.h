//
// Header file containing structs and #defines specific for NdigoAverager
// The current driver version for Ndigo devices is 1.4.3.0
//

#ifndef NDIGOAVERAGER_INTERFACE_H
#define NDIGOAVERAGER_INTERFACE_H
#include "Ndigo_common_interface.h"
#ifdef __cplusplus
extern "C" {
#endif

#define NDIGO_AVRG_ADC_MODE_A 8  // NDIGO_ADC_MODE_A
#define NDIGO_AVRG_ADC_MODE_B 9  // NDIGO_ADC_MODE_B
#define NDIGO_AVRG_ADC_MODE_C 10 // NDIGO_ADC_MODE_C
#define NDIGO_AVRG_ADC_MODE_D 11 // NDIGO_ADC_MODE_D

#define NDIGO_AVRG_TRIGGER_NONE 0
#define NDIGO_AVRG_TRIGGER_TDC 8   // NDIGO_TRIGGER_TDC
#define NDIGO_AVRG_TRIGGER_GATE 9  // NDIGO_TRIGGER_GATE
#define NDIGO_AVRG_TRIGGER_AUTO 14 // NDIGO_TRIGGER_AUTO

#define NDIGO_AVRG_MAX_PRECURSOR 31

/* Return output in the range -32768 to 32767*/
#define NDIGO_AVRG_OUTPUT_MODE_SIGNED16 0 // NDIGO_OUTPUT_MODE_SIGNED16
/* Return the native range 0 - 1023*/
#define NDIGO_AVRG_OUTPUT_MODE_RAW 1        // NDIGO_OUTPUT_MODE_RAW
#define NDIGO_AVRG_OUTPUT_MODE_CUSTOM 2     // NDIGO_OUTPUT_MODE_CUSTOM
#define NDIGO_AVRG_OUTPUT_MODE_CUSTOM_INL 3 // NDIGO_OUTPUT_MODE_CUSTOM_INL

#define NDIGO_AVRG_CHANNEL_COUNT 4

#define NDIGO_AVRG_MAX_WINDOW_SIZE 16384 // max averaging window size

/* A function that maps a value between 0 and 1 to a 16-bit output value ), must
 * be monotonous */
typedef short (*lut_func)(int channel, float x);

/* Contains all user changeable settings*/
typedef struct {
    /* size in bytes*/
    int size;

    /* A version number that is increased when the definition of the structure
     * is changed. The increment can be larger than one to match driver version
     * numbers or similar. Set to 0 for all versions up to first release.*/
    int version;

    /* ADCMODE as defined above NDIGOAVERAGER_ADC_MODE*/
    int adc_mode;

    /* Minimum bandwidth required by application */
    double bandwidth;

    /* Sets the offset-values to dac_neutral +- this value in volts.
       (Programmed parameter is dac_neutral +- (channel_offset*64k/2.5).
       Defaults to 0.
    */
    double analog_offset[NDIGO_AVRG_CHANNEL_COUNT];

    /* Set DAC channels 5 (GATE) and 6 (TRIG). Defaults for both are 1.95V. */
    double dc_offset[2];

    //
    int channel_enable;

    //
    int precursor;

    //
    int output_scale;

    //
    int iterations;

    /* configure polaritiy for the GATE and TRIG input */
    ndigo_bool_t trigger_rising[2];

    ndigo_bool_t single_shot_mode;

    ndigo_gating_block avrg_gating_block;

    ndigo_gating_block gating_block[NDIGO_GATE_COUNT];

    /* component to create a trigger either periodically or randomly.
       To be exact, there are two parameters M and N that result in a distance
       between triggers of T = 1 + M + [1...2^N] clock cycles. 0 <= M < 2^32 0
       <= N < 32 there is no enable or reset as the usage of this trigger can be
       configured in the channels.
    */
    int auto_trigger_period;
    int auto_trigger_random_exponent;

    int output_mode;
    /* if the output_mode was set to custom or custom_inl  this func is used for
     * mapping from ADC value to output value*/
    lut_func custom_lut;
} ndigo_avrg_configuration;

/* Copies the default configuration to the specified config pointer*/
NDIGO_API int
ndigo_avrg_get_default_configuration(ndigo_device *device,
                                     ndigo_avrg_configuration *config);

/* Copies the current configuration to the specified config pointer*/
NDIGO_API int
ndigo_avrg_get_current_configuration(ndigo_device *device,
                                     ndigo_avrg_configuration *config);

/* Configures Ndigo device, the config information is copied, so can be changed
 * after the called*/
NDIGO_API int ndigo_avrg_configure(ndigo_device *device,
                                   ndigo_avrg_configuration *config);

/* get the number of boards)*/
NDIGO_API int ndigo_avrg_count_devices(int *error_code,
                                       const char **error_message);

/* Sets up the standard parameters*/
NDIGO_API int
ndigo_avrg_get_default_init_parameters(ndigo_init_parameters *init);

/* init the given card for the given client  version number, use
 * NDIGO_API_VERSION)*/
NDIGO_API ndigo_device *ndigo_avrg_init(ndigo_init_parameters *params,
                                        int *error_code,
                                        const char **error_message);

/* The parameters of the read commands*/
struct ndigo_avrg_read_in {
    ndigo_bool_t
        acknowledge_last_read; // if set, ndigo_read automatically acknowledges
                               // packets from the last read
};
#define NDIGO_AVRG_READ_OK 0
#define NDIGO_AVRG_READ_NO_DATA 1
#define NDIGO_AVRG_READ_INTERNAL_ERROR 2

struct ndigo_avrg_read_out {
    volatile ndigo_packet *first_packet;
    /* The packet after the last one, this is not a valid packet*/
    volatile ndigo_packet *last_packet;
    int error_code;
    const char *error_message;
};

/** Reads packets from the board, optionally automatically acknowledges the last
 * read packets*/
NDIGO_API int ndigo_avrg_read(ndigo_device *device, ndigo_avrg_read_in *in,
                              ndigo_avrg_read_out *out);

/* this method acknowledges the processing of data up to and including the
 * packet passed as parameter */
NDIGO_API int ndigo_avrg_acknowledge(ndigo_device *device,
                                     volatile ndigo_packet *packet);

NDIGO_API short ndigo_avrg_convert_value(ndigo_device *device, int channel,
                                         short val, int outputModeFrom,
                                         int outputModeTo);

#ifdef __cplusplus
}
#endif

#endif
