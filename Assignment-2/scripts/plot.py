from tracemalloc import start
import matplotlib.pyplot as plt
import time
import subprocess 
import sys
import os

plot_name = sys.argv[1]

file1 = "./datasets/GSPANinput.txt"
file2 = "./datasets/FSGinput.txt"
supports = [5,10,25,50,95]
# supports = [50,95]
graphs_count = 64110
gaston_time = []
gspan_time = []
fsg_time = []
for s in supports:
	
		start_time=time.time()
		cmd=f"./tools/gaston {str( (s * graphs_count)/100.0)} {file1} ./datasets/plotOutput"
		os.system(cmd)
		end_time=time.time()
		gaston_time.append(end_time-start_time)

		start_time=time.time()
		cmd=f"./tools/gSpan-64 -s {str(s*1.0/100)} -f {file1} ./datasets/plotOutput"
		os.system(cmd)
		end_time=time.time()
		gspan_time.append(end_time-start_time)
	

		start_time=time.time()
		cmd=f"./tools/fsg -s {str(s)} {file2} ./datasets/plotOutput"
		os.system(cmd)
		end_time=time.time()
		fsg_time.append(end_time-start_time)
	
		
	


plt.figure()
plt.plot(supports, gspan_time, color='#199EF3', marker="*", label='Gspan')
plt.plot(supports, fsg_time, color='#FF8c00', marker="*", label='Fsg')
plt.plot(supports, gaston_time, color='#458B00', marker="*", label='Gaston')
plt.title('Execution Time Comparision')
plt.xlabel('Support Threshold')
plt.ylabel('Execution Time (s)')
plt.legend()	
plt.grid()
plt.savefig(plot_name+".png")
#plt.show()

