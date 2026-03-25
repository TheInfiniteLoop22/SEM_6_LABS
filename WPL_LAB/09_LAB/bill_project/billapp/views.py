from django.shortcuts import render

def index(request):
    return render(request, 'index.html')

def generate_bill(request):
    if request.method == 'POST':
        brand = request.POST.get('brand')
        # getlist is used for multiple checkboxes
        items = request.POST.getlist('items') 
        quantity = int(request.POST.get('quantity', 1))

        # Simple Price Logic (Base prices)
        brand_prices = {
            'HP': 500, 'Nokia': 200, 'Samsung': 400, 
            'Motorola': 300, 'Apple': 800
        }
        item_multipliers = {'Mobile': 1, 'Laptop': 2.5}

        base_price = brand_prices.get(brand, 0)
        total_amount = 0
        selected_items_summary = []

        for item in items:
            item_price = base_price * item_multipliers.get(item, 1)
            total_amount += item_price * quantity
            selected_items_summary.append(f"{brand} {item}")

        context = {
            'brand': brand,
            'items': ", ".join(selected_items_summary),
            'quantity': quantity,
            'total': total_amount
        }
        return render(request, 'bill.html', context)
    
    return render(request, 'index.html')