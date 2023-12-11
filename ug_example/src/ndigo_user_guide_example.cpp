//
// ndigo_user_guide_example.cpp : User guide example for Ndigo5G driver programming
//

#include "Ndigo_interface.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	printf("cronologic ndigo_user_guide_example using driver: %s\n", ndigo_get_driver_revision_str());

	ndigo_init_parameters params;
	ndigo_get_default_init_parameters(&params);

	params.card_index = 0;
	params.buffer_size[0] = 1 << 23;
	params.drive_external_clock = false;
	params.multiboard_sync = false;
	params.use_external_clock = false;
	params.hptdc_sync_enabled = false;
	params.is_slave = false;

	int error_code;
	const char *error_message;
	ndigo_device* ndgo = ndigo_init(&params, &error_code, &error_message);
	if (error_code != NDIGO_OK) {
		printf("\nError %d: %s\n", error_code, error_message);
		exit(-1);
	}

	ndigo_configuration config;
	ndigo_get_default_configuration(ndgo, &config);
	config.adc_mode = NDIGO_ADC_MODE_ABCD;
	config.output_mode = NDIGO_OUTPUT_MODE_SIGNED16;

	// disable unused trigger blocks
	config.trigger_block[1].enabled = false;
	config.trigger_block[2].enabled = false;
	config.trigger_block[3].enabled = false;
	config.trigger_block[4].enabled = false;

	// configure trigger block 0
	config.trigger_block[0].enabled = true;
	config.trigger_block[0].minimum_free_packets = 1.0;
	config.trigger_block[0].precursor = 1;
	config.trigger_block[0].retrigger = 0;
	config.trigger_block[0].sources = NDIGO_TRIGGER_SOURCE_A0;
	config.trigger_block[0].length = 16;
	config.trigger_block[0].gates = NDIGO_TRIGGER_GATE_NONE;

	config.analog_offset[0] = 0.1;

	config.trigger[NDIGO_TRIGGER_A0].edge = true;
	config.trigger[NDIGO_TRIGGER_A0].rising = false;
	config.trigger[NDIGO_TRIGGER_A0].threshold = 0;

	if (ndigo_configure(ndgo, &config) != NDIGO_OK) {
		printf("\nFatal configuration error. Aborting...\n");
		exit(-1);
	}

	ndigo_start_capture(ndgo);

	// counts the number of packets received
	int count = 0;

	while (count < 10) {
		ndigo_read_in in;
		// Do not wait for data
		// (if set to 1 the ndigo_acknowledge function has to be removed)
		in.acknowledge_last_read = 0;
		ndigo_read_out out;
		int result = ndigo_read(ndgo, &in, &out);
		if ((NDIGO_OK == result) && (out.first_packet != nullptr))
		{
			// buffer received with one or more packets
			volatile ndigo_packet *packet = out.first_packet;
			while (packet <= out.last_packet) {
				int length = 0;
				if (!(packet->type & NDIGO_PACKET_TYPE_TIMESTAMP_ONLY))
					length = packet->length;

				printf("Card %d, Channel %d, Flags %d, Length %d, Timestamp %lu \n",
					packet->card, packet->channel, packet->flags, length, packet->timestamp);

				if (!(packet->type & NDIGO_PACKET_TYPE_TIMESTAMP_ONLY))
				{
					short* data = (short*)packet->data;
					for (unsigned int i = 0; i < packet->length * 4; i++)
						printf("%6d, ", *(data++));
					printf("\n\n");
				}
				// current packet pointer is invalid after call to ndigo_acknowledge()
				volatile ndigo_packet *next_packet = ndigo_next_packet(packet);
				ndigo_acknowledge(ndgo, packet);
				packet = next_packet;
				count++;
			}
		}
	}
	ndigo_close(ndgo);

	system("pause");

	return 0;
}
