from django.contrib import admin

# Register your models here.
from IPLCloneApp import models

admin.site.register(models.deliveries)
admin.site.register(models.matches)