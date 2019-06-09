from django.db import models

# Create your models here.

class todolist(models.Model):
    name=models.CharField(max_length=128)
    created=models.DateTimeField(auto_now_add=True,auto_now=False)

    def __str__(self):
        return self.name

class todoitem(models.Model):
    description=models.TextField()
    due_date=models.DateTimeField(null=True)
    completed=models.BooleanField()

    todo_list=models.ForeignKey(todolist,on_delete=models.CASCADE,default="1")

    def __str__(self):
        return self.description
