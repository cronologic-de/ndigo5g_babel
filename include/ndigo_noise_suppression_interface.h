#ifndef NDIGO_NOISE_SUPPRESSION_INTERFACE_H
#define NDIGO_NOISE_SUPPRESSION_INTERFACE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#ifdef NDIGO_NOISE_SUPPRESSION_DLL_EXPORTS
#define NDIGO_NOISE_SUPPRESSION_API __declspec(dllexport)
#else
#define NDIGO_NOISE_SUPPRESSION_API __declspec(dllimport)
#endif // #ifdef NDIGO_NOISE_SUPPRESSION_DLL_EXPORTS
#else
// Linux
#define NDIGO_NOISE_SUPPRESSION_API
#endif
	/*
	pointer to capture device
	use nns_create() to initialize
	*/
	typedef struct {
		void* nns_inst;
	} ndigo_noise_sup;

	/*
	create capture device, may not be called more than once per Ndigo5G
	nns_inst   : pointer to capture device, valid only if function returns TRUE
	card_index : Ndigo5G to use
	returns FALSE if creation fails, TRUE otherwise
	*/
	NDIGO_NOISE_SUPPRESSION_API bool nns_create(ndigo_noise_sup* nns_inst, int card_index);

	/*
	initialize capture device and set capture parameters, nns_create() must be called first
	recording of ADC samples is triggered by falling edge on T input
	nns_inst      : pointer to capture device
	start         : delay between trigger event and start of sampling in 3.2ns clock periods
	length        : sample length in 3.2ns clock periods
	analog_offset : shift input baseline up to +/- 0.25 V
	returns FALSE if initialization fails, TRUE otherwise
	*/
	NDIGO_NOISE_SUPPRESSION_API bool nns_initialize(ndigo_noise_sup* nns_inst, int start, int length, double analog_offset);

	/*
	set threshold for zero-suppression
	nns_inst : pointer to capture device
	value    : threshold as ADC sample value 
	rising   : if FALSE replace samples above threshold, else replace samples below threshold
	*/
	NDIGO_NOISE_SUPPRESSION_API void nns_set_threshold(ndigo_noise_sup* nns_inst, double value, bool rising);

	/*
	set baseline value for zero-suppression
	nns_inst : pointer to capture device
	value    : baseline as ADC sample value 
	*/
	NDIGO_NOISE_SUPPRESSION_API void nns_set_baseline(ndigo_noise_sup* nns_inst, double value);

	/*
	measure the baseline of input A, no trigger on T required, nns_initialize() must be called first
	nns_inst   : pointer to capture device
	histogramm : ADC sample value histogram of baseline capture, user provided array, size (2^16 / binsize)
	binsize    : histogram bin size, must be power of 2 and no more than 64
	raw_data   : unaltered ADC samples are copied to this buffer, user provided array, size (sample length * 16)
	max_index  : histogram element with highest count
	baseline   : measured baseline value as ADC sample value 
	returns FALSE if data capture fails, TRUE otherwise
	*/
	NDIGO_NOISE_SUPPRESSION_API bool nns_capture_baseline(ndigo_noise_sup* nns_inst, int *histogram, int binsize, short *raw_data, int *max_index, double *baseline);

	/*
	capture spectrum data on input A after falling edge on T input, nns_initialize() must be called first
	nns_inst             : pointer to capture device
	spectrum             : zero-suppressed and FIR-filtered ADC samples are copied to this buffer, user provided array, size (sample length * 16)
	raw_data             : unaltered ADC samples are copied to this buffer, user provided array, size (sample length * 16)
	timestamp            : devices timestamp of the capture event
	filter               : if TRUE enable FIR filtering
	zero_suppression     : if TRUE set ADC samples above or below threshold to baseline value
	subpixel_positioning : if TRUE adjust ADC sample data phase depending on edge timing measured by TDC
	returns FALSE if data capture fails, TRUE otherwise
	*/
	NDIGO_NOISE_SUPPRESSION_API bool nns_capture_spectrum(ndigo_noise_sup* nns_inst, double *spectrum, short *raw_data, int64_t *timestamp, bool filter, bool zero_suppression, bool subpixel_positioning);

#ifdef __cplusplus
}
#endif

#endif