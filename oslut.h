/*******************************************************************************

This file is part of Osl Unit Test (Oslut).

Oslut is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Oslut is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You can get a copy of of the GNU General Public License
at<http://www.gnu.org/licenses/>.

Version: 1.0.0
Author:  Michele Mei
E-Mail:  michele.mei@gmail.com

*******************************************************************************/

/*
Example:

int question()
{
  return 42;
}

// optional: set a precompiler variable to enable test
#ifdef TEST_ENABLE

TEST(question_true)
	IS_TRUE(question() == 42)
ENDTEST
TEST(question_false)
	IS_FALSE(question() != 42)
ENDTEST

#endif

compile and run:

  oslut.exe mydll.dll report.xml
*/
#ifndef __oslut_h
#define __oslut_h

/*
Windows (and Visual Studio) export methods convention is extern "C" + __declspec
change __OSLUT_EXPORT with the appropriate value for your OS and compiler.
*/
#define __OSLUT_EXPORT extern "C" { __declspec(dllexport)

// two-level for __COUNTER__
#define __OSLUT_TEST_NAME_LEV2(name, counter) name##counter
#define __OSLUT_TEST_NAME(name, counter) __OSLUT_TEST_NAME_LEV2(name, counter)

// result method type, success and failure values
#define __OSLUT_RESULT_TYPE bool
#define __OSLUT_SUCCESS true
#define __OSLUT_FAILURE false

// test header
#define TEST(name) __OSLUT_EXPORT __OSLUT_RESULT_TYPE __OSLUT_TEST_NAME(oslut_test_, __COUNTER__)\
(char* __oslut_file, long* __oslut_line, char* __oslut_name) { strcpy(__oslut_name, name);\
*__oslut_line = __LINE__; strcpy(__oslut_file, __FILE__);

// assert methods:

// is true (a condition)
#define IS_TRUE(condition) if (!(condition)) { *__oslut_line = __LINE__;\
return __OSLUT_FAILURE; }

// is false (a condition)
#define IS_FALSE(condition) if ((condition)) { *__oslut_line = __LINE__;\
return __OSLUT_FAILURE; }

#define SUCCESS return __OSLUT_SUCCESS;
#define FAIL return __OSLUT_FAILURE;

// test footer
#define ENDTEST return __OSLUT_SUCCESS; } }

#endif // __oslut_h