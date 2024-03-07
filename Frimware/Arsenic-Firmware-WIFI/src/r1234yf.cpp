/* 
r1234yf digital pressure chart
Data pulled from Danfoss Cool Selector2 ver 5.1.0 'Refrigerant Calculator'
https://www.danfoss.com/en/service-and-support/downloads/dcs/coolselector-2/
Will get temp in °C and match aganst Kpa

Temp Range -10°C to 60°C

Written by rick spooner
 */
#include "r1234yf.h"
#include "Arduino.h"

double r1234yf::pressure (int temp)
{
    double x = 0.0;

    switch (temp)
    {
    case -10:
        x = 221.8;
        break;

    case -9:
        x = 230.1;
        break;

    case -8:
        x = 238.6;
        break;

    case -7:
        x = 247.4;
        break;

    case -6:
        x = 256.4;
        break;

    case -5:
        x = 265.6;
        break;

    case -4:
        x = 275.1;
        break;

    case -3:
        x = 284.9;
        break;

    case -2:
        x = 294.9;
        break;

    case -1:
        x = 305.2;
        break;

    case 0:
        x = 315.8;
        break;
    
    case 1:
        x = 326.7;
        break;

    case 2:
        x = 337.8;
        break;

    case 3:
        x = 349.2;
        break;

    case 4:
        x = 360.9;
        break;
    
    case 5:
        x = 372.9;
        break;
    
    case 6:
        x = 385.2;
        break;

    case 7:
        x = 397.8;
        break;

    case 8:
        x = 410.7;
        break;
    
    case 9:
        x = 424.0;
        break;
    
    case 10:
        x = 437.5;
        break;
    
    case 11:
        x = 451.4;
        break;

    case 12:
        x = 465.6;
        break;
    
    case 13:
        x = 480.2;
        break;

    case 14:
        x = 495.0;
        break;
    
    case 15:
        x = 510.3;
        break;

    case 16:
        x = 525.8;
        break;
    
    case 17:
        x = 541.8;
        break;
    
    case 18:
        x = 558.0;
        break;
    
    case 19:
        x = 574.7;
        break;
    
    case 20:
        x = 591.7;
        break;

    case 21:
        x = 609.1;
        break;
    
    case 22:
        x = 626.9;
        break;
    
    case 23:
        x = 645.1;
        break;

    case 24:
        x = 663.6;
        break;

    case 25:
        x = 682.6;
        break;
    
    case 26:
        x = 701.9;
        break;
    
    case 27:
        x = 721.7;
        break;
    
    case 28:
        x = 741.9;
        break;

    case 29:
        x = 762.5;
        break;
    
    case 30:
        x = 783.5;
        break;
    
    case 31:
        x = 805.0;
        break;
    
    case 32:
        x = 826.9;
        break;
    
    case 33:
        x = 849.2;
        break;
    
    case 34:
        x = 872.0;
        break;
    
    case 35:
        x = 895.2;
        break;
    
    case 36:
        x = 918.9;
        break;
    
    case 37:
        x = 943.1;
        break;
    
    case 38:
        x = 967.7;
        break;
    
    case 39:
        x = 992.8;
        break;
    
    case 40:
        x = 1018.0;
        break;
    
    case 41:
        x = 1044.0;
        break;

    case 42:
        x = 1070.0;
        break;
    
    case 43:
        x = 1098.0;
        break;
    
    case 44:
        x = 1126.0;
        break;

    case 45:
        x = 1154.0;
        break;
    
    case 46:
        x = 1182.0;
        break;
    
    case 47:
        x = 1212.0;
        break;
    
    case 48:
        x = 1241.0;
        break;
    
    case 49:
        x = 1272.0;
        break;
    
    case 50:
        x = 1302.0;
        break;
    
    case 51:
        x = 1334.0;
        break;
    
    case 52:
        x = 1366.0;
        break;
    
    case 53:
        x = 1398.0;
        break;
    
    case 54:
        x = 1431.0;
        break;
    
    case 55:
        x = 1465.0;
        break;
    
    case 56:
        x = 1499.0;
        break;
    
    case 57:
        x = 1534.0;
        break;
    
    case 58:
        x = 1569.0;
        break;
    
    case 59:
        x = 1605.0;
        break;
    
    case 60:
        x = 16.42;
        break;
    
    default:
        x = 0.0;
        break;
    }

    return x;
}