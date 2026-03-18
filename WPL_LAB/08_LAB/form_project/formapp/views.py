from django.shortcuts import render

# Page 1
def index(request):
    return render(request, 'index.html')


# Page 2 (handles form submission)
def result(request):
    if request.method == "POST":
        manufacturer = request.POST.get('manufacturer')
        model = request.POST.get('model')

        error = None

        # ✅ VALIDATION
        if not model or model.strip() == "":
            error = "Model name cannot be empty"

        if error:
            return render(request, 'index.html', {'error': error})

        context = {
            'manufacturer': manufacturer,
            'model': model.strip()
        }

        return render(request, 'result.html', context)

    return render(request, 'index.html')