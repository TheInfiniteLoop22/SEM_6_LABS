from django.shortcuts import render, redirect, get_object_or_404
from .models import Human
from .forms import HumanForm

def human_manage(request):
    humans = Human.objects.all()
    selected_human = None
    form = HumanForm()

    # 1. Handle selection from Dropdown (GET request)
    human_id = request.GET.get('human_id')
    if human_id and human_id.isdigit():
        selected_human = get_object_or_404(Human, id=human_id)
        form = HumanForm(instance=selected_human)

    # 2. Handle Update and Delete (POST request)
    if request.method == 'POST':
        curr_id = request.POST.get('curr_id')
        
        if curr_id:
            instance = get_object_or_404(Human, id=curr_id)
            if 'update' in request.POST:
                form = HumanForm(request.POST, instance=instance)
                if form.is_valid():
                    form.save()
                    return redirect('human_manage')
            elif 'delete' in request.POST:
                instance.delete()
                return redirect('human_manage')
        else:
            # Optional: Allow adding a new record if none is selected
            form = HumanForm(request.POST)
            if form.is_valid():
                form.save()
                return redirect('human_manage')

    return render(request, 'human_manage.html', {
        'humans': humans,
        'form': form,
        'selected_human': selected_human
    })