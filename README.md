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

## Black-Box Test Files
- .toc : program input.
- .exp : program output (tree intermediate representation).
- .llvm : program output (actual program output).
