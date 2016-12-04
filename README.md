# TOC Compiler

- In the root folder of the project:

| Task                                    | Make command                 |
| :-------------------------------------- | :--------------------------- |
| Compile everything                      | `make superb`                |
| Compile everything with Dump            | `make superb DUMP=1`         |
| Compile Code Analyzer                   | `make`                       |
| Compile LLVM Executable Code            | `make TYPE=LLVM`             |
| Compile LLVM Executable Code with Dump  | `make TYPE=LLVM DUMP=1`      |
| Clean                                   | `make clean`                 |
| Clean everything                        | `make veryclean`             |
| Run input/output tests                  | `make test-black-box`        |
| Run unit tests                          | `make test-unit`             |
| Run all the tests                       | `make test`                  |
| Clean/compile/test everything           | `make all`                   |
| *Show Code Evaluation Option*           | *`OPT=-DSCORE`*              |

## The TOC Language
Inspired by the many awful languages out there, TOC aims to gather together three things:
- Simplici**T**y: clear, clean and short keywords;
- **O**rganization: indentation patterns, unified variable and function identifiers;
- Qui**C**kness: more work, less time.

[Language Specification](https://github.com/lucaspetry/toc-compiler/blob/master/docs/Especifica%C3%A7%C3%A3o%20do%20Compilador.pdf)
