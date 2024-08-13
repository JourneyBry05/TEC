The following directory contains the respective folder for each application: GENERATOR and SORTER. 
Below is the explanation on how to run each script:

NOTE: It is recommended to run both applications from the Terminal (Windows Powershell for Windows), 
and navigate to the project directory, for example: C:\...\TEC\II_Semester2024\AlgorithmsAndDataStructureII\sorter> 
for SORTER and C:\...\TEC\II_Semester2024\AlgorithmsAndDataStructureII\generator> for GENERATOR.

GENERATOR:
    To generate the .exe file, run the command: $> g++ -o generator generator.cpp (this creates generator.exe).
    It expects a command in the following structure: $> generator –size <SIZE> -output <OUTPUT FILE PATH>.
    Where <SIZE> can be one of the following values:
        SMALL: generates a 512 MB file
        MEDIUM: generates a 1 GB file
        LARGE: generates a 2 GB file
    Where <OUTPUT FILE PATH> is the file path where the file is saved. For example:
        $> ./generator --size MEDIUM --output C:\...\TEC\II_Semester2024\AlgorithmsAndDataStructureII\generator\output.bin



SORTER:
    NOTE: The directory contains a file binary.cpp which has the logic to create random integers to be processed by 
    PagedArray, so it needs to be run first like this:
        g++ -o binary binary.cpp
        ./binary

    Run it in the terminal as follows:
        $> sorter –input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITMO>. 

        <INPUT FILE PATH> is the file path where the binary file with random integers to be sorted is located.

        <OUTPUT FILE PATH> is the file path where the sorted file will be saved.

        The <ALGORITHM> argument corresponds to one of the following values:
            QS: Quick sort
            IS: Insertion sort
            BS: Bubble sort
    
    To create the .exe file:
        g++ -o sorter PagedArray.cpp sorters.cpp main.cpp
    To sort the numbers:
        ./sorter -input input.bin -output output.bin -alg QS
    

