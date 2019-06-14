from django.contrib.auth.mixins import LoginRequiredMixin
from django.shortcuts import render, get_object_or_404, redirect
from django.urls import resolve
from django.views import View
from django.views.decorators.csrf import csrf_exempt

from rest_framework import status
from rest_framework.authentication import SessionAuthentication, BasicAuthentication
from rest_framework.decorators import api_view, authentication_classes, permission_classes
from rest_framework.permissions import IsAuthenticated
from rest_framework.response import Response
from rest_framework.parsers import JSONParser
from django.http import Http404
from rest_framework.views import APIView

from django.http import JsonResponse, HttpResponse
from onlineapp.models import *
from onlineapp.forms import *
from onlineapp.college_serializers import *


class CollegeView(LoginRequiredMixin,View):

    authentication_classes = (SessionAuthentication, BasicAuthentication)
    permission_classes = (IsAuthenticated,)

    login_url = '/login/'

    def get(self,request,*args,**kwargs):

        user_permissions = [permission['name'] for permission in request.user.user_permissions.values('name')]
        print(user_permissions)

        if kwargs:
            college = get_object_or_404(College,**kwargs)
            # students = Student.objects.filter(college_id=kwargs['id']).values('id','name','mocktest1__total').order_by('-mocktest1__total')
            students = college.student_set.order_by('-mocktest1__total')
            return render(request,
                          'onlineapp/studentdetails.html',
                          {'students_list': students,
                                'college': college,
                           'user_permissions':user_permissions,})

        colleges=College.objects.all()
        c = College.objects.values_list('name', 'acronym', 'id')
        return render(request,
                      template_name='onlineapp/allcolleges.html',
                      context={
                          'college':colleges,
                          'colleges_list': c,
                          'user_permissions': user_permissions,
                      })

class AddCollegeView(LoginRequiredMixin,View):
    authentication_classes = (SessionAuthentication, BasicAuthentication)
    permission_classes = (IsAuthenticated,)
    login_url = '/login/'

    def get(self,request,*args,**kwargs):

        user_permissions = [permission['name'] for permission in request.user.user_permissions.values('name')]
        print(user_permissions)

        form=AddCollege()
        header = "Add College"
        if kwargs:
            college=College.objects.get(**kwargs)
            form=AddCollege(instance=college)
            header = "Edit College"
        return render(request,'onlineapp/form_addcollege.html',{'form':form,'header':header,'user_permissions':user_permissions,})

    def post(self,request,**kwargs):
        if resolve(request.path_info).url_name=='delete_college':
            College.objects.get(id=kwargs.get('id')).delete()
            return redirect('get_all_colleges')

        if resolve(request.path_info).url_name=='edit_college':
            college=College.objects.get(pk=kwargs.get('id'))
            form=AddCollege(request.POST,instance=college)
            if form.is_valid():
                form.save()
                return redirect('get_all_colleges')

        form = AddCollege(request.POST)
        if form.is_valid():
            form.save()
            return redirect('get_all_colleges')

class AddStudentView(LoginRequiredMixin,View):
    authentication_classes = (SessionAuthentication, BasicAuthentication)
    permission_classes = (IsAuthenticated,)
    login_url = '/login/'
    def get(self,request,*args,**kwargs):

        user_permissions = [permission['name'] for permission in request.user.user_permissions.values('name')]
        print(user_permissions)

        form=AddStudent()
        form1=AddMarks()
        header="Add Student"
        if kwargs.get('id'):
            student=Student.objects.get(id=kwargs.get('id'))
            marks=MockTest1.objects.get(student=student)
            form=AddStudent(instance=student)
            form1=AddMarks(instance=marks)
            header = "Edit Student"
        return render(request,'onlineapp/form_addstudent.html',{'form':form,'form1':form1,'header':header,'user_permissions':user_permissions,})
        pass

    def post(self,request,**kwargs):
        if resolve(request.path_info).url_name=='delete_student':
            student=Student.objects.get(id=kwargs.get('id'))
            try:
                marks=MockTest1.objects.get(student=student)
                marks.delete()
            except Exception as e:
                pass
            student.delete()
            return redirect('student_details',id=kwargs.get('clg_id'))

        if resolve(request.path_info).url_name=='edit_student':
            student=Student.objects.get(id=kwargs.get('id'))
            form = AddStudent(request.POST,instance=student)
            if form.is_valid():
                try:
                    marks=MockTest1.objects.get(student=student)
                    form1=AddMarks(request.POST,instance=marks)
                    marks.total = sum([int(request.POST['problem' + str(i)]) for i in range(1,5)])
                    if form1.is_valid():
                        form1.save()
                        form.save()
                except Exception as e:
                    pass
            return redirect('student_details', id=kwargs.get('clg_id'))

        student=Student(college=College.objects.get(id=kwargs.get('clg_id')))
        form=AddStudent(instance=student,data=request.POST)
        if form.is_valid():
            form.save()
            marks=MockTest1(student=Student.objects.get(id=student.id))
            form1=AddMarks(instance=marks,data=request.POST)
            marks.total = sum([int(request.POST['problem' + str(i)]) for i in range(1,5)])
            form1.save()
            return redirect('student_details', id=kwargs.get('clg_id'))
    pass

# @api_view(['GET', 'POST'])
# def college_serializeView(request):
#     if request.method == 'GET':
#         colleges = College.objects.all()
#         serializer = CollegeSerializer(colleges, many=True)
#         return JSONResponse(serializer.data)
#
#     elif request.method == 'POST':
#         serializer = CollegeSerializer(data=request.data)
#         if serializer.is_valid():
#             serializer.save()
#             return JSONResponse(serializer.data, status=status.HTTP_201_CREATED)
#         return JSONResponse(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

@csrf_exempt
@api_view(['GET','POST'])
@authentication_classes((SessionAuthentication, BasicAuthentication))
@permission_classes((IsAuthenticated,))
def college_serializeView(request):
    if request.method == 'GET':
        colleges = College.objects.all()
        serializer = CollegeSerializer(colleges, many=True)
        return JsonResponse(serializer.data, safe=False)

    elif request.method == 'POST':
        data = JSONParser().parse(request)
        serializer = CollegeSerializer(data=data)
        if serializer.is_valid():
            serializer.save()
            return JsonResponse(serializer.data, status=201)
        return JsonResponse(serializer.errors, status=400)

@csrf_exempt
@api_view(['GET','PUT','DELETE'])
@authentication_classes((SessionAuthentication, BasicAuthentication))
@permission_classes((IsAuthenticated,))
def college_modify_serializeView(request,**kwargs):
    try:
        college = College.objects.get(**kwargs)
    except College.DoesNotExist:
        return HttpResponse(status=404)

    if request.method == 'GET':
        serializer = CollegeSerializer(college)
        return JsonResponse(serializer.data)

    elif request.method == 'PUT':
        data = JSONParser().parse(request)
        serializer = CollegeSerializer(college, data=data)
        if serializer.is_valid():
            serializer.save()
            return JsonResponse(serializer.data)
        return JsonResponse(serializer.errors, status=400)

    elif request.method == 'DELETE':
        college.delete()
        return HttpResponse(status=204)

class students_serializeView(APIView):
    authentication_classes = (SessionAuthentication, BasicAuthentication)
    permission_classes = (IsAuthenticated,)
    def get(self, request,*args, **kwargs):
        colleges = College.objects.get(id=kwargs['cid'])
        students = Student.objects.filter(college=colleges)
        serializer = StudentSerializer(students, many=True)
        return JsonResponse(serializer.data, safe=False)

    def post(self, request,*args, **kwargs):
        college = College.objects.get(id=kwargs['cid'])
        student=Student(college=college)
        serializer=StudentSerializer(student,data=request.data)
        if serializer.is_valid():
            serializer.save()
        else:
            return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

        data = serializer.data
        marks=MockTest1(student=student)
        serializer_marks=MockTestSerializer(marks,data=request.data["mocktest1"])
        if serializer_marks.is_valid():
            serializer_marks.save()
            data.update({"mocktest1":serializer_marks.data})
            return Response(data, status=status.HTTP_201_CREATED)
        else:
            return Response(serializer_marks.errors, status=status.HTTP_400_BAD_REQUEST)

class students_details_serializeView(APIView):
    authentication_classes = (SessionAuthentication, BasicAuthentication)
    permission_classes = (IsAuthenticated,)
    def get(self, request,*args, **kwargs):
        student = Student.objects.filter(id=kwargs['id'])
        serializer = StudentSerializer(student, many=True)
        return JsonResponse(serializer.data, safe=False)

    def put(self, request,*args, **kwargs):
        student=Student.objects.get(id=kwargs['id'])
        serializer=StudentSerializer(student,data=request.data)
        if serializer.is_valid():
            serializer.save()
        else:
            return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

        data = serializer.data
        marks=MockTest1.objects.get(student=student)
        serializer_marks=MockTestSerializer(marks,data=request.data["mocktest1"])
        if serializer_marks.is_valid():
            serializer_marks.save()
            data.update({"mocktest1":serializer_marks.data})
            return Response(data, status=status.HTTP_201_CREATED)
        else:
            return Response(serializer_marks.errors, status=status.HTTP_400_BAD_REQUEST)

    def delete(self,request,*args,**kwargs):
        student = Student.objects.filter(id=kwargs['id']).delete()
        return HttpResponse(status=204)