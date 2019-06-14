from django.contrib import messages
from django.contrib.auth.models import User
from django.shortcuts import render, get_object_or_404, redirect
from django.urls import resolve
from django.views import View
from onlineapp.forms import *
from django.contrib.auth import authenticate,login,logout

class LoginController(View):
    def get(self,request):
        login_form=LoginForm()
        if request.user.is_authenticated:
            return redirect('get_all_colleges')
        return render(request,'onlineapp/form_login.html',{'form':login_form})

    def post(self,request):
        login_form=LoginForm(request.POST)
        if login_form.is_valid():
            user=authenticate(request,
                              username=login_form.cleaned_data['username'],
                              password=login_form.cleaned_data['password'])
            if user is not None:
                login(request, user)
                return redirect('get_all_colleges')
            else:
                messages.error(request, 'Invalid credentials')
        return render(request,
                    template_name='onlineapp/form_login.html',
                    context={'form': login_form})


class SignUpController(View):
    def get(self,request):
        signup_form=SignUpForm()
        if request.user.is_authenticated:
            return redirect('get_all_colleges')
        return render(request, 'onlineapp/form_signup.html', {'form': signup_form})

    def post(self,request):
        signup_form=SignUpForm(request.POST)
        if signup_form.is_valid():
            newUser=User.objects.create_user(**signup_form.cleaned_data)
            newUser.save()
            if newUser is not None:
                login(request,newUser)
                return redirect('get_all_colleges')
            else:
                messages.error(request,'Invalid credentials')
        return render(request,
                    template_name='onlineapp/from_signup.html',
                    context={'form': signup_form})


def LogOutView(request):
    logout(request)
    return redirect('login_form')