//#include <iostream>
//#include <string>
//using namespace std;

//在程序中，需要创建的对象很多，导致对象的new操作多且杂时，需要使用简单工厂模式；
//由于对象的创建过程是我们不需要去关心的，而我们注重的是对象的实际操作，
//所以，我们需要分离对象的创建和操作两部分，如此，方便后期的程序扩展和维护。



////基类
//class Operation
//{
//public:
//    double numberA, numberB;
//    virtual double  getResult()
//    {
//        return 0;
//    }
//};
////加法
//class addOperation :public Operation
//{
//    double getResult()
//    {
//        return numberA + numberB;
//    }
//};
// 
////减法
//class subOperation :public Operation
//{
//    double getResult()
//    {
//        return numberA - numberB;
//    }
//};
////乘法
//class mulOperation :public Operation
//{
//    double getResult()
//    {
//        return numberA*numberB;
//    }
//};
////除法
//class divOperation :public Operation
//{
//    double getResult()
//    {
//        return numberA / numberB;
//    }
//};
////工厂类
//class operFactory
//{
//public:
//    static Operation *createOperation(char c)
//    {
//		//在c#中可以用反射来取消判断时用的switch，那么c++中用的是啥呢？RTTI？
//        switch (c)
//        {
//        case '+':
//            return new addOperation;
//            break;
// 
//        case '-':
//            return new subOperation;
//            break;
// 
//        case '*':
//            return new mulOperation;
//            break;
// 
//        case '/':
//            return new divOperation;
//            break;
//        }
//    }
//};
// 
//int main()
//{
//    Operation *oper = operFactory::createOperation('+');
//    oper->numberA = 9;
//    oper->numberB = 99;
//    cout << oper->getResult() << endl;
//    return 0;
//}