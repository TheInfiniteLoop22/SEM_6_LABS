from django.shortcuts import render, redirect
from .models import Institute
from .forms import InstituteForm

# View to display the list box
def home(request):
    institutes = Institute.objects.all()
    return render(request, 'home.html', {'institutes': institutes})

# View to populate the database manually
def add_institute(request):
    if request.method == 'POST':
        form = InstituteForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('home')
    else:
        form = InstituteForm()
    return render(request, 'add_institute.html', {'form': form})