from numpy import genfromtxt
import matplotlib.pyplot as plt


try:
	# Grafica que pide el enunciado
	# No se estan exportando valores en caos.txt pq q1 no esta cambiando de signo
	#
	q2,p2 = genfromtxt("caos.txt", unpack=True)

	plt.plot(q2,p2, 'o-')
	plt.xlabel('q2')
	plt.ylabel('p2')
	plt.savefig('caos.pdf')
except Exception as E:
	print("Problemas con los datos\n\n",E)


try:
	# Graficas para evaluar los resultados del programa
	q1,q2,p1,p2 = genfromtxt("datos.txt", unpack=True)

	xlims = [0,500]
	n=len(q1)
	nmax = int(0.001*n)

	plt.figure(figsize=(10,10))
	plt.subplot(2,2,1)
	plt.plot(q1[:nmax])
	plt.ylabel('q1')
	plt.xlabel('iteracion')
	#plt.xlim(xlims)
	
	plt.subplot(2,2,2)
	plt.plot(q2[:nmax])
	plt.ylabel('q2')
	plt.xlabel('iteracion')
	#plt.xlim(xlims)

	plt.subplot(2,2,3)
	plt.plot(p1[:nmax])
	plt.ylabel('p1')
	plt.xlabel('iteracion')
	#plt.xlim(xlims)

	plt.subplot(2,2,4)
	plt.plot(p2[:nmax])
	plt.ylabel('p2')
	plt.xlabel('iteracion')
	#plt.xlim(xlims)

	plt.savefig('caos2.pdf')
except Exception as E:
	print("Problemas con los datos\n\n",E)
