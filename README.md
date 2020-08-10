# 数据压缩器使用说明

## 0.包含
	该压缩包包含以下各个文件：
	- 数据压缩器实验报告doc文件
	- 数据压缩器介绍ppt文件（课堂上组长做的汇报）
	- 数据压缩器源码未压缩目录lab01,其中最终的可执行文件是目录第一层中的main文件
	- 数据压缩器源码压缩文件lab01.tar.gz
	- 测试相关文件位于lab01/test目录中，测试用例文件为lab01/test/test*.txt，测试压缩结果文件为lab01/test/test*.out, 测试解码文件为lab01/test/test*.dcd

## 1.安装

- 编译  
~$ make  
- 清除中间文件  
~$ make clean

## 2.查看使用帮助

- 在程序所在根目录运行  
~$ ./main -h  
usage: ./main -i input_file [OPTIONS] [FILE...]  
-i		input_file		:	text file for encoding  
-o		output_file		:	name of encoded outputfile  
-d		decode_file		:	name of decoded outputfile  
-h						:	display this message  

## 3.程序对文件进行压缩
- 在程序所在根目录运行  
~$ ./main -i test.txt -o test.out -d test.dcd  
1）-i选项：待压缩文件名  
2）-o选项：压缩结果输出文件名  
3）-d选项：解码结果输出文件名

## 4.测试

- 进入程序所在根目录，运行命令  
~$ cd test/src/ && make && cd ../../

## 5.随机生成测试用例，并自动测试程序
 
- ~$ cd test/ && ./init && ./test.sh && cd ../

## 6.清理目录

- ~$ cd test/ && ./clean && cd ../

## 7. 小组成员及分工
- 李嘉睿：程序框架、模块编码、测试模块、实验报告
- 李英韬：测试模块、模块编码
- 王晶晶：模块编码
