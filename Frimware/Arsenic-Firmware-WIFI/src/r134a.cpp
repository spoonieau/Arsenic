/* 
r134a digital pressure chart
Data pulled from Danfoss Cool Selector2 ver 5.1.0 'Refrigerant Calculator'
https://www.danfoss.com/en/service-and-support/downloads/dcs/coolselector-2/
Will get temp in °C and match aganst Kpa

Temp Range -10°C to 60°C

Written by rick spooner
 */
#include "r134a.h"
#include "Arduino.h"

double r134a::pressure (int temp)
{
    double x = 0.0;

    switch (temp)
    {
    case -10:
        x = 200.6;
        break;

    case -9:
        x = 208.7;
        break;

    case -8:
        x = 217.0;
        break;

    case -7:
        x = 225.5;
        break;

    case -6:
        x = 234.3;
        break;

    case -5:
        x = 243.4;
        break;

    case -4:
        x = 252.7;
        break;

    case -3:
        x = 262.3;
        break;

    case -2:
        x = 272.2;
        break;

    case -1:
        x = 282.4;
        break;

    case 0:
        x = 292.9;
        break;
    
    case 1:
        x =303.6;
        break;

    case 2:
        x = 314.7;
        break;

    case 3:
        x = 326.1;
        break;

    case 4:
        x = 337.8;
        break;
    
    case 5:
        x = 349.8;
        break;
    
    case 6:
        x = 362.1;
        break;

    case 7:
        x = 374.7;
        break;

    case 8:
        x = 387.7;
        break;
    
    case 9:
        x = 401.0;
        break;
    
    case 10:
        x = 414.7;
        break;
    
    case 11:
        x = 428.7;
        break;

    case 12:
        x = 443.1;
        break;
    
    case 13:
        x = 457.9;
        break;

    case 14:
        x = 473.0;
        break;
    
    case 15:
        x = 488.5;
        break;

    case 16:
        x = 504.4;
        break;
    
    case 17:
        x = 520.6;
        break;
    
    case 18:
        x = 537.3;
        break;
    
    case 19:
        x = 554.3;
        break;
    
    case 20:
        x = 571.8;
        break;

    case 21:
        x = 589.7;
        break;
    
    case 22:
        x = 608.0;
        break;
    
    case 23:
        x = 626.7;
        break;

    case 24:
        x = 645.8;
        break;

    case 25:
        x = 665.4;
        break;
    
    case 26:
        x = 685.5;
        break;
    
    case 27:
        x = 705.9;
        break;
    
    case 28:
        x = 762.9;
        break;

    case 29:
        x = 748.3;
        break;
    
    case 30:
        x = 770.2;
        break;
    
    case 31:
        x = 792.5;
        break;
    
    case 32:
        x = 815.4;
        break;
    
    case 33:
        x = 838.7;
        break;
    
    case 34:
        x = 862.5;
        break;
    
    case 35:
        x = 886.8;
        break;
    
    case 36:
        x = 911.7;
        break;
    
    case 37:
        x = 937.1;
        break;
    
    case 38:
        x = 962.9;
        break;
    
    case 39:
        x = 989.4;
        break;
    
    case 40:
        x = 1016.0;
        break;
    
    case 41:
        x = 1044.0;
        break;

    case 42:
        x = 1072.0;
        break;
    
    case 43:
        x = 1101.0;
        break;
    
    case 44:
        x = 1130.0;
        break;

    case 45:
        x = 1160.0;
        break;
    
    case 46:
        x = 1190.0;
        break;
    
    case 47:
        x = 1221.0;
        break;
    
    case 48:
        x = 1252.0;
        break;
    
    case 49:
        x = 1285.0;
        break;
    
    case 50:
        x = 1317.0;
        break;
    
    case 51:
        x = 1351.0;
        break;
    
    case 52:
        x = 1385.0;
        break;
    
    case 53:
        x = 1420.0;
        break;
    
    case 54:
        x = 1455.0;
        break;
    
    case 55:
        x = 1491.0;
        break;
    
    case 56:
        x = 1528.0;
        break;
    
    case 57:
        x = 1565.0;
        break;
    
    case 58:
        x = 1603.0;
        break;
    
    case 59:
        x = 1642.0;
        break;
    
    case 60:
        x = 1681.0;
        break;
    
    default:
        x = 0.0;
        break;
    }

    return x;
}