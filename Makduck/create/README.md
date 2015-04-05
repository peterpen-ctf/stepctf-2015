   To create the task use follow steps:

0. Generate ASCII flag by next url and put in flag.txt:

  http://patorjk.com/software/taag/#p=display&f=Blocks&t=STCTF%0A%23f1a9%0Af1a9f%0A1a9f1%0Aa9f1a%0A9f1a9%0Af1a9f%0A1a9

1. Encode flag.txt file to base64:

  base64 flag.txt > result

2. Create hexdump of result:

  cat result | perl -e "while (<>) { print unpack 'H*', $_; }" > result

3. Add comment to makduck.jpg:

  res=`cat result` && exiftool -Comment="DUCK=$res" -overwrite_original makduck.jpg
