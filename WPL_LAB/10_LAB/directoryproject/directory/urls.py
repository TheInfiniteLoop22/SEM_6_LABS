from django.urls import path
from . import views

urlpatterns = [
    path('', views.home, name='home'),
    path('add-category/', views.add_category, name='add_category'),
    path('add-page/', views.add_page, name='add_page'),
]