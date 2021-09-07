 
To compile the main project you will need to run the RebuildSln.sh file in your terminal.

Commands once project is is compiled and built:
    
    i-          -prints out some system specs
    
    f- X        -prints out PIDs and the sum of a calculation using forks X amount of times
    
    t- X        -prints out PIDs and the sum of a calculation using threads X amount of times

    
    
Task4.sh can be run through the terminal and takes a path as argumentin order to know where to start working.

    e.g.
    bash Task4.sh path
    
It will then add the text from the CopyrightHeader.txt file to the top of all .cpp and .h files.
Once that is done it will rename all .cpp files to .cc and change all instances of float into double and back for both the new .cc files and the .h files
