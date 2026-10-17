#include "workerManager.h"
#include <limits>
using namespace std;
using std::cout;

WorkerManager::WorkerManager() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //读文件

	//1、如果文件不存在
	if (!ifs.is_open())			
	{
		cout << "文件不存在" << endl;
		//初始化属性
		this->mEmpNum = 0;
		this->mEmpArray = NULL;
		this->mFileIsEmpty = true;

		ifs.close();
		return;
	}

	//2、如果文件存在
	char ch;
	ifs >> ch;

	
	if (ifs.eof())  //如果文件为空
	{
		cout << "文件为空，无员工数据" << endl;

		//初始化属性
		this->mEmpNum = 0;
		this->mEmpArray = NULL;
		this->mFileIsEmpty = true;

		ifs.close();
		return;
	}

	//3、文件存在且不为空
	this->mEmpNum = this->getEmpNum();  //获取职工人数
	cout << "文件中共有" << this->mEmpNum << "名职工" << endl;
	this->mEmpArray = new Worker * [this->mEmpNum]; //开辟数组空间，存放职工指针
	this->initEmp(); //初始化职工

	//测试代码，显示职工信息
	/*for (int i = 0; i < this->mEmpNum; i++) {
		cout << "职工编号：" << this->mEmpArray[i]->mId
			<< "\t职工姓名：" << this->mEmpArray[i]->mName
			<< "\t岗位：" << this->mEmpArray[i]->mDeptId << endl;
	}*/
}

WorkerManager::~WorkerManager() {
	if (this->mEmpArray != NULL) {
		delete[] this->mEmpArray;
		this->mEmpArray = NULL;
	}
}

void WorkerManager::showMenu() {
	cout << "*******************************************" << endl;
	cout << "********** 欢迎使用职工管理系统！**********" << endl;
	cout << "************* 0.退出管理程序 **************" << endl;
	cout << "************* 1.增加职工信息 **************" << endl;
	cout << "************* 2.显示职工信息 **************" << endl;
	cout << "************* 3.删除离职职工 **************" << endl;
	cout << "************* 4.修改职工信息 **************" << endl;
	cout << "************* 5.查找职工信息 **************" << endl;
	cout << "************* 6.按照编号排序 **************" << endl;
	cout << "************* 7.清空所有文档 **************" << endl;
	cout << "*******************************************" << endl;
	cout << endl;
}

//退出系统
void WorkerManager::exitSystem() {
	cout << endl;
	cout << "退出系统，欢迎下次使用。" << endl;
	system("pause");
	exit(0);
}

//添加员工
void WorkerManager::addEmployee() {
	cout << "请输入要添加员工的数量" << endl;
	int addNum = 0; //保存添加员工的数量

	cin >> addNum;
	if (addNum > 0) {
		int newSize = this->mEmpNum + addNum;

		//开辟新空间
		Worker** newSpace = new Worker* [newSize];
		for (int i = 0; i < newSize; ++i) {
			newSpace[i] = nullptr;
		}

		//将原来空间下数据，拷贝到新空间下
		if (this->mEmpArray != NULL) {
			for (int i = 0; i < this->mEmpNum; i++) {
				newSpace[i] = this->mEmpArray[i];
			}
		}

		//批量添加新数据
		for (int i = 0; i < addNum; i++) {
			int id; //职工编号
			string name; //职工姓名
			int deptId; //部门编号
			Worker* worker = NULL;

			cout << "请输入第" << i + 1 << "个新职工编号：" << endl;
			cin >> id;

			cout << "请输入第" << i + 1 << "个新员工的姓名：" << endl;
			cin >> name;

			while (true) {
				cout << "请输入部门编号，1. 员工 2. 经理 3. 老板" << endl;
				cin >> deptId;

				switch (deptId) {
				case 1:
					worker = new Employee(id, name, deptId);
					break;
				case 2:
					worker = new Manager(id, name, deptId);
					break;
				case 3:
					worker = new Boss(id, name, deptId);
					break;
				default:
					cout << "输入数据有误，请输入1/2/3之间的整数" << endl;
					continue;
				}
				break;
			}
			
			//将创建职工指针，保存到数组中
			newSpace[this->mEmpNum + i] = worker;
		}

		//在所有新数据填充完成后，再释放原有空间并替换指针
		if (this->mEmpArray != NULL) {
			delete[] this->mEmpArray;
			this->mEmpArray = nullptr;
		}

		//更改新空间的指向
		this->mEmpArray = newSpace;

		//更新新的职工人数
		this->mEmpNum = newSize;

		//提示添加成功
		cout << "成功添加了" << addNum << "名新员工" << endl;
		cout << "现在共有" << mEmpNum << "名员工" << endl;

		//将数据保存到文件
		this->save();

		//更改标志状态，文件不为空
		this->mFileIsEmpty = false;
		
	}
	else
	{
		cout << "输入有误，请输入大于0的整数。" << endl;
	}
}

//保存文件
void WorkerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	//遍历数组，写入每个员工的id，姓名以及部门编号
	for (int i=0; i < this->mEmpNum ; i++) {
		ofs << this->mEmpArray[i]->mId << " "
			<< this->mEmpArray[i]->mName << " "
			<< this->mEmpArray[i]->mDeptId << endl;
	}
	//关闭文件
	ofs.close();
}

int  WorkerManager::getEmpNum() {
	ifstream  ifs;
	ifs.open(FILENAME, ios::in); //读文件

	int id, dId; string name;
	int num = 0; //记录人数

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//统计人数
		num++;
	}
	return num;
}
//初始化员工
void WorkerManager::initEmp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //读文件

	int id, dId; string name;
	int  index = 0; //数组下标
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		if (dId == 1) {  //员工
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) {  //经理
			worker = new Manager(id, name, dId);
		}
		else {  //老板
			worker = new Boss(id, name, dId);
		}

		this->mEmpArray[index] = worker; //保存到数组中
		index++; //下标++
	}
}
//显示职工
void WorkerManager::showEmp() {
	if (this->mFileIsEmpty) { //文件不存在或记录为空
		cout << "文件不存在或记录为空" << endl;
	}
	else //文件存在且记录不为空
		{
			for(int i = 0; i < this->mEmpNum; i++){ 
				this->mEmpArray[i]->showInfo(); //多态调用接口，显示员工信息
		}
	}

	//暂停系统，按任意键继续
	system("pause");
	system("cls");
}

//删除职工
void WorkerManager::delEmp() {
	if (mFileIsEmpty) {
		cout << "文件不存在或者文件为空，无法删除" << endl;
	}
	else
	{
		cout << "请输入要删除职工的id：" << endl;
		int id = 0;
		cin >> id;
		int index = this->empExists(id);
		if (index != -1) {
			for (int i = index; i < this->mEmpNum - 1; i++) {
				this->mEmpArray[i] = this->mEmpArray[i + 1];
			}
			this->mEmpNum--;
			cout << "成功删除编号为" << id << "的员工！" << endl;
			this->save();
		}
		else
			cout << "删除失败，输入的id不存在。" << endl;
	}
	system("pause");
	system("cls");
}

//判断职工是否存在
int WorkerManager::empExists(int id) {
	int index = -1; //数组下标
	for (int i = 0; i < this->mEmpNum; i++) {
		if (this->mEmpArray[i]->mId == id) { //找到职工
			index = i; //拿到下标
			break;
		}
	}
	return index; //返回下标
}

//修改职工信息
void WorkerManager::modifyEmp() {
	if (this->mFileIsEmpty) {
		cout << "文件不存在或者记录为空！" << endl;
	}
	else //文件存在且有数据
	{
		cout << "请输入修改员工的编号：" << endl;
		int id = 0;
		cin >> id;
		int index = this->empExists(id);
		if (index != -1) { //找到员工
			delete this->mEmpArray[index];
			int newId = 0;
			string newName = "";
			int newDeptId = 0;
			cout << "找到id号为" << id << "的员工，请输入新的员工id：" << endl;
			cin >> newId;
			cout << "请输入新的姓名：" << endl;
			cin >> newName;
			cout << "请输入新的岗位：1、员工 2、经理 3、老板：" << endl;
			cin >> newDeptId;

			Worker* worker = NULL;
			switch (newDeptId) {
			case 1:
				worker = new Employee(newId, newName, newDeptId);
				break;
			case 2:
				worker = new Manager(newId, newName, newDeptId);
				break;
			case 3:
				worker = new Boss(newId, newName, newDeptId);
				break;
			default:
				break;
			}

			this->mEmpArray[index] = worker; //更新员工信息到数组中
			cout << "数据修改成功！" << endl;
			this->save();
		}
		else  //没找到员工
			cout << "修改失败，未找到员工" << endl;
	}

	system("pause");
	system("cls");
}

//查找职工
void WorkerManager::findEmp() {
	if (this->mFileIsEmpty) {
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入查找职工的方式：1、按编号查找 2、按姓名查找：" << endl;
		int selection = 0;
		if (!(cin >> selection)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "输入选项有误！请输入1或2 " << endl;
			return;
		}
		switch (selection) 
		{
			case 1: //按编号
			{
				int id = 0;
				int index = 0;
				cout << "请输入职工的编号：" << endl;
				cin >> id;
				index = this->empExists(id);
				if (index != -1) { //如果找到
					cout << "查找成功！该职工的信息如下：" << endl;
					this->mEmpArray[index]->showInfo();
				}
				else {
					cout << "未能找到编号为" << id << "的员工" << endl;
				}
				system("pause");
				system("cls");
				break;
			}
		
			case 2: //按姓名
			{
				cout << "请输入职工的姓名：" << endl;
				string name = "";
				cin >> name;
				bool flag = false;
				for (int j = 0; j < this->mEmpNum; j++) {
					if (this->mEmpArray[j]->mName == name) { //找到
						flag = true;
						cout << "查找成功！该员工信息如下：" << endl;
						this->mEmpArray[j]->showInfo();
					}
				}
				if (flag == false) { //没找到
					cout << "查无此人！" << endl;
				}
				system("pause");
				system("cls");
				break;
			}

			default: //输入错误
			{
				cout << "输入选项有误！请输入1或2 " << endl;
				system("pause");
				system("cls");
				break;
			}
		}
	}
}

//排序职工
void WorkerManager::sortEmp() {
	if (mFileIsEmpty) {
		cout << "文件不存在或记录为空！无需排序。" << endl;
	}
	else {
		int selection = 0;
		cout << "请输入排序方式，1、升序，2、降序：" << endl;
		cin >> selection;
		if (selection == 1) { //升序
			for (int i = 0; i < mEmpNum - 1; i++) {
				for (int j = 0; j < mEmpNum - 1 - i; j++) {
					if (mEmpArray[j]->mId > mEmpArray[j + 1]->mId) {
						Worker* temp = mEmpArray[j];
						mEmpArray[j] = mEmpArray[j + 1];
						mEmpArray[j + 1] = temp;
					}
				}
			}
		}
		else if(selection==2){ //降序
			for (int i = 0; i < mEmpNum - 1; i++) {
				for (int j = 0; j < mEmpNum - 1 - i; j++) {
					if (mEmpArray[j]->mId < mEmpArray[j + 1]->mId) {
						Worker* temp = mEmpArray[j];
						mEmpArray[j] = mEmpArray[j + 1];
						mEmpArray[j + 1] = temp;
					}
				}
			}
		}
		else {
			cout << "输入选项有误！" << endl;
		}
		cout << "排序成功，排序后的结果为：" << endl;
		this->showEmp();
		this->save(); //保存排序后的结果到文件
	}
}