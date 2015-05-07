1. Generate N E D using tool rsa-wiener-attack (https://github.com/pablocelayes/rsa-wiener-attack) and save selected in "Selected_n_e_d.txt" file.

```bash
   python RSAvulnerableKeyGenerator.py
```

2. Generate private.key PEM file using rsatool (https://github.com/ius/rsatool).

```bash
   python rsatool.py `cat Selected_n_e_d.txt` -o private.key
```

3. Generate public.key.

```bash
    openssl rsa -in private.key -out public.key -outform PEM -pubout
```

4. Encode message.

```bash
    openssl rsautl -encrypt -inkey public.key -pubin -in message -out secret
```
5. Test on decoding.

```bash
    openssl rsautl -decrypt -inkey private.key -in secret -out test && md5sum test message
```

6. Deploy "secret" and public.key files.