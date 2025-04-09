assembler: assembler.o macro_expander.o macro_linked_list.o first_pass.o label_linked_list.o second_pass.o line_utils.o instruction.o path_utils.o
	gcc -g -ansi -Wall -pedantic assembler.o macro_expander.o macro_linked_list.o first_pass.o label_linked_list.o second_pass.o line_utils.o instruction.o path_utils.o -o assembler
assembler.o: assembler.c macro_expander.o first_pass.o label_linked_list.o second_pass.o macro_expander.h first_pass.h label_linked_list.h second_pass.h status_codes.h
	gcc -c -ansi -Wall -pedantic assembler.c -o assembler.o
macro_expander.o: macro_expander.c macro_linked_list.o line_utils.o path_utils.o macro_expander.h status_codes.h consts.h macro_linked_list.h line_utils.h macro.h path_utils.h
	gcc -c -ansi -Wall -pedantic macro_expander.c -o macro_expander.o
macro_linked_list.o: macro_linked_list.c macro_linked_list.h macro.h
	gcc -c -ansi -Wall -pedantic macro_linked_list.c -o macro_linked_list.o
line_utils.o: line_utils.c instruction.o status_codes.h consts.h line_utils.h instruction.h label.h
	gcc -c -ansi -Wall -pedantic line_utils.c -o line_utils.o
instruction.o: instruction.c instruction.h
	gcc -c -ansi -Wall -pedantic instruction.c -o instruction.o
path_utils.o: path_utils.c path_utils.h
	gcc -c -ansi -Wall -pedantic path_utils.c -o path_utils.o
first_pass.o: first_pass.c label_linked_list.o line_utils.o first_pass.h label_linked_list.h status_codes.h consts.h label.h line_utils.h
	gcc -c -ansi -Wall -pedantic first_pass.c -o first_pass.o
label_linked_list.o: label_linked_list.c label_linked_list.h label.h status_codes.h
	gcc -c -ansi -Wall -pedantic label_linked_list.c -o label_linked_list.o
second_pass.o: second_pass.c line_utils.o instruction.o label_linked_list.o second_pass.h status_codes.h consts.h line_utils.h instruction.h label_linked_list.h
	gcc -c -ansi -Wall -pedantic second_pass.c -o second_pass.o
