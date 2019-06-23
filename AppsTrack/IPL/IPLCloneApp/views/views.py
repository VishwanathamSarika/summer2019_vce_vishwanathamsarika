from django.shortcuts import render, get_object_or_404
from django.db.models import Sum,Count
from django.views import View
from IPLCloneApp.models import *

# Create your views here.

class SeasonsView(View):
    def get(self,request,*args,**kwargs):
        if kwargs:
            number_of_seasons = list(range(2019,2008,-1))
            season_details=matches.objects.filter(season=kwargs.get('season')).values_list('city','team1','team2',
                                                                                           'toss_winner','toss_decision',
                                                                                           'winner','player_of_match','id')
            return render(request,
                          'IPLCloneApp/season_details.html',
                          {'season_details':season_details,
                           'number_of_seasons':number_of_seasons})
        else :
            season_details = matches.objects.filter(season=2019).values_list('city', 'team1', 'team2',
                                                                                             'toss_winner',
                                                                                             'toss_decision',
                                                                                             'winner',
                                                                                             'player_of_match')
            return render(request,
                          'IPLCloneApp/season_details.html',
                          {'season_details': season_details})
    pass

class MatchView(View):
    def get(self, request, *args, **kwargs):
        if kwargs:
            match=matches.objects.filter(id=kwargs.get('match_id')).values_list('team1', 'team2',
                                                                                'toss_winner',
                                                                                'toss_decision',
                                                                                'winner',
                                                                                'win_by_runs','player_of_match')
            match_details1=deliveries.objects.filter(match_id=kwargs.get('match_id'),inning=1).values_list('over','ball',
                                                                                                 'batsman','non_striker',
                                                                                                 'bowler','total_runs',)
            match_details2 = deliveries.objects.filter(match_id=kwargs.get('match_id'), inning=2).values_list('over',
                                                                                                              'ball',
                                                                                                              'batsman',
                                                                                                              'non_striker',
                                                                                                              'bowler',
                                                                                                              'total_runs', )

            top_scorers1=deliveries.objects.filter(match_id=kwargs.get('match_id'),inning=1).values_list('match_id', 'batsman').annotate(
                total=Sum('total_runs')).order_by('-total')[:3]
            top_scorers2 = deliveries.objects.filter(match_id=kwargs.get('match_id'), inning=2).values_list('match_id','batsman').annotate(
                total=Sum('total_runs')).order_by('-total')[:3]
            extras=deliveries.objects.filter(match_id=2).values_list('batting_team').annotate(extras=Sum('extra_runs'))
            wicket_takers1=deliveries.objects.filter(match_id=kwargs.get('match_id'),inning=1).values_list('bowler').annotate(total=Count('bowler')).order_by('-total')[:3]
            wicket_takers2 = deliveries.objects.filter(match_id=kwargs.get('match_id'), inning=2).values_list('bowler').annotate(total=Count('bowler')).order_by('-total')[:3]

            return render(request,
                          'IPLCloneApp/match_details.html',
                          {'match_details1':match_details1,
                           'match_details2': match_details2,
                           'match':match[0],
                           'top_scorers1':top_scorers1,
                           'top_scorers2': top_scorers2,
                           'wicket_takers1':wicket_takers1,
                           'wicket_takers2': wicket_takers2,
                           'extras':extras})