//#include <iostream>
//#include <string>
//using namespace std;

//�ڳ����У���Ҫ�����Ķ���ܶ࣬���¶����new����������ʱ����Ҫʹ�ü򵥹���ģʽ��
//���ڶ���Ĵ������������ǲ���Ҫȥ���ĵģ�������ע�ص��Ƕ����ʵ�ʲ�����
//���ԣ�������Ҫ�������Ĵ����Ͳ��������֣���ˣ�������ڵĳ�����չ��ά����



////����
//class Operation
//{
//public:
//    double numberA, numberB;
//    virtual double  getResult()
//    {
//        return 0;
//    }
//};
////�ӷ�
//class addOperation :public Operation
//{
//    double getResult()
//    {
//        return numberA + numberB;
//    }
//};
// 
////����
//class subOperation :public Operation
//{
//    double getResult()
//    {
//        return numberA - numberB;
//    }
//};
////�˷�
//class mulOperation :public Operation
//{
//    double getResult()
//    {
//        return numberA*numberB;
//    }
//};
////����
//class divOperation :public Operation
//{
//    double getResult()
//    {
//        return numberA / numberB;
//    }
//};
////������
//class operFactory
//{
//public:
//    static Operation *createOperation(char c)
//    {
//		//��c#�п����÷�����ȡ���ж�ʱ�õ�switch����ôc++���õ���ɶ�أ�RTTI��
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