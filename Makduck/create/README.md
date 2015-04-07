   To create the task use follow steps:

0. Generate ASCII flag by next url and put in flag.txt:

  http://patorjk.com/software/taag/#p=display&h=1&v=3&f=Blocks&t=STCTF%0A%23W17H%0AL0V3Y%0A0URDU%0ACMACD%0AUCKD0%0ATF1G%23

1. Encode flag.txt file to base64 and copy original.makduck.jpg to makduck.jpg:
  ```bash
  base64 flag.txt > result && cp original.makduck.jpg makduck.jpg
  ```

2. Create hexdump of result:
  ```bash
  cat result | perl -e "while (<>) { print unpack 'H*', $_; }" > result.new
  ```

3. Add comment to makduck.jpg:
  ```bash
  res=`cat result.new` && exiftool -Comment="DUCK=$res" -overwrite_original makduck.jpg
  ```

4. Remove temp result files:
   ```bash
   rm result result.new
   ```

5. Deploy your injected makduck.jpg image file to some place.
