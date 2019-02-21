/*  *********************************************************************
    *  Broadcom Common Firmware Environment (CFE)
    *  
    *  Ethernet Datalink			File: net_ether.c
    *  
    *  This module provides a simple datalink (LLC1) interface 
    *  capable of demultiplexing standard DIX-style Ethernet packets.
    *  
    *  Author:  Mitch Lichtenberg
    *  
    *********************************************************************  
    *
    *  Copyright 2000,2001,2002,2003
    *  Broadcom Corporation. All rights reserved.
    *  
    *  This software is furnished under license and may be used and 
    *  copied only in accordance with the following terms and 
    *  conditions.  Subject to these conditions, you may download, 
    *  copy, install, use, modify and distribute modified or unmodified 
    *  copies of this software in source and/or binary form.  No title 
    *  or ownership is transferred hereby.
    *  
    *  1) Any source code used, modified or distributed must reproduce 
    *     and retain this copyright notice and list of conditions 
    *     as they appear in the source file.
    *  
    *  2) No right is granted to use any trade name, trademark, or 
    *     logo of Broadcom Corporation.  The "Broadcom Corporation" 
    *     name may not be used to endorse or promote products derived 
    *     from this software without the prior written permission of 
    *     Broadcom Corporation.
    *  
    *  3) THIS SOFTWARE IS PROVIDED "AS-IS" AND ANY EXPRESS OR
    *     IMPLIED WARRANTIES, INCLUDING BUT NOT LIMITED TO, ANY IMPLIED
    *     WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
    *     PURPOSE, OR NON-INFRINGEMENT ARE DISCLAIMED. IN NO EVENT 
    *     SHALL BROADCOM BE LIABLE FOR ANY DAMAGES WHATSOEVER, AND IN 
    *     PARTICULAR, BROADCOM SHALL NOT BE LIABLE FOR DIRECT, INDIRECT,
    *     INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
    *     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
    *     GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
    *     BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY 
    *     OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
    *     TORT (INCLUDING NEGLIGENCE OR OTHERWISE), EVEN IF ADVISED OF 
    *     THE POSSIBILITY OF SUCH DAMAGE.
    ********************************************************************* */

#include "sys/types.h"

#define ENET_ADDR_LEN   6

/*  *********************************************************************
    *  Some utilities for manipulating Ethernet addresses.
    ********************************************************************* */

/*  *********************************************************************
    *  ENET_PARSE_XDIGIT(c)
    *  
    *  Parse a hex digit, returning its value
    *  
    *  Input parameters: 
    *  	   c - character
    *  	   
    *  Return value:
    *  	   hex value, or -1 if invalid
    ********************************************************************* */

static int enet_parse_xdigit(char c)
{
    int digit;

    if ((c >= '0') && (c <= '9'))      digit = c - '0';
    else if ((c >= 'a') && (c <= 'f')) digit = c - 'a' + 10;
    else if ((c >= 'A') && (c <= 'F')) digit = c - 'A' + 10;
    else                               digit = -1;

    return digit;
}

/*  *********************************************************************
    *  ENET_PARSE_HWADDR(str,hwaddr)
    *  
    *  Convert a string in the form xx:xx:xx:xx:xx:xx into a 6-byte
    *  Ethernet address.
    *  
    *  Input parameters: 
    *  	   str - string
    *  	   hwaddr - pointer to hardware address
    *  	   
    *  Return value:
    *  	   0 if ok, else -1
    ********************************************************************* */

int enet_parse_hwaddr(const char *str, uint8_t *hwaddr)
{
    int digit1, digit2;
    int idx = ENET_ADDR_LEN;

    while (*str && (idx > 0)) {
	digit1 = enet_parse_xdigit(*str);
	if (digit1 < 0) return -1;
	str++;
	if (!*str) return -1;

	if ((*str == ':') || (*str == '-')) {
	    digit2 = digit1;
	    digit1 = 0;
	    }
	else {
	    digit2 = enet_parse_xdigit(*str);
	    if (digit2 < 0) return -1;
	    str++;
	    }

	*hwaddr++ = (digit1 << 4) | digit2;
	idx--;

	if ((*str == ':') || (*str == '-'))
	    str++;
	}
    return 0;
}
