/*
 * Name: devmload.c
 *
 * Purpose: load to physical address from file.
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
	unsigned long addr;
	void *virt_addr;

	int fd;
	uint32_t file_len;
	struct stat file_stat;

	if (argc < 3) {
		ERR("\nUsage:\t%s {addr} {filename}\n"
			"\taddr:	destination physical address\n"
			"\tfilename:	file name will load from\n",
			argv[0]);
		return -1;
	}
	addr = strtoul(argv[1], 0, 0);

	DEBUG("addr 0x%lx, filename %s\n", addr, argv[2]);

	if ((fd = open(argv[2], O_RDONLY, 0)) < 0) {
		ERR("%s open failed\n", argv[2]);
		return -1;
	}

	fstat(fd, &file_stat);
	file_len = file_stat.st_size;
	DEBUG("file length %d\n", file_len);

	/* mmap addr */
	virt_addr = devm_map(addr, file_len);
	if (virt_addr == NULL) {
		ERR("map failed\n");
		close(fd);
		return -1;
	}

	/* load file content */
	if (read(fd, virt_addr, file_len) != file_len)
		ERR("read failed\n");

	devm_unmap(virt_addr, file_len);

	close(fd);

	return 0;
}
