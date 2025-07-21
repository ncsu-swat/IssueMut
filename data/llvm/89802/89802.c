__attribute__((availability(shadermodel, introduced = 2.0,
                            environment = pixel)))
__attribute__((availability(shadermodel, introduced = 6.6,
                            environment = compute)))
__attribute__((availability(shadermodel, introduced = 6.6, environment = mesh)))
__attribute__((availability(shadermodel, introduced = 6.6,
                            environment = amplification)))
__attribute__((clang_builtin_alias(__builtin_hlsl_ddx))) float
ddx(float val);