from django.http import HttpResponse

def MyFirstView(request):
    return HttpResponse("<html><body>My First View</body></html>")