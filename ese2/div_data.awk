#!/usr/bin/awk -f

{

  print $1 > "data1.txt"
  print $2 > "data2.txt"
  print $3 > "data3.txt"
  print $4 > "data4.txt"
  print $5 > "data5.txt"

}
