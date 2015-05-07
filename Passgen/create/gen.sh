
BOOT_PART=$(curl https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css | sha256sum)

DIGEST=$(echo $PS1 $BOOT_PART | sha256sum | cut -b 1-12)

echo $DIGEST | perl -nE 'chomp; say "STCTF#$_#"' > password.txt

