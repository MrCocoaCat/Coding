# 定义一个空类
class Student():
    pass


class PythonStudent():
    name = None
    age = 18

    def myfun(self):
        print("do homework")
        return None

wang = PythonStudent()
print(wang.age)

print(PythonStudent.__dict__)




