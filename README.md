*This project has been created as part of the 42 curriculum by rexposit.*

# CPP Module 06

`CPP Module 06` is part of the C++ modules of the 42 curriculum. The project introduces the different C++ casting operators, pointer serialization and runtime type identification.

Throughout the module, scalar values are converted between different C++ types, pointers are transformed into integer representations and restored, and polymorphic objects are identified at runtime using `dynamic_cast`.

---

# Table of Contents

- [Description](#description)
- [Project Rules](#project-rules)
- [Exercises Overview](#exercises-overview)
- [Casting Overview](#casting-overview)
- [Implementation](#implementation)
- [Compilation](#compilation)
- [Testing](#testing)
- [Project Structure](#project-structure)
- [What I Learned](#what-i-learned)
- [Author](#author)

---

# Description

CPP Module 06 is divided into three independent exercises, each focusing on a different form of type conversion in C++.

### ex00 — Scalar Conversion

Introduces the `ScalarConverter` class.

The program receives a scalar literal as a string and detects its original type among:

- `char`
- `int`
- `float`
- `double`

The detected value is then converted and displayed in all four scalar representations whenever the conversion is possible.

The exercise also handles:

- non-displayable characters;
- values outside the valid integer or character ranges;
- floating-point precision;
- `nan`;
- positive and negative infinity;
- float pseudo-literals.

This exercise focuses mainly on scalar conversions using `static_cast`.

---

### ex01 — Serialization

Introduces the `Serializer` class.

A pointer to a `Data` structure is converted into an unsigned integer representation using:

```cpp
reinterpret_cast
```

The resulting `uintptr_t` value can then be converted back into a `Data*`.

The recovered pointer must be identical to the original pointer and therefore reference the same object.

This exercise introduces low-level pointer representation and `reinterpret_cast`.

---

### ex02 — Runtime Type Identification

Introduces a polymorphic class hierarchy composed of:

- `Base`
- `A`
- `B`
- `C`

A random derived object is created and returned through a `Base*`.

Two overloaded identification functions determine the real type of the object:

```cpp
void identify(Base *p);
void identify(Base &p);
```

The pointer version uses the result of `dynamic_cast`, while the reference version handles `std::bad_cast` exceptions.

This exercise focuses on runtime type identification and polymorphism.

---

# Project Rules

The project follows the requirements of CPP Module 06.

- C++98 standard
- Compilation with:

```bash
-Wall -Wextra -Werror -std=c++98
```

- Explicit C++ casts
- Scalar type conversion
- Pointer serialization
- Runtime type identification
- Polymorphic base classes
- Virtual destructors where required
- Proper dynamic memory management

---

# Exercises Overview

| Exercise | Main Concept | Executable |
|----------|--------------|------------|
| ex00 | Scalar type conversion | `convert` |
| ex01 | Pointer serialization | `serialize` |
| ex02 | Runtime type identification | `identify_type` |

---

# Casting Overview

CPP Module 06 focuses on several explicit C++ casting mechanisms.

```text
ex00
Scalar values
     │
     ▼
 static_cast
     │
     ▼
char / int / float / double


ex01
Data*
     │
     ▼
reinterpret_cast
     │
     ▼
uintptr_t
     │
     ▼
reinterpret_cast
     │
     ▼
Data*


ex02
Base* / Base&
     │
     ▼
 dynamic_cast
     │
     ▼
A / B / C
```

Each cast serves a different purpose and should be used according to the relationship between the source and destination types.

---

# Implementation

## ScalarConverter

`ScalarConverter` cannot be instantiated.

Its public interface consists of a static conversion function:

```cpp
static void convert(const std::string &literal);
```

The input literal is first analyzed to determine its type.

Supported input types are:

```text
char
int
float
double
```

Once the type has been identified, the value is converted into all scalar representations.

---

## Scalar Type Detection

The converter uses dedicated functions to determine whether the input represents:

- a character;
- an integer;
- a float;
- a double.

Invalid literals are rejected before attempting conversions.

The detected type determines which conversion path is executed.

---

## Scalar Conversion

After parsing the original value, explicit conversions are performed using:

```cpp
static_cast
```

The converter checks whether each conversion can be represented safely.

For characters, the result can be:

```text
'<character>'
Non displayable
impossible
```

For integers, values outside the valid integer range are reported as:

```text
impossible
```

---

## Floating-Point Values

Float and double conversions preserve useful decimal precision while keeping integral floating-point values explicit.

For example:

```text
42
```

can be displayed as:

```text
float: 42.0f
double: 42.0
```

while non-integral values retain their significant digits.

Special floating-point values are also handled:

```text
nan
nanf
+inf
+inff
-inf
-inff
```

These values cannot be converted into valid characters or integers.

---

## Serializer

`Serializer` is a non-instantiable utility class.

It exposes two static functions:

```cpp
static uintptr_t serialize(Data *ptr);
static Data *deserialize(uintptr_t raw);
```

`serialize()` converts a `Data*` into an integer representation:

```text
Data*
  │
  ▼
uintptr_t
```

`deserialize()` performs the inverse conversion:

```text
uintptr_t
  │
  ▼
Data*
```

Both operations use:

```cpp
reinterpret_cast
```

The object itself is never copied or moved.

Only the representation of its address changes.

---

## Data Pointer Round Trip

The serialization exercise verifies the complete round trip:

```text
        Data object
             ▲
             │
       original Data*
             │
             ▼
        serialize()
             │
             ▼
         uintptr_t
             │
             ▼
       deserialize()
             │
             ▼
       recovered Data*
             │
             └──────────► same Data object
```

The original and recovered pointers must contain the same address.

This confirms that the integer representation preserves the pointer value correctly.

---

## Runtime Type Identification

The final exercise defines the following hierarchy:

```text
          Base
        /  |  \
       /   |   \
      A    B    C
```

`Base` contains a virtual destructor, making it polymorphic.

Objects of `A`, `B` or `C` can therefore be manipulated through a `Base*` or `Base&` while preserving their runtime type information.

---

## Random Object Generation

The function:

```cpp
Base *generate(void);
```

randomly creates one of the three derived types:

```text
A
B
C
```

The object is returned through a `Base*`.

The caller therefore knows the static type of the pointer but does not directly know the real type of the object.

---

## Identification Through Pointers

The first overload receives:

```cpp
void identify(Base *p);
```

It attempts to convert the pointer to each derived type using:

```cpp
dynamic_cast
```

When a pointer `dynamic_cast` fails, it returns `NULL`.

Conceptually:

```text
Base*
 │
 ├── dynamic_cast<A*> ──► valid pointer / NULL
 │
 ├── dynamic_cast<B*> ──► valid pointer / NULL
 │
 └── dynamic_cast<C*> ──► valid pointer / NULL
```

The successful conversion reveals the runtime type of the object.

---

## Identification Through References

The second overload receives:

```cpp
void identify(Base &p);
```

This version also uses `dynamic_cast`, but references behave differently.

A failed reference cast cannot return `NULL`.

Instead, it throws:

```cpp
std::bad_cast
```

The implementation attempts each possible derived type and catches failed conversions.

Conceptually:

```text
Base&
 │
 ├── dynamic_cast<A&> ──► success / std::bad_cast
 │
 ├── dynamic_cast<B&> ──► success / std::bad_cast
 │
 └── dynamic_cast<C&> ──► success / std::bad_cast
```

No pointers are used inside the reference overload.

---

# Compilation

Each exercise is independent.

Compile any exercise by entering its directory.

Example:

```bash
cd ex00
make
./convert 42.42
```

The other exercises can be compiled and executed with:

```bash
cd ex01
make
./serialize
```

or:

```bash
cd ex02
make
./identify_type
```

Available Makefile rules:

```bash
make
make clean
make fclean
make re
```

---

# Testing

The test programs verify:

- detection of scalar literal types;
- conversion between scalar types;
- printable and non-printable characters;
- integer range validation;
- float and double precision;
- floating-point pseudo-literals;
- invalid scalar input;
- serialization of a `Data*`;
- recovery of the original pointer;
- preservation of the `Data` object;
- random generation of `A`, `B` and `C`;
- runtime identification through pointers;
- runtime identification through references;
- correct deletion through a `Base*`.

Example scalar conversion:

```bash
./convert 42.42
```

Example output:

```text
char: '*'
int: 42
float: 42.42f
double: 42.42
```

Serialization verifies that:

```text
original pointer == recovered pointer
```

Runtime type identification verifies that both overloads identify the same generated object.

Memory usage can be checked with:

```bash
valgrind --leak-check=full ./identify_type
```

---

# Project Structure

```text
42_cpp_module_06/
│
├── ex00/
│   ├── ScalarConverter.cpp
│   ├── ScalarConverter.hpp
│   ├── main.cpp
│   └── Makefile
│
├── ex01/
│   ├── Serializer.cpp
│   ├── Serializer.hpp
│   ├── main.cpp
│   └── Makefile
│
├── ex02/
│   ├── Base.cpp
│   ├── Base.hpp
│   ├── main.cpp
│   └── Makefile
│
└── README.md
```

---

# What I Learned

Through this module I strengthened my understanding of:

- explicit C++ type conversions;
- `static_cast`;
- `reinterpret_cast`;
- `dynamic_cast`;
- scalar type detection;
- numeric range validation;
- floating-point precision;
- pointer representation;
- `uintptr_t`;
- serialization and deserialization of pointer values;
- inheritance;
- runtime polymorphism;
- virtual destructors;
- runtime type identification;
- pointer and reference casting behavior;
- exception handling with `std::bad_cast`.

CPP Module 06 demonstrates how different C++ casts solve fundamentally different problems, from ordinary scalar conversions to low-level pointer representation and runtime inspection of polymorphic objects.

---

# Author

**Raúl Expósito Campos**

42 Madrid Student

GitHub: https://github.com/raulrecrec