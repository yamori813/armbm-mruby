/*
 * Copyright (c) 2018 Hiroki Mori. All rights reserved.
 */

#include <_ansi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>

extern char _end[];

int _kill()
{
	return 0;
}

int _getpid()
{
	return 0;
}

int _exit()
{
	return 0;
}

int _gettimeofday()
{
	return 0;
}

void *
_sbrk (incr)
     int incr;
{
   static char * heap_end = _end;
   char *        prev_heap_end;

   prev_heap_end = heap_end;
   heap_end += incr;

   return (void *) prev_heap_end;
}

char * sbrk (int) __attribute__((weak, alias ("_sbrk")));
