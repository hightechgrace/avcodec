#ifndef _avframe_h_
#define _avframe_h_

#include <stdint.h>

enum picture_format 
{
	PICTURE_NONE = -1,

	PICTURE_YUV420 = 0,	///< AV_PIX_FMT_YUV420P: planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)
	PICTURE_YUV422 = 4,	///< AV_PIX_FMT_YUV422P: planar YUV 4:2:2, 16bpp, (1 Cr & Cb sample per 2x1 Y samples)
	PICTURE_YUV444 = 5,	///< AV_PIX_FMT_YUV444P: planar YUV 4:4:4, 24bpp, (1 Cr & Cb sample per 1x1 Y samples)

	PICTURE_NV12 = 25,	///< AV_PIX_FMT_NV12: planar YUV 4:2:0, 12bpp, 1 plane for Y and 1 plane for the UV components, which are interleaved (first byte U and the following byte V)
	PICTURE_NV21 = 26,	///< AV_PIX_FMT_NV21: as above, but U and V bytes are swapped

	// https://en.wikipedia.org/wiki/RGBA_color_space
	PICTURE_RGBA = 28,	///< AV_PIX_FMT_RGBA(byte-oreder): packed RGBA 8:8:8:8, 32bpp, RGBARGBA...
	PICTURE_RGB24 = 2,	///< AV_PIX_FMT_RGB24: packed RGB 8:8:8, 24bpp, RGBRGB...
	PICTURE_RGB16 = 43,	///< AV_PIX_FMT_RGB565BE: packed RGB 5:6:5, 16bpp, (msb)   5R 6G 5B(lsb), big-endian

	//PICTURE_BGRA	= 30,	///< AV_PIX_FMT_BGRA(byte-oreder): packed BGRA 8:8:8:8, 32bpp, BGRABGRA...
	//PICTURE_BGR24	= 3,	///< AV_PIX_FMT_BGR24: packed RGB 8:8:8, 24bpp, BGRBGR...
	//PICTURE_BRG16	= 47,	///< AV_PIX_FMT_BGR565BE: packed BGR 5:6:5, 16bpp, (msb)   5B 6G 5R(lsb), big-endian
};

#define PICTURE_RGB32	PICTURE_RGBA
#define PICTURE_RGB565	PICTURE_RGB16

enum picture_type
{
	PICTURE_TYPE_NONE = 0,	///< Undefined
	PICTURE_TYPE_I,			///< Intra
	PICTURE_TYPE_P,			///< Predicted
	PICTURE_TYPE_B,			///< Bi-dir predicted
	PICTURE_TYPE_S,			///< S(GMC)-VOP MPEG-4
	PICTURE_TYPE_SI,		///< Switching Intra
	PICTURE_TYPE_SP,		///< Switching Predicted
	PICTURE_TYPE_BI,		///< BI type
};

enum pcm_sample_format
{
	PCM_SAMPLE_FMT_NONE = -1,

	PCM_SAMPLE_FMT_U8	= 0,	///< unsigned 8 bits
	PCM_SAMPLE_FMT_S16	= 1,	///< signed 16 bits
	PCM_SAMPLE_FMT_S32	= 2,	///< signed 32 bits
	PCM_SAMPLE_FMT_FLOAT = 3,	///< float
	PCM_SAMPLE_FMT_DOUBLE = 4,	///< double

	PCM_SAMPLE_FMT_U8P	= 5,	///< unsigned 8 bits, planar
	PCM_SAMPLE_FMT_S16P = 6,	///< signed 16 bits, planar
	PCM_SAMPLE_FMT_S32P = 7,	///< signed 32 bits, planar
	PCM_SAMPLE_FMT_FLTP = 8,	///< float, planar
	PCM_SAMPLE_FMT_DBLP = 9,	///< double, planar

	PCM_SAMPLE_FMT_S64	= 10,	///< signed 64 bits
	PCM_SAMPLE_FMT_S64P = 11,	///< signed 64 bits, planar
};

struct avframe_t
{
	int format;	///< picture_format/pcm_sample_format

	int64_t pts;
	int64_t dts;

	/// video only
	int flags;		///< PICTURE_TYPE_XXX
	int width;		///< video width
	int height;		///< video height
	
	/// audio only
	int channel;	 ///< number of audio channels
	int samples;	 ///< number of audio samples (per channel)
	int sample_bits; ///< bits per sample
	int sample_rate; ///< samples per second

	uint8_t* data[8]; // AAC 8-channels

	/// For video, size in bytes of each picture line
	/// For audio, size in bytes of each plane
	int linesize[8];
};

#endif /* !_avframe_h_ */