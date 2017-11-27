#este script lee los datos producidos por el programa en C y los grafica.
import numpy as np
import matplotlib.pyplot as plt
import scipy.io.wavfile as sc

Datos = np.genfromtxt('new_dataCuerda.dat',delimiter= ' ')
Datos2 = np.genfromtxt('new_dataCuerdaPertur.dat',delimiter= ' ')
x =Datos[:,0]
t0=Datos[:,1]
t8=Datos[:,2]
t4=Datos[:,3]
t2=Datos[:,4]

xp =Datos2[:,0]
t0p=Datos2[:,1]
t8p=Datos2[:,2]
t4p=Datos2[:,3]
t2p=Datos2[:,4]

plt.plot(x,t0,label="condiciones iniciales")
plt.plot(x,t8,label="t/8")
plt.plot(x,t4,label="t/4")
plt.plot(x,t2,label="t/2")

plt.xlabel('longitud de la cuerda (m)')
plt.ylabel('Amplitud (m)')
plt.title('movimiento de la cuerda en diferentes tiempos,fija')
plt.legend()
plt.tight_layout()
plt.savefig('cuerdaFija.pdf')
#plt.show()
plt.close()

plt.plot(xp,t0p,label="condiciones iniciales")
plt.plot(xp,t8p,label="t/8")
plt.plot(xp,t4p,label="t/4")
plt.plot(xp,t2p,label="t/2")
 
plt.xlabel('longitud de la cuerda (m)')
plt.ylabel('Amplitud (m)')
plt.title('movimiento de la cuerda en diferentes tiempos, perturbada')
plt.legend()
plt.tight_layout()
plt.savefig('CuerdaFijaConPertur.pdf')
#plt.show()

Data3 = Datos
scaled = np.int16(Data3/np.max(np.abs(Data3)) * 32767)
sc.write('cuerda.wav', 258, scaled)

