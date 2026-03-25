from django.shortcuts import render

def feedback_view(request):
    context = {}
    if request.method == 'POST':
        name = request.POST.get('name')
        sex = request.POST.get('sex')
        
        # Logic to match the "Thanks Miss. Niveditha" format
        salutation = "Mr." if sex == "Male" else "Miss."
        
        context = {
            'submitted': True,
            'message': f"Thanks {salutation} {name} for your feedback."
        }
    
    return render(request, 'feedback.html', context)