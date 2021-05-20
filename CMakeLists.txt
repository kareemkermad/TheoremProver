cmake_minimum_required(VERSION 3.15)
project(TheoremProver C)

set(CMAKE_C_STANDARD 99)

add_executable(TheoremProver main.c token.h parser.h tokenizer.h tree.h formula_writer.h tableaux.h theory.h token.c tree.c formula_writer.c theory.c tokenizer.c parser.c tableaux.c)