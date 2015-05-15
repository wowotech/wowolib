/*
 * Name: devmem.h
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

#ifndef _DEVMEM_H_
#define _DEVMEM_H_

#include <stdint.h>

void *devm_map(unsigned long addr, int len);
void devm_unmap(void *virt_addr, int len);

uint8_t devmem_readb(unsigned long addr);
void devmem_writeb(unsigned long addr, uint8_t val);

uint16_t devmem_readw(unsigned long addr);
void devmem_writew(unsigned long addr, uint16_t val);

uint32_t devmem_readl(unsigned long addr);
void devmem_writel(unsigned long addr, uint32_t val);

uint64_t devmem_readq(unsigned long addr);
void devmem_writeq(unsigned long addr, uint64_t val);

void devmem_readsb(unsigned long addr, void *buf, int count);
void devmem_writesb(unsigned long addr, void *buf, int count);

void devmem_readsw(unsigned long addr, void *buf, int count);
void devmem_writesw(unsigned long addr, void *buf, int count);

void devmem_readsl(unsigned long addr, void *buf, int count);
void devmem_writesl(unsigned long addr, void *buf, int count);

void devmem_readsq(unsigned long addr, void *buf, int count);
void devmem_writesq(unsigned long addr, void *buf, int count);

void devmem_set(unsigned long addr, uint8_t value, int count);
void devmem_set32(unsigned long addr, uint32_t value, int count);

#endif
