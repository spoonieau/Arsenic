/* 
r744 digital pressure chart
Data pulled from Danfoss Cool Selector2 ver 5.1.0 'Refrigerant Calculator'
https://www.danfoss.com/en/service-and-support/downloads/dcs/coolselector-2/
Will get temp in °C and match aganst Kpa

Temp Range -10°C to 30°C

Written by rick spooner
 */
#include "r744.h"
#include "Arduino.h"

double r744::pressure (int temp)
{
    double x = 0.0;

    switch (temp)
    {
    case -10:
        x = 2649.0;
        break;

    case -9:
        x = 2725.0;
        break;

    case -8:
        x = 2803.0;
        break;

    case -7:
        x = 2882.0;
        break;

    case -6:
        x = 2963.0;
        break;

    case -5:
        x = 3046.0;
        break;

    case -4:
        x = 3130.0;
        break;

    case -3:
        x = 3216.0;
        break;

    case -2:
        x = 3304.0;
        break;

    case -1:
        x = 3394.0;
        break;

    case 0:
        x = 3485.0;
        break;
    
    case 1:
        x = 3578.0;
        break;

    case 2:
        x = 3673.0;
        break;

    case 3:
        x = 3770.0;
        break;

    case 4:
        x = 3869.0;
        break;
    
    case 5:
        x = 3969.0;
        break;
    
    case 6:
        x = 4072.0;
        break;

    case 7:
        x = 4177.0;
        break;

    case 8:
        x = 4283.0;
        break;
    
    case 9:
        x = 4392.0;
        break;
    
    case 10:
        x = 4502.0;
        break;
    
    case 11:
        x = 4615.0;
        break;

    case 12:
        x = 4730.0;
        break;
    
    case 13:
        x = 4847.0;
        break;

    case 14:
        x = 4966.0;
        break;
    
    case 15:
        x = 5087.0;
        break;

    case 16:
        x = 5211.0;
        break;
    
    case 17:
        x = 5337.0;
        break;
    
    case 18:
        x = 5465.0;
        break;
    
    case 19:
        x = 5596.0;
        break;
    
    case 20:
        x = 5729.0;
        break;

    case 21:
        x = 5865.0;
        break;
    
    case 22:
        x = 6003.0;
        break;
    
    case 23:
        x = 6144.0;
        break;

    case 24:
        x = 6288.0;
        break;

    case 25:
        x = 6434.0;
        break;
    
    case 26:
        x = 6584.0;
        break;
    
    case 27:
        x = 6736.0;
        break;
    
    case 28:
        x = 6892.0;
        break;

    case 29:
        x = 7051.0;
        break;
    
    case 30:
        x = 7214.0;
        break;
    
    default:
        x = 0.0;
        break;
    }

    return x;
}