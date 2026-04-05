from django.urls import path
from . import views

urlpatterns = [
    path('', views.human_manage, name='human_manage'),
]