from django.shortcuts import render, redirect

def firstPage(request):
    return render(request, 'firstPage.html')


def secondPage(request):
    if request.method == "POST":
        name = request.POST.get('name')
        roll = request.POST.get('roll')
        subject = request.POST.get('subject')

        # Validation
        if not name or not roll:
            return render(request, 'firstPage.html', {'error': 'All fields required'})

        if not roll.isdigit():
            return render(request, 'firstPage.html', {'error': 'Roll must be number'})

        # Store in session
        request.session['name'] = name
        request.session['roll'] = roll
        request.session['subject'] = subject

        # DIRECTLY render second page (no redirect)
        return render(request, 'secondPage.html', {
            'name': name,
            'roll': roll,
            'subject': subject,
        })

    return redirect('first')


def goBack(request):
    request.session.flush()
    return redirect('first')