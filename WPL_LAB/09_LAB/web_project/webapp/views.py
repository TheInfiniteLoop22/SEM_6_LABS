from django.shortcuts import render

def register(request):
    return render(request, 'register.html')

def success(request):
    if request.method == 'POST':
        # Extract data from the POST request
        username = request.POST.get('username')
        email = request.POST.get('email')
        contact = request.POST.get('contact')
        
        context = {
            'username': username,
            'email': email,
            'contact': contact
        }
        return render(request, 'success.html', context)
    return render(request, 'register.html') # Redirect back if accessed directly