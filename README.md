# c-train-station-db
A C language program that will simulate a data base for a train station to keep the information about it simpler and compact. The project wants to implement the most common operations of a train station to simplify the work of the employees

## Table of Contents

1. [Getting Started](#start-description)
2. [Building](#build-description)
3. [Testing](#test-description)

<a name="start-description"></a>
## Getting Started

The program will generat an **.o** file that will represent a single-file library for the station functions. The functions provided in the project are:

* **arrive_train**
* **leave_train**
* **add_train_wagon**
* **remove_train_wagons**
* **move_train_wagons**
* **find_express_train**
* **find_overload_train**
* **find_optimal_train**
* **find_heaviest_train**
* **order_train**
* **fix_overload_train**

You can find the documentation for every function [HERE](src/station.c)

<a name="build-description"></a>
## Building

In order to build the project make sure that you are on a LINUX machine or **WSL**, the enter the build folder and to run the *Makefile**:

```BASH
    cd build
    make
```

After that you will get the object file **station.o** that you can use in your future projects.

<a name="test-description"></a>
## Testing

In order to see how to work with project functions, I suggest to look up to [station_run.c](/src/station_run.c) file. This file is acollection
of tests to check every function, especially corener cases, like NULL station or trains, wrong platform number, etc.

In order to run the tests and to see what tests are passed you should run:

```BASH
    ./station_run.sh
```

To see how the output is printed you should look to [THIS_FOLDER](build/ref/) and to look in station_run.c to see how the output is redirected
to your specific file.
