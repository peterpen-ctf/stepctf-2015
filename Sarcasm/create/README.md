   To create the task use follow steps:

0. First, install next python libs to generate QR Code:
  ```bash
  sudo pip install qrcode
  sudo pip install git+git://github.com/ojii/pymaging.git#egg=pymaging
  sudo pip install git+git://github.com/ojii/pymaging-png.git#egg=pymaging-png
  ```
1. Generate QR codes and inject all of them LSB, after that, does tar with qr codes image files inside:
  ```bash
  perl create.pl
  ```

2. Deploy sarcasm.tar.gz to some place.
