   To create the task use follow steps:

0. Generate ASCII flag by next url and put in flag.txt:

  http://patorjk.com/software/taag/#p=display&h=1&v=3&f=Blocks&t=STCTF%0A%23W17H%0AL0V3Y%0A0URDU%0ACMACD%0AUCKD0%0ATF1G%23

1. Encode flag.txt file to base64:

  base64 flag.txt > result

2. Create hexdump of result:
  ```perl
  cat result | perl -e "while (<>) { print unpack 'H*', $_; }" > result
  ```

3. Add comment to makduck.jpg:
  ```bash
  res=`cat result` && exiftool -Comment="DUCK=$res" -overwrite_original makduck.jpg
  ```
