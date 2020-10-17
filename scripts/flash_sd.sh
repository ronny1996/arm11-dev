#!/bin/bash
block_size=512	#B
env_bsize=32
bl2_bsize=600
bl1_bsize=16

x=$(($bl2_bsize * $block_size))

flag=0
if [ ! -f $1 ]	#判断文件是否存在
then
	echo "File "$1" not exist!"
else
	file_name=`basename $1`
	#dir_name=`dirname $1`	#获取dir不含最后一个/
	dir_name=$PWD
	echo "Generate sd_writer_file.bin.temp file"
	cp $1 ${dir_name}/sd_writer_file.bin.temp
	dd if=/dev/zero bs=1 count=1 seek=$x of=${dir_name}/sd_writer_file.bin.temp

	echo "Generate sd_writer_file.dev.temp file"
	LC_ALL=C sudo fdisk -l > ${dir_name}/sd_writer_file.dev.temp
	if [  `dirname $2` != "/dev" ]
	then
		echo "SD not exist!"
	else
		LINE=`cat ${dir_name}/sd_writer_file.dev.temp | grep $2`
		flag=0
		for i in $LINE
		do
			flag=$(( $flag + 1 ))
			if [ $flag -eq 5 ]
			then 
				break
			fi
		done
		if [ $flag -eq 5 ]
		then	
			#echo $i
			seek=$(( $i / $block_size - 1024 - 2 - $bl1_bsize ))
			echo "sudo dd if=${dir_name}/sd_writer_file.bin.temp of=$2 bs=$block_size count=$bl1_bsize seek=$seek"
			sudo dd if=${dir_name}/sd_writer_file.bin.temp of=$2 bs=$block_size count=$bl1_bsize seek=$seek
			seek=$(( $i / $block_size - 1024 - 2 - $bl1_bsize - $env_bsize - $bl2_bsize ))
			echo "sudo dd if=${dir_name}/sd_writer_file.bin.temp of=$2 bs=$block_size count=$bl2_bsize seek=$seek"
			sudo dd if=${dir_name}/sd_writer_file.bin.temp of=$2 bs=$block_size count=$bl2_bsize seek=$seek
			sync
			sleep 2
		fi
		echo "remove all sd_writer_file.*.temp file"
		rm -rf ${dir_name}/sd_writer_file.*.temp
		
	fi
fi
