#include <vector>
#include <iostream>
#include <random>
#include <cstring>
#include <benchmark/benchmark.h>

using namespace std;

template<typename T>
static void Bench(benchmark::State& state, T linsearch) {
  constexpr int size = 100000;
  vector<char> values(size);
  size_t hash = 0;
  int seed = 1;
  default_random_engine generator(seed);
  uniform_int_distribution size_choice(8, size - 1);
  uniform_int_distribution align_choice(0, 7);
  uniform_int_distribution element_choice(1, 255);
  for (int i = 0; i < size; i++) {
    values[i] = element_choice(generator);
  }
  for (auto _ : state) {
    int random_size = size_choice(generator);
    int align = align_choice(generator);
    char save = values[random_size];
    values[random_size] = 0;
    hash += linsearch(values.data() + align);
    values[random_size] = save;
    benchmark::DoNotOptimize(hash);
    benchmark::DoNotOptimize(random_size);
  }
  cout << hash << "\n";
}

#define LIN_BENCHMARK(linsearch) \
  static void Bench_##linsearch(benchmark::State& state) { \
    Bench(state, linsearch); \
  } \
  BENCHMARK(Bench_##linsearch)

size_t basic(const char *values) {
  const char *p = values;
  while (*p != 0) {
    p++;
  }
  return p - values;
}

size_t glibc(const char *values) {
  return strlen(values);
}

template<typename T>
const char *check_align(const char *p) {
  constexpr unsigned int align_requirement = alignof(T);
  unsigned int misalign = ((uintptr_t) p) % align_requirement;
  if (misalign > 0) {
    for (unsigned int i = 0; i < (align_requirement - misalign); i++, p++) {
      if (*p == 0) {
        return p;
      }
    }
  }
  return p;
}

template<typename T>
constexpr int get_magic_constant() {
  T value = T(1);
  int size = sizeof(T);
  for (int i = 1; i < size; i++) {
    value = (value << 8) + 1;
  }
  return value;
}

template<typename T>
size_t bitmagic(const char *values) {
  const char *p = check_align<T *>(values);
  if (*p == 0) {
    return p - values;
  }
  if ((((uintptr_t)p) & 3) != 0) {
    cout << "fuck\n";
    abort();
  }
  constexpr T magic = get_magic_constant<T>();
  constexpr T magic80 = T(0x80) * magic;
  for (T *pp = (T *) p;; pp++) {
    if (((*pp) - magic) & ~(*pp) & magic80) {
      for (char *p = (char *) pp;; p++) {
        if (*p == 0) {
          return p - values;
        }
      }
    }
  }
}

size_t bitmagic32(const char *values) {
  return bitmagic<unsigned int>(values);
}

size_t bitmagic642(const char *values) {
  return bitmagic<unsigned long long>(values);
}

size_t bitmagic64(const char *values) {
  const char *p = values;
  int misalign = ((uintptr_t) p) & 7;
  for (int i = 0; i < misalign; i++, p++) {
    if (*p == 0) {
      return i;
    }
  }
  for (unsigned long long *pp = (unsigned long long *) p;; pp++) {
    auto index =((*pp) - 0x0101010101010101ULL) & ~(*pp) & 0x8080808080808080ULL;
    if (index) {
      for (char *p = (char *) pp;; p++) {
        if (*p == 0) {
          return p - values;
        }
      }
    }
  }
}

size_t bitmagic64_v2(const char *values) {
    const char *p = values;
    int misalign = ((uintptr_t)p) & 7;
    for (int i = 0; i < misalign; i++, p++) {
        if (*p == 0) {
            return i;
        }
    }
    for (unsigned long long *pp = (unsigned long long *)p;; pp++) {
        unsigned long long index = ((*pp) - 0x0101010101010101ULL) & ~(*pp) & 0x8080808080808080ULL;
        if (index) {
            return (char *)pp - values + __builtin_ctzll(index) / 8;
        }
    }
}


LIN_BENCHMARK(basic);
LIN_BENCHMARK(glibc);
LIN_BENCHMARK(bitmagic32);
LIN_BENCHMARK(bitmagic64);
LIN_BENCHMARK(bitmagic64_v2);
