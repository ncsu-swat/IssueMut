void constexprif() {
  if constexpr (300) {
  } // expected-error {{expected '(' after 'if'}}
}
void constevalif() {
  if consteval (300) {
  } // expected-error {{expected '(' after 'if'}}
}
