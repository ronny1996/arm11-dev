#/bin/bash

input="/home/${USER}/workspace/pkg/arm-linux-gcc/bin/"
output="/home/${USER}/workspace/pkg/arm-linux-crosstools/"
files=`ls  ~/workspace/pkg/arm-linux-gcc/bin/`
 
mkdir -p $output
for var in $files
do 
  var="${input}${var} ${output}arm-linux-${var#'arm-unknown-linux-gnueabihf-'}"
  ln -s $var
  #echo $var
done

