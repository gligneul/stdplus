/*
 * MIT License
 * 
 * Copyright (c) 2017 Gabriel de Quadros Ligneul
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

/* Memory manegment */

#ifndef stdplus_mem_h
#define stdplus_mem_h

#include <stdlib.h>

/* Similar to the standard realloc
 * Notice that this is a function pointer, so it can by monkey patched */
extern void *(*mem_alloc)(void *addr, size_t oldsize, size_t newsize);

/* Useful macros */
#define mem_new(T) (T *)mem_alloc(NULL, 0, sizeof(T))
#define mem_delete(ptr) mem_alloc(ptr, sizeof(*ptr), 0)
#define mem_newarray(T, n) mem_alloc(NULL, 0, sizeof(T) * n)
#define mem_deletearray(array, n) mem_alloc(array, sizeof(*array) * n, 0)

#endif

