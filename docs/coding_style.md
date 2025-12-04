# Bing's C++ Coding Style Guide
*For All projects based on `cpp-project-template-bing`*

This documentation defines the unified C++ coding conventions used across all of Bing's C++ projects. It covers coding style, naming, modules, and general structural rules.
(Documentation and comment formatting rules are defined separately in `comment-style.md`)

## 1. Project Structures and Module Boundaries

### 1.1 Top-Level Directory Layout

Every project follows this structure:
``` bash
src/                # Core library code
apps/               # Executables (GUI/CLI/Tools)
tests/              # Unit & integration tests (optional)
examples/           # Example programs
thirdparty/         # Third-party dependencies
cmake/              # CMake modules
docs/               # Project documentation
```

### 1.2 Module Layout inside `src/`

Core modules follow a consistent pattern:
``` bash
include/<proj>/infra/       # Basic utilities, logging, timing, helper classes
include/<proj>/domain/      # Bussiness Logic
include/<proj>/platform     # Optional, handle cross-platform part
include/<proj>/public_api   # Public API exposure layer 
```

### 1.3 Dependency Direction (Hard Rule)

Modules must depend **downward only**:

``` bash
infra <- no project-internal dependencies
domain <- depends on infra
api <- depends on infra + domain
apps/* <- depends ONLY on <proj>::api
```
If an `app` requires access to `infra` or `domain`, **you should extend the public API, not bypass it**

---

## 2. Naming Conventions

### 2.1 General Principles
+ Use **English** identifiers.
+ Use clear, descriptive names; avoid ambiguous abbreviations.
+ Names should reflect purpose and behavior.

### 2.2 Types, Classes, Enums
Use **PascalCase**:
``` cpp
class ExampleService;
struct PlatformInfo;
enum class LogLevel;
```

### 2.3 Functions
Use **PascalCase**
``` cpp
std::string MakeWelcomeMessage(const std::string& userName);
void UpdateFrame(double deltaTime);
```

### 2.4 Variables
+ Local variables: `camelCase`
+ Member variables: `camelCase_` suffix
+ Constants: `kPascalCase`
``` cpp
std::uint64_t frameIndex_ = 0;
constexpr int kMaxFrames = 3;
```

## 2.5 Macros
Avoid macros; if necessary, use **UPPER_SNAKE_CASE**
``` cpp
#define ENABLE_PROFILING
```

## 2.6 Namespaces
Use a short prefix (e.g. `cptb`)
``` cpp
namespace cptb::domain { ... }
```

Do **not** place `using namespace` inside header files.

---

## 3. Header File Rules

### 3.1 Include Guards
All headers must use:
``` cpp
#pragma once
```

### 3.2 Include Order
Follow this order:
1. Corresponding header (in `.cpp`)
2. Other project headers
3. Third-party headers
4. Standard library headers
```cpp
#include <cptb/Engine.h>
#include <cptb/infra/Loggers.h>
#include <fmt/core.h>
#include <string>
#include <vector>
```

### 3.3 Header File Restrictions
+ No `using namespace` in headers
+ No non-inline global variables in headers
+ Minimize includes; prefer **forward declarations** where possible

---

## 4. Class and Interface Design
### 4.1 Small, Focused Classes
+ Each class should have one primary responsibility.
+ If it grows beyond ~20 methods, consider refactoring.

### 4.2 Constructors & Factories
+ Use regular constructors for simple objects.
+ Use factories or builders for complex, multi-parameter configurations.

### 4.3 Copy & Move Semantics
Explicitly define or delete copy/move operations:
``` cpp
class NonCopyable
{
public:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
    
    NonCopyable(NonCopyable&&) = default;
    NonCopyable operator=(NonCopyable&&) = default;
};
```

---

## 5. Function Design

### 5.1 Parameters
Prefer:
+ `const T&` for large input objects
+ `std::string_view` for read-only strings
+ Keep parameter count <= 5; otherwise use a config struct

### 5.2 Return Values & Const
Add `const` wherever applicable:
``` cpp
std::string getName() const;
```
Small trivial types return by value.




