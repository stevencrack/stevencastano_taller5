import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.pyplot import figure, plot, ylim, cla, subplots
from matplotlib.animation import FuncAnimation

animacion = plt.figure()
cuerda = np.genfromtxt("salida.txt", delimiter=" ", skip_header=0, skip_footer=0, unpack=False)
x = np.linspace(0,100,np.size(cuerda,1))

def imggif(i):
	

	cla()
	plot(x,cuerda[i,:],lw=2)
	ylim(ymax=3)
	ylim(ymin=-2)   
animacion,ax = subplots()
anim = animation.FuncAnimation(animacion, imggif, frames=np.size(cuerda,0))
anim.save('cuerda.gif', writer='imagemagick', fps=np.size(cuerda,0)/2)

