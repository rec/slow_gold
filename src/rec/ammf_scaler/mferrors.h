#ifndef _MFERRORS_H_
#define _MFERRORS_H_

/*
 * Error codes.  
 */
typedef long MFError;

/* !!!! NOTE: DON'T EVER CHANGE THE NUMERICAL VALUE OF MF_SUCCESS !!!! */
#define MF_SUCCESS 				(0)

#define MF_FAILURE 				(1)
#define MF_OUT_OF_MEMORY 			(2)
#define MF_INCORRECT_COMMAND_LINE 		(3)
#define MF_CALLING_PROGRAM_ERROR		(4)
#define MF_INTERNAL_PROGRAM_ERROR		(5)
#define MF_FILE_IO_ERROR			(6)
#define MF_MALFORMED_INPUT_DATA			(7)
#define MF_NOT_IMPLEMENTED_YET			(8)
#define MF_UNSUPPORTED_SOUNDFILE_FORMAT		(9)
#define MF_NO_SOUND_DATA_IN_FILE		(10)
#define MF_HARDWARE_ERROR			(11)
#define MF_END_OF_FILE				(12)
#define MF_DROPPED_SAMPLES_ERROR		(13)
#define MF_NULL_POINTER				(14)
#define MF_PARAMETER_OUT_OF_RANGE		(15)
#define MF_COULDNT_CREATE_FILE		 	(16)
#define MF_BAD_HEADER				(17)
#define MF_COULDNT_OPEN_URL			(18)
#define MF_COULDNT_LOAD_REALAUDIO_DLL		(19)
#define MF_REALAUDIO_NO_MORE_PLAYERS		(20)
#define MF_REALAUDIO_SDK_ERROR			(21)
#define MF_WINDOWS_REGISTRY_ERROR		(22)
#define MF_WRONG_CODEC_VERSION			(23)
#define MF_CODEC_OPEN_ERROR			(24)
#define MF_CODEC_READ_ERROR			(25)
#define MF_CODEC_NO_MORE_PLAYERS		(26)
#define MF_STRING_TOO_SHORT			(27)
#define MF_THREAD_ERROR				(28)
#define MF_MUTEX_ERROR				(29)
#define MF_TIMEOUT				(30)

#define MF_ERROR_END				(31)




const char* MFGetErrorString(MFError err);



#endif /* _MFERRORS_H_ */
