//
// Header file containing structs and #defines specific for Ndigo250M
// The current driver version for Ndigo devices is 1.4.3.0
//

#ifndef NDIGO250M_INTERFACE_H
#define NDIGO250M_INTERFACE_H
#include "Ndigo_common_interface.h"
#ifdef __cplusplus
extern "C" {
#endif

/*! \defgroup config Configuration
 * \brief The device is configured with a configuration structure
 *
 * The user should first obtain a structure that contains the default settings
 * of the device read from an on board ROM, then modify the structure as needed
 * for the user application and use the result to configure the device.
 * @{
 */
/*! \defgroup conffuncts Functions for Configuration
 *@{
 */
/*! \defgroup defconffuncts define for ndigo250m_configure
 *	\brief define for @link conffuncts ndigo250m_configure @endlink
 */
/*!@}*/
/*! \defgroup ndigoconf Structure ndigo250m_configuration
 *	\brief This structure contains the configuration information.
 *
 *	It is used in conjunction with @link ndigo250m_get_default_configuration
 *	ndigo250m_get_default_configuration() @endlink
 *
 *	Internally it uses the structures @link ndigo_trigger_block
 *ndigo_trigger_block @endlink and @link ndigo_trigger ndigo_trigger @endlink
 *@{
 */
/*!@}*/
/*!@}*/
/*!	\defgroup initialization Initialization
 *@{
 */
/*! \defgroup initfuncts Functions for Initialization
 */
/*!@}*/
/*! \defgroup config Configuration
 * \brief The device is configured with a configuration structure
 *
 * The user should first obtain a structure that contains the default settings
 * of the device read from an on board ROM, then modify the structure as needed
 * for the user application and use the result to configure the device.
 * @{
 */
/*! \defgroup conffuncts Functions for Configuration
 *@{
 */
/*! \defgroup defconffuncts define for ndigo250m_configure
 *	\brief define for @link conffuncts ndigo250m_configure @endlink
 */
/*!@}*/
/*! \defgroup ndigoconf Structure ndigo250m_configuration
 *	\brief This structure contains the configuration information.
 *
 *	It is used in conjunction with @link ndigo250m_get_default_configuration
 *	ndigo_get_default_configuration() @endlink
 *
 *	Internally it uses the structures @link ndigo_trigger_block
 *ndigo_trigger_block @endlink and @link ndigo_trigger ndigo_trigger @endlink
 *@{
 */
/*! \defgroup outputdefs #defines for output_mode
 *	\brief defines for @link ndigo250m_configuration output_mode @endlink
 */
/*! \defgroup triggerdefs #defines for trigger
 *	\brief defines for @link ndigo250m_configuration trigger @endlink
 */
/*!@}*/
/*!@}*/

/*! \ingroup precursordef
 *	\brief maximum @link ndigo_trigger_block precursor @endlink
 */
#define NDIGO250M_MAX_PRECURSOR 27

/*! \ingroup multishotdef
 *	\brief maximum @link ndigo_trigger_block number of shots @endlink
 */
#define NDIGO250M_MAX_MULTISHOT 65535

/*! \ingroup constants
 *	\brief ADC sample fifo depth
 *
 *	number of samples that can be buffered before readout. Longer packets are
 *	possible under certain circumstances.
 */
#define NDIGO250M_FIFO_DEPTH 4094

/*TODO*/
#define NDIGO250M_CHANNEL_A_MASK 1
#define NDIGO250M_CHANNEL_B_MASK 2
#define NDIGO250M_CHANNEL_C_MASK 4
#define NDIGO250M_CHANNEL_D_MASK 8
#define NDIGO250M_CHANNEL_T_MASK 16

/*!	\ingroup constants
 *	\brief The number of analog input channels
 */
#define NDIGO250M_CHANNEL_COUNT 4

/*!	\ingroup constants
 *	\brief the number of TDC channels
 */
#define NDIGO250M_TDC_COUNT 1

/*! \ingroup constants
 *	\brief the number of DMA channels.
 *
 *	Unlike the Ndigo5G-10, this device has an individual DMA buffer for each
 *data source.
 */
#define NDIGO250M_DMA_COUNT 6

/*! \ingroup constants
 *	\brief the number of gating blocks.
 */
#define NDIGO250M_GATE_COUNT 4

/*! \ingroup ndigoconf
 *	\brief Contains all user changeable settings
 */
typedef struct {
    /*! \brief size in bytes
     */
    int size;

    /*! \brief A version number
     *
     *	that is increased when the definition of the structure is changed. The
     *increment can be larger than one to match driver version numbers or
     *similar. Set to 0 for all versions up to first release.
     */
    int version;

    /*! \brief Reserved for internal use.
     *
     * do not change.
     */
    int reserved1;

    /*! \brief Enable capturing of TDC measurements on external digital input
     *channel.
     *
     *	Only possible for divisor=2 for the Ndigo250M-14 and not possilbe at all
     *for the Ndigo125M. For lower sampling rates the decimation option can be
     *used.
     */
    ndigo_bool_t tdc_enabled;

    /*! \brief Enable enhanced TDC resolution
     *
     * Currently not implemented.
     */
    ndigo_bool_t tdc_fb_enabled;

    /*! \brief Sets the DC offset-values +- this value in volts.
     *
     *	Offsets 4 and 5 are Trigger and GATE input thresholds.
     */
    double analog_offset[6];

    /*! \brief Configuration of the external trigger sources.
     *
     *	Threshold is ignored for entries 8 and above. The trigger indices refer
     *to the entry in the trigger array and are defined like NDIGO_TRIGGER_*.
     *Sources 16 to 21 are positive edge triggered.
     */
    ndigo_trigger trigger[NDIGO_TRIGGER_COUNT];

    /*! \brief trigger settings
     *
     * of the 4 channels and the timestamp channel
     */
    ndigo_trigger_block trigger_block[NDIGO250M_CHANNEL_COUNT + 1];

    /*! \brief gating block settings
     *
     *	A structure describing the gating blocks that can be used by the trigger
     *blocks to filter triggers.
     */
    ndigo_gating_block gating_block[NDIGO250M_GATE_COUNT];

    /*! \brief Enable output drive for each of the four external sync lines.
     *
     *	Each integer represents a bitmask selecting the trigger sources for that
     *line. The bit mapping is described in the structure ndigo_trigger_block.
     */
    int drive_bus[4];

    /*! \brief component to create a trigger either periodically or randomly.
     *
     *  To be exact, there are two parameters M = @link auto_trigger_period
     *auto_trigger_period @endlink and N = @link auto_trigger_random_exponent
     *auto_trigger_random_exponent @endlink that result in a distance between
     *triggers of
     *
     *		T = 1 + M + [1...2^N]
     *
     *	clock cycles.
     *
     *		0 <= M < 2^32
     *
     *		0 <= N < 32
     *
     *  there is no enable or reset as the usage of this trigger can be
     *configured in the channels.
     */
    int auto_trigger_period;

    /** \brief component to create a trigger either periodically or randomly.
     *
     *  To be exact, there are two parameters M = @link auto_trigger_period
     *auto_trigger_period @endlink and N = @link auto_trigger_random_exponent
     *auto_trigger_random_exponent @endlink that result in a distance between
     *triggers of
     *
     *		T = 1 + M + [1...2^N]
     *
     *	clock cycles.
     *
     *		0 <= M < 2^32
     *
     *		0 <= N < 32
     *
     *  there is no enable or reset as the usage of this trigger can be
     *configured in the channels.
     */
    int auto_trigger_random_exponent;

    /*! \brief Divisor for the base frequency (500MHz) range: 2-32
     *
     *	The 500MHz base clock is divided by this divisor to create the rsampling
     *frequency. Valid values are 2 to 32 for the Ndigo250M and 4 to 32 for the
     *Ndigo125M.
     */
    int divisor;

    /*! \brief Reduces sample rate by given factor.
     *
     *  Range : 1 - 255
     *  Note  : Decimation factors 2 and 3 only skip samples
     *           factors 4 - 255 use a CIC decimation filter
     */
    int decimation;

    /*! \brief Gain in 3.5dB steps from 0 (0dB) to 1 (3.5dB).
     *
     *	The value can be set separately for the two ADCs. Gain[0] modifies
     *channels 0 and 1, gain[1] modifies channels 2 and 3. Default is 0.
     */
    int high_gain[2];

    /*!	\brief Gain in 0.5dB steps from 0 (0dB) to 12 (6.0dB).
     *
     * The value can be set separately for the two ADCs. Gain[0] modifies
     *channels 0 and 1, gain[1] modifies channels 2 and 3. Default is 0.
     */
    int fine_gain[2];

    /*! \brief Gain in 0.05dB steps from 0 (0dB) to 10 (0.5dB).
     *
     * The value can be set separately for the two ADCs. Gain[0] modifies
     *channels 0 and 1, gain[1] modifies channels 2 and 3. Default is 0.
     */
    int gain_correction[2];
} ndigo250m_configuration;

/*! \ingroup conffuncts
 *	\brief Copies the default configuration to the specified config pointer
 */
NDIGO_API int
ndigo250m_get_default_configuration(ndigo_device *device,
                                    ndigo250m_configuration *config);

/*!	\ingroup conffuncts
 *	\brief	Copies the current configuration to the specified config pointer
 */
NDIGO_API int
ndigo250m_get_current_configuration(ndigo_device *device,
                                    ndigo250m_configuration *config);

/*! \ingroup conffuncts
 *	\brief Configures ndigo device,
 *
 * the config information is copied, so can be changed after the called
 */
NDIGO_API int ndigo250m_configure(ndigo_device *device,
                                  ndigo250m_configuration *config);

/*! \ingroup initfuncts
 *	\brief returns net number of boards that are supported by this driver in the
 *system.
 */
NDIGO_API int ndigo250m_count_devices(int *error_code,
                                      const char **error_message);

/*! \ingroup initfuncts
 *	\brief Get a set of default parameters to feed into ndigo init().
 *
 *	This must always be used to initialize the ndigo_init_parameter structure.
 */
NDIGO_API int
ndigo250m_get_default_init_parameters(ndigo_init_parameters *init);

/*!	\ingroup initfuncts
 *	\brief Open and initialize the Ndigo250M-14 board with the given index.
 *
 *	With error_code and error_message the user must provide pointers where to
 *buffers where error information should be written by the driver. The buffer
 *for the error message must by at least 80 chars long.
 *
 *	Params is a structure of type ndigo_init_parameters that must be completely
 *	initialized.
 */
NDIGO_API ndigo_device *ndigo250m_init(ndigo_init_parameters *params,
                                       int *error_code,
                                       const char **error_message);

/*!	\brief The parameters of the read commands
 */
struct ndigo250m_read_in {
    ndigo_bool_t acknowledge_last_read;

    /*! \brief	A mask that tells which channels to be read,
     *
     *	all other values will be left untouched!!
     *	1 Channel A
     *	2 Channel B
     *	4 Channel C
     *	8 Channel D
     *	16 Channel
     *	if 0, this is treated as a full mask
     */
    int mask;
};

#define NDIGO_READ_OK 0
#define NDIGO_READ_NO_DATA 1
#define NDIGO_READ_INTERNAL_ERROR 2

/*! \ingroup readoutstruct
 *	\brief contains information about the read process
 */
struct ndigo250m_read_out {
    /*! \brief the first packet to read, NULL if no data
     */
    volatile ndigo_packet *first_packet[NDIGO250M_DMA_COUNT];
    /*! \brief The last valid packet
     *
     *	might be the same as first_packet if there is only one
     */
    volatile ndigo_packet *end[NDIGO250M_DMA_COUNT];
    int error_code[NDIGO250M_DMA_COUNT];
    const char *error_message[NDIGO250M_DMA_COUNT];
};

/*! \ingroup readfuncts
 *	\brief Reads packets from the board
 *
 *	For each DMA channel returns a pointer to an array of captured data in
 *read_out. The result can contain any number of packets of type ndigo_packet.
 *read_in provides parameters to the driver. A call to this method automatically
 *allows the driver to reuse the memory returned in the previous call.
 *
 *	Returns an error_code as definded in the structure ndigo_read_out.
 */
NDIGO_API int ndigo250m_read(ndigo_device *device, ndigo250m_read_in *in,
                             ndigo250m_read_out *out);

/*! \ingroup readfuncts
 *	\brief Acknowledge all data up to the packet provided as parameter.
 *
 *	This is mandatory if acknowledge_last_read in the ndigo_read_in structure is
 *set to false for calls to ndigo_read.
 *
 *	This feature allows to either free up partial DMA space early if there will
 *be no call to ndigo_read anytime soon. It also allows to keep data over
 *multiple calls to ndigo_read to avoid unnecessary copying of data.
 */
NDIGO_API int ndigo250m_acknowledge(ndigo_device *device, int channel,
                                    volatile ndigo_packet *packet);

#ifdef __cplusplus
}
#endif

#endif
