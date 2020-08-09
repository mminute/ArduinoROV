# NEMA Data Format

---

## [What is GPS NEMA Data](https://www.gpsworld.com/what-exactly-is-gps-nmea-data/)

> NMEA is an acronym for the [National Marine Electronics Association](https://www.nmea.org/). NMEA existed well before GPS was invented. According to the NMEA website, the association was formed in 1957 by a group of electronic dealers to create better communications with manufacturers. Today in the world of GPS, NMEA is a standard data format supported by all GPS manufacturers, much like ASCII is the standard for digital computer characters in the computer world.


## [NEMA Terminology](https://www.gpsinformation.org/dale/nmea.htm)

The example SoftwareSerialPortExample outputs data like:

	$GPGGA,190711.000,3747.7442,N,12225.4826,W,2,5,1.75,126.5,M,-25.3,M,,*61
	$GPGSA,A,3,17,24,12,02,06,,,,,,,,1.98,1.75,0.94*0B
	$GPRMC,190711.000,A,3747.7442,N,12225.4826,W,0.29,59.90,290619,,,D*41
	$GPVTG,59.90,T,,M,0.29,N,0.54,K,D*07
	
**GP** is a prefix representing GPS.

**GL** is a prefix representing GLONASS.

So read **GPGGA** as **GGA** in reference to the message being sent by the GPS unit

---

| Term | Definition |
| --- | --- |
| **GGA** | [Fix information](https://www.gpsinformation.org/dale/nmea.htm#GGA) |
| **GSA** | [Overall Satellite data](https://www.gpsinformation.org/dale/nmea.htm#GSA) |
| **RMC** | [Recommended minimum data for gps](https://www.gpsinformation.org/dale/nmea.htm#RMC) |
| **VTG** | [Vector track and Speed over the Ground](https://www.gpsinformation.org/dale/nmea.htm#VTG) |

---
## Terms **

#### GGA

Essential fix data which provide 3D location and accuracy data.

> $GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47

| Data point | Meaning |
| --- | --- |
| GGA | Global Positioning System Fix Data |
| 123519 | Fix taken at 12:35:19 UTC |
| 4807.038,N | Latitude 48 deg 07.038' N |
| 01131.000,E  | Longitude 11 deg 31.000' E |
| 1 | Fix quality (See below for value definitions) |
| 08 | Number of satellites being tracked |
| 0.9 | Horizontal dilution of position |
| 545.4,M  | Altitude, Meters, above mean sea level |
| 46.9,M | Height of geoid (mean sea level) above WGS84 ellipsoid |
| (empty field) | Time in seconds since last DGPS update |
| (empty field) | DGPS station ID number |
| *47 | Checksum data, always begins with * |

If the height of geoid is missing then the altitude should be suspect. Some non-standard implementations report altitude with respect to the ellipsoid rather than geoid altitude. Some units do not report negative altitudes at all. This is the only sentence that reports altitude.


| Fix Value | Definition |
| --- | --- |
| 0 | Invalid |
| 1 | GPS fix (SPS) |
| 2 | DGPS fix |
| 3 | PPS fix |
| 4 | Real Time Kinematic |
| 5 | Float RTK |
| 6 | Estimated (dead reckoning) (2.3 feature) |
| 7 | Manual input mode |
| 8 | Simulation mode |

---

#### GSA

GPS DOP and active satellites. This sentence provides details on the nature of the fix. It includes the numbers of the satellites being used in the current solution and the DOP. DOP (dilution of precision) is an indication of the effect of satellite geometry on the accuracy of the fix. It is a unitless number where smaller is better. For 3D fixes using 4 satellites a 1.0 would be considered to be a perfect number, however for overdetermined solutions it is possible to see numbers below 1.0.

There are differences in the way the PRN's are presented which can effect the ability of some programs to display this data. For example, in the example shown below there are 5 satellites in the solution and the null fields are scattered indicating that the almanac would show satellites in the null positions that are not being used as part of this solution. Other receivers might output all of the satellites used at the beginning of the sentence with the null field all stacked up at the end. This difference accounts for some satellite display programs not always being able to display the satellites being tracked. Some units may show all satellites that have ephemeris data without regard to their use as part of the solution but this is non-standard.

> $GPGSA,A,3,04,05,,09,12,,,24,,,,,2.5,1.3,2.1*39

| Data point | Meaning |
| --- | --- |
| GSA | Satellite status |
| A | Auto selection of 2D or 3D fix (M = manual)  |
| 3 | 3D fix - values (See below for value definitions) |
| 04,05... | PRNs of satellites used for fix (space for 12)  |
| 2.5 | PDOP (dilution of precision)  |
| 1.3 | Horizontal dilution of precision (HDOP)  |
| 2.1 | Vertical dilution of precision (VDOP) |
| *39 | Checksum data, always begins with * |

| Fix Value | Definition |
| --- | --- |
| 1 | No fix |
| 2 | 2D fix |
| 3 | 3D fix |

---
#### RMC

NMEA has its own version of essential gps pvt (position, velocity, time) data. It is called RMC, The Recommended Minimum, which will look similar to:

> $GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A
 
| Data point | Meaning |
| --- | --- |
| RMC | Recommended Minimum sentence C |
| 123519 | Fix taken at 12:35:19 UTC |
| A | Status A=active or V=Void |
| 4807.038,N | Latitude 48 deg 07.038' N |
| 01131.000,E | Longitude 11 deg 31.000' E |
| 022.4 | Speed over the ground in knots |
| 084.4  | Track angle in degrees True |
| 230394 | Date - 23rd of March 1994 |
| 003.1,W | Magnetic Variation |
| *6A | The checksum data, always begins with * |

Note that, as of the 2.3 release of NMEA, there is a new field in the RMC sentence at the end just prior to the checksum. For more information on this field see [here](https://www.gpsinformation.org/dale/nmea.htm#2.3).

---
#### VTG
Velocity made good. The gps receiver may use the LC prefix instead of GP if it is emulating Loran output.

>$GPVTG,054.7,T,034.4,M,005.5,N,010.2,K*48

| Data point | Meaning |
| --- | --- |
| VTG | Track made good and ground speed |
| 054.7,T | True track made good (degrees) |
| 034.4,M   | Magnetic track made good |
| 005.5,N | Ground speed, knots |
| 010.2,K | Ground speed, Kilometers per hour |
| *48 | Checksum |

Note that, as of the 2.3 release of NMEA, there is a new field in the VTG sentence at the end just prior to the checksum. For more information on this field see [here](https://www.gpsinformation.org/dale/nmea.htm#2.3).

Receivers that don't have a magnetic deviation (variation) table built in will null out the Magnetic track made good.

---
To google latitude/longitude:

ex)
> 3747.7442,N,12225.4826,W

search for:
> 37 47.7442 N 122 25.4826 W

> 37 (Degrees) 47.7442 (Minutes) N 122 (Degrees) 25.4826 (Minutes) W


---
** Definitions taken from https://www.gpsinformation.org/dale/nmea.htm