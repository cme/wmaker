/*
 *  Window Maker miscelaneous function library
 * 
 *  Copyright (c) 1997 Alfredo K. Kojima
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


#include "../src/config.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

extern char *_WINGS_progname;

#define MAXLINE	1024


/*********************************************************************
 * Returns the system error message associated with error code 'errnum'
 *********************************************************************/
char*
wstrerror(int errnum)
{
#if defined(HAVE_STRERROR)
    return strerror(errnum);
#elif !defined(HAVE_STRERROR) && defined(BSD)
    extern int errno, sys_nerr;
#  ifndef __DECC
    extern char *sys_errlist[];
#  endif
    static char buf[] = "Unknown error number 12345678901234567890";

    if (errno < sys_nerr)
        return sys_errlist[errnum];

    sprintf (buf, "Unknown error number %d", errnum);
    return buf;
#else /* no strerror() and no sys_errlist[] */
    static char buf[] = "Error number 12345678901234567890";

    sprintf(buf, "Error number %d", errnum);
    return buf;
#endif
}


/**************************************************************************
 * Prints a fatal error message with variable arguments and terminates
 * 
 * msg - message to print with optional formatting
 * ... - arguments to use on formatting 
 **************************************************************************/
void 
wfatal(const char *msg, ...)
{
    va_list args;
    char buf[MAXLINE];

    va_start(args, msg);

    vsprintf(buf, msg, args);
    strcat(buf,"\n");
    fflush(stdout);
    fputs(_WINGS_progname, stderr);
    fputs(" fatal error: ",stderr);
    fputs(buf, stderr);
    fflush(stdout);
    fflush(stderr);

    va_end(args);
}


/*********************************************************************
 * Prints a warning message with variable arguments 
 * 
 * msg - message to print with optional formatting
 * ... - arguments to use on formatting
 *********************************************************************/
void 
wwarning(const char *msg, ...)
{
    va_list args;
    char buf[MAXLINE];
    
    va_start(args, msg);
    
    vsprintf(buf, msg, args);
    strcat(buf,"\n");
    fflush(stdout);
    fputs(_WINGS_progname, stderr);
    fputs(" warning: ",stderr);
    fputs(buf, stderr);
    fflush(stdout);
    fflush(stderr);
    
    va_end(args);
}


/*********************************************************************
 * Prints a system error message with variable arguments 
 * 
 * msg - message to print with optional formatting
 * ... - arguments to use on formatting
 *********************************************************************/
void 
wsyserror(const char *msg, ...)
{
    va_list args;
    char buf[MAXLINE];
    int error=errno;

    va_start(args, msg);
    vsprintf(buf, msg, args);
    fflush(stdout);
    fputs(_WINGS_progname, stderr);
    fputs(" error: ", stderr);
    strcat(buf, ": ");
    strcat(buf, wstrerror(error));
    strcat(buf,"\n");
    fputs(buf, stderr);
    fflush(stderr);
    fflush(stdout);
    va_end(args);
}

