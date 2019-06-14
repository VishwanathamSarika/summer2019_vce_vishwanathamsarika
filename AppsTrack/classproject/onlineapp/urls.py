from django.contrib import admin
from django.conf import settings
from django.urls import include, path
from django.conf.urls import url
from .views import *

urlpatterns = [
    path('',lambda req: redirect('get_all_colleges',permanent=True)),
    url(r'^get_colleges/$',college.CollegeView.as_view(),name='get_all_colleges'),
    url(r'^get_colleges/(?P<id>\d+)/$',college.CollegeView.as_view(),name="student_details"),
    path('get_colleges/<str:acronym>/',college.CollegeView.as_view(),name="student_details_acr"),

    path('api/v1/colleges',college.college_serializeView),
    path('api/v1/colleges/<int:id>',college.college_modify_serializeView),
    path('api/v1/colleges/<str:acronym>',college.college_modify_serializeView),

    path('api/v1/college/<int:cid>/students',college.students_serializeView.as_view()),
    path('api/v1/college/<str:acronym>/students',college.students_serializeView.as_view()),
    path('api/v1/college/<int:cid>/students/<int:id>',college.students_details_serializeView.as_view()),
    path('api/v1/college/<str:acronym>/students/<int:id>',college.students_details_serializeView.as_view()),


    url(r'^get_college/add/$',college.AddCollegeView.as_view(),name="add_college"),
    url(r'get_college/(?P<id>\d+)/edit',college.AddCollegeView.as_view(),name="edit_college"),
    url(r'get_college/(?P<id>\d+)/delete',college.AddCollegeView.as_view(),name="delete_college"),

    url(r'^get_student/(?P<clg_id>\d+)/add/$',college.AddStudentView.as_view(),name="add_student"),
    url(r'^get_student/(?P<clg_id>\d+)/(?P<id>\d+)/edit',college.AddStudentView.as_view(),name="edit_student"),
    url(r'^get_student/(?P<clg_id>\d+)/(?P<id>\d+)/delete',college.AddStudentView.as_view(),name="delete_student"),

    url(r'login/',LoginController.as_view(),name="login_form"),
    url(r'signup/',SignUpController.as_view(),name="signup_form"),
    url(r'logout/',LogOutView,name="logout_form"),

    url('myfirstview/$',views.MyFirstView,name="first_view")
]

