from django.urls import path
from . import views

urlpatterns = [
    path('', views.label_view, name='label'),
]
