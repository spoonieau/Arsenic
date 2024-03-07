/* 
Hychill30 digital pressure chart
Data pulled from https://hychill.com.au/media/pages/info/8815c50841-1662605920/hychill-pressure-temperature-chart-automotive.pdf
Will get temp in °C and match aganst kpa

Temp Range -10°C to 60°C

Written by rick spooner
 */

#include "hychill30.h"
#include "Arduino.h"

double hychill30::pressure (int temp)
{
    double x = 0.0;

    switch (temp)
    {
    case -10:
        x = 158.5;
        break;

    case -9:
        x = 168.9;
        break;

    case -8:
        x = 179.2;
        break;

    case -7:
        x = 189.6;
        break;

    case -6:
        x = 199.9;
        break;

    case -5:
        x = 206.8;
        break;

    case -4:
        x = 213.7;
        break;

    case -3:
        x = 224.0;
        break;

    case -2:
        x = 234.4;
        break;

    case -1:
        x = 248.2;
        break;

    case 0:
        x = 262.0;
        break;
    
    case 1:
        x = 272.3;
        break;

    case 2:
        x = 282.6;
        break;

    case 3:
        x = 293.0;
        break;

    case 4:
        x = 303.3;
        break;
    
    case 5:
        x = 317.1;
        break;
    
    case 6:
        x = 330.9;
        break;

    case 7:
        x = 344.7;
        break;

    case 8:
        x = 358.5;
        break;
    
    case 9:
        x = 372.3;
        break;
    
    case 10:
        x = 386.1;
        break;
    
    case 11:
        x = 399.8;
        break;

    case 12:
        x = 413.6;
        break;
    
    case 13:
        x = 427.4;
        break;

    case 14:
        x = 441.2;
        break;
    
    case 15:
        x = 458.5;
        break;

    case 16:
        x = 475.7;
        break;
    
    case 17:
        x = 489.5;
        break;
    
    case 18:
        x = 503.3;
        break;
    
    case 19:
        x = 520.5;
        break;
    
    case 20:
        x = 537.7;
        break;

    case 21:
        x = 555.0;
        break;
    
    case 22:
        x = 572.2;
        break;
    
    case 23:
        x = 592.9;
        break;

    case 24:
        x = 613.6;
        break;

    case 25:
        x = 630.8;
        break;
    
    case 26:
        x = 648.1;
        break;
    
    case 27:
        x = 668.7;
        break;
    
    case 28:
        x = 689.4;
        break;

    case 29:
        x = 710.1;
        break;
    
    case 30:
        x = 730.8;
        break;
    
    case 31:
        x = 751.5;
        break;
    
    case 32:
        x = 772.2;
        break;
    
    case 33:
        x = 792.8;
        break;
    
    case 34:
        x = 813.5;
        break;
    
    case 35:
        x = 837.6;
        break;
    
    case 36:
        x = 861.8;
        break;
    
    case 37:
        x = 882.5;
        break;
    
    case 38:
        x = 903.2;
        break;
    
    case 39:
        x = 927.3;
        break;
    
    case 40:
        x = 951.4;
        break;
    
    case 41:
        x = 979.0;
        break;

    case 42:
        x = 1006.6;
        break;
    
    case 43:
        x = 1030.7;
        break;
    
    case 44:
        x = 1054.8;
        break;

    case 45:
        x = 1082.4;
        break;
    
    case 46:
        x = 1110.0;
        break;
    
    case 47:
        x = 1137.6;
        break;
    
    case 48:
        x = 1165.2;
        break;
    
    case 49:
        x = 1192.7;
        break;
    
    case 50:
        x = 1220.3;
        break;
    
    case 51:
        x = 1251.3;
        break;
    
    case 52:
        x = 1282.4;
        break;
    
    case 53:
        x = 1313.4;
        break;
    
    case 54:
        x = 1344.4;
        break;
    
    case 55:
        x = 1375.5;
        break;
    
    case 56:
        x = 1406.5;
        break;
    
    case 57:
        x = 1437.5;
        break;
    
    case 58:
        x = 1468.5;
        break;
    
    case 59:
        x = 1503.0;
        break;
    
    case 60:
        x = 1537.5;
        break;
    
    default:
        x = 0.0;
        break;
    }

    return x;
}