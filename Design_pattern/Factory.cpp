//#include <iostream>
//#include <string>
//
//using namespace std;
//
//class ExportFileApi {
//public:
//	virtual bool exportData(string Data) = 0;
//
//protected:
//	ExportFileApi(){}
//};
//
////具体化的子类
//class ExportTxtFile :public ExportFileApi {
//public:
//	bool exportData(string data)
//	{
//		cout << "正在导出数据" << data << "到csv文件" << endl;
//		return true;
//	}
//};
//
////生产数据到数据库
//class ExportDB :public ExportFileApi {
//public:
//	bool exportData(string data)
//	{
//		cout << "正在导出数据" << data << "到数据库" << endl;
//		return true;
//	}
//};
//
////实现一个ExportOperate,这个叫导出数据的业务功能对象
//class ExportOperate {
//public:
//	bool exportData(string data)
//	{
//		ExportFileApi* pApi = factoryMethod();
//		return pApi->exportData(data);
//	}
//protected:
//	virtual ExportFileApi* factoryMethod() = 0;
//};
//
////具体的实现对象，完成导出工作
//class ExportTxtFileOperate : public ExportOperate {
//protected:
//	ExportFileApi* factoryMethod()
//	{
//		return new ExportTxtFile();
//	}
//};
//
//class ExportDBOperate : public ExportOperate {
//protected:
//	ExportFileApi* factoryMethod()
//	{
//		return new ExportDB;
//	}
//};
//int main()
//{
//	ExportOperate* pOperate = new ExportTxtFileOperate();
//	pOperate->exportData("haha");
//	system("pause");
//	return 0;
//}