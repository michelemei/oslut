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

Author: Michele Mei
E-Mail: michele.mei@gmail.com

*******************************************************************************/
#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <sstream>
#include "pugixml.hpp"
#include <ctime>

using namespace pugi;

// test function proptotype
typedef bool (__cdecl *f_test)(char* __oslut_file, long* __oslut_line, char* __oslut_name);

void run(const wchar_t* dll_filename, const wchar_t* result_filename)
{
	std::wstring dllname_wstring(dll_filename);
	std::string dllname_string(dllname_wstring.begin(), dllname_wstring.end());
	
	HINSTANCE hGetProcIDDLL = LoadLibrary(dll_filename);
	if (!hGetProcIDDLL)
	{
		return;
	}

	xml_document doc;
	doc.load_file(result_filename);
	
	xml_node node = doc.append_child("module_test");
	xml_attribute name = node.append_attribute("name");
	name.set_value(dllname_string.c_str());
	xml_attribute date = node.append_attribute("date");
	
	time_t now = time(nullptr);
	tm *ltm = localtime(&now);

	std::stringstream ss_time;
	ss_time << ltm->tm_mday;
	ss_time << "/" << ltm->tm_mon + 1;
	ss_time << "/" << ltm->tm_year + 1900;
	ss_time << " " << ltm->tm_hour;
	ss_time << ":" << ltm->tm_min + 1;
	ss_time << ":" << ltm->tm_sec + 1;
	date.set_value(static_cast<const char*>(ss_time.str().c_str()));

	unsigned int succeded = 0;
	unsigned int fail = 0;

	unsigned int t = 0;
	f_test test_function;
	char __osltu_file[1024];
	long __osltu_line;
	char __osltu_name[2048];
	do {
		// test name
		std::stringstream ss;
		ss << "oslut_test_" << t++;
		std::string oslut_test_number = ss.str();

		test_function = (f_test)GetProcAddress(hGetProcIDDLL,
		                                       oslut_test_number.c_str());
		if (test_function)
		{
			xml_node testnode = node.append_child("test");

			// result
			xml_attribute testname_attr = testnode.append_attribute("name");
			xml_attribute testresult_attr = testnode.append_attribute("result");

			try
			{
				if (test_function(__osltu_file, &__osltu_line, __osltu_name))
				{
					testresult_attr.set_value("succeded");
					++succeded;
				}
				else
				{
					testresult_attr.set_value("failure");

					xml_attribute file_attr = testnode.append_attribute("file");
					file_attr.set_value(static_cast<const char*>(__osltu_file));
				
					xml_attribute line_attr = testnode.append_attribute("line");
					line_attr.set_value(__osltu_line);
					++fail;
				}
			}
			catch(std::exception e)
			{
				testresult_attr.set_value("failure");
				xml_attribute msg_attr = testnode.append_attribute("msg");
				msg_attr.set_value("exception");

				xml_attribute what_attr = testnode.append_attribute("what");
				what_attr.set_value(e.what());

				++fail;
			}
			catch(...)
			{
				testresult_attr.set_value("failure");
				xml_attribute msg_attr = testnode.append_attribute("msg");
				msg_attr.set_value("exception");

				xml_attribute what_attr = testnode.append_attribute("what");
				what_attr.set_value("not standard exception");

				++fail;
			}

			// name
			testname_attr.set_value(static_cast<const char*>(__osltu_name));
		}
	} while(test_function);

	xml_attribute succeded_attr = node.append_attribute("succeded");
	succeded_attr.set_value(succeded);
	xml_attribute failures_attr = node.append_attribute("failures");
	failures_attr.set_value(fail);

	doc.save_file(result_filename);

	FreeLibrary(hGetProcIDDLL);
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc < 3)
	{
		printf("Usage:\n   oslut.exe mydll.dll report.xml");
		return 0;
	}
	try
	{
		run(argv[1], argv[2]);
	}
	catch(...)
	{
		printf("crash!");
	}
	return 0;
}