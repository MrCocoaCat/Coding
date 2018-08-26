# 定义一个空类
class Student():
    pass


class PythonStudent():
    name = None
    age = 18
    # self 相当于 this 函数

    def myfun(self):
        print("do homework")
        self.age = 23
        return None


wang = PythonStudent()
print(wang.age)
print(PythonStudent.__dict__)
print(" ")
print(wang.__dict__)

wang.age = 19
print(wang.__dict__)

wang.myfun()
print(wang.age)



