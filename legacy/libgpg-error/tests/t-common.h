/* t-common.h - Common code for the tests.
 * Copyright (C) 2013 g10 Code GmbH
 *
 * This file is part of libgpg-error.
 *
 * libgpg-error is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * libgpg-error is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, see <https://www.gnu.org/licenses/>.
 */

#include <stdarg.h>

#include "../src/gpg-error.h"

#ifndef PGM
#error Macro PGM not defined.
#endif
#ifndef DIM
#define DIM(array) (sizeof(array) / sizeof(*array))
#endif

static int verbose;
static int debug;
static int errorcount;

static void die(const char *format, ...) {
  va_list arg_ptr;

  fflush(stdout);
  flockfile(stderr);
  fprintf(stderr, "%s: ", PGM);
  va_start(arg_ptr, format);
  vfprintf(stderr, format, arg_ptr);
  va_end(arg_ptr);
  if (*format && format[strlen(format) - 1] != '\n') putc('\n', stderr);
  funlockfile(stderr);
  exit(1);
}

static void fail(const char *format, ...) {
  va_list arg_ptr;

  fflush(stdout);
  flockfile(stderr);
  fprintf(stderr, "%s: ", PGM);
  va_start(arg_ptr, format);
  vfprintf(stderr, format, arg_ptr);
  va_end(arg_ptr);
  if (*format && format[strlen(format) - 1] != '\n') putc('\n', stderr);
  funlockfile(stderr);
  errorcount++;
  if (errorcount >= 50) die("stopped after 50 errors.");
}

static void show(const char *format, ...) {
  va_list arg_ptr;

  if (!verbose) return;
  flockfile(stderr);
  fprintf(stderr, "%s: ", PGM);
  va_start(arg_ptr, format);
  vfprintf(stderr, format, arg_ptr);
  if (*format && format[strlen(format) - 1] != '\n') putc('\n', stderr);
  va_end(arg_ptr);
  funlockfile(stderr);
}
