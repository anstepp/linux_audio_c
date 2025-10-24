#include <assert.h>
#include <jack/control.h>
#include <jack/jack.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>

#include "portaudio.h"
#include "pa_ringbuffer.c"
#include "pa_ringbuffer.h"

#include "synthesis/waves.h"

#define SR 44100
#define OUT_CHANS 2
#define BUF_FRAMES 256

int check_pa_err(PaError pa_err){
	if(paNoError != pa_err){
		puts(Pa_GetErrorText(pa_err));
		return(pa_err);
	}

	return(0);
}

static int jackCallback(){
	return 0;
}

static int paCallback(const void* inBuf,
		void* outBuf,
		unsigned long frames_per_buf,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void* data)
{
	return 0;
}

int process(jack_nframes_t nframes, void* arg){
	return 0;
}

int main(){

	int err; // use for "acutal" c mistakes
	PaError pa_err; // for port audio specific error handling

	jack_port_t *input_port;
	jack_port_t *output_port;
	jack_status_t *jack_status = NULL;
	jack_client_t *client;
	client = jack_client_open("client", JackNoStartServer, jack_status);	
	pa_err = Pa_Initialize();

	err = check_pa_err(pa_err);
	assert(!err);

	int pa_device_count;

	pa_device_count = Pa_GetDeviceCount();

	if(pa_device_count < 0){
		check_pa_err(pa_device_count);
	} else {
		for(int dev = 0; dev < pa_device_count; dev++){
			printf("device num: %d, Name: %s\n" ,dev, Pa_GetDeviceInfo(dev)->name);
		}
	}

	int device_no;

	printf("Select Device (by device number):");
	scanf("%d", &device_no);
	printf("Selected Device: %d\n", device_no);

	char str[20];
	int block = 1024;
	int16_t *data;
        data = (int16_t*) malloc(block*sizeof(int16_t));
	if (data == NULL){
		return 1;
	};
	PaUtilRingBuffer buf_struct;
	PaUtilRingBuffer* buf_struct_ptr = &buf_struct;
	ring_buffer_size_t size = block;

	err = PaUtil_InitializeRingBuffer(buf_struct_ptr, size, size, data);

	assert(!err);

	for(int i = 0; i < block; i++){

		data[i] = (int16_t)audio_sine(i);
	}

	err = PaUtil_WriteRingBuffer(buf_struct_ptr, data, size);

	PaStream* stream;

	pa_err = Pa_OpenDefaultStream(&stream,
		        0,	
			OUT_CHANS,
			paFloat32, // please change me
			SR,
			BUF_FRAMES,
			paCallback,
			&data);

	if(pa_err != paNoError){
		puts(Pa_GetErrorText(pa_err));
	}

	pa_err = Pa_Terminate();
	err = check_pa_err(pa_err);

	assert(!err);	

	sprintf(str, "%d", err);
	puts(str);
	return err;

}
