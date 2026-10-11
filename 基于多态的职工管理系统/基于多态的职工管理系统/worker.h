#pragma once
#include <iostream>
using namespace std;
#include <string>

//员工的抽象类
class Worker {
public:
	//员工的编号
	int mId;

	//员工的姓名
	string mName;

	//员工的部门编号
	int mDeptId;
	
	//显示员工信息
	virtual void showInfo() = 0;

	//获取员工岗位
	virtual string getDeptName() = 0;
};