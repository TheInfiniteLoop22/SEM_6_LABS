from django.urls import path
from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('generate_bill/', views.generate_bill, name='generate_bill'),
]