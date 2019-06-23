from django.contrib import admin
from django.conf import settings
from django.urls import include, path
from django.conf.urls import url
from .views import *

urlpatterns = [
    path('get_season/<int:season>/',views.SeasonsView.as_view(),name='get_season_details'),
    path('get_match/<int:match_id>/',views.MatchView.as_view(),name='get_match_details'),
]