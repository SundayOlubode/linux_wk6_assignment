gcc -o multi_adder multi_threaded_adder.c -pthread
gcc -o single_adder single_threaded_adder.c


# When the multi-threaded adder is run, the output is as follows:
# 1. When n = 1500,
# CPU Usage:
# User CPU Time: 1689 microseconds
# System CPU Time: 0 microseconds
# Total CPU Time: 1689 microseconds

# 2. When n= 2000,
# CPU Usage:
# User CPU Time: 2790 microseconds
# System CPU Time: 0 microseconds
# Total CPU Time: 2790 microseconds

# When the single-threaded adder is run, the output is as follows:
# 1. When n = 1500,
# CPU Usage:
# User CPU Time: 11 microseconds
# System CPU Time: 0 microseconds
# Total CPU Time: 11 microseconds

# 2. When n= 2000,
# CPU Usage:
# User CPU Time: 12 microseconds
# System CPU Time: 0 microseconds
# Total CPU Time: 12 microseconds