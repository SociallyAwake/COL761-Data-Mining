import matplotlib.pyplot as plt
import timeit
import subprocess 
import sys


plot_name = sys.argv[0]

file1 = "GSPANinput.txt"
file2 = "FSGinput.txt"
supports = [5,10,25,50,95]

graphs_count = 64110
gaston_time = []
gspan_time = []
fsg_time = []
for s in supports:
	
	
		run_gaston = "subprocess.run(\"./gaston "+str( (s * graphs_count)/100.0)+" "+file1+" plotOutput\",shell=True,timeout=60)"
		gaston_time.append(timeit.timeit(run_gaston, setup = "import subprocess", number = 1))
	
		
	
	
		run_gspan = "subprocess.run(\"./gSpan-64 -s"+str(s*1.0/100)+" -f"+file1+" plotOutput\",shell=True,timeout = 60)"
		gspan_time.append(timeit.timeit(run_gspan, setup = "import subprocess", number = 1))
	
		
	
		run_fsg = "subprocess.run(\"./fsg -s "+str(s)+" "+file2+" plotOutput\",shell=True, timeout=60)"
		fsg_time.append(timeit.timeit(run_fsg, setup = "import subprocess", number = 1))
	
		
	


plt.figure()
plt.plot(supports, gspan_time, color='#199EF3', marker='o', label='Gspan')
plt.plot(supports, fsg_time, color='#FF8c00', marker='o', label='Fsg')
plt.plot(supports, gaston_time, color='#458B00', marker='o', label='Gaston')
plt.title('Execution Time Comparision')
plt.xlabel('Support Threshold')
plt.ylabel('Execution Time (s)')
plt.legend()	
plt.grid()
plt.savefig(plot_name+".png")
#plt.show()

