//#include <iostream>
//#include <string>
//using namespace std;
// 
////1.�����ǵĶ������Ͳ��ǿ�ʼ����ȷ���ģ��������������������ȷ���Ļ�����ô����ͨ��������͵Ķ����¡��һ���µĶ���Ƚ�����һЩ��
////
////2.�е�ʱ��������Ҫһ��������ĳ��״̬�µĸ�������ʱ������ʹ��ԭ��ģʽ����õ�ѡ�����磺һ�����󣬾���һ�δ���֮�����ڲ���״̬�����˱仯�����ʱ��������Ҫһ�����״̬�ĸ��������ֱ��newһ���µĶ���Ļ�����������״̬�ǲ��Եģ���ʱ������ʹ��ԭ��ģʽ����ԭ���Ķ��󿽱�һ���������������ͺ�֮ǰ�Ķ�������ȫһ�µ��ˣ�
////
////3.�����Ǵ���һЩ�Ƚϼ򵥵Ķ���ʱ�����Ҷ���֮��������С�����ܾͼ������Բ�ͬ���ѣ���ô�Ϳ���ʹ��ԭ��ģʽ����ɣ�ʡȥ�˴�������ʱ���鷳�ˣ�
////
////4.�е�ʱ�򣬴�������ʱ�����캯���Ĳ����ܶ࣬���Լ��ֲ���ȫ��֪��ÿ�����������壬�Ϳ���ʹ��ԭ��ģʽ������һ���µĶ��󣬲���ȥ��ᴴ���Ĺ��̡�
////
////->�ʵ���ʱ����һ��ԭ��ģʽ���ܼ��ٶ�Ӧ�Ĺ����������ٳ���ĸ��Ӷȣ����Ч�ʡ�
//
//class Prototype
//{
//private:
//    string str;
//public:
//    Prototype(string s)
//    {
//        str = s;
//    }
//    Prototype()
//    {
//        str = "";
//    }
//    void show()
//    {
//        cout << str << endl;
//    }
//    virtual Prototype *clone() = 0;
//};
// 
//class ConcretePrototype1 :public Prototype
//{
//public:
//    ConcretePrototype1(string s) :Prototype(s)
//    {}
//    ConcretePrototype1(){}
//    virtual Prototype *clone()
//    {
//        ConcretePrototype1 *p = new ConcretePrototype1();
//        *p = *this;
//        return p;
//    }
//};
// 
// 
//class ConcretePrototype2 :public Prototype
//{
//public:
//    ConcretePrototype2(string s) :Prototype(s)
//    {}
//    ConcretePrototype2(){}
//    virtual Prototype *clone()
//    {
//        ConcretePrototype2 *p = new ConcretePrototype2();
//        *p = *this;
//        return p;
//    }
//};
// 
//int main()
//{
//    ConcretePrototype1 *test = new ConcretePrototype1("С��");
//    ConcretePrototype2 *test2 = (ConcretePrototype2 *)test->clone();
//    test->show();
//    test2->show();
//    return 0;
//}