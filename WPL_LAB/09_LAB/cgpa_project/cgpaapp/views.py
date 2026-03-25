from django.shortcuts import render, redirect

def page1(request):
    if request.method == 'POST':
        # Get data from form
        name = request.POST.get('name')
        marks = request.POST.get('marks')

        # Calculate CGPA
        cgpa = float(marks) / 50

        # Store in Sessions
        request.session['user_name'] = name
        request.session['user_cgpa'] = cgpa

        return redirect('page2')
    
    return render(request, 'page1.html')

def page2(request):
    # Retrieve data from Sessions
    name = request.session.get('user_name', 'Guest')
    cgpa = request.session.get('user_cgpa', 0)
    
    return render(request, 'page2.html', {'name': name, 'cgpa': cgpa})