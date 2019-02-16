	[PROJECT 2]

	"Shell Program"

Name

myshell



Synopsis

myshell [program] [arguments]
myshell [program] [arguments] < [inputfile]
myshell [program] [arguments] > [outputfile]
mysehll [command] [argument]



Description

'myshell' is a basic Unix shell implementation. Each user can use commands to navigate the OS, run 
programs, create new files, and view environment variables.

[internal commands]
Built into this program are several internal commands. These can be invoked by typing them into the 
command line. They are listed below.

cd <directory> - changes current working directory to <directory>
clr - clears shell screen
environ - lists environment variables of shell
echo <comment> - displays comment followed by a new line (tabs/multiple spaces are reduced to one space)
help <filter> - displays user manual, <filter> may be "more" (reads next)  or "q" (quits manual)
pause - pauses current operation of shell
quit - quits 'myshell'

[environment variables]
The executing process keeps a set of environment variables that keep track of the process's origin and 
its current location.

[batchfiles]
This program is capable of reading input from a batch file (a file parsed as command line input). To use 
this functionality, just type 'batchfile' into the command line, and the program will look for the batchfile 
in the process's path.

[program execution]
To invoke a new process, just type the program name (absolute or relative, depending on where your PWD is). 
'myshell' will handle your input by searching for the executable, then running it on a newly allocate process 
space with its following arguments. While the new process runs, 'myshell' will pause operations until the new 
process is finished executing. 

[i/o redirection]
To redirect the output of a new process, use the '>' char, like so...
	...directory> helloworld a1 b2 > output
This will execute 'helloworld' with arguments 'a1' and 'b2', and print its output to 'output'.
NOTE: You may substitute '>' with '>>' if you'd like to append an existing file ('>' will replace an existing file)

You may also use the '<' char to read in a text file as program arguments. Note that this is different than the 
batchfile execution, as the text file is only used as program arguments - not a command line input.
To redirect the input of a new process, use the '<' char, like so...
	...directory> helloworld a1 b2 < input
This will execute 'helloworld' with arguments taken from 'input', and print its output to the standard output 
stream.

[background execution]
Executing processes in the background is another supported feature. Simply add the ampersand character '&' to the 
end of the command line input. When added, a new process will be created and executed, but 'myshell' will continue 
operations regardless of whether the new process is running or not.



