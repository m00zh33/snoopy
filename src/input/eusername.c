/*
 * SNOOPY LOGGER
 *
 * File: snoopy/input/eusername.c
 *
 * Copyright (c) 2014 bostjan@a2o.si
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */



/*
 * SNOOPY INPUT PROVIDER: eusername
 *
 * Description:
 *     Returns literal effective user name (User ID) of current process
 *
 * Params:
 *     input: pointer to string, to write result into
 *
 * Return:
 *     number of characters in the returned string
 */
#include "snoopy.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>



int snoopy_input_eusername (char *input)
{
    struct passwd  pwd;
    struct passwd *pwd_uid         = NULL;
    char          *buffpwd_uid     = NULL;
    size_t         buffpwdsize_uid = 0;
    int            messageLength  = 0;

    /* Allocate memory */
    buffpwdsize_uid = sysconf(_SC_GETPW_R_SIZE_MAX);
    if (buffpwdsize_uid == -1) {
        buffpwdsize_uid = 16384;
    }
    buffpwd_uid = malloc(buffpwdsize_uid);
    if(buffpwd_uid == NULL) {
        return snprintf(input, SNOOPY_INPUT_MESSAGE_MAX_SIZE, "ERROR(malloc)");
    }

    /* Format return string */
    getpwuid_r(geteuid(), &pwd, buffpwd_uid, buffpwdsize_uid, &pwd_uid);
    messageLength = snprintf(input, SNOOPY_INPUT_MESSAGE_MAX_SIZE, "%s", pwd_uid->pw_name);

    /* Cleanup and return */
    free(buffpwd_uid);
    return messageLength;
}
