#include <assert.h>
#include <stdio.h>


#include "pa_err_custom.h"
#include "portaudio.h"

int check_pa_err(PaError pa_err){
	if(paNoError != pa_err){
		puts(Pa_GetErrorText(pa_err));
		return(pa_err);
	}

	return(0);
}
