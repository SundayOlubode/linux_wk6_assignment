gcc -shared -o libweatherstats.so -fPIC weather_stats.c
python3 weather_analysis.py