from django.contrib import admin
from django.conf import settings
from django.urls import include, path
from django.conf.urls import url
from . import views

urlpatterns = [
    path('home/', views.home),
    path('getmyclg/', views.gmc),
    path('getallclg/',views.gac),
    url(r'getstudents/(?P<id>\d+)/$',views.get_students,name="student_details"),
]

