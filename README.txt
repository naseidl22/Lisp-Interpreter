Nicholas Seidl CS 503

YISP / LISP Interpreter Submission 

Lisp interpreter written in C++

-----------------------------------------------------------------

Build Intructions: 

-----------------------------------------------------------------

I used g++ to compile my project

Navigate in a terminal to the directory containing the source code and use the following command to compile:

g++ --std=c++17 ./env.cpp ./interpreter.cpp ./main.cpp ./parser.cpp ./scanner.cpp ./sexpr.cpp -o yisp.exe

This line will produce an output file called yisp.exe, you can change the output flag to change the output file name if desired

-----------------------------------------------------------------

Running the Interpreter: 

-----------------------------------------------------------------

To run the interpreter on a program file in the current directory, use the command: ./yisp.exe filename,
for example, to run the test cases I've provided, use the command: ./yisp.exe testcases.txt

To run the interpreter with just the REPL, don't include any arguments from the command line, simply use the command: ./yisp.exe

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

Sample Output: 

-----------------------------------------------------------------

I included the output I got from running my test cases in a file called test_output.txt in the zip folder I'm submitting

-----------------------------------------------------------------

Snapshots: 

-----------------------------------------------------------------

I included the five snapshot folders containing the source code for each snapshot preceeding the final submission.