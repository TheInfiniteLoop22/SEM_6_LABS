from django import forms
from .models import Student

class StudentForm(forms.ModelForm):
    class Meta:
        model = Student
        fields = ['student_id', 'student_name', 'course_name', 'dob']
        # Adding a widget to make the DOB field a date picker
        widgets = {
            'dob': forms.DateInput(attrs={'type': 'date'}),
        }