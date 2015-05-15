/*
 * Name: devmcpy.c
 *
 * Purpose: copy between two physical address.
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
  
#include "debug.h"

#include "devmem.h"

/*
 * define the debug level of this file,
 * please see 'debug.h' for detail info
 */
DEBUG_SET_LEVEL(DEBUG_LEVEL_DEBUG);

int main(int argc, char **argv)
{
	int count, width = 32, i;
	unsigned long src_addr, dst_addr;

	if (argc < 4) {
		ERR("\nUsage:\t%s {src_addr} {dst_addr} {count} [width]\n"
			"\tsrc_addr:	source address\n"
			"\tdst_addr:	destination address\n"
			"\tcount:	copy count, default is 1\n\n"
			"\twidth:	width, 8/16/32/64..., default is 32\n\n",
			argv[0]);
		return -1;
	}
	src_addr = strtoul(argv[1], 0, 0);
	dst_addr = strtoul(argv[2], 0, 0);
	count = strtoul(argv[3], 0, 0);

	if (argc > 4)
		width = strtoul(argv[4], 0, 0);

	DEBUG("src_addr 0x%lx, dst_addr 0x%lx, count %d, width %d\n",
		src_addr, dst_addr, count, width);

	switch (width) {
	case 8:
		for (i = 0; i < count; i++)
			devmem_writeb(dst_addr + i, devmem_readb(src_addr + i));

		break;
	case 32:
		for (i = 0; i < count; i++)
			devmem_writel(dst_addr + i * 4,
					devmem_readl(src_addr + i * 4)); 
		break;

	default:
		ERR("width %d invalid\n", width);
		break;
	}

	return 0;
}
