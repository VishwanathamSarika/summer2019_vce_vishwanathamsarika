from rest_framework import serializers
from onlineapp.models import *

class CollegeSerializer(serializers.ModelSerializer):
    class Meta:
        model=College
        fields=('name','location','acronym','contact')


class StudentSerializer(serializers.ModelSerializer):
    class Meta:
        model=Student
        fields=('name','email','db_folder','dropped_out')


class MockTestSerializer(serializers.ModelSerializer):
    class Meta:
        model=MockTest1
        fields=('problem1','problem2','problem3','problem4','total')

# class StudentdetaillsSerializer(serializers.ModelSerializer):
#     mocktest1=MockTestSerializer(read_only=False,many=False)
#     class Meta:
#         model=Student
#         fields=('name','dob','email','db_folder','dropped_out','mocktest1')



