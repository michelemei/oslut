# Oslut - osl Unit Test

A Cpp Test Unit Framework (currently only for Windows). 

There are a lot of [framework for testing the c++ code](https://en.wikipedia.org/wiki/List_of_unit_testing_frameworks#C.2B.2B). Most of them test only exported classes and methods from a shared library. During the development of [G2D](https://github.com/michelemei/g2d) i needed to test **internal** (not exported) geometric algorithms.

The goal of Oslut is to be a very very *quick* and *simple* framework, using only header files, that it is able to test internal classes, methods and functions.

## Quick Start

### Installation

The oslut installation is very simple:

1. copy `oslut.h` somewhere on your hard disk,
2. copy `test.cpp` (you can rename it) in your project and change the first line to point to `oslut.h`.

Finish. Write your tests.

> I suggest you create a directory called **oslut**, parallel to the source's root directory and put in this folder `oslut.h`.

Suppose you have to write tests for the **Point** class, you can choose between two possibilities:

* write all tests in test.cpp file,
* differentiate the test file.

Some examples of tests:
 
```cpp
TEST("Point_cstr_without_params")
	Point point;
	IS_TRUE(point.GetX() == 0);
	IS_TRUE(point.GetY() == 0);
ENDTEST

TEST("Point_cstr_params")
	Point point(10, 15);
	IS_TRUE(point.GetX() == 10);
	IS_TRUE(point.GetY() == 15);
ENDTEST

TEST("Point_cstr_exception")
	try
	{
		/* do anything that throws an exception */
		FAIL;
	}
	catch(...)
	{
		SUCCEDED;
	}
ENDTEST
```

### Run

To run tests call `oslut.exe` passing two parameters:

 1. the dll name to test,
 2. XML file where append the test results,

in this way:

```
oslut.exe myshared.dll myresult.xml
```

> **Warning**
> Oslut uses *LoadLibrary*, therefore **oslut.exe** must be in the same shared library's folder.

### How it works?

The Oslut strategy is very simple:

1. `TEST` define create an exported the test function,
2. `olsult.exe` load library and calls `TEST` functions. 

#### Test define

The test define have a signature like this: `bool(char* filename, long* line, char* name)`, where:

1. `filename` is the name of file that contains the test,
2. `line` is the starting line of test into `filename`,
3. `name` is the name of test.

All these are output parameters that are automatically populated by `TEST` define.