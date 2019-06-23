from django.db import models

# Create your models here.

class matches(models.Model):
    id=models.IntegerField(primary_key=True)
    season=models.IntegerField()
    city=models.CharField(max_length=50,blank=True,null=True)
    date=models.DateField()
    team1=models.CharField(max_length=50)
    team2=models.CharField(max_length=50)
    toss_winner=models.CharField(max_length=50)
    toss_decision=models.CharField(max_length=50)
    result=models.CharField(max_length=50)
    dl_applied=models.BooleanField(default=False)
    winner=models.CharField(max_length=50,blank=True,null=True)
    win_by_runs=models.IntegerField(default=0)
    win_by_wickets=models.IntegerField(default=0)
    player_of_match=models.CharField(max_length=50,blank=True,null=True)
    venue=models.CharField(max_length=100,blank=True,null=True )
    umpire1=models.CharField(max_length=50,blank=True,null=True)
    umpire2=models.CharField(max_length=50,blank=True,null=True)
    umpire3=models.CharField(max_length=50,blank=True,null=True)

    def __str__(self):
        return str(self.id)

class deliveries(models.Model):
    match_id=models.ForeignKey(matches,on_delete=models.CASCADE)
    inning=models.IntegerField()
    batting_team=models.CharField(max_length=50)
    bowling_team=models.CharField(max_length=50)
    over=models.IntegerField()
    ball=models.IntegerField()
    batsman=models.CharField(max_length=50)
    non_striker=models.CharField(max_length=50)
    bowler=models.CharField(max_length=50)
    is_super_over=models.BooleanField(default=False)
    wide_runs=models.IntegerField()
    bye_runs=models.IntegerField()
    legbye_runs=models.IntegerField()
    noball_runs=models.IntegerField()
    penalty_runs=models.IntegerField()
    batsman_runs=models.IntegerField()
    extra_runs=models.IntegerField()
    total_runs=models.IntegerField()
    player_dismissed=models.CharField(max_length=50,blank=True,null=True)
    dismissal_kind=models.CharField(max_length=50,blank=True,null=True)
    fielder=models.CharField(max_length=50,blank=True,null=True)

    def __str__(self):
        return self.match_id

