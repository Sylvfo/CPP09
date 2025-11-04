## CPP09 / ex01 – Reverse Polish Notation

The goal of this exercise is to **evaluate mathematical expressions written in Reverse Polish Notation (RPN)** using a stack-based calculator.

Reverse Polish Notation is a mathematical notation where operators follow their operands, eliminating the need for parentheses

### Technical Skills

- C++ (98 standard)
- Stack data structure (std::stack)
- String parsing and tokenization
- Expression evaluation algorithms
- Error handling and input validation
- Operator precedence (implicit in RPN)


### Compilation & Usage

- **Supported operators:** `+`, `-`, `*`, `/`
- **Input:** Single-digit positive integers (0-9) separated by spaces

```bash
$> make
$> ./RPN "expression"
$> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
42
$> ./RPN "1 2 * 2 / 2 * 2 4 - +"
0
$> ./RPN "(1 + 1)"
Error
```


[A bit of piano to help 🎵🎹🎶](https://www.youtube.com/watch?v=_WzCnz8goTM&list=RDSpQ8-xiDYWI&index=27) 


*Part of the C++ module series at 42 Lausanne*