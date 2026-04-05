from django.shortcuts import render, redirect
from .models import Student
from .forms import StudentForm

def student_entry(request):
    # Retrieve all student records for display [cite: 469]
    students = Student.objects.all()
    form = StudentForm()

    if request.method == 'POST':
        form = StudentForm(request.POST)
        if form.is_valid():
            form.save() # Save the data into the db [cite: 463, 539]
            return redirect('student_entry')

    return render(request, 'student_page.html', {
        'form': form,
        'students': students
    })