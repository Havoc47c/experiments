#include <vector>
#include <cstdlib>
#include <time.h>

constexpr int kBaseTypeIndex = 0;

int last;
void SetLast(int l) { last = l; }

struct Derived0 {
	// Force a read every time.
	volatile int value;
	virtual void vcall() const {
		SetLast(value);
	}
};
using Base = Derived0;
template <int i>
Base Create() {
	assert(false);
}
template <>
Base Create<0>() {
	return Derived0();
}

#define DERIVED_NAME(n) Derived##n

#define DERIVED(d, b) \
struct DERIVED_NAME(d) : public DERIVED_NAME(b) {   \
	void vcall() const override {                      \
		SetLast(value);                             \
	}                                           \ 
}; \
template<> \
Base Create<d>() { \
	return DERIVED_NAME(d)(); \
}

DERIVED(1, 0)
DERIVED(2, 1)
DERIVED(3, 2)
DERIVED(4, 3)
DERIVED(5, 4)
DERIVED(6, 5)
DERIVED(7, 6)
DERIVED(8, 7)
DERIVED(9, 8)
// DERIVED(10, 9)
// DERIVED(11, 10)
// DERIVED(12, 11)
// DERIVED(13, 12)
// DERIVED(14, 13)
// DERIVED(15, 14)
// DERIVED(16, 15)
// DERIVED(17, 16)
// DERIVED(18, 17)
// DERIVED(19, 18)
// DERIVED(20, 19)
// DERIVED(21, 20)
// DERIVED(22, 21)
// DERIVED(23, 22)
// DERIVED(24, 23)
// DERIVED(25, 24)
// DERIVED(26, 25)
// DERIVED(27, 26)
// DERIVED(28, 27)
// DERIVED(29, 28)
// DERIVED(30, 29)
// DERIVED(31, 30)
// DERIVED(32, 31)
// DERIVED(33, 32)
// DERIVED(34, 33)
// DERIVED(35, 34)
// DERIVED(36, 35)
// DERIVED(37, 36)
// DERIVED(38, 37)
// DERIVED(39, 38)
// DERIVED(40, 39)
// DERIVED(41, 40)
// DERIVED(42, 41)
// DERIVED(43, 42)
// DERIVED(44, 43)
// DERIVED(45, 44)
// DERIVED(46, 45)
// DERIVED(47, 46)
// DERIVED(48, 47)
// DERIVED(49, 48)
// DERIVED(50, 49)
// DERIVED(51, 50)
// DERIVED(52, 51)
// DERIVED(53, 52)
// DERIVED(54, 53)
// DERIVED(55, 54)
// DERIVED(56, 55)
// DERIVED(57, 56)
// DERIVED(58, 57)
// DERIVED(59, 58)
// DERIVED(60, 59)
// DERIVED(61, 60)
// DERIVED(62, 61)
// DERIVED(63, 62)
// DERIVED(64, 63)
// DERIVED(65, 64)
// DERIVED(66, 65)
// DERIVED(67, 66)
// DERIVED(68, 67)
// DERIVED(69, 68)
// DERIVED(70, 69)
// DERIVED(71, 70)
// DERIVED(72, 71)
// DERIVED(73, 72)
// DERIVED(74, 73)
// DERIVED(75, 74)
// DERIVED(76, 75)
// DERIVED(77, 76)
// DERIVED(78, 77)
// DERIVED(79, 78)
// DERIVED(80, 79)
// DERIVED(81, 80)
// DERIVED(82, 81)
// DERIVED(83, 82)
// DERIVED(84, 83)
// DERIVED(85, 84)
// DERIVED(86, 85)
// DERIVED(87, 86)
// DERIVED(88, 87)
// DERIVED(89, 88)
// DERIVED(90, 89)
// DERIVED(91, 90)
// DERIVED(92, 91)
// DERIVED(93, 92)
// DERIVED(94, 93)
// DERIVED(95, 94)
// DERIVED(96, 95)
// DERIVED(97, 96)
// DERIVED(98, 97)
// DERIVED(99, 98)
// DERIVED(100, 99)
#define MAX_DERIVED 9

#define CREATE_CASE(n, place) case n: return new (place) DERIVED_NAME(n)()

Base* Create(int n, Base* storage) {
	switch(n) {
		CREATE_CASE(0, storage);
		CREATE_CASE(1, storage);
		CREATE_CASE(2, storage);
		CREATE_CASE(3, storage);
		CREATE_CASE(4, storage);
		CREATE_CASE(5, storage);
		CREATE_CASE(6, storage);
		CREATE_CASE(7, storage);
		CREATE_CASE(8, storage);
		CREATE_CASE(9, storage);
	}
}

// Creates n objects of type Base in some buffer.
std::tuple<std::vector<Base*>, std::vector<Base>> CreateNBases(int n) {
	srand(time(NULL));
	std::vector<Base> storage(n);
	std::vector<Base*> n_bases(n, nullptr);
	for (int i = 0; i < n; ++i) {
		n_bases[i] = Create(kBaseTypeIndex, &storage[i]);
	}
	
	return {n_bases, std::move(storage)};
}

// Create some random derived classes in a random order in a buffer.
std::tuple<std::vector<Base*>, std::vector<Base>> CreateNOrderedDerived(int n) {
	static_assert(sizeof(DERIVED_NAME(5)) == sizeof(Base));
	srand(time(NULL));
	// Create sorted list of types, ex: 0, 0, 0, 1, 1, 2, 3, 3, 3, 3, 3, 4, 4 ...
	std::vector<int> derived_types;
	for (int i = 0; i < n; ++i) {
		int type = rand() % MAX_DERIVED;
		derived_types.push_back(type);
	}
	std::sort(derived_types.begin(), derived_types.end());

	std::vector<Base> storage(n);
	std::vector<Base*> n_derived(n, nullptr);
	for (int i = 0; i < n; ++i) {
		n_derived[i] = (Create(derived_types[i], &storage[i]));
	}
	
	return {n_derived, std::move(storage)};
}

// Create some random derived classes in a random order in a buffer.
std::tuple<std::vector<Base*>, std::vector<Base>> CreateNDerived(int n) {
	static_assert(sizeof(DERIVED_NAME(5)) == sizeof(Base));
	srand(time(NULL));
	std::vector<Base> storage(n);
	std::vector<Base*> n_derived(n, nullptr);
	for (int i = 0; i < n; ++i) {
		int derived = rand() % MAX_DERIVED;
		n_derived[i] = Create(derived, &storage[i]);
	}
	
	return {n_derived, std::move(storage)};
}
