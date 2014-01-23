#
# Name:    Makefile
#
# Purpose: the make file of this project
#
# Copyright (C) 2014 wowotech
# Subject to the GNU Public License, version 2.

# Created By:         wowo<www.wowotech.net>
# Created Date:       2014-01-23
# 
# ChangeList:
# Created in 2014-01-23 by wowo;
#

CC      = gcc 
CFLAGS  = -Wall -O3
INCFLAGS= 
LDFLAGS = 

OBJS    = debug_test.o
TARGETS = debug_test

.PHONY:all 
all:$(TARGETS)

$(TARGETS):$(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(INCFLAGS)

%.d:%.c
	@set -e; rm -f $@; $(CC) -MM $< $(INCFLAGS) > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(OBJS:.o=.d)

.PHONY:clean 
clean:
	rm -f $(TARGETS) *.exe *.o *.d *.d.*
