//
// Header file containing structs and #defines specific for Ndigo5G
//

#ifndef NDIGO_INTERFACE_H
#define NDIGO_INTERFACE_H
#include "Ndigo_common_interface.h"
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @addtogroup constants
 * @{
 */
/*!
 * @brief The number of analog input channels.
 */
#define NDIGO_CHANNEL_COUNT 4
/*!
 * @brief The number of gating blocks.
 */
#define NDIGO_GATE_COUNT 4
/*!
 * @brief The number of external triggers.
 */
#define NDIGO_EXTENSION_COUNT 4
/*!
 * @brief ADC sample FIFO depth.
 */
#define NDIGO_FIFO_DEPTH 8176
 /*! @} */

/*!
 * @defgroup adcdefs ADC modes
 * @{
 */
/*!
 * @brief 4-channel mode at sample rate 1.25GHz.
 */
#define NDIGO_ADC_MODE_ABCD 0
/*!
 * @brief 2-channel mode at sample rate 2.5GHz.
 */
#define NDIGO_ADC_MODE_AC 4
/*!
 * @brief 2-channel mode at sample rate 2.5GHz.
 */
#define NDIGO_ADC_MODE_BC 5
/*!
 * @brief 2-channel mode at sample rate 2.5GHz.
 */
#define NDIGO_ADC_MODE_AD 6
/*!
 * @brief 2-channel mode at sample rate 2.5GHz.
 */
#define NDIGO_ADC_MODE_BD 7
/*!
 * @brief Single channel mode at sample rate 5GHz.
 */
#define NDIGO_ADC_MODE_A 8
/*!
 * @brief Single channel mode at sample rate 5GHz.
 */
#define NDIGO_ADC_MODE_B 9
/*!
 * @brief Single channel mode at sample rate 5GHz.
 */
#define NDIGO_ADC_MODE_C 10
/*!
 * @brief Single channel mode at sample rate 5GHz.
 */
#define NDIGO_ADC_MODE_D 11
/*!
 * @brief Single channel mode at sample rate 1.25GHz.
 */
#define NDIGO_ADC_MODE_AAAA 12
/*!
 * @brief Single channel mode at sample rate 1.25GHz.
 */
#define NDIGO_ADC_MODE_BBBB 13
/*!
 * @brief Single channel mode at sample rate 1.25GHz.
 */
#define NDIGO_ADC_MODE_CCCC 14
/*!
 * @brief Single channel mode at sample rate 1.25GHz.
 */
#define NDIGO_ADC_MODE_DDDD 15
/*! @} */

/*!
 * @defgroup unavailadcdefs Unavailable ADC modes
 * @brief   Currently unavailable ADC modes.
 * @details Availability of the following modes depends on the specific
 *          hardware/firmware revision.
 * @{
 */
#define NDIGO_ADC_MODE_A12 28
#define NDIGO_ADC_MODE_B12 29
#define NDIGO_ADC_MODE_C12 30
#define NDIGO_ADC_MODE_D12 31
/*! @} */

/*!
 * @defgroup precursordef Precursor definitions
 * @{
 */
/*!
 * @brief Maximum of @ref ndigo_trigger_block::precursor.
 */
#define NDIGO_MAX_PRECURSOR 25
/*! @} */

/*!
 * @defgroup multishotdef Multishot definitions
 * @{
 */
/*!
 * @brief Maximum @ref ndigo_trigger_block::multi_shot_count.
 */
#define NDIGO_MAX_MULTISHOT 65535
/*! @} */

/*!
 * @defgroup outputdefs Output format definitions
 * @{
 */
/*!
 * @brief   Output in signed16 integer format.
 * @details Raw ADC values are scaled and INL corrected to a range
 *          of -32768 to 32767.
 */
#define NDIGO_OUTPUT_MODE_SIGNED16 0
/*!
 * @brief   Return the native ADC range.
 * @details Ranges from @ref NDIGO_RAW_VALUE_MIN to
 *          @ref NDIGO_RAW_VALUE_MAX.
 */
#define NDIGO_OUTPUT_MODE_RAW 1
/*!
 * @brief   Custom output mode.
 * @details Requires that @ref lut_func is set to an appropriate
 *          function pointer.
 * @details Requires configuration of @ref ndigo_configuration::custom_lut.
 */
#define NDIGO_OUTPUT_MODE_CUSTOM 2
/*!
 * @brief   Custom output mode which applies a custom LUT correction.
 * @details Requires that @ref lut_func is set to an appropriate
 *          function pointer.
 * @details Requires configuration of @ref ndigo_configuration::custom_lut.
 */
#define NDIGO_OUTPUT_MODE_CUSTOM_INL 3
/*!@}*/

/*!
 * @brief   Maps a value between 0 and 1 to a 16-bit output value.
 * @details The mapping has to be monotonous.
 * @details The mapping can be used, e.g., for custom INL, offset and
 *          gain correction that cover user frontend electronics. It can also
 *          invert the signal or correct the effect of logarithmic input
 *          amplifiers, etc.
 * @details The LUT is applied on the board, thus using it does not cause any
 *          additional CPU load.
 * @details In the mode @ref NDIGO_OUTPUT_MODE_CUSTOM_INL the on-board
 *          INL correction table is applied before the user function, while
 *          @ref NDIGO_OUTPUT_MODE_CUSTOM does not perform the INL correction.
 * @details In order to use the user lookup table functionality,
 *          @ref ndigo_configuration::custom_lut
 *          must be set to a pointer of the user's LUT function.
 */
typedef short (*lut_func)(int channel, float x);

/*!
 * @brief   Contains all configurable settings.
 * @details The struct should be first populated using
 *          @ref ndigo_get_default_configuration(), or if the Ndigo5G has
 *          already been previously configured, using
 *          @ref ndigo_get_current_configuration().
 * @details Afterwards, user-specific changes can be applied.
 * @details An initialized Ndigo5G device can then be configured using
 *          @ref ndigo_configure().
 */
typedef struct {
    /*!
     * @brief The number of bytes occupied by the structure.
     */
    int size;

    /*!
     * @brief Version number of the struct used by the API.
     */
    int version;

    /*!
     * @brief Reserved for internal usage. Do not change.
     */
    int reserved1;

    /*!
     * @brief ADC mode.
     * @details Must be one of the following:
     * @details @rst
     *          .. doxygengroup:: adcdefs
     *              :content-only:
     *          @endrst
     */
    int adc_mode;

    /*!
     * @brief   Minimum bandwidth in Hz.
     * @details Set to the minimum bandwidth required for the application.
     * @details Lower bandwidth results in reduced noise. The driver will set
     *          the ADC to the minimum setting that has at least the desired
     *          bandwidth and report the selected bandwidth in
     *          @ref ndigo_param_info::bandwidth.
     * @details The -8, -10 and -12 versions currently supports 1GHz and 3GHz
     *          bandwidth. The -8AQ version supports 2GHz, 1.5GHz, 600MHz
     *          and 500 MHz.
     */
    double bandwidth;

    /*!
     * @brief   Reserved for internal usage. Do not change.
     */
    ndigo_bool_t reserved;

    /*!
     * @brief   Enable capturing of TDC measurements on external digital
     *          input channel.
     */
    ndigo_bool_t tdc_enabled;

    /*!
     * @brief   Enable enhanced TDC resolution.
     * @details Currently not implemented.
     */
    ndigo_bool_t tdc_fb_enabled;

    /*!
     * @brief   Configure DC offset values for ADC channels.
     * @details Sets the input DC offset-values to this value in Volts.
     * @details Default is 0.
     * @details @rst
     *          .. attention::
     *
     *              After calling :func:`ndigo_init`, the ADC chip will heat up,
     *              which will slightly shift its baseline.
     *
     *              If you plan to measure very small pulses, wait for about
     *              2 minutes after calling ``ndigo_init`` before you start
     *              capturing data and set the values of ``analog_offset``
     *              only after this startup period.
     *          @endrst
     */
    double analog_offset[NDIGO_CHANNEL_COUNT];

    /*!
     * @brief   Sets DC offset for GATE input and TRIGGER input.
     * @details The default value of -0.35V is ideal for negative NIM
     *          pulses of -0.8V.
     * @details Index 0 refers to the TRIGGER input, index 1 to the GATE input.
     */
    double dc_offset[2];

    /*!
     * @brief   Configuration of the external trigger sources.
     * @details The indices correspond to the following defines.
     * @details `_PE` are additional triggers that are always a positive edge
     *          trigger in hardware.
     * @details @rst
     *          .. doxygengroup:: triggerdefs
     *              :content-only:
     *          @endrst
     */
    ndigo_trigger trigger[NDIGO_TRIGGER_COUNT + NDIGO_ADD_TRIGGER_COUNT];

    /*!
     * @brief   Trigger settings of input ADC and timestamp channels.
     * @details This configures the trigger sources, trigger block lengths, etc,
     *          not the trigger type, which is configured by
     *          @ref ndigo_configuration::trigger.
     * @details The number of enabled input channels depends on
     *          @ref ndigo_configuration::adc_mode.
     */
    ndigo_trigger_block trigger_block[NDIGO_CHANNEL_COUNT + 1];

    /*!
     * @brief   Configuration of gating blocks.
     * @details Gating blocks are used to filter
     *          @ref ndigo_configuration::trigger_block.
     */
    ndigo_gating_block gating_block[NDIGO_GATE_COUNT];

    /*!
     * @brief   Configuration of extension blocks.
     * @details A structure describing the routing of the four digital channels
     *          of the Ndigo extension board to the trigger matrix.
     */
    ndigo_extension_block extension_block[NDIGO_EXTENSION_COUNT];

    /*!
     * @brief   Enables output drives.
     * @details Enables output drive for each of the four external sync lines.
     *          Each integer represents a bitmask selecting the trigger sources
     *          for that line.
     * @details The bit mapping is documented in
     *          @ref ndigo_trigger_block::sources.
     */
    int drive_bus[4];

    /*!
    * @brief   Configure periodicity of the auto trigger.
    * @details Works in conjunction with
    *          @ref ndigo_configuration::auto_trigger_random_exponent.
    * @details The two parameters @f$ M @f$ = @ref auto_trigger_period
    *          and @f$ N @f$ = @ref auto_trigger_random_exponent
    *          result in a distance between triggers of
    *
    *          @f$ T = M + [1 \dots 2^N] - 1 @f$
    *
    *          clock cycles.
    *
    *          @f$ 8 \leq M < 2^{32} @f$
    *
    *          @f$ 0 \leq N < 32 @f$
    * @details There is no enable or reset as the usage of this trigger can be
    *          configured in the channels.
    * @details To actually use this trigger, it has to be set as a trigger
    *          source in @ref trigger_block.
    * @details @rst
    *          See also :doc:`../functionality/auto_trigger`.
    *          @endrst
    */
    int auto_trigger_period;

    /*!
     * @brief   Configure randomness of the auto trigger.
     * @details See also @ref auto_trigger_period.
     */
    int auto_trigger_random_exponent;

    /*!
     * @brief   Defines the data representation in the output.
     * @details This influences the meaning of the values of
     *          @ref ndigo_packet::data.
     * @details Must be one of the following:
     * @details @rst
     *          .. doxygengroup:: outputdefs
     *              :content-only:
     *          @endrst
     */
    int output_mode;

    /*!
     * @brief   Custom mapping from raw ADC value to output value.
     * @details If the @ref ndigo_configuration::output_mode is set to
     *          @ref NDIGO_OUTPUT_MODE_CUSTOM or
     *          @ref NDIGO_OUTPUT_MODE_CUSTOM_INL this function is used for
     *          mapping from ADC value to output value. The driver will call
     *          this function with a value from -1 to +1 and the function must
     *          return the corresponding signed 16 bit value that the board
     *          should return for an input voltage relative to the full scale
     *          range.
     */
    lut_func custom_lut;

} ndigo_configuration;

/*!
 * @brief Parameters for @ref ndigo_read().
 */
struct ndigo_read_in {
    /*!
     * @brief   Automatic acknowledgement of packets.
     * @details If set, @ref ndigo_read() automatically acknowledges
     *          packets from the last read.
     */
    ndigo_bool_t acknowledge_last_read;
};

/*!
 * @brief Parameters for @ref ndigo_read().
 */
struct ndigo_read_out {
    /*!
     * @brief Pointer to the first packet that was captured by the call of
     *        @ref ndigo_read().
     */
    volatile ndigo_packet *first_packet;

    /*!
     * @brief Address of the header of the last packet in the buffer.
     */
    volatile ndigo_packet *last_packet;

    /*!
     * @brief   Read error code.
     * @details Will be one of the following:
     * @details @rst
     *          .. doxygengroup:: readerror
     *              :content-only:
     *          @endrst
     */
    int error_code;

    /*!
     * @brief Corresponding error message.
     */
    const char *error_message;
};

/*!
 * @brief Contains buffer information.
 */
struct ndigo_buffer_info {
    /*!
     * @brief Buffer address.
     */
    uint64_t *buffer_address;

    /*!
     * @brief Size of the buffer in bytes.
     */
    int64_t buffer_size;
};

/*!
 * @brief   Copies the default configuration to the specified config pointer.
 * @param[in] device Pointer to the device from which to get the information.
 * @param[out] config Pointer to a structure in which to store the
 *          configuration values.
 * @return  A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_get_default_configuration(ndigo_device *device,
                                              ndigo_configuration *config);

/*!
 * @brief   Copies the current configuration to the specified config pointer
 * @param[in] device Pointer to the device from which to get the information.
 * @param[out] config Pointer to a structure in which to store the
 *          configuration values.
 * @return  A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_get_current_configuration(ndigo_device *device,
                                              ndigo_configuration *config);

/*!
 * @brief   Configures Ndigo device.
 * @details The config information is copied so that it can
 *          be changed after the call of `ndigo_configure` without corrupting
 *          the current configuration of the device.
 * @param[in] device Pointer to the device from which to get the information.
 * @param[out] config Pointer to the configuration structure.
 * @return  A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_configure(ndigo_device *device,
                              ndigo_configuration *config);

/*!
 * @brief   Get the number of Ndigo5G boards that are installed in the system.
 * @param[out] error_code Pointer to an integer in which to store the
 *          @ref funcreturnsndigo "status code".
 * @param[out] error_message Location in which to store the error message
 *          as plain text.
 * @return  The number of devices.
 */
NDIGO_API int ndigo_count_devices(int *error_code, const char **error_message);

/*!
 * @brief   Sets up the standard parameters.
 * @details Gets a set of default parameters for @ref ndigo_init().
 *          This must always be used to initialize the
 *          @ref ndigo_init_parameters structure.
 * @param[in] init Pointer to a structure in which to store the
 *          initialization values.
 * @return  A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_get_default_init_parameters(ndigo_init_parameters *init);

 /*!
 * @brief   Open and initialize an Ndigo5G board.
 * @details Which Ndigo5G board will be initialized is
 *          determined by @ref ndigo_init_parameters::card_index.
 * @param[in] params  Pointer to the structure that contains the
 *          initialization parameters.
 * @param[out] error_code Pointer to where the error code will be stored.
 * @param[out] error_message Pointer to a char pointer to where an
 *          error message as plain text will be stored.
 * @return  A pointer to an initialized Ndigo5G device.
 */
NDIGO_API ndigo_device *ndigo_init(ndigo_init_parameters *params,
                                   int *error_code, const char **error_message);

/*!
 * @brief   Reads packets.
 * @details Returns a pointer to an array of captured data in `out`.
 *          The result contains any number of packets of type
 *          @ref ndigo_packet.
 * @param[in] device Pointer to the device from which to read.
 * @param[in] in Pointer to the struct that configures the read call.
 * @param[out] out Pointer to a struct in which the read-out will be stored.
 * @return  A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_read(ndigo_device *device, ndigo_read_in *in,
                         ndigo_read_out *out);

/*!
 * @brief   Retrieve buffer information.
 * @param[in] device Pointer to the device from which to read.
 * @param[out] info Pointer to a struct in which the information will be stored.
 * @return  A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_get_buffer_info(ndigo_device *device,
                                    ndigo_buffer_info *info);

/*!
 * @brief   Convert one output data type to another.
 * @param[in] device Pointer to the device.
 * @param[in] channel Source channel of the data.
 * @param[in] val Value to convert.
 * @param[in] outputModeFrom Original
 *          @link ndigo_configuration::output_mode output mode @endlink.
 * @param[in] outputModeTo New
 *          @link ndigo_configuration::output_mode output mode @endlink.
 * @returns The converted value.
 */
NDIGO_API short ndigo_convert_value(ndigo_device *device, int channel,
                                    short val, int outputModeFrom,
                                    int outputModeTo);

#ifdef __cplusplus
}
#endif

#endif
