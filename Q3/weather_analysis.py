import ctypes
import csv
import os


lib_path = os.path.join(os.path.dirname(__file__), 'libweatherstats.so')
weather_stats = ctypes.CDLL(lib_path)

weather_stats.calculate_mode.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.c_int]
weather_stats.calculate_mode.restype = ctypes.c_double
weather_stats.calculate_median.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.c_int]
weather_stats.calculate_median.restype = ctypes.c_double
weather_stats.calculate_std_dev.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.c_int]
weather_stats.calculate_std_dev.restype = ctypes.c_double

def analyze_temperatures(file_path):
    temperatures = []
    with open(file_path, 'r') as csvfile:
        csvreader = csv.DictReader(csvfile)
        for row in csvreader:
            try:
                temp = float(row['Data.Temperature.Avg Temp'])
                temperatures.append(temp)
            except (ValueError, KeyError):
                print(f"Skipping invalid temperature entry: {row}")
    
    # C array
    temp_array = (ctypes.c_double * len(temperatures))(*temperatures)
    
    mode = weather_stats.calculate_mode(temp_array, len(temperatures))
    median = weather_stats.calculate_median(temp_array, len(temperatures))
    std_dev = weather_stats.calculate_std_dev(temp_array, len(temperatures))
    
    return {
        'mode': mode,
        'median': median,
        'standard_deviation': std_dev
    }

def main():
    file_path = 'weather.csv'
    results = analyze_temperatures(file_path)
    
    print("Temperature Analysis Results:")
    print(f"Mode Temperature: {results['mode']}")
    print(f"Median Temperature: {results['median']}")
    print(f"Standard Deviation: {results['standard_deviation']}")

if __name__ == "__main__":
    main()