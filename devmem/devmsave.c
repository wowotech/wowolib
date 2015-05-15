/*
 * Name: devmsave.c
 *
 * Purpose: save physical address's content to file.
 *
 * Copyright (C) 2015 wowotech
 * Subject to the GNU Public License, version 2.
 *
 * Created By:		wowo<www.wowotech.net>
 * Created Date:	2015-05-05
 *
 * ChangeList:
 * Created in 2015-05-05 by wowo;
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
  
#include "debug.h"

#include "devmem.h"

/*
 * define the debug level of this file,
 * please see 'debug.h' for detail info
 */
DEBUG_SET_LEVEL(DEBUG_LEVEL_DEBUG);

int main(int argc, char **argv)
{
	int len;
	unsigned long addr;
	void *virt_addr;

	int fd;
	if (argc < 4) {
		ERR("\nUsage:\t%s {addr} {len} {filename}\n"
			"\taddr:	physical address need to save\n"
			"\tlen:		length in byte\n"
			"\tfilename:	file save to\n",
			argv[0]);
		return -1;
	}
	addr = strtoul(argv[1], 0, 0);
	len = strtoul(argv[2], 0, 0);

	DEBUG("addr 0x%lx, len %d, filename %s\n", addr, len, argv[3]);

	if ((fd = open(argv[3], O_WRONLY | O_CREAT, 0)) < 0) {
		ERR("%s open failed\n", argv[3]);
		return -1;
	}

	/* mmap addr */
	virt_addr = devm_map(addr, len);
	if (virt_addr == NULL) {
		ERR("map failed\n");
		close(fd);
		return -1;
	}

	if (write(fd, virt_addr, len) != len)
		ERR("write failed\n");

	devm_unmap((void *)virt_addr, len);

	close(fd);

	return 0;
}
