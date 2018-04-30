from numpy import genfromtxt, shape
from matplotlib.pyplot import figure, pcolormesh, streamplot,savefig,colorbar

D = genfromtxt('salida.txt', delimiter=',')
D = D[:,:-1] # Retirar ultima columna de nans
n1,n2 = shape(D) # Contar datos

# Separar datos
n = int(n1/3)
P = D[:n,:]
Ex = D[n:2*n,:]
Ey = D[2*n:3*n,:]
print(shape(P),shape(Ex),shape(Ey))


XY = genfromtxt('XY.txt', delimiter=',')
XY = XY[:,:-1] # Retirar ultima columna de nans
# Separar datos
X = XY[:n,:]
Y = XY[n:2*n,:]
print(shape(X),shape(Y))


figure()
pcolormesh(X,Y,P)
colorbar()
streamplot(X,Y,Ex,Ey,density=1.5, color='k')
savefig('placas.pdf')


