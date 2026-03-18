from django.urls import path
from . import views

urlpatterns = [
    path('', views.firstPage, name='first'),
    path('submit/', views.secondPage, name='submit'),
    path('back/', views.goBack, name='back'),
]