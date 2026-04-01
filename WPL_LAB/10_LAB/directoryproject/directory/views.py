from django.shortcuts import render, redirect
from .models import Category, Page
from .forms import CategoryForm, PageForm

def home(request):
    categories = Category.objects.all()
    pages = Page.objects.all()
    return render(request, 'home.html', {
        'categories': categories,
        'pages': pages
    })

def add_category(request):
    if request.method == 'POST':
        form = CategoryForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('home')
    else:
        form = CategoryForm()
    return render(request, 'add_category.html', {'form': form})

def add_page(request):
    if request.method == 'POST':
        form = PageForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('home')
    else:
        form = PageForm()
    return render(request, 'add_page.html', {'form': form})