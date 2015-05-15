/*
 * Name: devmem.c
 *
 * Purpose: simple library to access physical address in userspace.
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
DEBUG_SET_LEVEL(DEBUG_LEVEL_ERR);

static int		devmem_fd;

void *devm_map(unsigned long addr, int len)
{
	off_t offset;
	void *map_base; 

	if ((devmem_fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) {
		ERR("cannot open '/dev/mem'\n");
		goto err_open;
	}
	DEBUG("/dev/mem opened.\n");

	/*
	 * Map it
	 */

	/* offset for mmap() must be page aligned */
	offset = addr & ~(sysconf(_SC_PAGE_SIZE) - 1);

	map_base = mmap(NULL, len + addr - offset, PROT_READ | PROT_WRITE,
			MAP_SHARED, devmem_fd, offset);
	if (map_base == MAP_FAILED) {
		ERR("mmap failed\n");
		goto err_mmap;
	}
	DEBUG("Memory mapped at address %p.\n", map_base); 

	return map_base + addr - offset;

err_mmap:
	close(devmem_fd);

err_open:
	return NULL;
}

void devm_unmap(void *virt_addr, int len)
{
	unsigned long addr;

	if (devmem_fd == -1) {
		ERR("'/dev/mem' is closed\n");
		return;
	}

	/* page align */
	addr = (((unsigned long)virt_addr) & ~(sysconf(_SC_PAGE_SIZE) - 1));
	munmap((void *)addr, len + (unsigned long)virt_addr - addr);
	close(devmem_fd);
}

/*==================================================================
 *				APIs
 *================================================================*/

/* read & write a byte */
uint8_t devmem_readb(unsigned long addr)
{
	uint8_t val;
	void *virt_addr;

	virt_addr = devm_map(addr, 1);

	if (virt_addr == NULL) {
		ERR("addr map failed");
		return 0;
	}

	val = *(uint8_t *)virt_addr;
	
	devm_unmap(virt_addr, 1);

	return val;
}

void devmem_writeb(unsigned long addr, uint8_t val)
{
	void *virt_addr;

	virt_addr = devm_map(addr, 1);

	if (virt_addr == NULL) {
		ERR("addr map failed");
		return;
	}

	*(uint8_t *)virt_addr = val;
	
	devm_unmap(virt_addr, 1);
}

/* read & write a half-word */
uint16_t devmem_readw(unsigned long addr)
{
	uint16_t val;
	void *virt_addr;

	virt_addr = devm_map(addr, 2);

	if (virt_addr == NULL) {
		ERR("addr map failed");
		return 0;
	}

	val = *(uint16_t *)virt_addr;
	
	devm_unmap(virt_addr, 2);

	return val;
}

void devmem_writew(unsigned long addr, uint16_t val)
{
	void *virt_addr;

	virt_addr = devm_map(addr, 2);

	if (virt_addr == NULL) {
		ERR("addr map failed");
		return;
	}

	*(uint16_t *)virt_addr = val;
	
	devm_unmap(virt_addr, 2);
}

/* read & write a word */
uint32_t devmem_readl(unsigned long addr)
{
	uint32_t val;
	void *virt_addr;

	virt_addr = devm_map(addr, 4);

	if (virt_addr == NULL) {
		ERR("addr map failed");
		return 0;
	}

	val = *(uint32_t *)virt_addr;
	
	devm_unmap(virt_addr, 4);

	return val;
}

void devmem_writel(unsigned long addr, uint32_t val)
{
	void *virt_addr;

	virt_addr = devm_map(addr, 4);

	if (virt_addr == NULL) {
		ERR("addr map failed");
		return;
	}

	*(uint32_t *)virt_addr = val;
	
	devm_unmap(virt_addr, 4);
}

/* read & write a dword */
uint64_t devmem_readq(unsigned long addr)
{
	uint64_t val;
	void *virt_addr;

	virt_addr = devm_map(addr, 8);

	if (virt_addr == NULL) {
		ERR("addr map failed");
		return 0;
	}

	val = *(uint64_t *)virt_addr;
	
	devm_unmap(virt_addr, 8);

	return val;
}

void devmem_writeq(unsigned long addr, uint64_t val)
{
	void *virt_addr;

	virt_addr = devm_map(addr, 8);

	if (virt_addr == NULL) {
		ERR("addr map failed");
		return;
	}

	*(uint64_t *)virt_addr = val;
	
	devm_unmap(virt_addr, 8);
}

/* read & write a serial bytes */
void devmem_readsb(unsigned long addr, void *buf, int count)
{
	uint8_t *src, *dst;
	int len = count;
	void *virt_addr;

	virt_addr = devm_map(addr, len);

	if (virt_addr == NULL) {
		ERR("addr map failed");
	}

	if (count) {
		src = virt_addr;
		dst = buf;
		do {
                        *dst++ = *src++;
                } while (--count);
        }

	devm_unmap(virt_addr, len);
}

void devmem_writesb(unsigned long addr, void *buf, int count)
{
	uint8_t *src, *dst;
	int len = count;
	void *virt_addr;

	virt_addr = devm_map(addr, len);

	if (virt_addr == NULL) {
		ERR("addr map failed");
	}

	if (count) {
		dst = virt_addr;
		src = buf;
		do {
                        *dst++ = *src++;
                } while (--count);
        }

	devm_unmap(virt_addr, len);
}

/* read & write a serial hwords */
void devmem_readsw(unsigned long addr, void *buf, int count)
{
	uint16_t *src, *dst;
	int len = count * 2;
	void *virt_addr;

	virt_addr = devm_map(addr, len);

	if (virt_addr == NULL) {
		ERR("addr map failed");
	}

	if (count) {
		src = virt_addr;
		dst = buf;
		do {
                        *dst++ = *src++;
                } while (--count);
        }

	devm_unmap(virt_addr, len);
}

void devmem_writesw(unsigned long addr, void *buf, int count)
{
	uint16_t *src, *dst;
	int len = count * 2;
	void *virt_addr;

	virt_addr = devm_map(addr, len);

	if (virt_addr == NULL) {
		ERR("addr map failed");
	}

	if (count) {
		dst = virt_addr;
		src = buf;
		do {
                        *dst++ = *src++;
                } while (--count);
        }

	devm_unmap(virt_addr, len);
}

/* read & write a serial words */
void devmem_readsl(unsigned long addr, void *buf, int count)
{
	uint32_t *src, *dst;
	int len = count * 4;
	void *virt_addr;

	virt_addr = devm_map(addr, len);

	if (virt_addr == NULL) {
		ERR("addr map failed");
	}

	if (count) {
		src = virt_addr;
		dst = buf;
		do {
                        *dst++ = *src++;
                } while (--count);
        }

	devm_unmap(virt_addr, len);
}

void devmem_writesl(unsigned long addr, void *buf, int count)
{
	uint32_t *src, *dst;
	int len = count * 4;
	void *virt_addr;

	virt_addr = devm_map(addr, len);

	if (virt_addr == NULL) {
		ERR("addr map failed");
	}

	if (count) {
		dst = virt_addr;
		src = buf;
		do {
                        *dst++ = *src++;
                } while (--count);
        }

	devm_unmap(virt_addr, len);
}

/* read & write a serial dwords */
void devmem_readsq(unsigned long addr, void *buf, int count)
{
	uint64_t *src, *dst;
	int len = count * 8;
	void *virt_addr;

	virt_addr = devm_map(addr, len);

	if (virt_addr == NULL) {
		ERR("addr map failed");
	}

	if (count) {
		src = virt_addr;
		dst = buf;
		do {
                        *dst++ = *src++;
                } while (--count);
        }

	devm_unmap(virt_addr, len);
}

void devmem_writesq(unsigned long addr, void *buf, int count)
{
	uint64_t *src, *dst;
	int len = count * 8;
	void *virt_addr;

	virt_addr = devm_map(addr, len);

	if (virt_addr == NULL) {
		ERR("addr map failed");
	}

	if (count) {
		dst = virt_addr;
		src = buf;
		do {
                        *dst++ = *src++;
                } while (--count);
        }

	devm_unmap(virt_addr, len);
}

void devmem_set(unsigned long addr, uint8_t value, int count)
{
	uint8_t *dst;
	int i;

	dst = devm_map(addr, count);
	if (dst == NULL) {
		ERR("addr map failed");
		return;
	}

	for (i = 0; i < count; i++)
		dst[i] = value;

	devm_unmap((void *)dst, count);
}

/* I/O memory should 32 bit allign */
void devmem_set32(unsigned long addr, uint32_t value, int count)
{
	uint32_t *dst;
	int i;

	dst = devm_map(addr, count * 4);
	if (dst == NULL) {
		ERR("addr map failed");
		return;
	}

	for (i = 0; i < count; i++)
		dst[i] = value;

	devm_unmap((void *)dst, count * 4);
}
