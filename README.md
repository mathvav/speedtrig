# SpeedTrig

[![@mathvav stability level: stable](https://img.shields.io/badge/%40mathvav_stability_level-stable-brightgreen)](https://gist.github.com/mathvav/76a115a315ec08b07728f98f99fe9a77)
[![@mathvav maintenance level: not maintained (pull requests still accepted)](https://img.shields.io/badge/%40mathvav_maintenance_level-not_maintained_%28PRs_still_accepted%29-orange)](https://gist.github.com/mathvav/033a4d949e94650a68bee81d94a371b3)


Simple Arduino library that speeds up trigonometry functions, based on work by Oscar Liang.

Simply drag the main folder into the `libraries` subdirectory of your Arduino IDE sketch folder.

This is a simple output (via serial) to show accuracy of library compared to the Arduino functions:

```
Sin 15: 
 - Standard [RAD]: 0.6503
 - Fast [DEG]: 0.2588
Cos 15: 
 - Standard [RAD]: -0.7597
 - Fast [DEG]: 0.9659
Acos .15: 
 - Standard [RAD]: 1.4202
 - Fast [RAD]: 1.4230
Atan2 5, 5: 
 - Standard [RAD]: 0.7854
 - Fast [RAD]: 0.7823
```

As it stands, sine and cosine both return degrees from this library—however, it's simple to **[convert between radians and degrees](https://www.purplemath.com/modules/radians.htm).** I'd happily welcome a pull request to unify all four functions to use the same units, along with helper functions to convert from degrees to radians and vice versa.
