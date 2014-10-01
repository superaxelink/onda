#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/** pi  = dphi/dt*/
/** psi = dphi/dx*/
/**compilar con "gcc -o archivo archivo.c -lm"*/
int main()
{   
    /**Definimos variables*/
    float t,dx,dt, v,a0,x0,s0;
    int nx,nt,z,n;
    FILE *fp,*fp1,*fp2;
    /**ancho de la malla*/
    printf("Introduzca el ancho de la malla\n");
    scanf("%d",&nx);
    /**nx=30*/
    /**Matrices que daran informacion de las ecuaciones diferenciales*/
    float X[nx],PI[nx], PHI[nx],PSI[nx],DPSI[nx],DPI[nx],SPSI[nx],SPI[nx],SPHI[nx],OPHI[nx],OPI[nx],OPSI[nx];
    /**Introducimos valores de avance espacial y temporal, la velocidad de la onda, y los parametros iniciales a0,x0,s0 de la gaussiana*/
    printf("Introduzca la division espacial\n");
    scanf("%f",&dx);
    /**dx=0.05;*/
    printf("Introduzca la division temporal\n");
    scanf("%f",&dt);
    /**dt=0.05;*/
    printf("Introduzca la velocidad\n");
    scanf("%f",&v);
    /**v=0.1;*/
    printf("Introduzca el numero total de pasos temporales\n");
    scanf("%d",&nt);
    /**nt=15;*/
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
    for(z=0;z<nt;z++){
/**Avance temporal*/
    t=t+dt;
/**Salvamos el paso temporal anterior*/
        for(n=1;n<nx-1;n++){ 
            OPHI[z]=PHI[z];
            OPSI[z]=PSI[z];
            OPI[z]=PI[z];
        }
      /**Calculando puntos nuevos para un tiempo t*/ 
       for(n=1;n<nx-1;n++){
            /**Primero calculamos las derivadas*/
            DPSI[z]=(PSI[z+1]-PSI[z-1])/(2*dx);
            DPI[z]=(PI[z+1]-PI[z-1])/(2*dx);
            /**Evaluamos las fuentes*/
            SPHI[z]=PI[z];
            SPSI[z]=DPI[z];
            SPI[z]=(pow(v,2))*DPSI[z];
            /**Actualizamos ecuaciones*/
            PHI[z]=OPHI[z]+dt*SPHI[z];
            PSI[z]=OPSI[z]+dt*SPSI[z];
            PI[z]=OPI[z]+dt*SPI[z];
        } 
    /**condiciones de frontera*/
    /**frontera derecha*/
    PHI[nx]=-v*PSI[nx];
    /**Frontera izquierda*/
    PHI[0]=v*PSI[0];
    }
    /**Creamos documentos de escritura*/
    fp=fopen("salidaphi.txt","wt");
    fp1=fopen("salidapsi.txt","wt");
    fp2=fopen("salidapi.txt","wt");
    /**Se escribe el resultado en el documento correspondiente*/
    for (z=0;z<nx;z++){
        fprintf(fp, "%f",PHI[z]);
        fprintf(fp,"\n");
    }
    for (z=0;z<nx;z++){
        fprintf(fp1, "%f",PSI[z]);
        fprintf(fp1,"\n");
    }
    for (z=0;z<nx;z++){
        fprintf(fp2, "%f",PI[z]);
        fprintf(fp2,"\n");
    }
}
