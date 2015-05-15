/*
 * Name: devmw.c
 *
 * Purpose: write physical address with special value.
 *	It is very usefull in Framebuffer testing.
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
DEBUG_SET_LEVEL(DEBUG_LEVEL_INFO);

int main(int argc, char **argv)
{
	int count, width = 32;
	unsigned long addr;
	unsigned long value;

	if (argc < 4) {
		ERR("\nUsage:\t%s {address} {value} {count} [width]\n"
			"\taddress:	Address to act upon\n"
			"\tvalue:	Value to write\n"
			"\tcount:	Set counts\n\n"
			"\twidth:	width, 8/16/32/64..., default is 32\n\n",
			argv[0]);
		return -1;
	}
	addr = strtoul(argv[1], 0, 0);
	value = strtoul(argv[2], 0, 0);
	count = strtoul(argv[3], 0, 0);

	if (argc > 4)
		width = strtoul(argv[width], 0, 0);

	DEBUG("addr 0x%lx, value 0x%lx, count %d, width %d\n",
		addr, value, count, width);

	if (width == 8)
		devmem_set(addr, value, count);
	else if (width == 32)
		devmem_set32(addr, value, count);
	else
		ERR("width %d invalid\n", width);

	return 0;
}
