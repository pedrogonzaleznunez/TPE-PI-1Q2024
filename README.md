
# TPE-PI-1Q2024 <a href="https://github.com/simple-icons/simple-icons/actions?query=workflow%3AVerify+branch%3Adevelop"><img src="https://img.shields.io/github/actions/workflow/status/simple-icons/simple-icons/verify.yml?branch=develop&logo=github&label=tests" alt="Build status"/></a>

## Brief:
The main objective of this work is to capture everything learned in the subject "Imperative Programming", from variables and strings, to complex data structures. This system is responsible for collecting and organizing data on traffic violations in the cities of NYC and CHI.

![image](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![image](https://img.shields.io/badge/Markdown-000000?style=for-the-badge&logo=markdown&logoColor=white)

## Authors:

| Name        | File           | Email  |
| ------------- |:-------------:| -----:|
| Gonzalez Nuñez, Pedro    | 64467 | pgonzaleznunez@itba.edu.ar |
|  Laurenza, Carolina Luciana  | 64647 | claurenza@itba.edu.ar|
| Lopez Vila, Jerónimo |   65778    |    jlopezvila@itba.edu.ar |

## List of files
* `main.c`: File destined for implementation of query1,query2 & query3

* `main.h`: Header file destined for declaration of the interface of C file main.c. It helps with code clarity as it outlines main.c's prototypes.

* `makefile`: File destined for ruling which parts of the program should be compiled.

* `queries.c`: File destined for implementation of functions for query1,query2 & query3.

* `queries.h`: File destined for declarating protypes and briefs for functions in queries.c.

* `front.c`: C file destined for implementation of frontEnd functions of the program.

* `front.h`: File destined for declarating protypes for functions in front.c.

## how to run

### Compilation 

To compile this program follow these rules:
> Keep in mind that you must have `make` installed on your device

- Command used for compiling: 
```bash
make all
```

- After compiling, the following command can be called in case you want to delete the files generated
```bash
make clean
```

### Execution
1. To run the compiled program for NYC, it should be done like this: 

```bash
./parkingticketsNYC ticketsNYC.csv infrationsNYC.csv
```

2. To run the compiled program for CHI, it should be done like this:

```bash
./parkingticketsCHI ticketsCHI.csv infrationsCHI.csv
```
3. Three files will be generated right into the directory where the file was created 

```bash
    ../yourDirectory
        ./query1.csv
        ./query2.csv
        ./query3.csv
```
