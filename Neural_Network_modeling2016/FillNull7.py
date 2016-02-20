__author__ = 'jason'
import csv
from pybrain.datasets import SupervisedDataSet
from pybrain.supervised.trainers import BackpropTrainer
from pybrain.tools.shortcuts import buildNetwork
import numpy as np
#read csv data:
reader = csv.reader(file('/Users/jason/Desktop/modeling/data/fillNull6.csv', 'rb'))

data = []
attributes = []
attrNullNum = {}
data_fit = []
#get the filter data:
for line in reader:
    if reader.line_num == 1:
        attributes = line
        for eachAttr in line:
            attrNullNum[eachAttr] = 0
    else:
        data_fit.append(line)
        oneSchool = {}
        i = 0
        for value in line:
            oneSchool[attributes[i]] = value
            if oneSchool[attributes[i]] == 'NULL' or oneSchool[attributes[i]] == 'PrivacySuppressed':
                attrNullNum[attributes[i]] += 1
            i+=1
        data.append(oneSchool)
#get the null attributes:
oneNull = {}
twoNull = {}
threeNull = {}
fourNull = {}
fiveNull = {}
sixNull = {}
sevenNull = {}
eightNull = {}
reader = csv.reader(file('/Users/jason/Desktop/modeling/data/fillNull6.csv', 'rb'))
for line in reader:
    if reader.line_num == 1:
        continue
    else:
        iter = 0
        nullAttr = ''
        nullNum = 0
        for value in line:
            if value == 'NULL' or value == 'PrivacySuppressed':
                nullAttr+=(attributes[iter]+',')
                nullNum+=1
            iter+=1
        if nullNum == 1:
            if nullAttr not in oneNull.keys():
                oneNull[nullAttr] = 1
            else:
                oneNull[nullAttr]+=1
        if nullNum == 2:
            if nullAttr not in twoNull.keys():
                twoNull[nullAttr] = 1
            else:
                twoNull[nullAttr]+=1
        if nullNum == 3:
            if nullAttr not in threeNull.keys():
                threeNull[nullAttr] = 1
            else:
                threeNull[nullAttr]+=1
        if nullNum == 4:
            if nullAttr not in fourNull.keys():
                fourNull[nullAttr] = 1
            else:
                fourNull[nullAttr]+=1
        if nullNum == 5:
            if nullAttr not in fiveNull.keys():
                fiveNull[nullAttr] = 1
            else:
                fiveNull[nullAttr]+=1
        if nullNum == 6:
            if nullAttr not in sixNull.keys():
                sixNull[nullAttr] = 1
            else:
                sixNull[nullAttr]+=1
        if nullNum == 7:
            if nullAttr not in sevenNull.keys():
                sevenNull[nullAttr] = 1
            else:
                sevenNull[nullAttr]+=1
        if nullNum == 8:
            if nullAttr not in eightNull.keys():
                eightNull[nullAttr] = 1
            else:
                eightNull[nullAttr]+=1

# print("********two********")
# for elem in twoNull.keys():
#     print(elem+"\n")
# print("********three********")
# for elem in threeNull.keys():
#     print(elem+"\n")
# print("********four********")
# for elem in fourNull.keys():
#     print(elem+'\n')
# print("********five********")
# for elem in fiveNull.keys():
#     print(elem+'\n')
# print("********six********")
# for elem in sixNull.keys():
#     print(elem+'\n')
# print("********seven********")
# for elem in sevenNull.keys():
#     print(elem+'\n')
# print("********eight********")
# for elem in eightNull.keys():
#     print(elem+'\n')

#get the training data:
readerTraining = csv.reader(file('/Users/jason/Desktop/modeling/data/TrainingData.csv', 'rb'))
data_training_raw = []
for line in readerTraining:
    if readerTraining.line_num == 1:
        continue
    else:
        data_training_raw.append(line)
#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#construct NN for TWO NULL:
ds1 = SupervisedDataSet(8, 7)

magic1 = [9,14,16,17,18,19,20]



for tuple in data_training_raw:
    tuple_data = []
    output_tmp1 = []
    for i in range(6, 21):
        if i == magic1[0] or i == magic1[1] or i == magic1[2] or i == magic1[3] or i == magic1[4] or i == magic1[5] or i == magic1[6]:
            output_tmp1.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    ds1.addSample(tuple_data, output_tmp1)

net_1 = buildNetwork(8, 10, 7, bias=True)
trainer_1 = BackpropTrainer(net_1, ds1,learningrate=0.01)
error_1 = trainer_1.trainEpochs(300)


iterOut = -1
for line in data_fit:
    iterOut += 1
    input_1_example = []
    output_1_example = []
    nullAttr = []
    nullNum = 0
    #get the null num:
    iterIn = 0
    for value in line:
        if value == 'NULL' or value == 'PrivacySuppressed':
            nullAttr.append(iterIn)
            nullNum+=1
        iterIn+=1

    if nullNum == 7:
        if nullAttr[0] == magic1[0] and nullAttr[1] == magic1[1] and nullAttr[2] == magic1[2] and nullAttr[3] == magic1[3] and nullAttr[4] == magic1[4] and nullAttr[5] == magic1[5] and nullAttr[6] == magic1[6]:
            for i in range(6,21):
                if i == magic1[0] or i == magic1[1] or i == magic1[2] or i == magic1[3] or i == magic1[4] or i == magic1[5] or i == magic1[6]:
                    continue
                else:
                    input_1_example.append(float(line[i]))
            output_1_example = net_1.activate(input_1_example)
            data_fit[iterOut][magic1[0]] = float(output_1_example[0])
            data_fit[iterOut][magic1[1]] = float(output_1_example[1])
            data_fit[iterOut][magic1[2]] = float(output_1_example[2])
            data_fit[iterOut][magic1[3]] = float(output_1_example[3])
            data_fit[iterOut][magic1[4]] = float(output_1_example[4])
            data_fit[iterOut][magic1[5]] = float(output_1_example[5])
            data_fit[iterOut][magic1[6]] = float(output_1_example[6])

writer = csv.writer(file('/Users/jason/Desktop/modeling/data/fillNull7.csv', 'wb'))
writer.writerow(attributes)
for school in data_fit:
    writer.writerow(school)