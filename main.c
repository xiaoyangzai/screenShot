#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "capture.h"
#include "jpeg_util.h"

int main(int argc,char *argv[])
{
	if(argc != 2)
	{
		printf("usage: ./capture_screen [JPEG File Path To Save]\n");
		return -1;
	}

	uint32_t width = 0,height = 0;
	uint8_t *outbuf = NULL;
	uint64_t outlen = 0;
	get_window_size(&width,&height);
	uint8_t *rgb24 = (uint8_t *)malloc(width*height*3);
	CaptureDesktop(rgb24);  
	encode_jpeg(rgb24,width,height,&outbuf,&outlen);

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
	free(rgb24);
	return 0;
}

