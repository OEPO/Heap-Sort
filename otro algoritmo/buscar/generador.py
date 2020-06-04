import random
for i in range(28):
    pj = []
    rut = []
    nombre = str(random.randint(28345,45453))+'.txt'
    archivo = open(nombre,'w')
    for j in range(30):
        rut_ = str(random.randint(18_000_000,22_000_000))
        puntaje =str(random.randint(250,850))
        rut.append(rut_)
        pj.append(puntaje)
    pj.sort()
    for n in range(len(rut)):
        es = rut[n]+','+pj[n]+'\n'
        archivo.write(es)
    archivo.close()
