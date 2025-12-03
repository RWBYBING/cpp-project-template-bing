# cpp-project-template-bing

*A Modern C++ project template with clean architecture, layered modules, and professional CMake structure.*

This repository provides a high-quality C++ project skeleton intended for reuse across all future C++ applications. It is designed around a clean architecture pattern, modern CMake conventions, and my personal unified coding and documentation standards.

The goal is to ensure that every new project starts from a consistent, maintainable, and production-ready foundation.

---

## Key Features
+ **Modern C++20** project layout
+ **Clean layered modules**
    + `infra` -- essential utilities
    + `domain` -- business logic
    + `api` -- the public facade exposed to applications
+ **Strict CMake organization** suitable for large-scale software
+ **Application directory (`app/`)** containing sample executables
+ **Examples and tests** included by default (optional)

---

## CMake Structure
The project uses modern target-based CMake:
> Every library and executable has its own isolated configuration

### Primary Modules
| Module | Purpose |
| ------ | ------- |
| infra | Logging, utils, small reusable foundational code |
| domain | Business logic |
| api | Facade exposed to applications |

### Applications
Applications in `apps/` must **only depend on** `api`. **Never** directly include `infra` and `domain` headers.

---

## Coding Style
All code in the repository follows the **Bing C++ Coding Style Guide** located in:
``` bash
docs/coding-style.md
```

---

## Comment Style
Documentation follows a strict Doxygen-style standard. Defined in:
``` bash
docs/comment-style.md
```

---

## Platform Support
Platform abstraction is handled through CMake modules inside `cmake/`:
+ `PlatformDetect.cmake`
+ `ConfigWarnings.cmake`
+ ...

Platform rules cover:
+ OS detection
+ Compiler features
+ System libraries
+ Framework linking (macOS)
+ Runtime differences (Windows vs Linux vs macOS)

---

## Build Options
| Option | Default | Description |
| --- | --- | --- |
| `PROJ_BUILD_APPS` | ON | Build executables under `apps/` |
| `PROJ_BUILD_TESTS` | OFF | Build and enable tests |
| `PROJ_BUILD_EXAMPLES` | OFF | Build example programs |
| `PROJ_ENABLE_WARNINGS | ON | Enable project-wide warning policies |

Example:
``` bash
cmake -B build -DPROJ_BUILD_TESTS=ON
```
