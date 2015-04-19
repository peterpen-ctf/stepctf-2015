- Download and build pifs from https://github.com/philipl/pifs

- Prepare everything

  $ ln -s src/πfs src/pifs  # For simplicity
  $ mkdir mnt/ metadata/

- Mount and copy the flag

  $ ./src/pifs -o mdd=FULLPATH/metadata mnt/
  $ cp flag.txt /mnt/ 

- Pack the metadata

  $ zip -9 -r metadata metadata
  $ base64 metadata.zip > metadata.zip.b64

- Cleanup

  $ umount mnt/
  $ rm -rf mnt/* metadata/*
  $ ./src/pifs -o mdd=FULLPATH/metadata mnt/

- Copy file

  $ cp metadata.zip.b64 mnt/

- Pack the metadata

  $ zip -9 -r metadata metadata

