int main()
{   
    /**Definimos variables*/
    float t,dx,dt, v,a0,x0,s0;
    int nx,nt,z;
    /**ancho de la malla*/
    nx=30;
    /**Matrices que daran informacion de las ecuaciones diferenciales*/
    float X[nx],PI[nx], PHI[nx],PSI[nx],DPSI[nx],DPI[nx],OPI[nx],OPSI[nx],SPSI[nx],SPI[nx],SPHI[nx];
    /**Introducimos valores de avance espacial y temporal, la velocidad de la onda, y los parametros iniciales a0,x0,s0 de la gaussiana*/
    dx=0.05;
    dt=0.05;
    v=0.1;
    a0 = 1.0;
    x0 = (nx/2.0)*dx;
    s0 = 1.0;
    t=0;
/**Fijamos valores iniciales*/
    for(z=0;z<nx;z++){
        X[z]=z*dx;
    }
    for(z=0;z<nx;z++){
        PHI[z] = a0*exp((-pow((X[z]-x0),2))/pow(s0,2));
        PI[z]=0.0;
    }
    for(z=0;z<nx;z++){
        PSI[z]=a0*((X[z]-x0)/pow(s0,2))*exp(-pow(X[z]-x0,2)/pow(s0,2));
    }
/**Loop principal*/
    for(z=1;z<nt-1;z++){
/**Avance temporal*/
    t=t+dt;
/**Guardando los puntos anteriores*/
    OPI[z]=DPI[z];
    OPSI[z]=DPSI[z];
/**Calculando puntos nuevos*/
    DPI[z]=(PSI[z+1]-PSI[z-1])/(2*dx);
    DPSI[z]=(PI[z+1]-PI[z-1])/(2*dx);
    SPHI[z]=PHI[z];
    SPSI[z]=DPI[z];
    SPI[z]=(pow(v,2))*DPSI[z];
/**condiciones de frontera*/
    /**frontera derecha*/
    SPHI[nx]=-SPSI[nx];
    /**Frontera izquierda*/
    SPHI[0]=SPSI[0];
    }
}
