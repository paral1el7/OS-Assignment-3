# Assignment 3: Parallel Merge Sort Implementation 

* Authors: Yiming Qian (README author), Rui Chen, Jan Philippe Banquicio
* Group name: Assignment 3 Groups 59


## Overview

This program uses the pthread library to create threads to process subarrays in parallel during the recursive process, so as to realize convergence sorting and sort randomly generated arrays. Users can specify array size, cutoff level and random seeds through command line parameters.


## Manifest

* `Makefile` - Build configuration file for compiling the project
* `mergesort.c` - Using pthread to implement the main functions of the parallel merge sort algorithm.
* `mergesort.h` - Header file containing function declarations and data structures
* `test-mergesort.c` - Test program for performance measurement and correctness verification
* `README.template` - Template file for README structure reference


## Building the project

### Environmental Requirements
- GCC compiler (with pthread library support)
- Make tool
- Linux/Unix environment
- If using Windows, please use tools such as Cygwin 

### Construction Steps
1. **Enter the source code directory** : 
```bash
cd <YourFilePath>/OS-Assignment-3
```

2. **Remove the previous compiled files** 
```bash
make clean
```

3. **Compilation Project**: 
```bash
make
```

4. **Verify successful compilation**: 
```bash
ls -la test-mergesort
```

### Using the Program
If the compilation complieted, the program can be used now. Please note that the path must remain within `OS-Assignment-3`. The specific usage method can be found in the "Features and Usage" section below.


## Features and usage

### Main Function
1. **Parallel Merge Sort**: Utilizes multi-threading technology to parallelize the traditional merge sort algorithm. By creating multiple threads to process different parts of the array simultaneously, it can improve the sorting performance. This is the purpose of the development of this program. 

2. **Configurable Parallelism Degree**: Users can control the depth of parallelization through the cutoff level parameter, ranging from serial sorting (cutoff = 0) to parallel sorting (cutoff > 0). 

3. **Performance Testing and Benchmarking**: The program automatically measures the sorting time and outputs the results, facilitating performance analysis and comparison. 

4. **Correctness Verification**: A built-in sorting result verification mechanism is included to ensure the correctness of the parallel algorithm. 

5. **Random Array Generation**: It supports the generation of test arrays using the random seed specified by the user, ensuring the reproducibility of the test results. 

### Usage Method
Enter the command in the `OS-Assignment-3` directory: 
```sh
./test-mergesort <input size> <cutoff level> <seed>
```

* `input size` - The number of elements to be sorted
* `cutoff level` - The depth of parallelization. 0 represents serial processing, while values above 0 indicate different levels of parallelism. **Attention, if the cutoff level is too high, it may impose a significant performance burden on your computer. Therefore, it is recommended to set it to 0-8**
* `seed` - The seed value used to generate the random array 

### Translation Result:
```sh
Sorting [element_number] elements took [time] seconds.
```


**Error Output**:
Depends on the error situation. For instance, when the input size is less than 2, the output will be: 
```sh
the input size must be at least 2!
```


## Testing

### Test method

The test is tested manually. The executable file `test-mergesort` is run in the command line, and different parameter combinations are passed in for testing. The main test contents include routine tests, boundary tests and error tests. Test the computer to use Windows system and Cygwin environment.

### 1. Routine range test

In order to ensure that the procedure is correct and meets the operation requirements, we have conducted the following tests using the cases in the operation requirements:
- An array of 100,000,000 elements has been tested. The cutoff is from 0-8, and the random seed is 1234.

**Test results**: The program works normally, and the output sorting time. When the cutoff value is between 1 and 4, the larger the cutoff value, the shorter the sorting time. When the cutoff value is between 5 and 8, the sorting time does not change much. When the cutoff is 0, the sorting time is the longest. The maximum duration of Parallel merge sort is 6.96s, and the duration of serial merge sort is 13.52, which is more than twice that of 6.96. This shows that the procedure meets the requirements.

### 2. Boundary test

In order to verify the performance of the program in extreme situations, we conducted a boundary test. The boundary test here is aimed at cutoff:
- An array of 100,000,000 elements was tested, cutoff from 9-14, and the random seed was 1234.

**Test results**: The program can work normally and output sorting time. When cutoff is 9-14, the sorting time gradually becomes longer. When the cutoff is 14, the sorting time even exceeds the serial sorting time with cutoff 0, reaching 18.89s.

### 3. Error test

In order to verify the robustness of the program, we conducted an error test. The error test here is aimed at cutoff:
- An array of 100,000,000 elements was tested, the cutoff was from -3 to -1, and the random seed was 1234.

**Test results**: The program can run and output the sorting time. When the cutoff is negative, the program still processes it according to serial sorting, and the sorting time is similar to that when the cutoff is 0. This shows that the program does not perform a range check when processing the value of cutoff.


## Known Bugs
The current system does not perform the cutoff range check. Users can input negative values for cutoff. Although we used the method of performing serial processing when thread creation fails, the negative cutoff value has no practical significance. The output could cause confusion for the users. However, since this part is implemented in `test-mergesort.c` and the tutor does not allow modifying this file, this issue cannot be fixed.


## Reflection and Self Assessment
At the beginning of the project, we were not familiar with the use of the pthread library. We did not know enough about the parameters and usage of functions such as ``pthread_create`` and ``pthread_join``. In order to solve this problem, we learned the relevant part in the textbook. Combined with the sample code given in the book, we understood the most basic thread creation and management methods.

In addition, during the development and testing process, we found that when the cutoff is too high, the system may not be able to create enough threads, and make the program crashes. To solve this problem, we have written the code about run serial processing when thread creation fails, which can ensure the program can still working when the resource is insufficient. Finally, after testing, it was found that when the input size is 1000000 and the cutoff is set to 14, the running time exceeds the time of serial sorting. This means that when the system cannot create enough threads, the program successfully regresses to serial processing. This can prove the validity of this method.

In this project, mastering the cutoff mechanism is a challenge. We need to understand how cutoff affects the depth of thread creation, and we also need to deal with the lack of resources when the cutoff is too high. However, when we understand the role and mechanism of cutoff, we can better control the parallelism of the program. This makes us "clicked". In general, the development and testing process of this project went smoothly.


## Sources Used

Using AI to help to understand the knowledge in the textbook. But did not use AI to generate any code.
