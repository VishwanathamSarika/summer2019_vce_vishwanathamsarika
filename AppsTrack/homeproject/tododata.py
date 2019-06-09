import os
import django
os.environ.setdefault("DJANGO_SETTINGS_MODULE","homeproject.settings")
django.setup()

from todoapp.models import *

def importdata():
    # for i in range(5):
    #     try:
    #         l=todolist()
    #         l.name="todolist "+str(i)
    #         l.save()
    #         del l
    #     except Exception as e:
    #         del l
    #         print(e)
    #
    # for i in range(5):
    #     try:
    #         item=todoitem()
    #         item.description="todoitem "+str(i)
    #         item.completed=False
    #         item.save()
    #         del item
    #     except Exception as e:
    #         del item
    #         print(e)

    # for j in range(1,5):
    #     for i in range(5):
    #         try:
    #             item=todoitem()
    #             item.description="todoitem "+str(i)
    #             item.completed=False
    #             item.todo_list=todolist.objects.get(id=j)
    #             item.save()
    #             del item
    #         except Exception as e:
    #             del item
    #             print(e)

    for i in range(1,6):
        try:
            item = todoitem()
            item=todoitem.objects.get(id=i)
            item.todo_list=todolist.objects.get(id=5)
            item.save()
            del item
        except Exception as e:
            del item
            print(e)

importdata()
