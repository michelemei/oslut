# Oslut - osl Unit Test

A Cpp Test Unit Framework
(for now only Windows)

There are a lot of framework for testing the c++ code: see [wikipedia](https://en.wikipedia.org/wiki/List_of_unit_testing_frameworks#C.2B.2B).
During the development of [G2D](https://github.com/michelemei/g2d) I created my framework for testing. The goal was a **quick** and **simple** framework, using only header files.

## Quick Start

### Installation

The oslut installation is very simple: copy the __oslut.h__ file somewhere on your hard disk, copy the files __test.cpp__ (you can rename it) in your project and change the first line to point to oslut.h. Finish. Write your tests.

> I suggest you create a directory called __oslut__, parallel to the source's root directory and put in this folder __oslut.h__.

Suppose you have to write tests for the __Point__ class, you can choose between two possibilities:
 - write all tests in test.cpp file,
 - differentiate the test file.

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

To run the tests, call oslut.exe passing two parameters:
 1. the dll name to test,
 2. XML file where append the test results,

in this way:

```
oslut.exe myshared.dll myresult.xml
```

Oslut uses **LoadLibrary**, then __oslut.exe__ must be put in the same folder the dll to be tested.

> If you are using Visual Studio, you can put in "Post Build Step" the test execution.
In this way, each time you compile you will have the test results.