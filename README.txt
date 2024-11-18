- Course: CSC173
- Assignment: Project 4
- Name: Zhijie Wang
- Email: zwang179@u.rochester.edu
- Collaborator: Aijia Yu
- Collaborator's email: ayu27@u.rochester.edu
- My program has a clean report from valgrind.
(There is no error reported from valgrind except memory leaks. 
The instructions say memory leaks will not be punished)

- To build and run my program:
    -Step 1: type code below on terminal:
    gcc -std=c99 -Wall -Werror -o EXECUTABLE *.c

    -Step 2: To run my code using valgrind, type code below on terminal:
    valgrind ./EXECUATBLE

    OR to run without valgrind, type code below on terminal:
    ./EXECUTABLE

- To check outputs:
    - After running the program, the hashtables for five schemas and the output for part 1 will be shown.

    - The program then will ask you for inputs to test part 2. By typing particular inputs 
    such as name, projectId, account, etc(depend on queries), you will see output for part 2. Type 'stop' to quit.

    - After you quit the REPL from part 2. You will see the output for part 3.
