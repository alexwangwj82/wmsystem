#pragma once
#include <iostream>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include <fstream>
#define FILENAME "empFile.txt"

class WorkerManager {
public:
	//构造函数
	WorkerManager();

	//析构函数
	~WorkerManager();

	//显示职工信息
	void showMenu();

	//退出系统
	void exitSystem();

	//保存文件
	void save();

	//职工数量
	int mEmpNum;

	//判断文件是否为空标志
	bool mFileIsEmpty;

	//统计员工人数
	int getEmpNum();

	//职工数组指针
	Worker** mEmpArray;

	//添加员工
	void addEmployee();

	//初始化员工
	void initEmp();

	//显示职工
	void showEmp();

	//删除职工
	void delEmp();

	//判断职工是否存在
	int empExists(int id);
};