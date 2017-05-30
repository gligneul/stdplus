/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2016 Gabriel de Quadros Ligneul
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <assert.h>
#include <stdio.h>
#include <stdplus.h>

static int usedmem = 0;
static void *checkmem(void *addr, size_t oldsize, size_t newsize) {
  usedmem = usedmem - oldsize + newsize;
  return mem_alloc_(addr, oldsize, newsize);
}

VEC_DECLARE(int);

int main(void) {
  mem_alloc = checkmem;

  /* vec_create/vec_destroy */ {
    Vector(int) v;
    vec_init(v);
    assert(v.data == NULL);
    assert(v.size == 0);
    assert(v.capacity == 0);
    vec_close(v);
    assert(usedmem == 0);
  }

  /* vec_reserve/vec_capacity */ {
    size_t i, n = 1000;
    Vector(int) v;
    vec_init(v);
    vec_reserve(v, n);
    assert(vec_capacity(v) == n);
    for (i = 0; i < n; ++i) {
      vec_push(v, i);
      assert(vec_capacity(v) == n);
    }
    vec_reserve(v, 0);
    assert(vec_capacity(v) == 0);
    vec_close(v);
    assert(usedmem == 0);
  }

  /* vec_shrink */ {
    size_t i, n = 1000;
    Vector(int) v;
    vec_init(v);
    for (i = 0; i < n; ++i) vec_push(v, i);
    assert(vec_capacity(v) == 1024);
    vec_shrink(v);
    assert(vec_capacity(v) == n);
    vec_close(v);
    assert(usedmem == 0);
  }

  /* vec_resize/vec_size */ {
    Vector(int) v;
    vec_init(v);
    vec_resize(v, 100);
    assert(vec_size(v) == 100);
    vec_resize(v, 10);
    assert(vec_size(v) == 10);
    vec_close(v);
    assert(usedmem == 0);
  }

  /* vec_clear/vec_empty */ {
    size_t i, n = 1000;
    Vector(int) v;
    vec_init(v);
    assert(vec_empty(v));
    for (i = 0; i < n; ++i) vec_push(v, i);
    assert(!vec_empty(v));
    vec_clear(v);
    assert(vec_empty(v));
    vec_close(v);
    assert(usedmem == 0);
  }

  /* vec_push */ {
    size_t i, n = 1000;
    Vector(int) v;
    vec_init(v);
    for (i = 0; i < n; ++i) {
      assert(vec_size(v) == i);
      vec_push(v, i);
      assert(vec_size(v) == i + 1);
      assert(vec_get(v, i) == (int)i);
    }
    vec_close(v);
    assert(usedmem == 0);
  }

  /* vec_pop */ {
    size_t i, n = 1000;
    Vector(int) v;
    vec_init(v);
    vec_push(v, 123);
    assert(vec_pop(v) == 123);
    assert(vec_empty(v));
    for (i = 0; i < n; ++i) vec_push(v, i);
    for (i = 0; i < n; ++i) assert(vec_pop(v) == (int)(n - i - 1));
    assert(vec_empty(v));
    vec_close(v);
    assert(usedmem == 0);
  }

  /* vec_insert */ {
    size_t i, n = 100;
    Vector(int) v;
    vec_init(v);
    for (i = 0; i < n; ++i) {
      vec_insert(v, i, i);
      assert(vec_get(v, i) == (int)i);
      assert(vec_size(v) == i + 1);
    }
    vec_insert(v, 0, 123);
    assert(vec_get(v, 0) == 123);
    assert(vec_size(v) == n + 1);
    for (i = 0; i < n; ++i)
      assert(vec_get(v, i + 1) == (int)i);
    vec_close(v);
    assert(usedmem == 0);
  }

  /* vec_erase */ {
    size_t i, n = 100;
    Vector(int) v;
    vec_init(v);
    for (i = 0; i < n; ++i) vec_insert(v, i, i);
    for (i = 0; i < n; ++i) {
      assert(vec_get(v, 0) == (int)i);
      vec_erase(v, 0);
    }
    vec_close(v);
    assert(usedmem == 0);
  }

  /* vec_get/vec_getref/vec_set/vec_data */ {
    Vector(int) v;
    vec_init(v);
    vec_push(v, 10);
    assert(vec_get(v, 0) == 10);
    vec_push(v, 20);
    assert(vec_get(v, 0) == 10);
    vec_set(v, 0, 123);
    assert(vec_get(v, 0) == 123);
    vec_set(v, 1, 456);
    assert(vec_get(v, 1) == 456);
    assert(*vec_getref(v, 1) == 456);
    *vec_getref(v, 1) = 789;
    assert(vec_get(v, 1) == 789);
    assert(vec_getref(v, 0) == vec_data(v));
    vec_close(v);
    assert(usedmem == 0);
  }

  /* test vec_front */ {
    Vector(int) v;
    vec_init(v);
    vec_push(v, 123);
    assert(vec_front(v) == 123);
    vec_push(v, 456);
    assert(vec_front(v) == 123);
    vec_close(v);
    assert(usedmem == 0);
  }

  /* test vec_back */ {
    Vector(int) v;
    vec_init(v);
    vec_push(v, 123);
    assert(vec_back(v) == 123);
    vec_push(v, 456);
    assert(vec_back(v) == 456);
    vec_close(v);
    assert(usedmem == 0);
  }

  /* test foreach */ {
    size_t i, n = 100;
    Vector(int) v;
    vec_init(v);
    for (i = 0; i < n; ++i) vec_push(v, i);
    vec_foreach(v, j, assert(vec_get(v, j) == (int)j));
    vec_close(v);
    assert(usedmem == 0);
  }

  return 0;
}

