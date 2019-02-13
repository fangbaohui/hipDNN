import os
import csv
import sys
import tarfile
from termcolor import colored

csv.field_size_limit(sys.maxsize)

def untar(fname,dest):
    if (fname.endswith("tar.gz")):
        tar = tarfile.open(fname)
        tar.extractall(path=dest)
        tar.close()
        print "Extracted in Current Directory"
    else:
        print "Not a tar.gz file: '%s '" % sys.argv[0]

abs_path = os.path.abspath('.')
benchmark_result_path = abs_path.rsplit('/',1)[0]
benchmarking_result = os.path.join(benchmark_result_path,'benchmark_results.tar.gz')
untar(benchmarking_result,benchmark_result_path)
local_folder = os.path.join(abs_path,'results_csv')
benchmarking_folder = os.path.join(benchmark_result_path,'benchmark_results','benchmarking_results_csv')

local_result = os.path.join(abs_path,'result_unittest.csv')
benchmarking_result = os.path.join(benchmark_result_path,'benchmark_results','benchmarking_result_unittest.csv')

local_dev = os.path.join(abs_path,'device.txt')
benchmark_dev = os.path.join(benchmark_result_path,'benchmark_results','benchmark_device.txt')

with open(local_dev, 'r') as myfile1:
  data1 = myfile1.read()

with open(benchmark_dev, 'r') as myfile2:
  data2 = myfile2.read()

reader1 = csv.DictReader(open(local_result, 'r'))
amd_op = []
for line1 in reader1:
    amd_op.append(line1)

reader2 = csv.DictReader(open(benchmarking_result, 'r'))
nv_op = []
for line2 in reader2:
    nv_op.append(line2)

string1 = 'Performance in '+str(data2)+' (microseconds)'
string2 = 'Performance in '+str(data1)+' (microseconds)'
string3 = str(data1)+' vs '+str(data2)+' speedup'
final_result = os.path.join(abs_path,'final_results.csv')
csvfile = open(final_result, 'w+')

fieldnames = ['TestName','Results','Input size', 'kernel size',
              'output size', string1, string2, string3]

writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
writer.writeheader()

count = 0
cnt_p = 0
cnt_f = 0

t_pass = colored('Test passed!', 'green', attrs=['bold'])
t_fail = colored('Test failed!', 'red', attrs=['bold'])
test_name = colored('Test name: ', 'blue', attrs=['bold'])

for filename1 in os.listdir(local_folder):
    for filename2 in os.listdir(benchmarking_folder):
       if (filename1 == filename2):
          with open((local_folder+"/"+filename1),'rb') as csvfile1, open((benchmarking_folder+"/"+filename2),'rb') as csvfile2:
                    readCSV1 = csv.reader(csvfile1, delimiter=',')
                    readCSV2 = csv.reader(csvfile2, delimiter=',')
                    for row1 in readCSV1:
                        for row2 in readCSV2:
                           x = 0.0
                           y = 0.0
                           avg_mismatch = 0.0
                           if (row1[0] == row2[0]):
                              count2 = 0
                              flag = t_pass
                              for op1,op2 in zip(row1[1:],row2[1:]):
                                  if (op1=='' or op2==''):
                                     break
                                  n1 = float(format(float(op1), '.1e'))
                                  n2 = float(format(float(op2), '.1e'))
                                  if (n1 != n2):
                                     if ((abs(n1 - n2)) > 0.001):
                                        if (count2 == 0):
                                            x = n1
                                            y = n2
                                            min_mismatch = abs(n1 - n2)
                                            max_mismatch = abs(n1 - n2)
                                        if (abs(n1 - n2) < min_mismatch):
                                           min_mismatch = abs(n1 - n2)
                                        if (abs(n1 - n2) > max_mismatch):
                                           max_mismatch = abs(n1 - n2)
                                        avg_mismatch = (avg_mismatch + abs(n1 - n2))
                                        count2 = count2 + 1
                                        flag = t_fail
                              if (flag == t_pass) :
                                 print test_name, row1[0]
                                 print "  Test status: ",t_pass
                                 for op3 in amd_op:
                                    for op4 in nv_op:
                                        if (op3['Test_name'] == op4['Test_name'] == row1[0]):
                                           writer.writerow({'TestName':row1[0],
                                                 'Results':'PASS',
                                                 'Input size':op3['Input size'],
                                                 'kernel size':op3['kernel size'],
                                                 'output size':op3['output size'],
                                                 string1: op4['Average Excecution Time (microseconds)'],
                                                 string2: op3['Average Excecution Time (microseconds)'],
                                                 string3:(float)(float(op3['Average Excecution Time (microseconds)'])/
                                                                                float(op4['Average Excecution Time (microseconds)']))})
                                 cnt_p = cnt_p + 1
                              else:
                                  print test_name, row1[0]
                                  print "  Test status: ", t_fail
                                  print "  Total number of mismatches: ",count2
                                  print "  First mismatch: ",x," != ",y
                                  print "  Minimum mismatch: ", min_mismatch
                                  print "  Maximum mismatch: ",max_mismatch
                                  print "  Average mismatch: ",(avg_mismatch/count2)
                                  cnt_f = cnt_f + 1
                                  for op3 in amd_op:
                                     for op4 in nv_op:
                                         if (op3['Test_name'] == op4['Test_name'] == row1[0]):
                                            writer.writerow({'TestName':row1[0],
                                                  'Results':'FAIL',
                                                  'Input size':op3['Input size'],
                                                  'kernel size':op3['kernel size'],
                                                  'output size':op3['output size'],
                                                  string1: op4['Average Excecution Time (microseconds)'],
                                                  string2: op3['Average Excecution Time (microseconds)'],
                                                  string3:(float)(float(op3['Average Excecution Time (microseconds)'])/
                                                                                  float(op4['Average Excecution Time (microseconds)']))})
                              count = count + 1
                              print "\n"
                              break

print "\nTotal number of tests: ", count
print "Number of tests passed: ", cnt_p
print "Number of tests failed: ", cnt_f
