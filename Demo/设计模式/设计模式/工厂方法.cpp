//#include <iostream>
//#include <string>
//using namespace std;
// 
//class Operation
//{
//public:
//    double numberA, numberB;
//    virtual double  getResult()
//    {
//        return 0;
//    }
//};
// 
//class addOperation :public Operation
//{
//    double getResult()
//    {
//        return numberA + numberB;
//    }
//};
// 
// 
//class subOperation :public Operation
//{
//    double getResult()
//    {
//        return numberA - numberB;
//    }
//};
// 
//class mulOperation :public Operation
//{
//    double getResult()
//    {
//        return numberA*numberB;
//    }
//};
// 
//class divOperation :public Operation
//{
//    double getResult()
//    {
//        return numberA / numberB;
//    }
//};
// 
//class IFactory
//{
//public:
//    virtual Operation *createOperation() = 0;
//};
// 
//class AddFactory :public IFactory
//{
//public:
//    static Operation *createOperation()
//    {
//        return new addOperation();
//    }
//};
// 
// 
//class SubFactory :public IFactory
//{
//public:
//    static Operation *createOperation()
//    {
//        return new subOperation();
//    }
//};
// 
//class MulFactory :public IFactory
//{
//public:
//    static Operation *createOperation()
//    {
//        return new mulOperation();
//    }
//};
// 
//class DivFactory :public IFactory
//{
//public:
//    static Operation *createOperation()
//    {
//        return new divOperation();
//    }
//};
// 
//int main()
//{
//	//MulFactory::createOperation()返回mulOperation()对象，即Operation的子类对象
//    Operation *oper = MulFactory::createOperation();
//    oper->numberA = 9;
//    oper->numberB = 99;
//    cout << oper->getResult() << endl;
//    return 0;
//}