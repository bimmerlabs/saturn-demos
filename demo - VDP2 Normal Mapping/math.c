#include "math.h"

FIXED FIXED_127 = toFIXED(127);
FIXED FIXED_255 = toFIXED(255);

// from danny duarte
Uint32 ApproximateIntegerSqrt(Uint32 value)
{
    // Initial variables for approximation
    Uint32 baseValue = 1;                // Base value used to scale the approximation
    Uint32 estimatedValue = value >> 2; // Initial approximation, roughly value / 4

    // Refine the approximation using bit shifts
    while (baseValue < estimatedValue)
    {
        estimatedValue >>= 1;  // Halve the estimated value
        baseValue <<= 1;      // Double the base value
    }

    // Return the refined approximation
    return baseValue + estimatedValue;
}
