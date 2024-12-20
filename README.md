# snakes-and-ladders

--> A console based snakes and ladders game written using C++ using the libraries: 
    - Standard Library  
    - Simple & Fast Multimedia Library (SFML) Library - for sound effects


--> To run the code: 
    - You must have a C++ compiler supporting C++11 or later
    - SFML Library must be installed on your system 


--> Compilation Command:
    clang++ -std=c++11 -o sal snakesandladders.cpp -I/opt/homebrew/opt/sfml/include -L/opt/homebrew/opt/sfml/lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

    Note: 
    I am using a macOS system so the compilation code makes use of clang as the compiler. 
    It uses homebrew since I installed SFML using homebrew.
    It may need to modify the -I and -L flags if you are on Windows or if you installed SFML another way.


--> Execution Command:
    After you have compiled the code, enter the following code to execute the code - 
    ./sal

    Because an executable file sal is created when we pass the compilation command given.


Make sure you have all the four audio files downloaded and in the right directory.
If the files are in a different directory, the path in the code will need to be modified accordingly. 




