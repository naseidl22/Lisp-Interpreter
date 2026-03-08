LISP Interpreter

Lisp interpreter written in C++

-----------------------------------------------------------------

Build Intructions: 

-----------------------------------------------------------------

I used g++ to compile my project

Navigate in a terminal to the directory containing the source code and use the following command to compile:

g++ --std=c++17 ./env.cpp ./interpreter.cpp ./main.cpp ./parser.cpp ./scanner.cpp ./sexpr.cpp -o lisp.exe

This line will produce an output file called lisp.exe, you can change the output flag to change the output file name if desired

-----------------------------------------------------------------

Running the Interpreter: 

-----------------------------------------------------------------

To run the interpreter on a program file in the current directory, use the command: ./lisp.exe filename,
for example, to run the test cases I've provided, use the command: ./lisp.exe testcases.txt

To run the interpreter with just the REPL, don't include any arguments from the command line, simply use the command: ./lisp.exe

-----------------------------------------------------------------

Test Cases & Built in Functions: 

-----------------------------------------------------------------

I have included the following commands in my interpreter:

print -> print s-expr
eval
quote
defun -> define function
set -> define variable
cons 
if 
cond 
car 
cdr 
and 
or 
NUMBER? 
SYMBOL? 
LIST? 
NIL? 
add -> addition
sub -> subtraction
mul -> multiplication
div -> division
lt -> less than
lte -> less than or equal to
gt -> greater than
gte -> greater than or equal to
eq -> equal to 

Please see testcases.txt for examples of how these functions are used. (cond and eval is used within the function declarations towards the end)

-----------------------------------------------------------------
