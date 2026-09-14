//
// Header file containing structs and #defines commonly used by header files of
// derived Ndigo device classes The current driver version for Ndigo devices
//

#ifndef NDIGO_COMMON_INTERFACE_H
#define NDIGO_COMMON_INTERFACE_H

#ifdef __linux__
#define __stdcall
#include <stddef.h>
#define TRUE 1
#define FALSE 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32) || defined(_WIN64)
#ifdef NDIGO_DRIVER_EXPORTS
#define NDIGO_API __declspec(dllexport)
#else
#define NDIGO_API __declspec(dllimport)
#endif
#else
#define NDIGO_API
#endif

#include "crono_interface.h"

/*!
 * @defgroup constants Constants
 * @{
 */
/*!
 * @brief Used for @ref ndigo_init_parameters::version.
 */
#define NDIGO_API_VERSION 0
/*!
 * @brief Current version of @ref ndigo_static_info.
 */
#define NDIGO_STATIC_INFO_VERSION 1
/*!
 * @brief Current version of @ref ndigo_fast_info.
 */
#define NDIGO_FAST_INFO_VERSION 1
/*!
 * @brief   The number of triggers.
 * @details Two per analog input, one per digital input plus some specials.
 */
#define NDIGO_TRIGGER_COUNT 16
/*!
 * @brief Additional set of triggers for digital inputs.
 */
#define NDIGO_ADD_TRIGGER_COUNT 6
/*!
 * @brief   Minimal raw ADC value.
 * @details RAW mode should not be used.
 */
#define NDIGO_RAW_VALUE_MIN 0
/*!
 * @brief   Raw ADC value corresponding to zero.
 * @details RAW mode should not be used.
 */
#define NDIGO_RAW_VALUE_ZERO 512
/*!
 * @brief   Maximal raw ADC value.
 * @details RAW mode should not be used.
 */
#define NDIGO_RAW_VALUE_MAX 1023
/*!
 * @brief   Number of raw ADC values.
 * @details RAW mode should not be used.
 */
#define NDIGO_RAW_VALUE_COUNT 1024
/*!
 * @brief   Fixed length of calibration date string.
 * @details Calibration date format is YYYY-MM-DD hh:mm.
 * @details Used by @ref ndigo_static_info::calibration_date.
 */
#define NDIGO_CALIBRATION_DATE_LEN 20
/*!
 * @brief   Bitstream date format is YYYY-MM-DD hh:mm:ss
 * @details Used by @ref ndigo_static_info::bitstream_date.
 */
#define NDIGO_BITSTREAM_DATE_LEN 20
/*! @} */

/*!
 * @defgroup funcreturnsndigo Return codes
 * @brief Defines representing error codes used by various API functions.
 * @{
 */
#define NDIGO_OK 0
#define NDIGO_WINDRIVER_NOT_FOUND 1
#define NDIGO_DEVICE_NOT_FOUND 2
#define NDIGO_NOT_INITIALIZED 3
#define NDIGO_WRONG_STATE 4
#define NDIGO_INVALID_DEVICE 5
#define NDIGO_BUFFER_ALLOC_FAILED 6
#define NDIGO_TDC_NO_EDGE_FOUND 7
#define NDIGO_INVALID_BUFFER_PARAMETERS 8
#define NDIGO_INVALID_CONFIG_PARAMETERS 9
#define NDIGO_WINDOW_CALIBRATION_FAILED 10
#define NDIGO_HARDWARE_FAILURE 11
#define NDIGO_INVALID_ADC_MODE 12
#define NDIGO_SYNCHRONIZATION_FAILED 13
#define NDIGO_DEVICE_OPEN_FAILED 14
#define NDIGO_INTERNAL_ERROR 15
#define NDIGO_INVALID_ARGUMENTS 17
/*! @} */

/*!
 * @brief Universally used boolean.
 */
#define ndigo_bool_t unsigned char

/*!
 * @defgroup packetflagdefs Packet flag defines
 * @{
 */
/*!
 * @brief Less than the requested number of samples have been written due to a
 *        full FIFO.
 */
#define NDIGO_PACKET_FLAG_SHORTENED 1

/*!
 * @brief Packets were discarded due to a full host buffer.
 */
#define NDIGO_PACKET_FLAG_PACKETS_LOST 2

/*!
 * @brief The previous packet included ADC samples with overflows
 */
#define NDIGO_PACKET_FLAG_OVERFLOW 4

/*!
 * @brief The trigger unit has discarded packets due to a full FIFO.
 */
#define NDIGO_PACKET_FLAG_TRIGGER_MISSED 8

/*!
 * @brief   The internal DMA FIFO was full.
 * @details This *may* result in missed data, but only if
 *          @ref NDIGO_PACKET_FLAG_SHORTENED or
 *          @ref NDIGO_PACKET_FLAG_TRIGGER_MISSED are set.
 */
#define NDIGO_PACKET_FLAG_DMA_FIFO_FULL 16

/*!
 * @brief   Host buffer was full.
 * @details This *may* result in missed data, but only if
 *          @ref NDIGO_PACKET_FLAG_PACKETS_LOST is set.
 */
#define NDIGO_PACKET_FLAG_HOST_BUFFER_FULL 32

/*!
 * @brief No valid edge was found in TDC packet, timestamp uncorrected.
 */
#define NDIGO_PACKET_FLAG_TDC_NO_EDGE 64
/*! @} */

/*!
 * @defgroup usedtypedefs Used packet data type defines
 * @{
 */
/*!
 * @brief   16-bit signed ADC data.
 */
#define NDIGO_PACKET_TYPE_16_BIT_SIGNED 1
/*!
 * @brief   64-bit unsigned TDC data.
 * @details Only for internal processing.
 */
#define NDIGO_PACKET_TYPE_TDC_DATA 8
/*!
 * @brief   Empty @ref ndigo_packet::data.
 * @details @ref ndigo_packet::length may contain alternative information.
 */
#define NDIGO_PACKET_TYPE_TIMESTAMP_ONLY 128
/*!
 * @brief   Empty @ref ndigo_packet::data.
 * @details The packet may contain other data.
 */
#define NDIGO_PACKET_TYPE_END_OF_BUFFER 129
/*! @} */

/*!
 * @defgroup unusedtypedefs Unused packet data type defines
 * @{
 */
#define NDIGO_PACKET_TYPE_8_BIT_SIGNED 0
#define NDIGO_PACKET_TYPE_32_BIT_SIGNED 2
#define NDIGO_PACKET_TYPE_64_BIT_SIGNED 3
#define NDIGO_PACKET_TYPE_8_BIT_UNSIGNED 4
#define NDIGO_PACKET_TYPE_16_BIT_UNSIGNED 5
#define NDIGO_PACKET_TYPE_32_BIT_UNSIGNED 6
#define NDIGO_PACKET_TYPE_64_BIT_UNSIGNED 7
/*! @} */

/*!
 * @defgroup sourcedefs Trigger sources defines
 * @{
 */
#define NDIGO_TRIGGER_SOURCE_NONE 0x00000000
#define NDIGO_TRIGGER_SOURCE_A0 0x00000001
#define NDIGO_TRIGGER_SOURCE_A1 0x00000002
#define NDIGO_TRIGGER_SOURCE_B0 0x00000004
#define NDIGO_TRIGGER_SOURCE_B1 0x00000008
#define NDIGO_TRIGGER_SOURCE_C0 0x00000010
#define NDIGO_TRIGGER_SOURCE_C1 0x00000020
#define NDIGO_TRIGGER_SOURCE_D0 0x00000040
#define NDIGO_TRIGGER_SOURCE_D1 0x00000080
#define NDIGO_TRIGGER_SOURCE_TDC 0x00000100
#define NDIGO_TRIGGER_SOURCE_GATE 0x00000200
#define NDIGO_TRIGGER_SOURCE_BUS0 0x00000400
#define NDIGO_TRIGGER_SOURCE_BUS1 0x00000800
#define NDIGO_TRIGGER_SOURCE_BUS2 0x00001000
#define NDIGO_TRIGGER_SOURCE_BUS3 0x00002000
#define NDIGO_TRIGGER_SOURCE_AUTO 0x00004000
#define NDIGO_TRIGGER_SOURCE_ONE 0x00008000
#define NDIGO_TRIGGER_SOURCE_TDC_PE 0x01000000
#define NDIGO_TRIGGER_SOURCE_GATE_PE 0x02000000
#define NDIGO_TRIGGER_SOURCE_BUS0_PE 0x04000000
#define NDIGO_TRIGGER_SOURCE_BUS1_PE 0x08000000
#define NDIGO_TRIGGER_SOURCE_BUS2_PE 0x10000000
#define NDIGO_TRIGGER_SOURCE_BUS3_PE 0x20000000
/*! @} */

/*!
 * @defgroup gatedefs Gate defines
 * @{
 */
#define NDIGO_TRIGGER_GATE_NONE 0x0000
#define NDIGO_TRIGGER_GATE_0 0x0001
#define NDIGO_TRIGGER_GATE_1 0x0002
#define NDIGO_TRIGGER_GATE_2 0x0004
#define NDIGO_TRIGGER_GATE_3 0x0008
/*! @} */

/*!
 * @defgroup bufferdef Defines for buffer
 * @{
 */
/*!
 * @brief Buffer is allocated by the device driver.
 */
#define NDIGO_BUFFER_ALLOCATE 0
/*!
 * @brief   Not implemented. Do not use.
 */
#define NDIGO_BUFFER_USE_PHYSICAL 1
/*!
 * @brief Not implemented. Do not use.
 */
#define NDIGO_BUFFER_USE_PREALLOCATED 2
/*! @} */

/*!
 * @defgroup triggerdefs Defines for triggers
 * @{
 */
#define NDIGO_TRIGGER_A0 0
#define NDIGO_TRIGGER_A1 1
#define NDIGO_TRIGGER_B0 2
#define NDIGO_TRIGGER_B1 3
#define NDIGO_TRIGGER_C0 4
#define NDIGO_TRIGGER_C1 5
#define NDIGO_TRIGGER_D0 6
#define NDIGO_TRIGGER_D1 7
#define NDIGO_TRIGGER_TDC 8
#define NDIGO_TRIGGER_TRIGGER NDIGO_TRIGGER_TDC
#define NDIGO_TRIGGER_GATE 9
#define NDIGO_TRIGGER_BUS0 10
#define NDIGO_TRIGGER_BUS1 11
#define NDIGO_TRIGGER_BUS2 12
#define NDIGO_TRIGGER_BUS3 13
#define NDIGO_TRIGGER_AUTO 14
#define NDIGO_TRIGGER_ONE 15
#define NDIGO_TRIGGER_TDC_PE 16
#define NDIGO_TRIGGER_GATE_PE 17
#define NDIGO_TRIGGER_BUS0_PE 18
#define NDIGO_TRIGGER_BUS1_PE 19
#define NDIGO_TRIGGER_BUS2_PE 20
#define NDIGO_TRIGGER_BUS3_PE 21
/*! @} */

/*!
 * @defgroup readerror Read error defines
 * @{
 */
/*!
 * @brief No read error occurred.
 */
#define NDIGO_READ_OK 0
/*!
 * @brief Read did not yield any data.
 */
#define NDIGO_READ_NO_DATA 1
/*!
 * @brief Error in buffer handling. The device has to be re-initialized.
 */
#define NDIGO_READ_INTERNAL_ERROR 2
/*!
 * @brief Currently not used.
 */
#define NDIGO_READ_TIMEOUT 3
/*! @} */

/*!
 * @defgroup ndigoalertdefs Alert defines
 * @{
 */
/*!
 * @brief FPGA temperature alert (> 85 Celsius).
 */
#define NDIGO_ALERT_FPGA_TEMPERATURE 1
/*!
 * @brief Internal FPGA voltage out of range (< 1.01V or > 1.08V).
 */
#define NDIGO_ALERT_VCCINT 2
/*!
 * @brief FPGA auxiliary voltage out of range (< 2.375V or > 2.625V).
 */
#define NDIGO_ALERT_VCCAUX 4
/*!
 * @brief FPGA temperature critical (> 125 Celsius).
 */
#define NDIGO_ALERT_FPGA_TEMPERATURE_CRITICAL 8
/*!
 * @brief ADC temperature alert (> 90 Celsius).
 */
#define NDIGO_ALERT_ADC_TEMPERATURE 16
/*!
 * @brief ADC temperature critical (> 100 Celsius).
 */
#define NDIGO_ALERT_ADC_TEMPERATURE_CRITICAL 32
/*! @} */

/*!
 * @brief Macro that gets the length of @ref ndigo_packet::data
 *        in multiples of 64 bytes.
 */
#define ndigo_packet_data_length(current)                                      \
    ((current)->type & 128 ? 0 : (current)->length)

/*!
 * @brief Macro that gets the size of @ref ndigo_packet::data in bytes.
 */
#define ndigo_packet_bytes(current)                                            \
    ((ndigo_packet_data_length(current) + 2) * 8)

/*!
 * @brief   Macro that gets the address of the next packet after the current
 *          packet.
 * @details The validity of the address must be checked.
 * @code
 * int status = ndigo_read(device, &in, &out);
 * if (status == NDIGO_OK && out.first_packet != nullptr) {
 *     volatile ndigo_packet *packet = ndigo_next_packet(out.first_packet);
 *     while (packet <= out.last_packet) { // while packet address is valid
 *         // do stuff
 *         volatile ndigo_packet *next_packet = ndigo_next_packet(packet);
 *         packet = next_packet;
 *     }
 * }
 * @endcode
 */
#define ndigo_next_packet(current)                                             \
    ((volatile ndigo_packet                                                    \
          *)(((int64_t)(current)) +                                            \
             (((current)->type & 128 ? 0 : (current)->length) + 2) * 8))

/*!
 * @brief   Contains all packet information.
 * @details Packets are retrieved by @ref ndigo_read().
 */
struct ndigo_packet {
    /*!
     * @brief   Enumeration of channels.
     * @details 0 to 3 for the ADC input channels, 4 for the TDC,
     *          and 5 for the timestamp channel.
     */
    unsigned char channel;

    /*!
     * @brief   Identify source card among others.
     * @details Defaults to 0 if no value is assigned to the parameter
     *          @ref ndigo_init_parameters::board_id.
     */
    unsigned char card;

    /*!
     * @brief   Type indicator for @ref ndigo_packet::data.
     * @details One of the following:
     * @details @rst
     *          .. doxygengroup:: usedtypedefs
     *              :content-only:
     *          @endrst
     */
    unsigned char type;

    /*!
     * @brief   Contains packet flags.
     * @details One of the following:
     * @details @rst
     *          .. doxygengroup:: packetflagdefs
     *              :content-only:
     *          @endrst
     */
    unsigned char flags;

    /*!
     * @brief   Length of @ref ndigo_packet::data in units of 64 bit.
     * @details Number of 64-bit elements (each containing 4 samples) in the
     *          data array as long as
     *          @ref ndigo_packet::type < @ref NDIGO_PACKET_TYPE_TIMESTAMP_ONLY.
     * @details If @ref ndigo_packet::type =
     *          @ref NDIGO_PACKET_TYPE_TIMESTAMP_ONLY.
     *          this is the pattern of
     *          trigger sources that where active in the clock cycle given by
     *          @ref ndigo_packet::timestamp. Bits are set according to the
     *          trigger sources, i.e. bit 0 is set if trigger
     *          @ref NDIGO_TRIGGER_SOURCE_A0 was active,
     *          bit 29 is set if @ref NDIGO_TRIGGER_SOURCE_BUS3_PE was active,
     *          etc, as listed in @ref ndigo_trigger_block::sources.
     */
    unsigned int length;

    /*!
     * @brief   Timestamp in ps.
     * @details ADC channels A to D: timestamp of the last word in the packet.
     * @details TDC channel (@ref ndigo_packet::channel = 4):
     *          timestamp of the trigger event (falling edge) of the
     *          TDC channel.
     *          When @ref ndigo_process_tdc_packet() is called once on the
     *          the packet, the timestamp is replaced with the precise
     *          timestamp for the edge.
     * @details Timestamp channel (@ref ndigo_packet::channel = 5):
     *          timestamp of the trigger event.
     */
    uint64_t timestamp;

    /*!
     * @brief   Sample data.
     * @details For the Ndigo5G each 64-bit word contains four 16bit signed
     *          words from the ADC.
     * @details The user can cast the array to `short*` to directly operate on
     *          the sample data.
     */
    uint64_t data[1];
};

/*!
 * @brief   Contains information on the current device.
 * @details Returned by @ref ndigo_init.
 */
typedef struct {
    bool is_valid;
    void *ndigo;
} ndigo_device;

/*!
 * @brief   Struct containing trigger settings.
 * @details Used by @ref ndigo_configuration::trigger.
 */
typedef struct {
    /*!
     * @brief   Threshold of both triggers units.
     * @details Valid values depend on output mode:
     *          - @link NDIGO_OUTPUT_MODE_RAW @endlink: 0 to 1023
     *          - @link NDIGO_OUTPUT_MODE_SIGNED16 @endlink: -32768 to +32767
     * @details For trigger indices @ref NDIGO_TRIGGER_TDC to
     *          @ref NDIGO_TRIGGER_BUS3_PE the threshold is ignored.
     */
    short threshold;

    /*!
     * @brief   Enable edge trigger functionality.
     * @details If true, operate as an edge trigger.
     * @details If false, operate as a level trigger.
     * @details An edge trigger triggers as soon as its set threshold is
     *          crossed by the signal. Thus the roots in reference to the
     *          threshold are recorded.
     * @details A level trigger triggers as long as the signal is above
     *          (or below) the set threshold. Therefore, the trigger gives
     *          the sign of the signal in reference to the threshold.
     * @details For trigger indices @ref NDIGO_TRIGGER_AUTO and
     *          @ref NDIGO_TRIGGER_ONE this is ignored.
     * @details For trigger indices @ref NDIGO_TRIGGER_TDC_PE to
     *          @ref NDIGO_TRIGGER_BUS3_PE this must be set.
     */
    ndigo_bool_t edge;

    /*!
     * @brief   Configure rising or falling edge trigger functionality.
     * @details If true (false)
     *          - @ref ndigo_trigger::edge is true:
     *            Trigger on rising (falling) edges,
     *            that is, when the signal level crosses from below to above
     *            the value of @ref ndigo_trigger::threshold.
     *          - @ref ndigo_trigger::edge is false (level triggering):
     *            Trigger parts of the signal that are above (below)
     *            the value of @ref ndigo_trigger::threshold.
     * @details For trigger indices @ref NDIGO_TRIGGER_AUTO and
     *          @ref NDIGO_TRIGGER_ONE this is ignored.
     * @details For trigger indices @ref NDIGO_TRIGGER_TDC_PE to
     *          @ref NDIGO_TRIGGER_BUS3_PE this must be set.
     */
    ndigo_bool_t rising;
} ndigo_trigger;

/*!
 * @brief   Struct for the initialization of the Ndigo board.
 * @details This structure must be completely initialized by calling
 *          @ref ndigo_get_default_init_parameters() before
 *          initializing an Ndigo5G using @ref ndigo_init().
 */
typedef struct {
    /*!
     * @brief   Version number.
     * @details It is increased when the definition of the structure is changed.
     *          The increment can be larger than one to match driver version
     *          numbers or similar.
     * @details Set to 0 for all versions up to first release.
     * @details Must be set to @ref NDIGO_API_VERSION.
     */
    int version;

    /*!
     * @brief   The index in the list of installed Ndigo boards that should
     *          be initialized.
     *
     * @details There might be multiple boards in the system that are handled
     *          by this driver as reported by ndigo count devices. This index
     *          selects one of them. Boards are enumerated depending on the
     *          PCIe slot. The lower the bus number and the lower the slot
     *          number the lower the card index.
     */
    int card_index;

    /*!
     * @brief   8-bit board ID number.
     * @details This number is filled into each packet created by the board
     *          and is useful if data streams of multiple boards will be merged.
     *          If boards of different types that use a compatible data format
     *          are used in a system each board should get a unique ID.
     * @details Can be changed with @ref ndigo_set_board_id().
     */
    int board_id;

    /*!
     * @brief   Use 10MHz clock supplied by IPC at band cable.
     * @details Must be set for all slaves when synchronizing multiple boards.
     */
    ndigo_bool_t use_external_clock;

    /*!
     * @brief   Drive internal 10MHz clock of this board to IPC at band cable.
     * @details Must be set for the master board when synchronizing
     *          multiple boards.
     */
    ndigo_bool_t drive_external_clock;

    /*!
     * @brief   Data acquisition of this board is controlled by the
     *          master board.
     */
    ndigo_bool_t is_slave;

    /*!
     * @brief   Set whether board is used in a multiple boards environment.
     */
    ndigo_bool_t multiboard_sync;

    /*!
     * @brief   If >0, the direct sync method is used for
     *          multi-board applications.
     * @details Value corresponds to accuracy (higher values for more
     *          accurate phase match).
     */
    int direct_sync;

    /*!
     * @brief   Period of the multi-card sync pulse.
     * @details Should be set to 4 if only Ndigo5G boards are present in the
     *          system. If other boards are synchronized, the correct value is
     *          the lowest common denominator of the value of all boards.
     * @details Ignored for single board setups.
     */
    int sync_period;

    /*!
     * @brief   Fine tap delay for incoming sync signals.
     * @details Ignored for single board setups.
     */
    int sync_delay;

    /*!
     * @brief   Fine tap delay for sync signals.
     * @details Ignored for single board setups
     */
    int sync_delay_master;

    /*!
     * @brief   Window calibration.
     * @details If true, a valid data window is automatically detected at
     *          initialization.
     * @details If false, values from flash memory are used in order to set
     *          the data window to the correct position.
     * @details Defaults to false.
     */
    ndigo_bool_t force_window_calibration;

    /*!
     * @brief   Enable the CLK and sync line for the HPTDC.
     * @details Must be set to false.
     * @details If an HPTDC is connected to the board this enables the CLK and
     *          sync line for the HPTDC.
     */
    ndigo_bool_t hptdc_sync_enabled;

    /*!
     * @brief   The minimum size of the host buffer.
     * @details If set to 0, the default size of 16MByte is used.
     * @details Only buffer_size[0] is used.
     */
    int64_t buffer_size[8];

    /*!
     * @brief   Type of buffer.
     * @details Possible values follow. Currently, this has to be set to
     *          @ref NDIGO_BUFFER_ALLOCATE.
     * @details @rst
     *          .. doxygengroup:: bufferdef
     *               :content-only:
     *          @endrst
     */
    int buffer_type;

    /*!
     * @brief   The start of the memory address in case
     *          @ref NDIGO_BUFFER_USE_PHYSICAL is used.
     * @details Currently ignored. May be used for future buffer types.
     * @details The buffers will be allocated with the sizes given by
     *          @ref ndigo_init_parameters::buffer_size.
     */
    uint64_t buffer_address;

    /*!
     * @brief   The size of the preallocated buffer.
     * @details Used if @ref NDIGO_BUFFER_USE_PREALLOCATED is used.
     */
    unsigned int preallocated_buffer_size;

    /*!
     * @brief   Specify board variant.
     * @details Can be used to activate future device variants,
     *          such as different base frequencies.
     * @details Defaults to 0.
     */
    int variant;

    /*!
     * @brief   A constant for the different devices from cronologic.
     * @details Initialized by @ref ndigo_get_default_init_parameters()
     *          and set to @ref CRONO_DEVICE_NDIGO5G.
     * @details Must be left unchanged.
     */
    int device_type;

    /*!
     * @brief   The write pointer is delayed by this number 4n clock periods.
     * @details The write pointer update is delayed by this number of 4n clock
     *          periods to hide race conditions between software and DMA.
     * @details Initialized by @ref ndigo_get_default_init_parameters().
     */
    int dma_read_delay;
} ndigo_init_parameters;

/*!
 * @brief   Configuration of a trigger block.
 * @details Used by @ref ndigo_configuration::trigger_block.
 */
typedef struct {
    /*!
     * @brief Activates triggers on this channel.
     */
    ndigo_bool_t enabled;

    /*!
     * @brief   Activates LED on input even if trigger block is not enabled.
     * @details Required for LED activity in Multi/SingleShot mode.
     */
    ndigo_bool_t force_led;

    /*!
     * @brief   Enable retriggering.
     * @details If a new trigger condition occurs while the postcursor is
     *          acquired the packet is extended by starting a new postcursor.
     *          Otherwise the new trigger is ignored and the packet ends after
     *          the precursor of the first trigger.
     * @details The retrigger setting is ignored for the timestamp channel.
     */
    ndigo_bool_t retrigger;

    /*!
     * @brief   Reserved. Defaults to false. Do not change.
     */
    ndigo_bool_t reserved1;
    /*!
     * @brief   Reserved. Defaults to false. Do not change.
     */
    ndigo_bool_t reserved2;

    /*!
     * @brief   Number of packets created in single shot mode before packet
     *          generation stops.
     * @details Maximum is @ref NDIGO_MAX_MULTISHOT.
     * @details @rst
     *          .. doxygengroup:: multishotdef
     *              :content-only:
     *          @endrst
     */
    int multi_shot_count;

    /*!
     * @brief   Precursor in multiples of the device main clock period (3.2ns).
     * @details It is the amount of data preceding a trigger that is captured.
     * @details The precursor setting is ignored for the TDC channel.
     * @details The maximum allowed value is @ref NDIGO_MAX_PRECURSOR.
     * @details @rst
     *          .. doxygengroup:: precursordef
     *              :content-only:
     *          @endrst
     */
    int precursor;

    /*!
     * @brief   Length in multiples of the device main clock period (3.2ns).
     * @details It corresponds to the total amount of data that is recorded in
     *          addition to the trigger window. @ref precursor determines how
     *          many of these are ahead of the trigger and how many are
     *          appended after the trigger.
     * @details In edge trigger mode (see @ref ndigo_trigger::edge), the trigger
     *          window is always one main clock cycle wide.
     * @details In level trigger mode it is as long as the trigger
     *          condition is fulfilled.
     * @details The length setting is ignored for the TDC channel.
     */
    int length;

    /*!
     * @brief   A bitmask with a bit set for all trigger sources that can
     *          trigger this channel.
     * @details The bits correspond to the following defines, where the `_PE`
     *          defines are always triggered by a positive edge in the hardware.
     * @details Defaults to a bitmask triggering the current channel.
     * @details @rst
     *          .. doxygengroup:: sourcedefs
     *              :content-only:
     *          @endrst
     */
    int sources;

    /*!
     * @brief   A bitmask with a bit set for all gates controlling this channel.
     * @details The bits correspond to the following defines.
     * @details Defaults to @ref NDIGO_TRIGGER_GATE_NONE.
     * @details @rst
     *          .. doxygengroup:: gatedefs
     *              :content-only:
     *          @endrst
     */
    int gates;

    /*!
     * @brief   Number of packets that need to fit into the onboard FIFO.
     * @details This parameter sets how many packets are supposed to fit into
     *          the on-board FIFO before a new packet is recorded after the
     *          FIFO was full. That is, a certain amount of free space in the
     *          FIFO is demanded before a new packet is written after the FIFO
     *          was full.
     * @details As a measure for the packet length the gate length (configured
     *          by @ref ndigo_gating_block::start and
     *          @ref ndigo_gating_block::stop) is used.
     * @details The onboard algorithm checks the free FIFO space only in case
     *          the FIFO is full. Therefore, if this number is 1.0 or more
     *          at least every second packet in the host buffer is guaranteed
     *          to have the full length set by the gate length parameters.
     * @details In many cases smaller values will also result in full length
     *          packets. But below a certain value multiple packets that are
     *          cut off at the end will appear.
     */
    double minimum_free_packets;
} ndigo_trigger_block;

/*!
 * @brief   Contains settings of the gating blocks.
 * @details Used by @ref ndigo_configuration::gating_block.
 */
typedef struct {
    /*!
     * @brief   Invert output polarity.
     * @details Defaults to false.
     */
    ndigo_bool_t negate;

    /*!
     * @brief   Enable retrigger functionality.
     * @details If retriggering is enabled, the timer is reset to the value of
     *          the start parameter whenever the input signal is set while
     *          waiting to reach the stop time.
     * @details Defaults to false.
     */
    ndigo_bool_t retrigger;

    /*!
     * @brief   Currently not implemented. Do not use.
     * @details Defaults to true. If set, a gate is created with the set timing
     *          from the first occurrence of the input trigger even for short
     *          gates. If not set, the input signal must persist for the gate
     *          to be created.
     */
    ndigo_bool_t extend;

    /*!
     * @brief   Defaults to false. Do not change.
     */
    ndigo_bool_t reserved1;

    /*!
     * @brief   The time from the first input signal seen in the idle state
     *          until the gating output is set.
     * @details `start` needs to be >=0 and <2^16.
     * @details `start` must be set to a value <= @ref stop.
     * @details In multiples of 3.2ns.
     */
    int start;

    /*!
     * @brief   The number of samples from leaving the idle state until the
     *          gating output is reset.
     * @details If retriggering is enabled the timer is reset to the value of
     *          the start parameter whenever the input signal is set while
     *          waiting to reach the stop time.
     * @details `stop` needs to be >=0 and <2^16.
     * @details In multiples of 3.2ns.
     */
    int stop;

    /*!
     * @brief   A bitmask with a bit set for all trigger sources that can
     *          trigger this gating block.
     * @details The bits correspond to the same defines listed in
     *          @ref ndigo_trigger_block::sources.
     * @details The gating blocks cannot use the digital trigger as
     *          as a source, that is, bitmasks
     *          @ref NDIGO_TRIGGER_SOURCE_TDC_PE to
     *          @ref NDIGO_TRIGGER_SOURCE_BUS3_PE
     */
    int sources;
} ndigo_gating_block;

/*!
 * @brief   Configures the optional extension board.
 * @details This structure configures the merging of the inputs from the
 *          synchronization bus and the optional extension board.
 * @details Used by @ref ndigo_configuration::extension_block.
 */
typedef struct {
    /*!
     * @brief   Enables routing of digital signal from the Ndigo extension
     *          board.
     * @details The signals are routed to the corresponding BUSx trigger unit.
     */
    ndigo_bool_t enable;

    /*!
     * @brief   Control signal routing.
     * @details If true, only the signal from Ndigo extension board is used.
     * @details If false, input signal and BUS signal are read before routing
     *          to the according BUSx trigger unit.
     */
    ndigo_bool_t ignore_cable;
} ndigo_extension_block;

/*!
 * @brief   Structure contains static information
 * @details This structure contains information about the board that does not
 *          change during run time.
 * @details It is provided by @ref ndigo_get_static_info().
 */
struct ndigo_static_info {
    /*!
     * @brief The number of bytes occupied by the structure.
     */
    int size;

    /*!
     * @brief   Version number of this struct used by this API.
     * @details Equal @ref NDIGO_STATIC_INFO_VERSION and must be left unchanged.
     */
    int version;

    /*!
     * @brief   Index of the board as passed to the constructor.
     * @details Can also be set via @ref ndigo_set_board_id().
     */
    int board_id;

    /*!
     * @brief   Driver revision number.
     * @details The lower three bytes contain a triple level hierarchy of
     *          version numbers. E.g., 0x010103 codes version 1.1.3.
     * @details Versioning follows the [semver](https://semver.org/) standard.
     */
    int driver_revision;

    /*!
     * @brief SVN revision of the driver build.
     */
    int driver_build_revision;

    /*!
     * @brief   Revision number of the FPGA configuration.
     * @details This can be read from a register.
     */
    int firmware_revision;

    /*!
     * @brief   Board revision number.
     * @details This can be read from a register.
     * @details It is a four bit number that changes when the schematic of the
     *          board is changed:
     *           - 0: Experimental first board Version. Labeled Rev. 1
     *           - 2: First commercial Version. Labeled Rev. 2
     *           - 3: Revised version starting in 2011 labeled Rev. 3
     */
    int board_revision;

    /*!
    * @brief Describes the schematic configuration of the board.
    *
    * - **Board revision 0:** Always reads 0.
    * - **Board revision 2:**
    *   - **If Bit 3 = 0:**
    *     - Bit 0: ADC resolution (0 = 8-bit, 1 = 10-bit).
    *     - Bit 1: TDC-oscillator (0 = oscillator present, 1 = simple trigger).
    *     - Bit 2: Input connectors (0 = single ended, 1 = differential).
    *   - **If Bit 3 = 1 (special version):**
    *     - 0xA: Ndigo1250M-12 single ended with digital trigger.
    *     - 0x8: Ndigo5G-8 single ended with digital trigger.
    * - **Board revision 3:**
    *   - Bit 2: Input connectors (0 = single ended, 1 = differential).
    *   - Other bit patterns [Bits 3...0]:
    *     - 0010: Ndigo5G-10 2.5u 10
    *     - 0011: Ndigo5G-8-AQ 2.5u 8
    *     - 0110: Ndigo5G-10-Diff 560pF 10 DIFF
    *     - 1000: Ndigo5G-8 560pF 8+
    *     - 1010: Ndigo1250M-12 2.2uF 12 S DC
    *     - 1011: Ndigo5G-10 560pF 10
    *     - 1110: Ndigo5G-S 2.2uF 10 S Infiniband, DIFF
    *     - 1111: Ndigo5G-R = fADC4/10 560pF 10
    */
    int board_configuration;

    /*!
     * @brief   Number of bits of the ADC
     */
    int adc_resolution;

    /*!
     * @brief   Maximum sample rate in Hz.
     * @details Equals 5e9.
     */
    double nominal_sample_rate;

    /*!
     * @brief   Analog bandwidth in Hz.
     * @details Equals 3e9.
     */
    double analog_bandwidth;

    /*!
     * @brief Chip ID as read from the 16-bit ADC chip ID register.
     */
    int chip_id;

    /*!
     * @brief   Serial number with year and running number in 8.24 format.
     * @details 8 bits are used to encode the year, 24 bits to encode the
     *          serial number.
     * @details The number is identical to the one printed on the silvery
     *          sticker on the board.
     */
    int board_serial;

    /*!
     * @brief   64-bit serial number from the configuration flash chip.
     */
    int flash_serial_low;

    /*!
     * @brief   64-bit serial number from the configuration flash chip
     */
    int flash_serial_high;

    /*!
     * @brief   If not 0, the driver found valid calibration data in the flash
                on the board and is using it.
     */
    int flash_valid;

    /*!
     * @brief   False for the standard AC coupled Ndigo5G.
     */
    ndigo_bool_t dc_coupled;

    /*!
     * @brief Subversion revision ID of the FPGA configuration.
     */
    int subversion_revision;

    /*!
     * @brief   Calibration date.
     * @details DIN EN ISO 8601 string YYYY-MM-DD HH:DD describing the time
     *          when the card was calibrated.
     */
    char calibration_date[NDIGO_CALIBRATION_DATE_LEN];

    /*!
     * @brief   Bitstream creation date
     * @details DIN EN ISO 8601 string YYYY-MM-DD HH:DD:SS describing the time
     *          when the bitstream was created.
     */
    char bitstream_date[NDIGO_BITSTREAM_DATE_LEN];

    /*!
     * @brief   FPGA module revision number.
     * @details It is a 4-bit number that changes when the schematic of the
     *          FPGA module is changed.
     */
    int fpga_module_revision;

    /*!
     * @brief   FPGA module configuration.
     * @details The same FPGA module can be populated in multiple variants
     *          encoded in 6 bits.
     */
    int fpga_module_configuration;
};

/*!
 * @brief   Contains fast-to-obtain dynamic information.
 * @details Struct is populated using @ref ndigo_get_fast_info.
 */
typedef struct {
    /*!
     * @brief The number of bytes occupied by the structure.
     */
    int size;

    /*!
     * @brief   Version number of this struct used by the API.
     * @details Equals @ref NDIGO_FAST_INFO_VERSION and should be left
     *          unchanged.
     */
    int version;

    /*!
     * @brief   Speed of the ADC fan in rpm.
     * @details Reports 0 if no fan is present.
     */
    int adc_rpm;

    /*!
     * @brief   Speed of th FPGA fan in rpm.
     * @details Reports 0 if no fan is present.
     */
    int fpga_rpm;

    /*!
     * @brief   Alert bits from the system monitor.
     * @details Bits correspond to the following defines:
     * @details @rst
     *          .. doxygengroup:: ndigoalertdefs
     *              :content-only:
     *          @endrst
     */
    int alerts;

    /*!
     * @brief   Auxiliary FPGA voltage, nominal 2.5V.
     */
    double voltage_aux;

    /*!
     * @brief   Internal FPGA voltage, nominal 1.0V.
     */
    double voltage_int;

    /*!
     * @brief   In Celsius as measured on die.
     */
    double fpga_temperature;

    /*!
     * @brief   Organizes power supply of PCIe lanes.
     */
    int pcie_pwr_mgmt;

    /*!
     * @brief   Number of PCIe lanes that the card uses.
     * @details Should be 4 for Ndigo5G.
     */
    int pcie_link_width;

    /*!
     * @brief   Maximum size in bytes for one PCIe transaction.
     * @details Depends on system configuration.
     */
    int pcie_max_payload;

    /*!
     * @brief   Data rate of the PCIe card.
     * @details Depends on system configuration.
     */
    int pcie_link_speed;
} ndigo_fast_info;

/*!
 * @brief   Contains configuration changes.
 * @details This structure contains information that change indirectly due to
 *          configuration changes.
 * @details It is populated using @ref ndigo_get_param_info.
 */
typedef struct {
    /*!
     * @brief   The number of bytes occupied by the structure.
     */
    int size;

    /*!
     * @brief   Version number of this struct used by the API.
     */
    int version;

    /*!
     * @brief   Bandwidth in Hz.
     * @details Currently fixed at 3e9.
     */
    double bandwidth;

    /*!
     * @brief   Actual sample rate of currently sampled data.
     * @details Depends on @ref ndigo_configuration::adc_mode.
     */
    double sample_rate;

    /*!
     * @brief   The period one sample in the data represent in picoseconds.
     */
    double sample_period;

    /*!
     * @brief   The ID the board uses to identify itself in the output data
     *          stream.
     * @details Takes values between 0 to 255.
     */
    int board_id;

    /*!
     * @brief   Number of channels in the current mode
     */
    int channels;

    /*!
     * @brief   Mask with a set bit for each enabled input channel.
     */
    int channel_mask;

    /*!
     * @brief   Size of the host buffer in bytes.
     */
    int64_t total_buffer;
} ndigo_param_info;

/*!
 * @brief   Contains slow-to-obtain dynamic information.
 * @details The data reported in this structure requires milliseconds to be
 *          obtained.
 * @details The application should only call it in situation where the program
 *          flow can cope with an interruption of that magnitude.
 * @details Populated by @ref ndigo_get_slow_info.
 */
struct ndigo_slow_info {
    /*!
     * @brief The number of bytes occupied by the structure.
     */
    int size;

    /*!
     * \brief Version number of this struct used by the API.
     */
    int version;

    /*!
     * @brief   ADC temperature in Celsius as measured on die.
     */
    double adc_temperature;

    /*!
     * @brief Temperature of the board in Celsius.
     */
    double board_temperature;
};

/*!
 * @brief  Finalize the driver for this device.
 * @param[in] device Pointer to the device.
 * @return A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_close(ndigo_device *device);

/*!
 * @brief   Starts data acquisition.
 * @details `ndigo_start_capture` will reset the memory buffer. If you do wish
 *          to stop recording and resume later without clearing the buffer, use
 *          @ref ndigo_pause_capture and @ref ndigo_continue_capture instead.
 * @param[in] device Pointer to the device.
 * @return  A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_start_capture(ndigo_device *device);

/*!
 * @brief   Pause data acquisition.
 * @details Data acquisition can be continued using @ref ndigo_continue_capture.
 * @details @ref ndigo_pause_capture and @ref ndigo_continue_capture have less
 *          overhead than @ref ndigo_stop_capture and @ref ndigo_start_capture,
 *          but do not allow for a configuration change.
 * @param[in] device Pointer to the device.
 * @return  A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_pause_capture(ndigo_device *device);

/*!
 * @brief   Resume data acquisition.
 * @details Can only be called if data acquisition was paused using
 *          @ref ndigo_pause_capture.
 * @details @ref ndigo_pause_capture and @ref ndigo_continue_capture have less
 *          overhead than @ref ndigo_stop_capture and @ref ndigo_start_capture,
 *          but do not allow for a configuration change.
 * @param[in] device Pointer to the device.
 * @return  A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_continue_capture(ndigo_device *device);

/*!
 * @brief Stop data acquisition.
 * @param[in] device Pointer to the device.
 * @return A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_stop_capture(ndigo_device *device);

/*!
 * @brief   Enable each of the specified channels for one (or more) trigger(s),
 *          respectively.
 * @details The number of triggers is configured using
 *          @ref ndigo_trigger_block::multi_shot_count.
 * @param[in] device Pointer to the device.
 * @param[in] channel_mask Bitmask of channels to trigger.
 * @return A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_single_shot(ndigo_device *device, int channel_mask);

/*!
 * @brief  Enable manual triggering.
 * @param[in] device Pointer to the device.
 * @param[in] channel_mask Bitmask of channels to manually trigger.
 * @return A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_manual_trigger(ndigo_device *device, int channel_mask);

/*!
 * @brief   Acknowledge data.
 * @details Acknowledge all data up to the packet provided as the input
 *          parameter. This is mandatory if @ref ndigo_read() was called with
 *          @ref ndigo_read_in::acknowledge_last_read set to false.
 * @details This feature allows freeing up partial host memory early if there
 *          will be no call to @ref ndigo_read() anytime soon.
 * @details It also allows to keep data over multiple calls to @ref ndigo_read,
 *          avoiding unnecessary copying of data.
 * @details @rst
 *          .. attention::
 *
 *               After acknowledging a packet it becomes *immediately* invalid.
 *               It is *immediately* unsafe to attempt accessing its content.
 *          @endrst
 * @param[in] device Pointer to the device.
 * @param[in] packet Pointer to a packet. All packets up to this one will be
 *          acknowledged.
 * @return  A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_acknowledge(ndigo_device *device,
                                volatile ndigo_packet *packet);
/*!
 * @brief  Populate @ref ndigo_static_info.
 * @param[in] device Pointer to the device.
 * @param[out] info Pointer to a structure in which to store the information
 * @return A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_get_static_info(ndigo_device *device,
                                    ndigo_static_info *info);

/*!
 * @brief  Populate @ref ndigo_param_info.
 * @param[in] device Pointer to the device.
 * @param[out] info Pointer to a struct to be filled.
 * @return A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_get_param_info(ndigo_device *device,
                                   ndigo_param_info *info);

/*!
 * @brief   Populate @ref ndigo_fast_info.
 * @details The information can be obtained within a few microseconds.
 * @param[in] device Pointer to the device.
 * @param[out] info Pointer to a struct to be filled.
 */
NDIGO_API int ndigo_get_fast_info(ndigo_device *device, ndigo_fast_info *info);

/*!
 * @brief   Get init parameters of a device
 * @param[in] device Pointer to the device.
 * @param[out] init_params Pointer to a struct to be filled.
 * @return A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_get_init_parameters(ndigo_device *device,
                                        ndigo_init_parameters *init_params);

/*!
 * @brief  Returns the driver version.
 * @return The version in the same format as
 *         @ref ndigo_static_info::driver_revision
 */
NDIGO_API int ndigo_get_driver_revision();

/*!
 * @brief  Returns the driver version including SVN build revision. as a string
 * @return The format is x.y.z.svn.
 */
NDIGO_API const char *ndigo_get_driver_revision_str();

/*!
 * @brief  Obtain information that can be obtained within a few milliseconds.
 * @param[in] device A pointer to the device.
 * @param[out] info A pointer to a structure to be filled.
 * @return A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_get_slow_info(ndigo_device *device, ndigo_slow_info *info);

/*!
 * @brief   Calculate the exact TDC packet timestamp.
 * @details Call on a TDC packet (that is, @ref ndigo_packet::channel = 4)
 *          to update the timestamp of the packet with a more accurate value.
 * @details @rst
 *          .. attention::
 *
 *              If called more than once on a packet, the timestamp will be
 *              invalid.
 *          @endrst
 * @param[in] device A pointer to the device.
 * @param[out] packet Pointer to a TDC packet in which to update the
 *          timestamp.
 * @return  A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_process_tdc_packet(ndigo_device *device,
                                       volatile ndigo_packet *packet);

/*!
 * @brief   Set the LED to the selected color.
 * @details No automatic updates are performed.
 * @param[in] device Pointer to the device.
 * @param[in] led    Which LED to set.
 * @param[in] r      Red value from 0 to 255.
 * @param[in] g      Green value from 0 to 255.
 * @param[in] b      Blue value from 0 to 255.
 * @return  A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_set_led_color(ndigo_device *device, int led,
                                  unsigned short r, unsigned short g,
                                  unsigned short b);

/*!
 * @brief  Set LED to be controlled automatically by the hardware.
 * @param[in] device A pointer to the device.
 * @param[in] led Which LED to set.
 * @return A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_set_led_automode(ndigo_device *device, int led);

/*!
 * @brief  Enable or disable the status LEDs.
 * @param[in] device A pointer to the device.
 * @param[in] enable Boolean to enable or disable the LEDs.
 * @return A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_set_status_led(ndigo_device *device, bool enable);

/*!
 * @brief  Get latest error message of the current device.
 * @param[in] device A pointer to the device.
 * @return The error message in plain text.
 */
NDIGO_API const char *ndigo_get_last_error_message(ndigo_device *device);

/*!
 * @brief  Flash the LEDs on the card.
 * @param[in] device A pointer to the device.
 * @param[in] repeat Number of times to flash the LEDs.
 * @return A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_identify(ndigo_device *device, int repeat);

/*!
 * @brief  Return the type of the device
 * @param[in] device A pointer to the device.
 * @return @ref CRONO_DEVICE_NDIGO5G.
 */
NDIGO_API int ndigo_get_device_type(ndigo_device *device);

/*!
 * @brief  Return the product name of the card.
 * @param[in] device A pointer to the device.
 * @return The name in plain text.
 */
NDIGO_API const char *ndigo_get_device_name(ndigo_device *device);

/*!
 * @brief   Overwrite the board ID
 * @details The board ID can be changed after initialization of the card.
 *          If `cronotools` are used, the board ID changes have to be done
 *          before the initialization of `cronotools`.
 * @param[in] device A pointer to the device.
 * @param[in] board_id New board ID.
 * @return  A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_set_board_id(ndigo_device *device, int board_id);

/*!
 * @brief  Obtain PCIe info.
 * @param[in] device A pointer to the device.
 * @param[out] pcie_info  A pointer to a structure to be filled.
 * @return A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_get_pcie_info(ndigo_device *device,
                                  crono_pcie_info *pcie_info);

/*!
 * @brief   Clear PCIe errors.
 * @details Only useful for PCIe problem debugging.
 * @param[in] device A pointer to the device.
 * @param[in] flags One of
 *          @rst
 *          .. doxygengroup:: pcieclearflags
 *              :content-only:
 *          @endrst
 * @return  A @ref funcreturnsndigo "status code".
 */
NDIGO_API int ndigo_clear_pcie_errors(ndigo_device *device, int flags);

#ifdef __cplusplus
}
#endif

#endif
