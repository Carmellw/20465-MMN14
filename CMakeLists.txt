cmake_minimum_required(VERSION 3.29)
project(MMN14 C)

set(CMAKE_C_STANDARD 90)

add_executable(MMN14 assembler.c
        macro_expander.c
        macro_expander.h
        consts.h
        macro.h
        macro_linked_list.c
        macro_linked_list.h
        first_pass.c
        first_pass.h
        label.h
        label_linked_list.h
        label_linked_list.c
        second_pass.c
        second_pass.h
        line_utils.c
        line_utils.h
        status_codes.h
        instruction.h
        instruction.c
        path_utils.h
        path_utils.c
)
