from django import forms

from onlineapp.models import *

class AddCollege(forms.ModelForm):
    class Meta:
        model=College
        exclude=['id']
        widgets={'name':forms.TextInput(attrs={'class':'input','placeholder':'Enter College name'}),
                 'location':forms.TextInput(attrs={'class':'input','placeholder':'Enter College Location'}),
                 'acronym': forms.TextInput(attrs={'class': 'input', 'placeholder': 'Enter College Acronym'}),
                 'contact': forms.EmailInput(attrs={'class': 'input', 'placeholder': 'Enter College Contact Info'})}

class AddStudent(forms.ModelForm):
    class Meta:
        model=Student
        exclude=['id','college']
        widgets={'name':forms.TextInput(attrs={'class':'input','placeholder':'Enter Student name'}),
                 'dob':forms.DateInput(attrs={'class':'input','placeholder':'Enter Student DOB'}),
                 'email': forms.EmailInput(attrs={'class': 'input', 'placeholder': 'Enter Student Email'}),
                 'db_folder': forms.TextInput(attrs={'class': 'input', 'placeholder': 'Enter Student dbname'}),
                 'dropped_out':forms.CheckboxInput(attrs={'class':'input'})}

class AddMarks(forms.ModelForm):
    class Meta:
        model=MockTest1
        exclude=['id','student','total']
        widgets = {'problem1': forms.NumberInput(attrs={'class': 'input', 'placeholder': 'Enter marks of Problem 1'}),
                   'problem2': forms.NumberInput(attrs={'class': 'input', 'placeholder': 'Enter marks of Problem 2'}),
                   'problem3': forms.NumberInput(attrs={'class': 'input', 'placeholder': 'Enter marks of Problem 3'}),
                   'problem4': forms.NumberInput(attrs={'class': 'input', 'placeholder': 'Enter marks of Problem 4'}),
                   }


