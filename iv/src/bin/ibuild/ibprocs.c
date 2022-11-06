/*
 * Copyright (c) 1991 Stanford University
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Stanford not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  Stanford makes no representations about
 * the suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * STANFORD DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
 * IN NO EVENT SHALL STANFORD BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * Hack to workaround portability problems with setpgrp.
 */

#include "ibprocs.h"

#if defined(SYSV) && !defined(_BSD_COMPAT)

extern "C" {
    extern int setpgrp(void);
};

void set_child_process_group() { setpgrp(); }

#else

#ifdef ultrix

#include <OS/types.h>

extern "C" {
    extern int setpgrp(int, int);
    extern pid_t getpid();
};

void set_child_process_group() { setpgrp(0, getpid()); }

#else

extern "C" {
    extern int setpgrp(int, int);
}

void set_child_process_group() { setpgrp(0, 0); }

#endif

#endif
