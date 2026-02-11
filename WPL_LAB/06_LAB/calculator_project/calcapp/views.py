from django.shortcuts import render

def calculator(request):
    result = None

    if request.method == "POST":
        num1 = int(request.POST.get('num1'))
        num2 = int(request.POST.get('num2'))
        operation = request.POST.get('operation')

        if operation == 'add':
            result = num1 + num2
        elif operation == 'sub':
            result = num1 - num2
        elif operation == 'mul':
            result = num1 * num2
        elif operation == 'div':
            result = num1 / num2 if num2 != 0 else "Cannot divide by zero"

    return render(request, 'calculator.html', {'result': result})
