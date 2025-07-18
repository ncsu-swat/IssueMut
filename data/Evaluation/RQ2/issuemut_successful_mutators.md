## Representative List of Mutators from IssueMut

**Note**: 
- † = C23 standard contribution

<!-- **Table**: Representative list of mutators revealed more than three crashes from the tool. (C23 standard contributions marked with †) -->
<!-- 
## Legend
- **At** = Attribute
- **BF** = Builtin function  
- **Uo** = Unary Operator
- **FD** = Function Declaration
- **L** = Literal
- **I** = Initialization
- **P** = Parameter
- **E** = Expression
- **Sc** = Storage Class Specifier
- **S** = Statement
- **T** = Type
- **VD** = Variable Declaration
- **C** = Character -->

<!-- ## Mutators -->

| Id | Src. | Action | Pgm. Elements | Description |
|----|------|--------|---------------|-------------|
| M1 | GCC | Add | Builtin function, Expression | Adds built-in function `__builtin_assoc_barrier()` around the return expression. |
| M2 | GCC | Swap | Expression | Swaps two arguments of function calls. |
| M3 | GCC | Modify | Storage Class Specifier | Replaces `extern` storage class specifier with `static`. |
| M4 | GCC | Remove | Unary Operator | Removes a type cast operator. |
| M5 | GCC | Modify | Parameter, Type | Replaces const pointer parameters with non-const non-pointer parameters. |
| M6 | GCC | Modify | Expression | Replaces a variable reference with a call expression. |
| M7 | LLVM | Remove | Variable Declaration | Removes the size expression from an array variable declaration. |
| M8 | LLVM | Modify | Literal | † Replaces integer literals with a large numeric value using a new integer literal suffix. (e.g., changing `123` to `66666...wb` (The `wb` suffix is a bit-precise integer literal suffix introduced in the C23 standard)). |
| M9 | LLVM | Modify | Literal | † Replaces integer zero literals into binary zero literals, which is introduced in the C23 standard (e.g., 0b0). |
| M10 | LLVM | Add | Attribute, Function Declaration | Adds `__attribute__((target_clones("default,avx")))` to function declarators. |
| M11 | GCC | Modify | Literal | † Replaces integer literals with the `nullptr`, a new null pointer constant introduced in C23. |
| M12 | GCC | Modify | Statement | Replaces standard goto statement with `asm goto` equivalents. |
| M13 | GCC | Modify | Statement, Variable Declaration | Replaces inline assembly register constraints of asm stmt with floating-point constraints (e.g., changing `+r` to `+d`). Replaces `__asm__` with `__asm` in variable declarations. |
| M14 | GCC | Add | Statement | Adds a conditional assignment statement to an array element. |
| M15 | GCC | Modify | Statement | Replaces `for` loop constructs with equivalent `while` loop implementations. |
| M16 | GCC | Modify | Function Declaration | Replaces function identifiers with generic identifier. |
| M17 | GCC | Add | Function Declaration | Adds explicit `extern` declarations for implicitly declared functions in call expressions. |
| M18 | GCC | Modify | Variable Declaration | Removes temporary variables and replaces references with their initializers. |
| M19 | GCC | Add | Attribute, Function Declaration | Adds `__attribute__((noreturn))` to function declarations. |
| M20 | GCC | Remove | Attribute | Removes the attribute specifier from a function declarator or a variable declaration. |
| M21 | GCC | Modify | Expression | Replaces type cast expressions in return statements with equivalent variable declarations and assignments. |
| M22 | GCC | Modify | Parameter, Type | Replaces function parameter types with `char`. |
| M23 | GCC | Add | Type | Modifies a struct by introducing a typedef alias. |
| M24 | GCC | Add | Parameter | Adds two `long long` type parameters to a function declarator. |
| M25 | GCC | Add | Builtin function, Expression | Adds `__builtin_assume_aligned` to destination pointers in calls with `__builtin_memcpy`. |
| M26 | GCC | Remove | Initialization | Removes the zero initialization expression from a pointer variable declaration. |
| M27 | GCC | Remove | Initialization | Removes the initialization expression from a variable declaration. |
| M28 | GCC | Add | Type | Adds a field of type `long double` to a union. |
| M29 | LLVM | Add | Attribute | Adds the `no-` prefix to existing target attribute specifier. |
| M30 | LLVM | Modify | Type | Replaces platform-specific types declarations with explicit-size alternatives. (e.g., `size_t` with `long long`). |
| M31 | LLVM | Remove | Unary Operator | † Removes `typeof()` operators, introduced in the C23 standard. |
| M32 | LLVM | Add | Character | Adds escape characters (e.g., backslashes) after line break characters. |
| M33 | LLVM | Remove | Parameter | Removes `void` parameter from function declarator. |
| M34 | | Add | Attribute, Function Declaration | Adds `__attribute__((noipa))` to function declarators. |
| M35 | | Modify | Expression | Modifies array index in array subscript expressions. | 
| M36 | | Modify | Type, Field Declaration | † Replaces bit-field types with `unsigned _BitInt`(e.g., changing `int` to `unsigned _BitInt(32)`). |
| M37 | | Modify | Type | † Increases the width of `_BitInt` type declarations. |
| M38 | | Modify | Type | Replaces unsigned integer types with signed integer types in variable declarations. |
| M39 | | Modify | Type | Replaces signed int types with unsigned types in variable declarations. |
| M40 | | Modify | Type | Converts a struct to a union and updates associated variables and parameters. |
| M41 | | Duplicate	| Storage Class Specifier, Function Declaration | Duplicates function declarations with opposite storage class specifier. |
| M42 | | Duplicate | Statement | Duplicates function call expressions. |
| M43 | | Modify | Statement | Replaces a `#include` directive with a `#embed` directive. |
| M44 | | Modify | Statement | Combines nested `if` statements into single `if` statements with logical AND operator. |
| M45 | | Remove | Storage Class Specifier | Removes `static` storage class specifier from declarations. |
| M46 | | Remove | Field Declaration | Removes a field declaration from struct/union declarations. |
| M47 | | Remove | Parameter | Removes a parameter from variadic functions and updates references. |
| M48 | | Remove | Initialization | Removes initialization expressions from global variable declarations. |
| M49 | | Remove | Statement | Removes a macro definition (`#define`). |
| M50 | | Remove | Statement | Removes an assignment statement. |
| M51 | | Modify | Type | Converts named struct declarations to anonymous struct declarations. |
| M52 | | Modify | Type | † Modifies the width of `_BitInt` type declarations. |
| M53 | | Modify | Builtin Function, Statement | Replaces a return statement with `__builtin_unreachable()`. |
| M54 | | Modify | Expression | Replaces a return expression with 0. |
| M55 | | Modify | Type | Replaces type `size_t` with type `int`. |
| M56 | | Modify | Type | Converts a struct definition into a forward declaration. |
| M57 | | Modify | Type | Inlines struct definitions by replacing named struct usage with anonymous struct bodies. |
| M58 | | Modify | Type | Replaces `int` types with `short int` in variable declarations. |
| M59 | | Add | Attribute | Adds `__attribute__((returns\_twice))` to function declarators. |
| M60 | | Swap | Parameter | Swaps parameters of a function declaration and updates corresponding function call expressions. |

