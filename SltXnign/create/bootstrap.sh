#!/bin/bash

apt-get update && apt-get install -y \
 vim nginx nano tree htop wget faketime

# Remove global sudo 
rm -f /etc/sudoers.d/box

echo 'box ALL = (ALL) NOPASSWD:ALL' >> /etc/sudoers.d/box


# Update sudoers
echo "
# box ALL = NOPASSWD: /etc/init.d/nginx, /usr/sbin/nginx, /usr/sbin/service nginx * 
" >> /etc/sudoers.d/box

# Change permissions
chgrp -R box /etc/nginx /var/log/nginx
chmod -R g+w /etc/nginx /var/log/nginx

# Write keys/certs
echo "-----BEGIN CERTIFICATE-----
MIIDiTCCAnGgAwIBAgIJAN6BAdm7qcYZMA0GCSqGSIb3DQEBCwUAMFsxCzAJBgNV
BAYTAlJVMRMwEQYDVQQIDApTb21lLVN0YXRlMQwwCgYDVQQHDANTUGIxETAPBgNV
BAoMCFBldGVyUGVuMRYwFAYDVQQDDA0yMDE1LnN0ZXAuY3RmMB4XDTE1MDQyNTIy
MjYyMVoXDTE4MDExOTIyMjYyMVowWzELMAkGA1UEBhMCUlUxEzARBgNVBAgMClNv
bWUtU3RhdGUxDDAKBgNVBAcMA1NQYjERMA8GA1UECgwIUGV0ZXJQZW4xFjAUBgNV
BAMMDTIwMTUuc3RlcC5jdGYwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIB
AQDzLYYCN8nGlNwArEVsPTT9eI/5ntrend2wW6C7/WBfUgL5nxL0unmbnjupuiPG
0TJshVNuvIiTljAjT6oaJws69b5OKWykN/UJFUmk4OsdffSQICVFMqXRhBbiNR1k
e2s+orBpJO8mb0k1QGiCiwuS23mpV332qfUMuD9082JmZcWT6wk/Qu3UyDRZQs4T
WGd1jd9x58Xw964mZFuiWA9bDtcMfQM+8eBcSC5J6/lRMPWZ4ruRb/v2LFhsm1Or
vuc8+iXWvXycVhbE5+2lStH893mJVMlohxctf+bUhPw7isR09SWbtnagWpFzx2kH
vdwsJ43ImPI3n/Wnxr+/YGK3AgMBAAGjUDBOMB0GA1UdDgQWBBREVXODpDmDpLiP
H3gkKW7o5taw6TAfBgNVHSMEGDAWgBREVXODpDmDpLiPH3gkKW7o5taw6TAMBgNV
HRMEBTADAQH/MA0GCSqGSIb3DQEBCwUAA4IBAQAtvihvx6KODbhmt/y95ANTB4WC
xbyovkV2DwDNaToDkhqGe5FXrsKiIeoFHbkaSKg1OuWaJ6EWgkG2kd++BiGTjPm2
hI6WPoLsr4uhkI708u3HOVFlX7AUd9FCadMVFOn+zXu7+dg7M3/61ytmExQKWAuD
I7F1NbY2qUcbv4X6JQflguOO3kZvQPGi+oXjUK9POA7y7wck9+3/cJkuoO/TZHMj
JblhFJ2nmD6iunngTYZKgq05TDridXTRJMWe7QX+cO+8jWJj52nx82lCVBtYg5Sx
9wwg7Ab8libNzmlCqtgMB9QtYpqaVJXmWTisNjfZUCxzQpFr+l/XZmLomwTg
-----END CERTIFICATE-----" > /home/box/cert.pem

echo "-----BEGIN PRIVATE KEY-----
MIIEvwIBADANBgkqhkiG9w0BAQEFAASCBKkwggSlAgEAAoIBAQDzLYYCN8nGlNwA
rEVsPTT9eI/5ntrend2wW6C7/WBfUgL5nxL0unmbnjupuiPG0TJshVNuvIiTljAj
T6oaJws69b5OKWykN/UJFUmk4OsdffSQICVFMqXRhBbiNR1ke2s+orBpJO8mb0k1
QGiCiwuS23mpV332qfUMuD9082JmZcWT6wk/Qu3UyDRZQs4TWGd1jd9x58Xw964m
ZFuiWA9bDtcMfQM+8eBcSC5J6/lRMPWZ4ruRb/v2LFhsm1Orvuc8+iXWvXycVhbE
5+2lStH893mJVMlohxctf+bUhPw7isR09SWbtnagWpFzx2kHvdwsJ43ImPI3n/Wn
xr+/YGK3AgMBAAECggEBAJgz5wteVZlINIbrTCxaBt+a5SpMphrt3gJy5yCijv46
O4h3awrn6BNhr2AlFB1tdEz+CeFmeWk+eHSxePsTcvD9PJZ5UPlb2K9NtqFO8Xmt
CzRmGk28TJLdROFiczogEVjLxPSaXGDHCKAe5wrF8oGBgx1dmIaZi7nhXD5b0zvY
wL9C/qq8pAtx8lcDci1SdPu/VIz7FMXizKpIqCh/Hhr+ccAK1XnZplzP09RX8tkm
iZZV+aK3ocHJz+CQZTkME74tYpp2ukLk4jxcJ5WX31DK2UangUFbJojMa/xKMMAT
EC0CdXFaRg4w3W4q+tWzyIWaSW7Y9rZRFQ6LAqZ30ZkCgYEA+/ixVY5zfKe2kKll
1I2YnaO/x8kRG3DRz9aXLTuT17OD38OkLVpb/U6GwXIn3LhNe+EVMUUuN2dVLMAQ
WGh1q8N3Pu9M31T3xyHVPHpcHgd3OOcQMQdCM+ZGG8VbwixNvYV1OdusKuiJmDP2
gSFDSthB5S5nxUktfYPj9ozyZ3UCgYEA9xDWvrH7UVirLQOwAcyrBcnDwWTzfRD0
WuNUqiJ+jS46BYrPk62B/tkq6bfYPN5uA9reen9gFwSPppUE0eA9Rp6YOP42FoAS
xOKl0wB1ollUxvS7Vlak9NQJI77rVZ5AltJTQ35i9ZIKOyREAkB4ZPhvsNiJjQwn
19xjcXIFx/sCgYBecBhu+6QXPXi0gXkUEDn6I2x2wcpyoXdR0Zj5sBG6T6MGk/oN
sYc2yl7BVDrShBUub+8Ud1xaEZWf3yCBMi2gQfOImAIU1nDDps+YCjhKXPv3TMsJ
xTGv6Aew0uiQPzCn7sQ/+jBuKJehfyBNx5zECYexERJ9o+6z02H2f18/HQKBgQC0
HtegcRt7A7zP9YdE2JS6hI0tmk6VmF29QU0BOGKwxMnSLpAE5xMF3AeYGssQHU1x
jAh0oBZK0a100eGQrP2fVZI+wr5mCvskBOTF/ujD8oKHBfbqDAL45vi+0bq6UcRe
8Hl5lFPLGqxQz7CxP5VGb4TmFge6B+moSulI1Mr4LwKBgQD3O6j9nZEWPmEhRCuD
YRfuVmeoBHFmPlQFNNlVTYlIZSjsXgLbWn8u/vgjWNnK99xsESIuV/VV7IEHNf+j
ksEhh8ZL7At5HaPXqh0cpnPgc2yjSDd0HWMoY6B2TlSerHy7xFztLCLtLlK19Hh4
NpwpLRF7Dz2WXME2CBz3ndTMnA==
-----END PRIVATE KEY-----" > /home/box/cert.key

# Add the certificate
cp /home/box/cert.pem /usr/local/share/ca-certificates/step.crt
update-ca-certificates

# Update 'hosts'
echo '127.0.0.1   2015.step.ctf' >> /etc/hosts

