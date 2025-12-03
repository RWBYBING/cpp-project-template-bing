# Bing C++ Comment Style Guide
*For all projects based on `cpp-project-template-bing`*

This documentation defines the unified commenting conventions used across all C++ projects. It covers file headers, class and function documentation, member variable, and inline comments.

All comment syntax is standardized using **Doxygen-style** tags to ensure:
+ IDE-friendly hover documentation
+ Automatic API generation possibility
+ Consistent structure across all modules (`domain`, `infra`, `api`)

## 1. General Principles
+ Write comment for intention, not repetition. Do not describe what the code does, describe why it exists.
+ English-only comment, unless other clarification is necessary.
+ Use Doxygen-compatible syntax: `///` single-line comments, `/** ... */` when necessary.
+ Keep comments updated. Outdated comments are worse than no comments.
+ Documentation should be comprehensive for:
    + Public API
    + Library interfaces
    + Core module
    + Complex algorithms

## 2. Comment Types (Overview)
There are four major categories:
1. File header comments
2. Class / struct comments
3. Function comments
4. Inline comments for logic blocks & member variables

Each category has its own format rules below.

## 3. File Header Comment Format
File header documentation is recommended for:
+ Important modules
+ Public API headers
+ Core infrastructure files

Example:
``` cpp
/**
 * @file Logger.h
 * @author Bing
 * @brief Thread-safe logging utilities
 * @date 2025-11-30
 * 
 * @details
 *  Provides a minimal logging utility with thread safety
 *  Intended for demos and small tools; replaceable in real-world applications.
 */
```

Required elements:
+ `@file`
+ `@brief`

Optional elements:
+ `@details`
+ `@author`
+ `@date`

## 4. Class and Struct Comment Format
Classes and structs exposed via public API or defining core logic must include full comments.

Example:
``` cpp
/**
 * @brief Thread-safe Logger
 * 
 * @details
 *  Supports multiple log levels and is safe for multi-threaded usage
 *  Implements a simple singleton pattern
 */
class Logger
{
public:

};
```

Required:
+ `@brief`

Optional:
+ `@details` (Design consideration, behavior notes)

## 5. Function and Method Comment Format

This is the most important documentation requirement. Use the Doxygen style with the following fields:

+ `@brief` - one-sentence summary
+ `@param` - description for each parameter
+ `@return` - meaning of return value
+ `@note` - design details, behavior notes, performance considerations
+ `@throws` - execptions thrown (if any)

Example:
``` cpp
/**
 * @brief Create a welcoming message including platform information
 * 
 * @param userName Name of the user, appears inside the greeting
 * @return std::string, Fully composed welcome message
 * 
 * @throw std::runtime_error, If platform infomation cannot be retrieved
 */
std::string generateWelcomeMessage(const std::string& userName);
```

Simplified form is acceptable when:
+ parameters are obvious
+ function is a small internal helper
+ no return complexity or exceptional behavior

Example:
``` cpp
/// @brief Covert log level to a printable string
const char* levelToString(Level level) const noexcept;
```

## 6. Inline Comments and Logic Block Comments
Inline comments must not repeat code. They should clarify complex logic or document the *reason* for non-obvious behavior.

Example:
``` cpp
// Step 1: Collect visitable entities
collectVisiableEntities(scene);

// Step 2: Sort by material to reduce GPU/CPU state switches
sortByMaterial(visibleEntities);
```

Use inline comments to annotate:
+ algorithm steps
+ performance-critical decisions
+ special-case handling

## 7. Member Variable Comments
Document member variables only when their purpose cannot be inferred from naming.

example:
``` cpp
class Engine
{
private:
    // Core domain service used to generate greetings
    domain::ExampleService* exampleService_ = nullptr;

    // Cached Platform info to avoid repeated system queries
    infra::PlatformInfo* platformInfo_ = nullptr;

    // Frame index used for profiling and debugging
    std::uint64_t frameIndex_ = 0;
};
```



