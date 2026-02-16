from django.shortcuts import render

def label_view(request):
    context = {}

    if request.method == "POST":
        name = request.POST.get('name')
        message = request.POST.get('message')
        color = request.POST.get('color')

        bold = request.POST.get('bold')
        italic = request.POST.get('italic')
        underline = request.POST.get('underline')

        full_message = f"{name} - {message}"

        style = ""

        if color:
            style += f"color:{color};"

        if bold:
            style += "font-weight:bold;"

        if italic:
            style += "font-style:italic;"

        if underline:
            style += "text-decoration:underline;"

        context = {
            'full_message': full_message,
            'style': style
        }

    return render(request, 'label.html', context)
