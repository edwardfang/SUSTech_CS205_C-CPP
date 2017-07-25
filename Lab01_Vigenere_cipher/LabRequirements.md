## LAB 1 in C/C++ 
### Target:
 1. Review the basic concepts and usage about C programming, data types（int, char .etc）,  arrays, functions.
 2. Learn how to handle input and output, how to use arrays, how to calculate with characters, and the basic control flow in a C program.
 3. Learn how to use gcc, and basic linux commands.
### Requirement:
You are normally expected to finish all the tasks before this lab ends; the code should compile without error，the program should run without crashing. Code should be commented, especially in complicated functions.

 1. If you cannot finish all the tasks, just try your best to do what you can. You can get help from professor/assistant later, including on Friday. The lab work should be handed in before Saturday this week. Some points will be taken off for late submission, but you'll certainly get a better score than if you handle on time something that doesn't work.
 2. Save your code by naming your .c files with the prefix “LABx_ Student ID_tasky” (x is the number of the LAB , y is the number of the task in the LAB) . Submit it by mail or in Sakai (preferred). We only need the code, not executable files (it will be recompiled for grading). 

### Tasks 
(Each task should be a runnable program with enough comments , not crush ,correct function, friendly to user):
 1. To get familiar with the environment write a very simple program that reads your name and Student ID from the keyboard, and outputs “Welcome XXX to the C and C++ world” on the screen. XXX is your name and Student ID. ( 2 points)
 2. Initialize the shifted alphabet table of Vigenere encoding and display it on the screen. (3 points)
 3. Using “ Vigenere” as a key, encrypt the ouput from task1 (just encrypt the alpha, keep other characters unchanged). Hint: You can use a Unix pipe so that the output of task1 becomes the in input of task3 (5 points)
OPTIONAL
 1. Perform encryption using only letter computations and without using the shifted alphabet table as indicated in LAB1_SUBJECT.(2 points)
 2. Decode encoded text as indicated in LAB1_SUBJECT.(2 points) Try it on the output of task3 and check that you get back the output of task1.
