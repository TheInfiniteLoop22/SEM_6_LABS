from django.db import models

class Student(models.Model):
    student_id = models.CharField(max_length=20, primary_key=True)
    student_name = models.CharField(max_length=100)
    course_name = models.CharField(max_length=100)
    dob = models.DateField() # Date of Birth field [cite: 400]

    def __str__(self):
        return self.student_name