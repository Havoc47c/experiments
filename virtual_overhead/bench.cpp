#include "benchmark/benchmark.h"
#include "virtual.h"

static void BM_SetLastBaseline(benchmark::State& state) {
  // Perform setup here
  int max_objects = 100000;
  auto [objects, storage] = CreateNBases(max_objects);
  for (auto _ : state) {
    for (int i = 0; i < max_objects; ++i) {
	    SetLast(storage[i].value);
    }
  }
}
// Register the function as a benchmark
BENCHMARK(BM_SetLastBaseline);

static void BM_IndexedAccessStaticCallToBaseObjects(benchmark::State& state) {
  // Perform setup here
  int max_objects = 100000;
  auto [objects, storage] = CreateNBases(max_objects);
  for (auto _ : state) {
    // This code gets timed
    // Uses storage to directly vcall object.
    for (int i = 0; i < max_objects; ++i) {
            storage[i].Base::vcall();
	    //escape(&storage[i].value)
    }
  }
}
// Register the function as a benchmark
BENCHMARK(BM_IndexedAccessStaticCallToBaseObjects);

static void BM_RangeBasedForStaticCallToBaseObjects(benchmark::State& state) {
  // Perform setup here
  int max_objects = 100000;
  auto [objects, storage] = CreateNBases(max_objects);
  for (auto _ : state) {
    for (Base& b : storage) {
	    b.Base::vcall();
    }
  }
}
// Register the function as a benchmark
BENCHMARK(BM_RangeBasedForStaticCallToBaseObjects);

static void BM_IndexedAccessVirtualCallToBaseObjects(benchmark::State& state) {
  // Perform setup here
  int max_objects = 100000;
  auto [objects, storage] = CreateNBases(max_objects);
  for (auto _ : state) {
    // This code gets timed
    // Uses storage to directly vcall object.
    for (int i = 0; i < max_objects; ++i) {
            storage[i].vcall();
    }
  }
}
// Register the function as a benchmark
BENCHMARK(BM_IndexedAccessVirtualCallToBaseObjects);

static void BM_RangeBasedForVirtualCallToBaseObjects(benchmark::State& state) {
  // Perform setup here
  int max_objects = 100000;
  auto [objects, storage] = CreateNBases(max_objects);
  for (auto _ : state) {
    for (Base& b : storage) {
            b.vcall();
    }
  }
}
// Register the function as a benchmark
BENCHMARK(BM_RangeBasedForVirtualCallToBaseObjects);

static void BM_VirtualCallToBaseObjects(benchmark::State& state) {
  // Perform setup here
  int max_objects = 100000;
  auto [objects, storage] = CreateNBases(max_objects);
  for (auto _ : state) {
    // This code gets timed
    for (Base* b : objects) {
	    b->vcall();
    }
  }
}
// Register the function as a benchmark
BENCHMARK(BM_VirtualCallToBaseObjects);

static void BM_SortedDerivedObject(benchmark::State& state) {
  // Perform setup here
  int max_objects = 100000;
  auto [objects, storage] = CreateNOrderedDerived(max_objects);
  for (auto _ : state) {
    // This code gets timed
    for (Base* b : objects) {
	    b->vcall();
    }
  }
}
BENCHMARK(BM_SortedDerivedObject);

static void BM_RandomDerivedObject(benchmark::State& state) {
  // Perform setup here
  int max_objects = 100000;
  auto [objects, storage] = CreateNDerived(max_objects);
  for (auto _ : state) {
    // This code gets timed
    for (Base* b : objects) {
	    b->vcall();
    }
  }
}
// Register the function as a benchmark
BENCHMARK(BM_RandomDerivedObject);

// Run the benchmark
BENCHMARK_MAIN();
