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

/* Dynamic array */

#ifndef stdplus_vector_h
#define stdplus_vector_h

#include <stdplus/defines.h>
#include <stdplus/mem.h>

/** Vector that contains elements of type T */
#define Vector(T) Vector##T

/** Declare a vector */
#define VEC_DECLARE(T) \
typedef struct Vector(T) { \
  size_t size; \
  size_t capacity; \
  T *data; \
} Vector(T)

/* Private functions **********************************************************/

/* Obtain the size of the vec element */
#define vec_elemsize_(v) \
  (sizeof(*(v).data))

/* Change the vector capacity */
#define vec_changecap_(v, newcap) \
  (((v).data = mem_alloc((v).data, (v).capacity * vec_elemsize_(v), \
                         (newcap) * vec_elemsize_(v))), \
   ((v).capacity = (newcap)), (void)0)

/* Increase the vector capacity if necessary */
#define vec_grow_(v) \
  ((v).size + 1 > (v).capacity ? \
   vec_changecap_(v, (v).capacity == 0 ? 4 : (v).capacity * 2) : (void)0)

/* Public functions ***********************************************************/

/** Initialize a vector */
#define vec_init(v) \
  ((v).size = 0, (v).capacity = 0, (v).data = NULL, (void)0)

/** Destroy de vector */
#define vec_close(v) \
  (((v).capacity != 0 ? \
    mem_alloc((v).data, (v).capacity * vec_elemsize_(v), 0) : \
    NULL), \
   vec_init(v))

/** Obtain the vector capacity */
#define vec_capacity(v) \
  ((v).capacity)

/** Update the vector capacity. If the new capacity is smaller than the current
 * size, the vector will be resized */
#define vec_reserve(v, newcap) \
  ((newcap) == 0 ? \
   vec_close(v) : \
   (vec_changecap_(v, newcap), \
    ((v).size > newcap ? ((v).size = newcap, (void)0) : (void)0)))

/** Shrink the vector capacity to the current size */
#define vec_shrink(v) \
  (vec_reserve(v, (v).size))

/** Return 1 if size equals to 0 */
#define vec_empty(v) \
  ((v).size == 0)

/** Return the number of elements */
#define vec_size(v) \
  ((v).size)

/** Change the vector size */
#define vec_resize(v, newsize) \
  ((newsize > (v).capacity ? vec_changecap_(v, newsize) : (void)0), \
   ((v).size = newsize), (void)0)

/** Remove all elements from the vector */ 
#define vec_clear(v) \
  ((v).size = 0, (void)0)

/** Insert an element into the last position */
#define vec_push(v, value) \
  (vec_grow_(v), (v).data[(v).size++] = value, (void)0)

/** Remove the last element and return it */
#define vec_pop(v) \
  ((v).data[--(v).size])

/** Insert an element at the required position */
#define vec_insert(v, pos, value) do { \
  size_t _i; \
  vec_grow_(v); \
  for (_i = (v).size; _i > (pos); --_i) \
    (v).data[_i] = (v).data[_i - 1]; \
  (v).data[pos] = (value); \
  (v).size++; \
} while(0)

/** Erase the element at the required position */
#define vec_erase(v, pos) do { \
  size_t _i; \
  for (_i = (pos); _i < (v).size - 1; ++_i) \
    (v).data[_i] = (v).data[_i + 1]; \
  (v).size--; \
} while(0)

/** Obtain the element */
#define vec_get(v, pos) \
  ((v).data[pos])

/** Obtain a reference to the element */
#define vec_getref(v, pos) \
  ((v).data + pos)

/** Set the value of an element */
#define vec_set(v, pos, value) \
  ((v).data[pos] = value, (void)0)

/** Obtain the element at the first position */
#define vec_front(v) \
  ((v).data[0])

/** Obtain the element at the last position */
#define vec_back(v) \
  ((v).data[(v).size - 1])

/** Obtain the raw pointer to the internal buffer */
#define vec_data(v) \
  ((v).data)

/** Iterates throgh the vector and executes the command */
#define vec_foreach(v, it, cmd) do { \
  size_t it; \
  size_t _n##it = vec_size(v); \
  for (it = 0; it < _n##it; ++it) { \
    cmd; \
  } \
} while(0)

#endif

