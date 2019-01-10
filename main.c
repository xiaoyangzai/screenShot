#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "memory_pool.h"
#include "capture.h"
#include "jpeg_util.h"

int main(int argc,char *argv[])
{
#ifdef DECODE_TEST
	if(argc != 3)
	{
		printf("usage: ./capture_screen [Source JPEG File Path] [JPEG File Path To Save]\n");
		return -1;
	}

	memory_pool_t *pool = memory_pool_create(20*1024*1024);

	uint32_t width = 0,height = 0;
	uint8_t *outbuf = NULL;
	uint64_t outlen = 0;
	uint32_t bpp;
	uint8_t *rgb24 = decode_jpeg(argv[1],&width,&height,&bpp,pool);
	printf("========JPEG File Informatoin =========\n");
	printf("Image size: %d * %d * %d = %d\n",width,height,bpp,width*height*bpp);
	printf("=======================================\n");

	encode_jpeg(rgb24,width,height,&outbuf,&outlen,pool);

	int fd = open(argv[2],O_WRONLY|O_CREAT,0664);
	if(write(fd,outbuf,outlen) != (ssize_t)outlen)
	{
		printf("write failed: %s\n",strerror(errno));
		return 0;
	}
	close(fd);
	printf("Image length: %d\n",outlen);
	printf("Screen capture has been saved into %s\n",argv[2]);
	memory_pool_destroy(pool);
#endif
#ifdef ENCODE_TEST
	if(argc != 2)
	{
		printf("usage: ./capture_screen [JPEG File Path To Save]\n");
		return -1;
	}

	memory_pool_t *global_pool = memory_pool_create(20*1024*1024);
	uint32_t width = 0,height = 0;
	uint8_t *outbuf = NULL;
	uint64_t outlen = 0;
	get_window_size(&width,&height);
	uint8_t *rgb24 = (uint8_t *)memory_pool_alloc(global_pool,width*height*3);
	CaptureDesktop(rgb24);  
	encode_jpeg(rgb24,width,height,&outbuf,&outlen,global_pool);

	CaptureDesktop(rgb24);  
	encode_jpeg(rgb24,width,height,&outbuf,&outlen,global_pool);

	int fd = open(argv[1],O_WRONLY|O_CREAT,0664);
	if(write(fd,outbuf,outlen) != (ssize_t)outlen)
	{
		printf("write failed: %s\n",strerror(errno));
		return 0;
	}
	close(fd);
	printf("Image size: %d * %d\n",width,height);
	printf("Image length: %ld\n",outlen);

	printf("Screen capture has been saved into %s\n",argv[1]);
	memory_pool_destroy(global_pool);
#endif
	return 0;
}

