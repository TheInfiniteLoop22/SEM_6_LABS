from django import forms
from .models import Institute

class InstituteForm(forms.ModelForm):
    class Meta:
        model = Institute
        fields = ['institute_id', 'name', 'no_of_courses']