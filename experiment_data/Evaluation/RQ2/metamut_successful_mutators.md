| Mutator | Action | Program Elements |
|---------|--------|------------------|
| s.add-initialization | Add | Initialization |
| s.add-suffix-unaryop | Add | Unary Operator |
| s.change-declref | Modify | Expr |
| s.change-decltype | Modify | Type, Variable Decl. |
| s.change-integer-literal | Modify | Literal |
| s.change-parmtype | Modify | Parameter, Type |
| s.change-vardecl-qualifier | Modify | Variable Decl., Qualifier |
| s.combine-variable | Modify | Variable Decl. |
| s.copy-expr | Add | Expr., Literal |
| s.copy-propagation | Modify | Expr. |
| s.duplicate-with-binop | Duplicate | Expr., Binary Operator |
| s.duplicate-with-unop | Duplicate | Expr., Unary Operator |
| s.group-stmts-into-compound | Modify | Stmt. |
| s.increase-array-dimension | Modify | Variable Decl. |
| s.inverse-inline | Toggle | Attribute, Function Decl. |
| s.mutate-binop | Modify | Binary Operator |
| s.mutate-unop | Modify | Unary Operator |
| s.random-copy-propagation | Modify | Expr. |
| s.randomize-string-literal | Modify | String Literal |
| s.remove-stmt | Remove | Stmt. |
| s.remove-unop | Remove | Unary Operator |
| s.simple-uninliner | Modify | Stmt., Function Def. |
| s.struct-to-int | Modify | Type, Variable Decl. |
| s.swap-child-expr | Swap | Expr. |
| s.swap-expr | Swap | Expr. |
| s.switch-to-if | Modify | Stmt. |
| s.toggle-bitfield | Toggle | Field Decl. |
| u1.DecayRandomFunctionToPointer | Modify | Function Decl., Expr. |
| u1.DecayRandomPointerToArray | Modify | Variable Decl. |
| u1.DuplicateRandomUnaryOperator | Duplicate | Unary Operator |
| u1.InlineRandomVarDecl | Modify | Variable Decl. |
| u1.InterchangeFuncCalls | Swap | Expr. |
| u1.ModifyPointerTarget | Modify | Initialization |
| u1.ModifyRandomEnum | Modify | Type |
| u1.ModifyRandomLiteralInExpr | Modify | Literal |
| u1.NegateLiteral | Modify | Literal |
| u1.RandomizeFunctionOrder | Swap | Function Def. |
| u1.ReplaceIntWithEquivalentBitwiseExpr | Modify | Literal |
| u1.ReplaceLiteralWithConstant | Modify | Literal |
| u1.ReplaceLiteralWithRandomValue | Modify | Literal |
| u1.ReplaceRandomTypeWithTypedef | Modify | Type |
| u1.SwapFuncDeclParams | Swap | Function Decl., Parameter |
| u1.SwapNestedFunctionCalls | Swap | Expr. |
| u1.SwapRandomBinaryOperands | Swap | Expr. |