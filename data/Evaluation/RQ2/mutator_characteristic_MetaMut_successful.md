|mutators|#crashes                                           |action   |Program elements         |
|--------|---------------------------------------------------|---------|-------------------------|
|s.duplicate-with-binop|6                                                  |Duplicate|Expr., Binary Operator   |
|u1.DecayRandomPointerToArray|6                                                  |Modify   |Variable Decl.           |
|u1.ReplaceLiteralWithRandomValue|6                                                  |Modify   |Literal                  |
|s.copy-expr|5                                                  |Add      |Expr., Literal           |
|s.swap-expr|5                                                  |Swap     |Expr.                    |
|s.randomize-string-literal|5                                                  |Modify   |String Literal           |
|s.duplicate-with-unop|5                                                  |Duplicate|Expr., Unary Operator    |
|u1.ModifyRandomLiteralInExpr|5                                                  |Modify   |Literal                  |
|s.change-declref|4                                                  |Modify   |Expr                     |
|s.combine-variable|4                                                  |Modify   |Variable Decl.           |
|s.change-vardecl-qualifier|4                                                  |Modify   |Variable Decl., Qualifier|
|u1.NegateLiteral|4                                                  |Modify   |Literal                  |
|s.remove-stmt|4                                                  |Remove   |Stmt.                    |
|s.change-integer-literal|4                                                  |Modify   |Literal                  |
|s.increase-pointer-level|3                                                  |Modify   |Variable Decl.           |
|s.copy-propagation|3                                                  |Modify   |Expr.                    |
|s.random-copy-propagation|3                                                  |Modify   |Expr.                    |
|s.change-parmtype|3                                                  |Modify   |Parameter, Type          |
|s.mutate-binop|3                                                  |Modify   |Binary Operator          |
|u1.SwapRandomBinaryOperands|3                                                  |Swap     |Expr.                    |
|s.remove-unop|2                                                  |Remove   |Unary Operator           |
|s.change-decltype|2                                                  |Modify   |Type, Variable Decl.     |
|u1.ModifyRandomEnum|2                                                  |Modify   |Type                     |
|s.add-initialization|2                                                  |Add      |Initialization           |
|s.switch-to-if|2                                                  |Modify   |Stmt.                    |
|s.swap-child-expr|2                                                  |Swap     |Expr.                    |
|u1.RandomizeFunctionOrder|2                                                  |Swap     |Function Def.            |
|s.struct-to-int|2                                                  |Modify   |Type, Variable Decl.     |
|u1.ReplaceLiteralWithConstant|1                                                  |Modify   |Literal                  |
|u1.ModifyPointerTarget|1                                                  |Modify   |Initialization           |
|u1.ReplaceRandomTypeWithTypedef|1                                                  |Modify   |Type                     |
|s.decay-small-struct|1                                                  |Modify   |Type                     |
|s.duplicate-fields|1                                                  |Duplicate|Field Decl.              |
|s.mutate-unop|1                                                  |Modify   |Unary Operator           |
|u1.SwapFuncDeclParams|1                                                  |Swap     |Function Decl., Parameter|
|u1.DecayRandomFunctionToPointer|1                                                  |Modify   |Function Decl., Expr.    |
|s.toggle-bitfield|1                                                  |Toggle   |Field Decl.              |
|u1.InterchangeFuncCalls|1                                                  |Swap     |Expr.                    |
|s.add-suffix-unaryop|1                                                  |Add      |Unary Operator           |
|s.simple-uninliner|1                                                  |Modify   |Stmt., Function Def.     |
|u1.DuplicateRandomUnaryOperator|1                                                  |Duplicate|Unary Operator           |
|s.simple-inliner|1                                                  |Modify   |Expr.                    |
|u1.InlineRandomVarDecl|1                                                  |Modify   |Variable Decl.           |
|s.increase-array-dimension|1                                                  |Modify   |Variable Decl.           |
|s.inverse-inline|1                                                  |Toggle   |Attribute, Function Decl.|
|u1.ReplaceIntWithEquivalentBitwiseExpr|1                                                  |Modify   |Literal                  |

## Number of Crashes x Number of Mutators
|#crashes|#mutators                                          |
|--------|---------------------------------------------------|
|6       |3                                                  |
|5       |5                                                  |
|4       |6                                                  |
|3       |6                                                  |
|2       |8                                                  |
|1       |18                                                 |

## Actions
|actions|MetaMut                                            |
|-------|---------------------------------------------------|
|Add    |3                                                  |
|Duplicate|4                                                  |
|Modify |29                                                 |
|Swap   |6                                                  |
|Toggle |2                                                  |
|Remove |2                                                  |

## Program Elements
|program elements|MetaMut                                            |
|----------------|---------------------------------------------------|
|Variable Decl.  |8                                                  |
|Function Decl.  |3                                                  |
|Parameter       |2                                                  |
|Expr.           |12                                                 |
|Builtin Function|0                                                  |
|Initialization  |2                                                  |
|Stmt.           |3                                                  |
|Attribute       |1                                                  |
|Type            |6                                                  |
|Storage Class Specifier|0                                                  |
|Literal         |8                                                  |
|Character       |0                                                  |
|Unary Operator  |5                                                  |
|Binary Operator |2                                                  |
|Function Def.   |2                                                  |
|Field Decl.     |2                                                  |
|Qualifier       |1                                                  |
