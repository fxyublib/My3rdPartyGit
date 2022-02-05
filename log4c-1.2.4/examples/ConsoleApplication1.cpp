// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "log4c.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\lib\\Win32\\Debug\\log4cd.lib")
#else
#pragma comment(lib, "..\\lib\\Win32\\Release\\log4c.lib")
#endif

int main()
{
    std::cout << "Hello World!\n";
	log4c_init();

	log4c_category_t* mylog = log4c_category_get("framework");
	log4c_category_log(mylog, LOG4C_PRIORITY_DEBUG, "Hello World!");

	log4c_category_t* mycat = NULL;
	mycat = log4c_category_get("six13log.log.app.application2");

	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG, "Debugging app 2");
	log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
		"some error from app2 at line %d in file %s",
		__LINE__, __FILE__);

	log4c_fini();
}
