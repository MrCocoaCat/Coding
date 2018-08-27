# 封装，多态
class A():
    name = "ttttt"
    # 前面加＂__＂就是私有成员
    __age = 18

    def __init__(self):
        self.name = "aaa"

a = A()
# 不可以访问，其为私有变量
# 其为假私有，只是改名字存储

# print(a.age),会出错
# 通过更改名字可以进行访问
print(a._A__age)


#　封装，对成员对象进行封装
#  公开　public
#  保护　protected
#  私有　private　
