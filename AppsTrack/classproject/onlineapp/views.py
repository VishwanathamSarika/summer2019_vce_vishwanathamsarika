from django.http import HttpResponse
from django.shortcuts import render, get_object_or_404
from .models import *

# Create your views here.

def home(request):
    return render(request,'onlineapp/home.html')

def gmc(request):
    c=College.objects.values('name').filter(acronym="vce")
    return HttpResponse(c)

def gac(request):

    c=College.objects.values_list('name','acronym','id')

    # res="<table border=1 cellspacing=2 cellpadding=5><tr><th>Name</th><th>Acronym</th></tr>"
    # for i in c:
    #     res=res+"<tr><td>"+i[0]+"</td><td>"+i[1]+"</td></tr>"
    # res=res+"</table>"
    # return HttpResponse("<html><body>"+res+"</body></html>")

    return render(request,'onlineapp/allcolleges.html',{'colleges_list':c})

def get_students(request,id):
    college = get_object_or_404(College, pk=id)
    students=Student.objects.filter(college_id=id).values('id','name','mocktest1__total')
    return render(request,'onlineapp/studentdetails.html',{'students_list':students,'college':college})


