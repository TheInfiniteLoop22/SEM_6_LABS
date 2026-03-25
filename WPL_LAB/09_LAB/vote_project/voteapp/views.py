from django.shortcuts import render

# Global dictionary to store vote counts (for lab simplicity)
# This data resets whenever the development server restarts.
vote_data = {
    'good': 0,
    'satisfactory': 0,
    'bad': 0,
    'total': 0,
}

def vote_page(request):
    context = {}
    if request.method == 'POST':
        # Get the value from the radio button group named 'choice'
        choice = request.POST.get('choice')
        
        # Verify that a valid choice was submitted
        if choice in ['good', 'satisfactory', 'bad']:
            # Increment the vote count
            vote_data[choice] += 1
            vote_data['total'] += 1

            # Calculate percentages (handle division by zero if total is 0)
            good_pct = (vote_data['good'] / vote_data['total'] * 100) if vote_data['total'] > 0 else 0
            satisfactory_pct = (vote_data['satisfactory'] / vote_data['total'] * 100) if vote_data['total'] > 0 else 0
            bad_pct = (vote_data['bad'] / vote_data['total'] * 100) if vote_data['total'] > 0 else 0

            # Update context with results to display them on the page
            context = {
                'good_pct': round(good_pct, 1),
                'satisfactory_pct': round(satisfactory_pct, 1),
                'bad_pct': round(bad_pct, 1),
                'has_voted': True # Flag to potentially show results section
            }
        else:
             context = {'error_message': 'No choice selected'}

    return render(request, 'voting_page.html', context)