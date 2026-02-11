from django.shortcuts import render

def cover(request):
    context = {}

    if request.method == "POST":
        context = {
            'title': request.POST.get('title'),
            'subtitle': request.POST.get('subtitle'),
            'bgcolor': request.POST.get('bgcolor'),
            'fontcolor': request.POST.get('fontcolor'),
            'fontsize': request.POST.get('fontsize'),
            'image': request.POST.get('image'),
        }

    return render(request, 'cover.html', context)
